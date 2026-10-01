#include "job.h"
#include "job_state.h"
#include "resource.h"
#include "node.h"
#include "job_queue.h"
#include "scheduler.h"
#include "executor.h"

#include <iostream>
#include <memory>
#include <vector>

void print_cluster_state(const Scheduler& scheduler, const JobQueue& queue) {
    std::cout << "\n--- Cluster Status ---\n";
    std::cout << "Nodes:\n";
    for (const auto& node : scheduler.get_nodes()) {
        std::cout << "  " << node->to_string_summary() << "\n";
    }
    std::cout << "Pending Queue (" << queue.size() << " jobs):\n";
    for (const auto& job : queue.get_jobs()) {
        std::cout << "  [Job " << job->get_id() << "] "
                  << "Owner: " << job->get_owner() << " | "
                  << "Priority: " << job->get_priority() << " | "
                  << "CPUs: " << job->get_requested_cpus() << " | "
                  << "Memory: " << job->get_requested_memory() << "MB | "
                  << "Exec: " << job->get_executable() << " | "
                  << "State: " << to_string(job->get_state()) << "\n";
    }
    std::cout << "----------------------\n\n";
}

int main() {
    std::cout << "=========================================================\n";
    std::cout << "        Aegis Scheduler V0 End-to-End Demonstration       \n";
    std::cout << "=========================================================\n";

    // 1. Initialize Compute Nodes (Phases 1 & 2: Resource & Node Models)
    auto node1 = std::make_shared<Node>(1, "compute-node-01", 4, 8192); // 4 CPUs, 8GB RAM
    auto node2 = std::make_shared<Node>(2, "compute-node-02", 2, 4096); // 2 CPUs, 4GB RAM

    Scheduler scheduler;
    scheduler.add_node(node1);
    scheduler.add_node(node2);

    // 2. Initialize Job Queue and Submit Workloads (Phase 3: Priority Job Queue)
    JobQueue queue;

    // Job 1: Normal priority echo workload
    auto job1 = std::make_shared<Job>(
        1, "izaaan", "/bin/echo", std::vector<std::string>{"[Job 1] Aegis HPC task running successfully"}, 2, 2048, 10
    );

    // Job 2: High priority sleep workload
    auto job2 = std::make_shared<Job>(
        2, "alice", "/bin/sleep", std::vector<std::string>{"1"}, 2, 4096, 50
    );

    // Job 3: Low priority failing workload (non-zero exit code)
    auto job3 = std::make_shared<Job>(
        3, "bob", "/bin/false", std::vector<std::string>{}, 1, 1024, 5
    );

    // Job 4: Large workload exceeding single node capacity (requires 8 CPUs)
    auto job4 = std::make_shared<Job>(
        4, "carol", "/bin/echo", std::vector<std::string>{"[Job 4] Large task"}, 8, 16384, 100
    );

    std::cout << "Submitting jobs to queue...\n";
    queue.submit(job1);
    queue.submit(job2);
    queue.submit(job3);
    queue.submit(job4);

    print_cluster_state(scheduler, queue);

    // 3. Scheduling Cycle (Phase 4: First-Fit Scheduler)
    std::cout << "Running Scheduler Cycle...\n";
    auto allocations = scheduler.schedule_cycle(queue);
    std::cout << "Allocations made: " << allocations.size() << "\n";

    for (const auto& alloc : allocations) {
        std::cout << "  -> Matched [Job " << alloc.job->get_id() << "] "
                  << "with [" << alloc.node->get_name() << "]\n";
    }

    print_cluster_state(scheduler, queue);

    // 4. Execution Engine (Phase 5: Process Execution and Resource Reclamation)
    std::cout << "Executing Scheduled Workloads...\n";
    Executor executor;

    for (const auto& alloc : allocations) {
        std::cout << "\nExecuting [Job " << alloc.job->get_id() << "] ("
                  << alloc.job->get_executable() << ") on "
                  << alloc.node->get_name() << "...\n";

        ExecutionResult result = executor.execute(alloc);

        std::cout << "  Execution Result: "
                  << (result.success ? "SUCCESS" : "FAILED")
                  << " (Exit Code: " << result.exit_code << ")\n"
                  << "  Status Message: " << result.message << "\n"
                  << "  Job Final State: " << to_string(alloc.job->get_state()) << "\n";
    }

    std::cout << "\nPost-Execution Cluster State (verifying resource reclamation):\n";
    print_cluster_state(scheduler, queue);

    return 0;
}