//
// Created by izpiz on 9/28/26.
//
#include "job.hpp"

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
      priority_(priority) {}

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
