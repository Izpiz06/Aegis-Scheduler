# Aegis Architecture

## 1. Purpose

This document describes the conceptual architecture of Aegis.

It intentionally does not prescribe C++ classes, APIs, directory structures, or implementation details.

---

# 2. Reference Architecture

Aegis can be understood as several cooperating responsibilities:

```text
                    AEGIS
                      │
        ┌─────────────┼─────────────┐
        │             │             │
       Jobs       Scheduler      Resources
        │             │             │
        └─────────────┼─────────────┘
                      │
                  Execution
                      │
                   Nodes
                      │
                 Monitoring
```

A production HPC scheduler similarly separates central scheduling/resource management from compute-node execution. Slurm, for example, has a central `slurmctld` daemon responsible for accepting work and allocating resources, while `slurmd` runs on compute nodes and launches/manages tasks.

---

# 3. Major Concepts

## Job

Represents work requested by a user.

A job contains information describing:

* What should execute
* Required resources
* Scheduling requirements
* Execution information
* Current lifecycle state

See:

`job-model.md`

---

## Scheduler

Responsible for deciding:

> Which waiting job should receive which available resources?

The scheduler should not necessarily be responsible for every operation associated with a job.

Scheduling and resource selection are distinct responsibilities in mature systems. Slurm's resource-selection subsystem determines resources that can be allocated to a job, while the controller manages broader cluster state and scheduling.

---

## Resource

Represents computational capacity.

Examples:

```text
CPU
Memory
GPU
Node
```

Resources have:

```text
capacity
availability
allocation
```

---

## Node

Represents a machine capable of executing workloads.

A node can expose:

```text
CPU capacity
Memory capacity
GPU capacity
Node state
Hardware information
```

Slurm maintains node information including processors, memory, temporary disk and node state.

---

## Execution

Responsible for actually launching work on allocated resources.

This should be considered separately from the decision to schedule the work.

---

## Monitoring

Observes:

```text
Jobs
Nodes
Resources
Execution
Failures
```

Monitoring becomes especially important for the future self-healing layer.

---

# 4. Single-Node V0

The first architecture can remain very small:

```text
             Job Submission
                    │
                    ▼
              ┌──────────┐
              │   Queue  │
              └────┬─────┘
                   │
                   ▼
              ┌──────────┐
              │ Scheduler│
              └────┬─────┘
                   │
                   ▼
            Resource Allocation
                   │
                   ▼
              ┌──────────┐
              │ Execution│
              └────┬─────┘
                   │
                   ▼
                 Job
                State
```

There is no need to introduce distributed communication, GPUs, agentic reasoning or complex persistence at this stage.

---

# 5. Future Multi-Node Architecture

Eventually:

```text
                    Controller
                        │
             ┌──────────┼──────────┐
             │          │          │
           Node 1     Node 2     Node 3
             │          │          │
          Worker     Worker     Worker
```

This resembles the general controller/compute-node separation used by systems such as Slurm.

The exact Aegis communication architecture should be decided when multi-node scheduling is actually implemented.

---

# 6. Future Intelligent Layer

The eventual architecture may extend to:

```text
                 User
                  │
                  ▼
          Workload Understanding
                  │
                  ▼
          Execution Planning
                  │
                  ▼
              Scheduler
                  │
                  ▼
             Execution
                  │
                  ▼
             Monitoring
                  │
                  ▼
        ┌──── Failure? ────┐
        │                  │
       No                 Yes
        │                  │
        ▼                  ▼
      Finish           Diagnosis
                           │
                           ▼
                       Recovery
                           │
                           ▼
                         Retry
```

This layer is deliberately outside V0.
