#include "executor.h"
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sstream>
#include <cstring>

ExecutionResult Executor::execute(const Allocation& allocation) {
    return execute(allocation.job, allocation.node);
}

ExecutionResult Executor::execute(std::shared_ptr<Job> job, std::shared_ptr<Node> node) {
    if (!job) {
        return ExecutionResult{false, -1, "Invalid job pointer"};
    }

    // Prepare argument array for execvp
    std::vector<const char*> argv;
    argv.push_back(job->get_executable().c_str());
    for (const auto& arg : job->get_arguments()) {
        argv.push_back(arg.c_str());
    }
    argv.push_back(nullptr);

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failure
        job->mark_failed();
        if (node) {
            node->release(*job);
        }
        return ExecutionResult{false, -1, "Failed to fork child process: " + std::string(strerror(errno))};
    }

    if (pid == 0) {
        // Child process: execute the workload
        execvp(argv[0], const_cast<char* const*>(argv.data()));
        // If execvp returns, it encountered an error (e.g. file not found, permission denied)
        _exit(127);
    }

    // Parent process: monitor child execution
    int status = 0;
    if (waitpid(pid, &status, 0) < 0) {
        job->mark_failed();
        if (node) {
            node->release(*job);
        }
        return ExecutionResult{false, -1, "Failed waiting for child process"};
    }

    int exit_code = -1;
    bool success = false;
    std::ostringstream msg;

    if (WIFEXITED(status)) {
        exit_code = WEXITSTATUS(status);
        if (exit_code == 0) {
            success = true;
            job->mark_completed();
            msg << "Process exited successfully (exit code 0)";
        } else {
            success = false;
            job->mark_failed();
            msg << "Process failed with non-zero exit code: " << exit_code;
        }
    } else if (WIFSIGNALED(status)) {
        int sig = WTERMSIG(status);
        success = false;
        exit_code = 128 + sig;
        job->mark_failed();
        msg << "Process terminated by signal: " << sig;
    } else {
        success = false;
        job->mark_failed();
        msg << "Process terminated abnormally";
    }

    // Invariant: Reclaim allocated resources on the node upon job completion or failure
    if (node) {
        node->release(*job);
    }

    return ExecutionResult{success, exit_code, msg.str()};
}
