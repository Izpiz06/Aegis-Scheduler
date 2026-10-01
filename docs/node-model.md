# Aegis Node & Resource Model

## 1. Purpose

A node represents a compute entity capable of executing jobs. Compute nodes own resources (CPUs and memory) and maintain an operational state.

---

## 2. Resource Model (`Resource`)

The `Resource` component tracks compute capacity and allocations:

```text
Resource
 ├── total_cpus
 ├── available_cpus
 ├── total_memory (MB)
 └── available_memory (MB)
```

### Invariants & Validation

1. **Over-allocation Prevention**: `allocate(cpus, memory)` verifies `available_cpus >= cpus` and `available_memory >= memory` before committing resources.
2. **Release Validation**: `release(cpus, memory)` prevents reclaiming more resources than total capacity (`available + released <= total`).

---

## 3. Node Model (`Node`)

A node owns a `Resource` instance, maintains an operational state, and enforces node-level availability:

```text
Node
 ├── ID / Name
 ├── State (READY, DRAINING, DOWN)
 └── Resource (CPU + Memory capacity)
```

### Node States

* `READY`: Healthy and actively accepting workload allocations.
* `DRAINING`: Completing running workloads; rejecting new allocations (maintenance mode).
* `DOWN`: Offline or faulty; cannot host allocations.

### Separation of Responsibilities

* **Node Role**: The node verifies fit (`can_fit(job)`) and performs allocation/release accounting on its owned `Resource`.
* **Scheduler Role**: The node does **not** decide which job gets scheduled. All arbitration and job selection decisions remain exclusively in the `Scheduler`.
