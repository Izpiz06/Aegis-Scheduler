# Aegis Execution

## 1. Purpose

Scheduling decides **when and where** work should run.

Execution is responsible for actually launching the operating system process, tracking its termination status, transitioning the job's lifecycle state, and returning allocated resources to the compute node.

---

## 2. Conceptual Flow

```text
                  Scheduler
                      │
                 Allocation (Job, Node)
                      │
                      ▼
                   Executor
                      │
                  fork() & execvp()
                      │
                      ▼
                  OS Process
                      │
                  waitpid()
                      │
             ┌────────┴────────┐
             ▼                 ▼
          Exit 0           Exit != 0 / Signal
             │                 │
             ▼                 ▼
      Job: COMPLETED      Job: FAILED
             │                 │
             └────────┬────────┘
                      │
            Reclaim Node Resources
```

---

## 3. V0 Execution Engine (`Executor`)

The `Executor` handles process execution locally using standard POSIX systems calls:

1. **Argument Vector Assembly**: Builds standard `char* const argv[]` from the job's executable and argument list.
2. **Process Spawning**: Calls `fork()`. The child process executes `execvp()`, falling back to `_exit(127)` on execution failure.
3. **Status Monitoring**: The parent process waits for process completion via `waitpid()`.
4. **Lifecycle State Transition**:
   * Clean exit (`exit_code == 0`) transitions the job to `JobState::COMPLETED`.
   * Non-zero exit code or signal termination transitions the job to `JobState::FAILED`.
5. **Resource Reclamation**: Automatically releases allocated CPUs and memory back to the node (`node->release(*job)`), ensuring resources are not leaked regardless of execution success or failure.
