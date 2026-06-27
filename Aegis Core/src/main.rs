mod job;
mod queue;
mod resources;
mod executor;

use job::Job;
use queue::QueueManager;

#[tokio::main]
async fn main() {
    println!("⚡ Aegis Core Engine [v0.1] booted successfully.");

    let job_queue = QueueManager::new();

    let mock_job=Job::new(
        "job_001".to_string(),
        "izaan".to_string(),
        "sleep".to_string(),
        vec!["2".to_string()],
        2,
        2048,
    );
    job_queue.enqueue(mock_job);
    println!("Workload enqueued successfully. Current queue depth: {}", job_queue.len());
}