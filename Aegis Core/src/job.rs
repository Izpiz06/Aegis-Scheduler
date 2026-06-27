use serde::{Deserialize, Serialize};
use std::time::SystemTime;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub enum JobStatus{
    Pending,
    Running,
    Completed,
    Failed,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Job{
    pub id: String,
    pub user_id: String,
    pub command: String,
    pub args: Vec<String>,

    pub required_cores: usize,
    pub required_memory_mb: u64,

    pub status: JobStatus,
    pub exit_code: Option<i32>,

    pub submitted_at: SystemTime,
    pub started_at: Option<SystemTime>,
    pub ended_at: Option<SystemTime>,
}

impl Job{
    pub fn new(id: String, user_id: String, command: String, args: Vec<String>, cores: usize, mem: u64) -> Self {
        Self{
            id,
            user_id,
            command,
            args,
            required_cores: cores,
            required_memory_mb: mem,
            status: JobStatus::Pending,
            exit_code: None,
            submitted_at: SystemTime::now(),
            started_at: None,
            ended_at: None
        }
    }
}