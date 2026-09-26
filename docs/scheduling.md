# Aegis Scheduling

## 1. Purpose

The scheduler answers:

> Given waiting jobs and available resources, which job should run, and where?

---

# 2. Basic Scheduling Loop

The conceptual loop is:

```text
          ┌──────────────────┐
          │  Waiting Jobs    │
          └────────┬─────────┘
                   │
                   ▼
          ┌──────────────────┐
          │ Scheduling Policy│
          └────────┬─────────┘
                   │
                   ▼
          ┌──────────────────┐
          │ Resource Check   │
          └────────┬─────────┘
                   │
             Can it run?
              /       \
            YES        NO
             │          │
             ▼          ▼
        Allocate      Remain
        Resources     Pending
             │
             ▼
          Execute
```

---

# 3. Scheduling Policy

The policy determines how waiting jobs are ordered.

Possible policies include:

```text
FIFO
Priority
Shortest Job First
Fair Share
Backfilling
```

Production schedulers can have substantially more sophisticated policies. Slurm, for example, considers priority and resource availability during scheduling and may use backfill scheduling.

V0 does not need to reproduce production scheduling complexity.

---

# 4. Resource Selection

After deciding which job to consider, the scheduler must determine whether its requested resources can be allocated.

Conceptually:

```text
Job Request
     │
     ▼
Available Resources
     │
     ├── insufficient → remain pending
     │
     └── sufficient → allocate
```

In Slurm, resource selection is an explicit subsystem responsible for selecting and allocating resources.

---

# 5. Queue

A queue is conceptually a collection of jobs waiting for scheduling.

Do not assume that a queue must automatically imply a complicated database or distributed system.

For V0:

```text
Submit
  ↓
Queue
  ↓
Scheduler
```

is sufficient as a conceptual model.

---

# 6. Priority

Priority is a separate concept from resource availability.

A job can have high priority but still be unable to run if its requested resources are unavailable.

HTCondor similarly evaluates job requirements against machine availability and ranking preferences.

---

# 7. Future Scheduling

As Aegis grows, scheduling may incorporate:

```text
Multiple nodes
CPU topology
GPU topology
Network topology
Job dependencies
Reservations
Preemption
Fairness
Backfilling
Historical workload information
```

These should be introduced incrementally.

---

# 8. V0 Goal

The first scheduler should answer only the fundamental questions:

```text
What jobs are waiting?
Which job should be considered?
Does it fit?
Which resources are available?
Can it start?
```

Everything beyond this is an extension.
