#pragma once

#include "job.h"
#include "node.h"
#include "job_queue.h"
#include <vector>
#include <memory>

/**
 * @brief Represents a scheduled resource binding between a Job and a Node.
 */
struct Allocation {
    std::shared_ptr<Job> job;
    std::shared_ptr<Node> node;
};

/**
 * @brief Core scheduler responsible for resource matching and job dispatch decisions.
 * 
 * In V0, implements First-Fit scheduling over priority-ordered pending jobs:
 * 1. Iterates through pending jobs in priority order.
 * 2. Scans registered compute nodes for the first node with sufficient capacity.
 * 3. Allocates node resources and transitions the job state to RUNNING.
 * 4. Yields allocations to the execution layer.
 * 
 * Separates scheduling policy/matchmaking from node resource management and job definition.
 */
class Scheduler {
private:
    std::vector<std::shared_ptr<Node>> nodes_;

public:
    Scheduler() = default;

    // Node Registration
    void add_node(std::shared_ptr<Node> node);
    const std::vector<std::shared_ptr<Node>>& get_nodes() const;

    // Scheduling Cycle
    std::vector<Allocation> schedule_cycle(JobQueue& queue);
};
