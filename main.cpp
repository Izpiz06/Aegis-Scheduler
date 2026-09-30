#include "src/Job/job.h"
#include "src/Job/job_state.h"
#include <iostream>
#include <vector>

void print_job_info(const Job& job) {
    std::cout << "[Job " << job.get_id() << "] "
              << "Owner: " << job.get_owner() << " | "
              << "State: " << to_string(job.get_state()) << " | "
              << "Exec: " << job.get_executable() << " | "
              << "CPUs: " << job.get_requested_cpus() << " | "
              << "Memory: " << job.get_requested_memory() << "MB\n";
}

int main() {
    std::cout << "===========================================\n";
    std::cout << "  Aegis Scheduler - Job Lifecycle Demo     \n";
    std::cout << "===========================================\n\n";

    // Scenario 1: Standard successful job lifecycle (HTCondor: Submit -> Match/Execute -> Exit 0)
    std::cout << "-- Scenario 1: Successful Job Lifecycle --\n";
    Job job1(1, "izaaan", "/bin/sleep", {"10"}, 2, 1024, 10);
    print_job_info(job1);

    std::cout << "Action: Dispatching job to execution agent...\n";
    job1.mark_running();
    print_job_info(job1);

    std::cout << "Action: Job process exited cleanly with code 0...\n";
    job1.mark_completed();
    print_job_info(job1);

    std::cout << "Action: Attempting invalid transition (RUNNING on COMPLETED job)...\n";
    bool invalid_attempt = job1.mark_running();
    std::cout << "Transition accepted: " << (invalid_attempt ? "YES" : "NO (Rejected: Terminal State)") << "\n\n";

    // Scenario 2: Administrative hold, release, and execution failure
    std::cout << "-- Scenario 2: Hold, Release, and Failure --\n";
    Job job2(2, "alice", "/usr/bin/compute_sim", {"--grid", "256"}, 8, 4096, 20);
    print_job_info(job2);

    std::cout << "Action: Putting job on administrative hold (e.g., policy check)...\n";
    job2.hold();
    print_job_info(job2);

    std::cout << "Action: Releasing job back to queue...\n";
    job2.release();
    print_job_info(job2);

    std::cout << "Action: Dispatching job...\n";
    job2.mark_running();
    print_job_info(job2);

    std::cout << "Action: Execution crashed / non-zero exit...\n";
    job2.mark_failed();
    print_job_info(job2);
    std::cout << "\n";

    // Scenario 3: User cancellation while queued
    std::cout << "-- Scenario 3: Job Cancellation in Queue --\n";
    Job job3(3, "bob", "/bin/render", {"scene.blend"}, 4, 2048, 5);
    print_job_info(job3);

    std::cout << "Action: User requested job removal (condor_rm / scancel)...\n";
    job3.cancel();
    print_job_info(job3);

    return 0;
}