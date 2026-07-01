mod job;
mod queue;
mod resources;
mod executor;
mod db; // <-- 1. Register the DB module

use job::Job;
use queue::QueueManager;
use resources::ResourceManager;
use executor::ExecutorEngine;
use tokio::time::{sleep, Duration};

#[tokio::main]
async fn main() {
    println!("⚡ Aegis Core Engine [v0.1] booting...");

    // 2. Boot up the Database Pool first!
    let _db_pool = db::init_db().await;

    // Initialize the cluster (4 Cores, ~8GB RAM)
    let job_queue = QueueManager::new();
    let cluster_resources = ResourceManager::new(4, 8192);

    // Initialize and start the Executor Engine in the background
    let executor = ExecutorEngine::new(job_queue.clone(), cluster_resources.clone());
    tokio::spawn(async move {
        executor.start().await;
    });

    sleep(Duration::from_millis(100)).await;

    // Submit mock workloads
    let job1 = Job::new("job_001".to_string(), "izaan".to_string(), "sleep".to_string(), vec!["3".to_string()], 2, 2048);
    job_queue.enqueue(job1);

    let job2 = Job::new("job_002".to_string(), "izaan".to_string(), "sleep".to_string(), vec!["2".to_string()], 2, 2048);
    job_queue.enqueue(job2);

    let job3 = Job::new("job_003".to_string(), "izaan".to_string(), "echo".to_string(), vec!["I finally got resources!".to_string()], 2, 2048);
    job_queue.enqueue(job3);

    // Keep the main program alive to watch the engine work
    sleep(Duration::from_secs(5)).await;
    println!("\n🛑 Shutting down Aegis Core Engine.");
}