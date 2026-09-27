//
// Created by izpiz on 9/28/26.
//
#include "src/Job/job.h"
#include <iostream>
#include <vector>

int main() {
    Job job(
        1,
        "izaaan",
        "/bin/sleep",
        {"10"},
        2,
        1024,
        10
    );

    std::cout << "Job ID: " << job.get_id() << '\n';
    std::cout << "Owner: " << job.get_owner() << '\n';
    std::cout << "Executable: " << job.get_executable() << '\n';
    std::cout << "CPUs: " << job.get_requested_cpus() << '\n';
    std::cout << "Memory: " << job.get_requested_memory() << " MB\n";
    std::cout << "Priority: " << job.get_priority() << '\n';
}