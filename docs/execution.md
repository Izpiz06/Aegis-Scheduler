# Aegis Execution

## 1. Purpose

Scheduling decides **when and where** work should run.

Execution is responsible for actually starting and managing that work.

---

# 2. Conceptual Separation

```text
Scheduler
    │
    │ allocation
    ▼
Execution
    │
    │ launch
    ▼
Process
```

The distinction becomes important when Aegis expands to multiple compute nodes.

Slurm follows this general separation: `slurmctld` manages jobs and resource allocation, while `slurmd` runs on compute nodes and launches/manages tasks.

---

# 3. Single-Node Execution

For V0:

```text
Job
 ↓
Scheduler
 ↓
CPU allocation
 ↓
Process launch
 ↓
Process exit
 ↓
Job state update
```

---

# 4. Execution Information

The execution layer may eventually provide:

```text
PID
Start time
Exit code
Signal
stdout
stderr
Runtime
Resource usage
```

---

# 5. Multi-Node Execution

Eventually:

```text
Controller
   │
   ├──── Node 1 → Worker
   ├──── Node 2 → Worker
   └──── Node 3 → Worker
```

The communication protocol and worker architecture should be designed when Aegis reaches multi-node scheduling.

---

# 6. Script Generation

Script generation belongs to the future orchestration layer.

Conceptually:

```text
User Workload
      ↓
Workload Understanding
      ↓
Execution Plan
      ↓
Generated Script / Command
      ↓
Scheduler
```

It should not be confused with the fundamental scheduling mechanism.
