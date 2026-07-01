use crate::job::JobStatus;
use crate::queue::QueueManager;
use crate::resources::ResourceManager;
use tokio::process::Command;
use tokio::time::{sleep, Duration};

#[derive(Clone)]
pub struct ExecutorEngine {
    queue: QueueManager,
    resources: ResourceManager,
}

impl ExecutorEngine {
    pub fn new(queue: QueueManager, resources: ResourceManager) -> Self {
        Self { queue, resources }
    }

    /// Starts the infinite background scheduling loop
    pub async fn start(self) {
        println!("Executor Engine listening for workloads...");

        loop {
            // 1. Check if there is a job waiting at the front of the queue
            if let Some(front_job) = self.queue.peek() {

                // 2. Check if we have enough hardware capacity
                if self.resources.has_capacity(front_job.required_cores, front_job.required_memory_mb) {

                    // 3. Dequeue and Allocate!
                    let mut active_job = self.queue.dequeue().unwrap();
                    let _ = self.resources.allocate(active_job.required_cores, active_job.required_memory_mb);
                    active_job.status = JobStatus::Running;

                    println!("Launching Job ID: {} (Command: {})", active_job.id, active_job.command);
                    self.resources.print_status();

                    // 4. Clone the resources reference so the background task can use it later
                    let resources_ref = self.resources.clone();

                    // 5. Spawn an async OS process in the background.
                    // This lets the loop immediately continue to check the queue for the NEXT job!
                    tokio::spawn(async move {
                        let process = Command::new(&active_job.command)
                            .args(&active_job.args)
                            .output() // This awaits the actual OS command finishing
                            .await;

                        match process {
                            Ok(output) => {
                                println!("✅ Job {} Completed! Exit Code: {:?}", active_job.id, output.status.code());
                            }
                            Err(e) => {
                                println!("❌ Job {} Failed to execute: {}", active_job.id, e);
                            }
                        }

                        // 6. Release resources back to the cluster when the OS command finishes
                        resources_ref.release(active_job.required_cores, active_job.required_memory_mb);
                        println!("♻Resources freed for Job {}.", active_job.id);
                    });
                }
            }

            // Sleep for 500ms to prevent the loop from maxing out your CPU
            sleep(Duration::from_millis(500)).await;
        }
    }
}