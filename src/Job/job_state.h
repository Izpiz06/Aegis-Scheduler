#pragma once

#include <string>

/**
 * @brief Represents the lifecycle states of an Aegis job.
 * 
 * Modeled after HTCondor JobStatus codes (ClassAd attribute JobStatus)
 * and Slurm job state codes:
 * - IDLE: Job is waiting in queue to be scheduled (HTCondor: IDLE, Slurm: PENDING).
 * - RUNNING: Job is actively executing on allocated resources (HTCondor: RUNNING, Slurm: RUNNING).
 * - COMPLETED: Job finished execution successfully with exit code 0 (HTCondor: COMPLETED, Slurm: COMPLETED).
 * - FAILED: Job terminated with non-zero exit code or runtime failure (HTCondor: HELD/COMPLETED(failed), Slurm: FAILED).
 * - HELD: Job is retained in queue but ineligible for scheduling until released (HTCondor: HELD, Slurm: HELD).
 * - CANCELED: Job was explicitly aborted by user/admin (HTCondor: REMOVED, Slurm: CANCELLED).
 */
enum class JobState {
    IDLE,
    RUNNING,
    COMPLETED,
    FAILED,
    HELD,
    CANCELED
};

/**
 * @brief Converts a JobState enum value to its canonical string representation.
 */
std::string to_string(JobState state);

/**
 * @brief Checks if a given state is terminal (no further transitions permitted).
 */
bool is_terminal_state(JobState state);

/**
 * @brief Validates whether a state transition from `from` to `to` is legally permitted.
 */
bool is_valid_transition(JobState from, JobState to);
