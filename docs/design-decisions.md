# Aegis Design Decisions

This document records why important architectural decisions are made.

It should be updated as the project evolves.

---

## Decision 001 — C++

**Decision**

Aegis will be implemented in C++.

**Reason**

Aegis is intended to become an HPC-oriented systems project where direct control over concurrency, resource management and systems-level execution is important.

---

## Decision 002 — Start with basic scheduling

**Decision**

The first implementation focuses on basic scheduling rather than the complete long-term vision.

**Reason**

The agentic and self-healing layers depend on a functioning scheduling and execution foundation.

---

## Decision 003 — Single node before multi-node

**Decision**

Aegis starts with single-node CPU scheduling.

**Reason**

This establishes the fundamental scheduling/resource-allocation model before distributed-system complexity is introduced.

---

## Decision 004 — Do not implement every production feature

**Decision**

Aegis will not reproduce the full feature set of Slurm, HTCondor or another mature scheduler.

**Reason**

Existing systems already solve those problems. Aegis should learn from their architecture and introduce functionality when it serves an actual project requirement.

---

## Decision 005 — Small components

**Decision**

Aegis should be decomposed around meaningful responsibilities.

**Reason**

Small, focused components are easier to understand, test and evolve.

---

## Decision 006 — Documentation before abstraction

**Decision**

Aegis concepts should be documented before unnecessary implementation abstractions are introduced.

**Reason**

The project is intended to develop the author's understanding of HPC scheduler architecture rather than simply reproduce an existing system.

---

## Decision 007 — Future intelligence is separate from V0

**Decision**

Agentic workload understanding, script generation, failure diagnosis and self-healing are long-term capabilities.

**Reason**

They depend on reliable scheduling, execution and monitoring foundations.

---

## Decision 008 — Industry concepts first

**Decision**

Established HPC concepts should be researched before introducing new terminology or abstractions.

**Reason**

Aegis should remain understandable to someone familiar with HPC systems.

---

## Decision 009 — Node and Resource separation

**Decision**

Nodes own Resource instances rather than hardcoding flat allocation variables inside Node or Scheduler.

**Reason**

Allows compute nodes to manage multiple consumable dimensions (CPUs, Memory, future GPUs) cleanly and independently validate capacity without coupling to scheduling policy.

---

## Decision 010 — POSIX process execution and automatic resource reclamation

**Decision**

The execution engine uses fork/execvp and synchronously monitors process termination via waitpid, immediately reclaiming node allocations upon job completion or failure.

**Reason**

Provides realistic OS-level workload execution for V0 while preventing resource leaks across job lifecycles.