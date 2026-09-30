#include "job_state.h"

std::string to_string(JobState state) {
    switch (state) {
        case JobState::IDLE:      return "IDLE";
        case JobState::RUNNING:   return "RUNNING";
        case JobState::COMPLETED: return "COMPLETED";
        case JobState::FAILED:    return "FAILED";
        case JobState::HELD:      return "HELD";
        case JobState::CANCELED:  return "CANCELED";
    }
    return "UNKNOWN";
}

bool is_terminal_state(JobState state) {
    switch (state) {
        case JobState::COMPLETED:
        case JobState::FAILED:
        case JobState::CANCELED:
            return true;
        case JobState::IDLE:
        case JobState::RUNNING:
        case JobState::HELD:
            return false;
    }
    return false;
}

bool is_valid_transition(JobState from, JobState to) {
    if (from == to) {
        return true; // No-op transition
    }

    if (is_terminal_state(from)) {
        return false; // Terminal states cannot transition to any other state
    }

    switch (from) {
        case JobState::IDLE:
            // An idle job can be dispatched (RUNNING), placed on hold (HELD), or canceled (CANCELED)
            return to == JobState::RUNNING ||
                   to == JobState::HELD ||
                   to == JobState::CANCELED;

        case JobState::RUNNING:
            // A running job can finish normally (COMPLETED), fail (FAILED), be put on hold (HELD), or canceled (CANCELED)
            return to == JobState::COMPLETED ||
                   to == JobState::FAILED ||
                   to == JobState::HELD ||
                   to == JobState::CANCELED;

        case JobState::HELD:
            // A held job can be released back to the queue (IDLE) or canceled (CANCELED)
            return to == JobState::IDLE ||
                   to == JobState::CANCELED;

        default:
            return false;
    }
}
