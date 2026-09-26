# Aegis Node Model

## 1. Purpose

A node represents a machine capable of executing jobs.

---

# 2. Basic Node Information

A node can conceptually contain:

```text
Node
 ├── Identity
 ├── CPU capacity
 ├── Memory capacity
 ├── State
 └── Allocations
```

Production HPC schedulers maintain additional information such as processor topology, memory, temporary disk, features and node state.

---

# 3. Node State

A node may eventually have states such as:

```text
AVAILABLE
BUSY
DOWN
DRAINING
DRAINED
```

The exact Aegis state set should be determined by actual requirements.

---

# 4. Node and Resource Separation

A node is not necessarily the same thing as a resource.

For example:

```text
Node
 ├── CPU resources
 ├── Memory resources
 └── GPU resources
```

This distinction becomes important when multiple jobs share a node.

Slurm's resource-selection system explicitly tracks resources within nodes rather than treating every allocation as an entire machine.

---

# 5. V0

For single-node CPU scheduling, the node model can remain minimal.

The scheduler primarily needs to know:

```text
Node identity
Total CPU capacity
Available CPU capacity
Node state
```

Additional topology and hardware information can be introduced when needed.
