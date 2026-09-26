# Aegis Job Model

## 1. Purpose

Aegis schedules computational jobs on HPC resources.

The job model defines the information Aegis needs to accept, schedule, execute, monitor, and eventually recover a workload.

The initial model should be based on established HPC scheduler concepts rather than inventing new representations where existing conventions are sufficient.

---

## 2. How Existing HPC Systems Model Jobs

### Slurm

Slurm maintains a substantial job record containing information such as:

* Job ID
* User and group
* Job name
* Priority
* Partition
* Job state
* Requested CPUs
* Requested nodes
* Memory requirements
* Time limit
* Dependencies
* Account
* Submission time
* Start/end times
* Allocated nodes
* Command
* Working directory
* Exit status

The `scontrol show job` interface exposes these concepts directly.

Slurm therefore treats a job as more than an executable command. It is a **workload request together with scheduling, resource, ownership, and execution state**.

### HTCondor

HTCondor takes a more attribute-oriented approach.

A job is represented as a **Job ClassAd**, which is a collection of named attributes. These attributes describe the workload, its requirements, preferences, state, and execution information.

A submit description can specify, among other things:

* Executable
* Arguments
* Working directory
* Input/output files
* CPU requirements
* Memory requirements
* Disk requirements
* Machine requirements
* Resource preferences
* Scheduling rank
* Environment
* Execution policies

HTCondor then creates the Job ClassAd used during scheduling.

An important concept is the separation between:

```text
Job
  ↓
requirements / preferences

Machine
  ↓
available characteristics
```

The scheduler matches the two rather than embedding a particular machine directly into the job definition.

---

# 3. Common Concepts

Although Slurm and HTCondor use different representations, several concepts appear repeatedly.

### Identity

A scheduler needs to distinguish one workload from another.

Typical information:

```text
Job ID
Job name
User
Account / project
```

### Workload

What should actually be executed?

```text
Executable
Arguments
Working directory
Environment
Input/output
```

HTCondor explicitly treats the executable and its execution environment as part of the job description.

### Resource Requirements

What does the workload require?

Examples:

```text
CPU
Memory
GPU
Disk
Node count
```

HTCondor exposes CPU and memory requests directly and uses them when matching jobs against machine resources.

Slurm similarly records requested CPUs, nodes, memory and other resource requirements in its job record.

### Scheduling Information

What affects when or where the job should run?

Examples:

```text
Priority
Partition / queue
Requirements
Constraints
Dependencies
Time limit
```

HTCondor distinguishes between **requirements** and **rank/preferences**. A requirement determines whether a machine is acceptable; rank expresses preference among acceptable machines.

Slurm likewise maintains priority, partition, dependencies, resource requirements and scheduling reasons in its job information.

### Lifecycle / State

The scheduler needs to know where the job currently is in its lifecycle.

A simplified model is:

```text
SUBMITTED
    ↓
PENDING
    ↓
RUNNING
    ↓
COMPLETED
```

with additional states for conditions such as:

```text
FAILED
CANCELLED
HELD
SUSPENDED
```

The exact state model should be determined separately from the job's static description.

### Execution Information

Once a job runs, additional information becomes available:

```text
Allocated resources
Execution node(s)
Start time
End time
Exit status
Runtime
```

Slurm's job record, for example, exposes allocated nodes, start/end times, exit code and current state.

---

# 4. Important Design Distinction

A useful distinction from existing systems is:

```text
             JOB
              │
      ┌───────┴────────┐
      │                │
 Job Description    Job State
      │                │
      │                ├── PENDING
      │                ├── RUNNING
      │                └── COMPLETED
      │
      ├── executable
      ├── arguments
      ├── resources
      ├── requirements
      └── scheduling information
```

The information describing **what the user requested** is conceptually different from information describing **what happened during execution**.

This distinction becomes increasingly important as Aegis grows.

---

# 5. Questions for Aegis

These are design questions, not predetermined answers.

### Identity

* What uniquely identifies a job?
* Does Aegis need a job name in addition to an ID?
* Does V0 need users/accounts?

### Workload

* Is a job initially an executable?
* Should Aegis accept a command?
* Should scripts be supported immediately or later?
* What execution environment does a job require?

### Resources

* What resources does V0 understand?
* CPU only?
* Memory?
* Number of nodes?
* Should resources be requested quantities or constraints?

### Scheduling

* Does every job have a priority?
* What determines priority?
* Does V0 need queues/partitions?
* Should jobs express constraints?

### Lifecycle

* What states does Aegis need?
* Which components are allowed to change state?
* What transitions are legal?
* What happens when execution fails?

### Execution

* Where is the job executed?
* Who launches it?
* How is its exit status obtained?
* Where are stdout/stderr stored?

### Future compatibility

The model should leave room for:

```text
single node
     ↓
multi-node
     ↓
CPU + GPU
     ↓
distributed workloads
```

without requiring all of these capabilities in V0.

---

# 6. Aegis V0 Scope

For the first single-node CPU implementation, the job model should remain substantially smaller than a production scheduler.

The objective is to establish the fundamental relationship:

```text
Job
 ↓
Scheduler
 ↓
Resource allocation
 ↓
Execution
 ↓
Job state
```

Features such as accounts, QoS, reservations, sophisticated constraints, job arrays, heterogeneous resources and advanced policies should only be introduced when a concrete Aegis requirement needs them.

---

# 7. Design Principle

Aegis should follow:

> **Use established HPC concepts where they already exist; introduce new abstractions only when Aegis has a specific reason to need them.**

Slurm and HTCondor demonstrate different valid approaches to representing jobs. Aegis does not need to reproduce either representation exactly.

The objective is to understand the underlying concepts and build the smallest model that supports Aegis's current scheduling requirements.

---

## References

* Slurm — `scontrol` and job information: official Slurm documentation.
* HTCondor — ClassAd mechanism: official HTCondor documentation.
* HTCondor — Job Description Language: official HTCondor documentation.
* HTCondor — Submitting a Job: official HTCondor documentation.
* HTCondor — Job Scheduling: official HTCondor documentation.
