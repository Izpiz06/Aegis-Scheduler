#pragma once

#include <string>

/**
 * @brief Represents compute resource capacity and tracking.
 * 
 * Modeled after consumable resource accounting in HPC workload managers
 * (Slurm consumable TRES and HTCondor slot resource attributes).
 * 
 * Tracks total configured capacity and currently available capacity
 * for CPU cores and memory (in MB). Enforces strict invariant validation
 * against over-allocation and invalid releases.
 */
class Resource {
private:
    int total_cpus_;
    int available_cpus_;
    int total_memory_;      // in MB
    int available_memory_;  // in MB

public:
    Resource(int total_cpus, int total_memory);

    // Capacity & Availability Getters
    int get_total_cpus() const;
    int get_available_cpus() const;
    int get_allocated_cpus() const;

    int get_total_memory() const;
    int get_available_memory() const;
    int get_allocated_memory() const;

    // Allocation logic
    bool can_allocate(int cpus, int memory) const;
    bool allocate(int cpus, int memory);
    bool release(int cpus, int memory);

    std::string to_string() const;
};
