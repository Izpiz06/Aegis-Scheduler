#pragma once

#include <string>

/**
 * @brief Represents the operational state of a compute node.
 * 
 * Modeled after HPC node states (Slurm node states and HTCondor machine states):
 * - READY: Node is healthy and accepting new job allocations.
 * - DRAINING: Node is completing existing jobs but rejecting new allocations (maintenance mode).
 * - DOWN: Node is unhealthy or offline; cannot accept allocations.
 */
enum class NodeState {
    READY,
    DRAINING,
    DOWN
};

std::string to_string(NodeState state);
