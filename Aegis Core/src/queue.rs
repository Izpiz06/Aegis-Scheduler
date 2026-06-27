use crate::job::Job;
use std::collections::VecDeque;
use std::sync::{Arc, Mutex};

#[derive(Debug, Clone)]
pub struct QueueManager{
    inner: Arc<Mutex<VecDeque<Job>>>,
}

impl QueueManager {
    pub fn new() -> Self {
        Self{
            inner: Arc::new(Mutex::new(VecDeque::new())),
        }
    }

    pub fn enqueue(&self, job: Job) {
        let mut queue=self.inner.lock().unwrap();
        queue.push_back(job);
    }

    pub fn len(&self) -> usize{
        let queue=self.inner.lock().unwrap();
        queue.len()
    }
    pub fn peek(&self) -> Option<Job> {
        let queue=self.inner.lock().unwrap();
        queue.front().cloned()
    }
}