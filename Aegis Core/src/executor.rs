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
            if let Some(front_job) = self.queue.peek() {
                // 1. Try to allocate atomically (Fixes TOCTOU)
                if self.resources.try_allocate(front_job.resources.cpu_cores, front_job.resources.memory_mb).is_ok() {

                    // 2. We got the resources! Safely dequeue and start the job.
                    let mut active_job = self.queue.dequeue().unwrap();
                    active_job.start(); // <-- Using our new safe state transition!

                    println!("🚀 Launching Job ID: {} (Command: {})", active_job.id, active_job.command);
                    self.resources.print_status();

                    let resources_ref = self.resources.clone();

                    tokio::spawn(async move {
                        let process = Command::new(&active_job.command)
                            .args(&active_job.args)
                            .output()
                            .await;

                        match process {
                            Ok(output) => {
                                let code = output.status.code().unwrap_or(1);
                                active_job.complete(code); // <-- Safe completion tracking
                                println!("✅ Job {} {:?}! Exit Code: {}", active_job.id, active_job.status, code);
                            }
                            Err(e) => {
                                active_job.complete(1);
                                println!("❌ Job {} Failed to execute: {}", active_job.id, e);
                            }
                        }

                        // Release resources back to the pool
                        resources_ref.release(active_job.resources.cpu_cores, active_job.resources.memory_mb);
                        println!("Resources freed for Job {}.", active_job.id);
                    });
                }
            }

            sleep(Duration::from_millis(500)).await;
        }
    }
}