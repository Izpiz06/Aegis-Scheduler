#include "resource.h"
#include <sstream>
#include <algorithm>

Resource::Resource(int total_cpus, int total_memory)
    : total_cpus_(std::max(0, total_cpus)),
      available_cpus_(std::max(0, total_cpus)),
      total_memory_(std::max(0, total_memory)),
      available_memory_(std::max(0, total_memory)) {}

int Resource::get_total_cpus() const {
    return total_cpus_;
}

int Resource::get_available_cpus() const {
    return available_cpus_;
}

int Resource::get_allocated_cpus() const {
    return total_cpus_ - available_cpus_;
}

int Resource::get_total_memory() const {
    return total_memory_;
}

int Resource::get_available_memory() const {
    return available_memory_;
}

int Resource::get_allocated_memory() const {
    return total_memory_ - available_memory_;
}

bool Resource::can_allocate(int cpus, int memory) const {
    if (cpus < 0 || memory < 0) {
        return false;
    }
    return available_cpus_ >= cpus && available_memory_ >= memory;
}

bool Resource::allocate(int cpus, int memory) {
    if (!can_allocate(cpus, memory)) {
        return false;
    }
    available_cpus_ -= cpus;
    available_memory_ -= memory;
    return true;
}

bool Resource::release(int cpus, int memory) {
    if (cpus < 0 || memory < 0) {
        return false;
    }
    // Prevent releasing more than what is currently allocated
    if (available_cpus_ + cpus > total_cpus_ ||
        available_memory_ + memory > total_memory_) {
        return false;
    }
    available_cpus_ += cpus;
    available_memory_ += memory;
    return true;
}

std::string Resource::to_string() const {
    std::ostringstream oss;
    oss << "CPUs: " << get_allocated_cpus() << "/" << total_cpus_
        << " (" << available_cpus_ << " free), "
        << "Memory: " << get_allocated_memory() << "/" << total_memory_ << "MB"
        << " (" << available_memory_ << "MB free)";
    return oss.str();
}
