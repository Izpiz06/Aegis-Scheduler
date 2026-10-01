#include "job_queue.h"
#include <algorithm>

void JobQueue::submit(std::shared_ptr<Job> job) {
    if (!job) {
        return;
    }

    // Maintain descending priority order with stable FIFO for identical priorities.
    // Insert before the first element with lower priority.
    auto insert_pos = std::find_if(
        jobs_.begin(),
        jobs_.end(),
        [&job](const std::shared_ptr<Job>& queued_job) {
            return queued_job->get_priority() < job->get_priority();
        }
    );

    jobs_.insert(insert_pos, std::move(job));
}

std::shared_ptr<Job> JobQueue::pop() {
    if (jobs_.empty()) {
        return nullptr;
    }
    auto job = jobs_.front();
    jobs_.erase(jobs_.begin());
    return job;
}

std::shared_ptr<Job> JobQueue::peek() const {
    if (jobs_.empty()) {
        return nullptr;
    }
    return jobs_.front();
}

bool JobQueue::remove(int job_id) {
    auto it = std::find_if(
        jobs_.begin(),
        jobs_.end(),
        [job_id](const std::shared_ptr<Job>& job) {
            return job->get_id() == job_id;
        }
    );

    if (it != jobs_.end()) {
        jobs_.erase(it);
        return true;
    }
    return false;
}

bool JobQueue::empty() const {
    return jobs_.empty();
}

size_t JobQueue::size() const {
    return jobs_.size();
}

const std::vector<std::shared_ptr<Job>>& JobQueue::get_jobs() const {
    return jobs_;
}
