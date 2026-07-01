use std::sync::{Arc, Mutex};

#[derive(Debug)]
struct ResourseState{
    pub total_cores: usize,
    pub available_cores: usize,
    pub total_memory_mb:u64,
    pub available_memory_mb:u64,
}

#[derive(Debug, Clone)]
pub struct ResourceManager{
    inner:Arc<Mutex<ResourseState>>,
}

impl ResourceManager{
    pub fn new(cores:usize, memory:u64)->Self{
        Self{
            inner:Arc::new(Mutex::new(ResourseState{
                total_cores: cores,
                available_cores: cores, // Starts at 100% free
                total_memory_mb: memory,
                available_memory_mb: memory,
            }))
        }
    }
    pub fn has_capacity(&self,required_cores:usize, required_memory:u64)->bool{
        let state=self.inner.lock().unwrap();
        state.available_cores >= required_cores && state.available_memory_mb >= required_memory
    }
    pub fn allocate(&self, required_cores: usize, required_memory: u64) -> Result<(), String> {
        let mut state = self.inner.lock().unwrap();

        if state.available_cores >= required_cores && state.available_memory_mb >= required_memory {
            state.available_cores -= required_cores;
            state.available_memory_mb -= required_memory;
            Ok(())
        } else {
            Err("Insufficient resources to allocate.".to_string())
        }
    }
    pub fn release(&self, released_cores: usize, released_memory: u64) {
        let mut state = self.inner.lock().unwrap();
        state.available_cores += released_cores;
        state.available_memory_mb += released_memory;

        // Safety check to prevent overflow bugs
        if state.available_cores > state.total_cores {
            state.available_cores = state.total_cores;
        }
        if state.available_memory_mb > state.total_memory_mb {
            state.available_memory_mb = state.total_memory_mb;
        }
    }
    pub fn print_status(&self) {
        let state = self.inner.lock().unwrap();
        println!(
            "💻 Hardware Capacity: CPU [{} / {}] | RAM [{} MB / {} MB]",
            state.available_cores, state.total_cores, state.available_memory_mb, state.total_memory_mb
        );
    }
}