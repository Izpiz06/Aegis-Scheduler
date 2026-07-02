use std::sync::{Arc, Mutex};
#[derive(Debug)]
struct ResourceState {
    pub total_cores: usize,
    pub available_cores: usize,
    pub total_memory_mb: u64,
    pub available_memory_mb: u64,
}

#[derive(Debug, Clone)]
pub struct ResourceManager {
    inner: Arc<Mutex<ResourceState>>,
}

impl ResourceManager {
    pub fn new(cores: usize, memory: u64) -> Self {
        Self {
            inner: Arc::new(Mutex::new(ResourceState {
                total_cores: cores,
                available_cores: cores,
                total_memory_mb: memory,
                available_memory_mb: memory,
            })),
        }
    }

    /// Atomically checks capacity and allocates in one thread-safe sweep.
    pub fn try_allocate(&self, required_cores: usize, required_memory: u64) -> Result<(), String> {
        let mut state = self.inner.lock().unwrap();

        if state.available_cores >= required_cores && state.available_memory_mb >= required_memory {
            state.available_cores -= required_cores;
            state.available_memory_mb -= required_memory;
            Ok(())
        } else {
            Err("Insufficient resources".to_string())
        }
    }

    pub fn release(&self, released_cores: usize, released_memory: u64) {
        let mut state = self.inner.lock().unwrap();
        state.available_cores = (state.available_cores + released_cores).min(state.total_cores);
        state.available_memory_mb = (state.available_memory_mb + released_memory).min(state.total_memory_mb);
    }

    pub fn print_status(&self) {
        let state = self.inner.lock().unwrap();
        println!(
            "💻 Hardware Capacity: CPU [{} / {}] | RAM [{} MB / {} MB]",
            state.available_cores, state.total_cores, state.available_memory_mb, state.total_memory_mb
        );
    }
}