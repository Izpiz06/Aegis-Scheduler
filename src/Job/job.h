#pragma once

#include "job_state.h"
#include <string>
#include <vector>

class Job
{
private:
    int id_;
    std::string owner_;

    std::string executable_;
    std::vector<std::string> arguments_;

    int requested_cpus_;
    int requested_memory_;
    int priority_;

    JobState state_;

public:
    Job(int id,
        std::string owner,
        std::string executable,
        std::vector<std::string> arguments,
        int requested_cpus,
        int requested_memory,
        int priority);

    // Getters
    int get_id() const;
    const std::string& get_owner() const;
    const std::string& get_executable() const;
    const std::vector<std::string>& get_arguments() const;

    int get_requested_cpus() const;
    int get_requested_memory() const;
    int get_priority() const;

    JobState get_state() const;

    // Lifecycle state transitions
    bool transition_to(JobState new_state);

    // Semantic transition helpers
    bool mark_running();
    bool mark_completed();
    bool mark_failed();
    bool hold();
    bool release();
    bool cancel();
};