#include "scheduler.h"

void Scheduler::add_node(std::shared_ptr<Node> node) {
    if (node) {
        nodes_.push_back(std::move(node));
    }
}

const std::vector<std::shared_ptr<Node>>& Scheduler::get_nodes() const {
    return nodes_;
}

std::vector<Allocation> Scheduler::schedule_cycle(JobQueue& queue) {
    std::vector<Allocation> allocations;
    std::vector<int> scheduled_job_ids;

    // Iterate through queued jobs in priority order
    for (const auto& job : queue.get_jobs()) {
        if (!job || job->get_state() != JobState::IDLE) {
            continue;
        }

        // First-fit search across registered compute nodes
        for (auto& node : nodes_) {
            if (node && node->can_fit(*job)) {
                if (node->allocate(*job)) {
                    job->mark_running();
                    allocations.push_back(Allocation{job, node});
                    scheduled_job_ids.push_back(job->get_id());
                    break; // Move to next job once placed
                }
            }
        }
    }

    // Remove placed jobs from pending queue
    for (int job_id : scheduled_job_ids) {
        queue.remove(job_id);
    }

    return allocations;
}
