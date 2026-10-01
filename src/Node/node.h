#pragma once

#include "node_state.h"
#include "resource.h"
#include "job.h"
#include <string>

/**
 * @brief Represents a compute node capable of executing workloads.
 * 
 * Owns resource capacity and state. Verifies whether workloads fit
 * and performs allocation/release accounting.
 * 
 * Invariant: The Node does NOT make scheduling or job selection decisions.
 * It strictly acts as a resource container and execution target.
 */
class Node {
private:
    int id_;
    std::string name_;
    NodeState state_;
    Resource resource_;

public:
    Node(int id, std::string name, int total_cpus, int total_memory);

    // Identity & State Getters/Setters
    int get_id() const;
    const std::string& get_name() const;
    NodeState get_state() const;
    void set_state(NodeState new_state);

    // Resource Accessors
    const Resource& get_resource() const;
    Resource& get_resource();

    // Capacity & Allocation Checks
    bool can_fit(const Job& job) const;
    bool can_fit(int cpus, int memory) const;

    bool allocate(const Job& job);
    bool allocate(int cpus, int memory);

    bool release(const Job& job);
    bool release(int cpus, int memory);

    std::string to_string_summary() const;
};
