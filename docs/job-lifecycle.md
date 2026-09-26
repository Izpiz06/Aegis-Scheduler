# Aegis Job Lifecycle

## 1. Purpose

A job lifecycle describes how a submitted job progresses through the scheduler and execution system.

The lifecycle should be treated independently from the job's static description.

---

# 2. Conceptual Lifecycle

A minimal lifecycle is:

```text
SUBMITTED
    │
    ▼
PENDING
    │
    │ resources available
    ▼
RUNNING
    │
    ├───────────────┐
    │               │
    ▼               ▼
COMPLETED        FAILED
```

Cancellation can occur while a job is waiting or running:

```text
PENDING ──────► CANCELLED

RUNNING ──────► CANCELLED
```

---

# 3. Submission

A job enters the system.

The scheduler should establish:

```text
Job identity
Submission time
Requested resources
Workload
Initial state
```

---

# 4. Pending

The job is accepted but cannot currently execute.

Possible reasons include:

```text
Insufficient CPU
Insufficient memory
Resources occupied
Scheduling policy
Dependency
Queue/partition restriction
```

The reason for waiting is useful operational information.

---

# 5. Running

The scheduler has allocated resources and execution has started.

The system can track:

```text
Start time
Allocated resources
Execution node
Process information
Runtime
```

---

# 6. Completion

The workload exits successfully.

The scheduler can record:

```text
End time
Exit code
Runtime
Resource usage
```

---

# 7. Failure

Execution terminates unsuccessfully.

Failure information may include:

```text
Exit code
Signal
Termination reason
Node failure
Resource failure
Execution error
```

This information becomes important to the future self-healing system.

---

# 8. Cancellation

A job may be explicitly terminated before normal completion.

The system should distinguish:

```text
Completed
Failed
Cancelled
```

because these represent different outcomes.

---

# 9. State Transition Principle

A useful invariant is:

> Not every component should be able to arbitrarily change every job state.

The scheduler, executor and monitoring subsystem may eventually have different responsibilities for state transitions.

The exact ownership model should be decided during implementation.

---

# 10. Future Recovery

The future Aegis system may extend:

```text
FAILED
  ↓
DIAGNOSING
  ↓
RECOVERABLE?
  │
  ├── YES → MODIFY → RETRY
  │
  └── NO  → FAILED
```

This is a future extension rather than part of the basic scheduler.
