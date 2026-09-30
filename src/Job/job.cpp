#include "job.h"
#include <utility>

Job::Job(int id,
         std::string owner,
         std::string executable,
         std::vector<std::string> arguments,
         int requested_cpus,
         int requested_memory,
         int priority)
    : id_(id),
      owner_(std::move(owner)),
      executable_(std::move(executable)),
      arguments_(std::move(arguments)),
      requested_cpus_(requested_cpus),
      requested_memory_(requested_memory),
      priority_(priority),
      state_(JobState::IDLE) {}

int Job::get_id() const {
    return id_;
}

const std::string& Job::get_owner() const {
    return owner_;
}

const std::string& Job::get_executable() const {
    return executable_;
}

const std::vector<std::string>& Job::get_arguments() const {
    return arguments_;
}

int Job::get_requested_cpus() const {
    return requested_cpus_;
}

int Job::get_requested_memory() const {
    return requested_memory_;
}

int Job::get_priority() const {
    return priority_;
}

JobState Job::get_state() const {
    return state_;
}

bool Job::transition_to(JobState new_state) {
    if (!is_valid_transition(state_, new_state)) {
        return false;
    }
    state_ = new_state;
    return true;
}

bool Job::mark_running() {
    return transition_to(JobState::RUNNING);
}

bool Job::mark_completed() {
    return transition_to(JobState::COMPLETED);
}

bool Job::mark_failed() {
    return transition_to(JobState::FAILED);
}

bool Job::hold() {
    return transition_to(JobState::HELD);
}

bool Job::release() {
    return transition_to(JobState::IDLE);
}

bool Job::cancel() {
    return transition_to(JobState::CANCELED);
}
