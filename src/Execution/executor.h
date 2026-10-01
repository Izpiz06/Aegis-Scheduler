#pragma once

#include "job.h"
#include "node.h"
#include "scheduler.h"
#include <string>
#include <memory>

/**
 * @brief Represents the outcome of an execution attempt.
 */
struct ExecutionResult {
    bool success;
    int exit_code;
    std::string message;
};

/**
 * @brief Executes scheduled jobs as OS processes and manages lifecycle completion.
 * 
 * Modeled after local task launcher agents (Slurm slurmd / HTCondor condor_starter):
 * - Spawns workload using POSIX fork/execvp.
 * - Monitors child process termination via waitpid.
 * - Transitions job state to COMPLETED on zero exit, or FAILED on error/non-zero exit.
 * - Reclaims allocated node resources upon completion.
 */
class Executor {
public:
    Executor() = default;

    /**
     * @brief Executes an allocated job on its assigned node synchronously.
     */
    ExecutionResult execute(const Allocation& allocation);

    /**
     * @brief Direct execution helper for a job and assigned node.
     */
    ExecutionResult execute(std::shared_ptr<Job> job, std::shared_ptr<Node> node);
};
