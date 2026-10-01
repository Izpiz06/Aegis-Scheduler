# Aegis Scheduling

## 1. Purpose

The scheduler answers:

> Given waiting jobs and available resources, which job should run, and where?

---

## 2. Job Queue (`JobQueue`)

The `JobQueue` holds submitted jobs waiting for scheduling evaluation:

* **Priority-Aware Ordering**: Workloads with higher priority integer values are placed ahead of lower-priority jobs.
* **Stable FIFO Preservation**: For jobs of equal priority, submission order is strictly preserved.
* **Direct Inspection & Removal**: Supports queue iteration, peek, pop, and removal by job ID (e.g. for cancellation).

---

## 3. V0 Scheduling Loop (`Scheduler`)

The V0 scheduler implements a First-Fit scheduling policy over priority-ordered pending jobs:

```text
               ┌──────────────────┐
               │    JobQueue      │
               └────────┬─────────┘
                        │
                  (Priority Pop)
                        │
                        ▼
               ┌──────────────────┐
               │    Scheduler     │
               └────────┬─────────┘
                        │
               Scan Registered Nodes
                        │
                  Can Node Fit?
                   /         \
                 YES          NO
                  │            │
                  ▼            ▼
             Allocate     Remain in Queue
             Resources    (Next Cycle)
                  │
                  ▼
             Job State -> RUNNING
                  │
                  ▼
             Return Allocation(Job, Node)
```

### Steps in `schedule_cycle()`:
1. Inspect pending jobs in priority order.
2. For each idle job, search registered compute nodes for the first node satisfying `node->can_fit(*job)`.
3. If a suitable node is found:
   * Allocate resources on node (`node->allocate(*job)`).
   * Transition job lifecycle state to `RUNNING` (`job->mark_running()`).
   * Record `Allocation{job, node}`.
   * Remove job from the pending queue.
4. If no node satisfies the request, the job remains in the queue for subsequent scheduling cycles.
