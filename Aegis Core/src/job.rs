use serde::{Deserialize, Serialize};
use std::time::SystemTime;

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub enum JobStatus {
    Pending,
    Running,
    Completed,
    Failed,
}

/// Groups hardware requirements together
#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ResourceRequest {
    pub cpu_cores: usize,
    pub memory_mb: u64,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct Job {
    pub id: String,
    pub user_id: String,
    pub command: String,
    pub args: Vec<String>,
    pub resources: ResourceRequest,

    pub status: JobStatus,
    pub exit_code: Option<i32>,
    pub submitted_at: SystemTime,
    pub started_at: Option<SystemTime>,
    pub ended_at: Option<SystemTime>,
}

impl Job {
    pub fn new(id: String, user_id: String, command: String, args: Vec<String>, cores: usize, mem: u64) -> Self {
        Self {
            id,
            user_id,
            command,
            args,
            resources: ResourceRequest { cpu_cores: cores, memory_mb: mem },
            status: JobStatus::Pending,
            exit_code: None,
            submitted_at: SystemTime::now(),
            started_at: None,
            ended_at: None,
        }
    }

    /// Safe state transitions
    pub fn start(&mut self) {
        self.status = JobStatus::Running;
        self.started_at = Some(SystemTime::now());
    }

    pub fn complete(&mut self, exit_code: i32) {
        self.status = if exit_code == 0 { JobStatus::Completed } else { JobStatus::Failed };
        self.exit_code = Some(exit_code);
        self.ended_at = Some(SystemTime::now());
    }
}