#pragma once

#include "job.h"
#include <vector>
#include <memory>

/**
 * @brief Holds submitted jobs waiting for scheduler evaluation.
 * 
 * Implements a priority-ordered job queue (Slurm pending queue / HTCondor Schedd queue).
 * Jobs with higher priority are scheduled ahead of lower priority jobs.
 * For jobs with equal priority, submission order (FIFO) is preserved.
 */
class JobQueue {
private:
    std::vector<std::shared_ptr<Job>> jobs_;

public:
    JobQueue() = default;

    // Queue Operations
    void submit(std::shared_ptr<Job> job);
    std::shared_ptr<Job> pop();
    std::shared_ptr<Job> peek() const;
    bool remove(int job_id);

    // Inspection
    bool empty() const;
    size_t size() const;
    const std::vector<std::shared_ptr<Job>>& get_jobs() const;
};
