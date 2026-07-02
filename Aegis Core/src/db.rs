use sqlx::{postgres::PgPoolOptions, PgPool};
use std::env;
use dotenvy::dotenv;
use crate::job::Job; // <-- 1. Import the Job struct

pub async fn init_db() -> PgPool {
    dotenv().ok();
    let database_url = env::var("DATABASE_URL").expect("DATABASE_URL must be set in .env file");

    println!("Connecting to DB...");

    let pool = PgPoolOptions::new()
        .max_connections(5)
        .connect(&database_url)
        .await
        .expect("Error connecting to Postgres; aborting. Check your connections and server status!");

    sqlx::query(
        r#"
        CREATE TABLE IF NOT EXISTS jobs (
            id VARCHAR(255) PRIMARY KEY,
            user_id VARCHAR(255) NOT NULL,
            command TEXT NOT NULL,
            status VARCHAR(50) NOT NULL,
            required_cores INT NOT NULL,
            required_memory_mb BIGINT NOT NULL
        );
        "#
    )
        .execute(&pool)
        .await
        .expect("❌ Failed to verify the jobs table schema.");

    println!("🗄Database connected and schema verified.");

    pool
}

/// 2. The new function to insert a job using the updated ResourceRequest struct
pub async fn insert_job(pool: &PgPool, job: &Job) -> Result<(), sqlx::Error> {
    sqlx::query(
        r#"
        INSERT INTO jobs (id, user_id, command, status, required_cores, required_memory_mb)
        VALUES ($1, $2, $3, $4, $5, $6)
        "#
    )
        .bind(&job.id)
        .bind(&job.user_id)
        .bind(&job.command)
        .bind(format!("{:?}", job.status))
        .bind(job.resources.cpu_cores as i32) // <-- Notice the nested struct access
        .bind(job.resources.memory_mb as i64) // <-- Notice the nested struct access
        .execute(pool)
        .await?;

    Ok(())
}