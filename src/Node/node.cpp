#include "node.h"
#include <utility>
#include <sstream>

Node::Node(int id, std::string name, int total_cpus, int total_memory)
    : id_(id),
      name_(std::move(name)),
      state_(NodeState::READY),
      resource_(total_cpus, total_memory) {}

int Node::get_id() const {
    return id_;
}

const std::string& Node::get_name() const {
    return name_;
}

NodeState Node::get_state() const {
    return state_;
}

void Node::set_state(NodeState new_state) {
    state_ = new_state;
}

const Resource& Node::get_resource() const {
    return resource_;
}

Resource& Node::get_resource() {
    return resource_;
}

bool Node::can_fit(const Job& job) const {
    return can_fit(job.get_requested_cpus(), job.get_requested_memory());
}

bool Node::can_fit(int cpus, int memory) const {
    if (state_ != NodeState::READY) {
        return false;
    }
    return resource_.can_allocate(cpus, memory);
}

bool Node::allocate(const Job& job) {
    return allocate(job.get_requested_cpus(), job.get_requested_memory());
}

bool Node::allocate(int cpus, int memory) {
    if (state_ != NodeState::READY) {
        return false;
    }
    return resource_.allocate(cpus, memory);
}

bool Node::release(const Job& job) {
    return release(job.get_requested_cpus(), job.get_requested_memory());
}

bool Node::release(int cpus, int memory) {
    return resource_.release(cpus, memory);
}

std::string Node::to_string_summary() const {
    std::ostringstream oss;
    oss << "[Node " << id_ << ": " << name_ << "] "
        << "State: " << to_string(state_) << " | "
        << resource_.to_string();
    return oss.str();
}
