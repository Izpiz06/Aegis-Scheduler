use sqlx::{postgres::PgPoolOptions, PgPool, };
use std::env;
use dotenvy::dotenv;

pub async fn init_db()->PgPool{
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
