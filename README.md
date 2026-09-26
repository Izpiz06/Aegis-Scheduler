# Aegis

## Brief

Aegis is a C++ based HPC job scheduling system designed to evolve into an agentic, self-healing HPC orchestration system.

The project begins with the fundamentals of job scheduling and resource management, with the goal of progressively extending from single-node scheduling to distributed and heterogeneous HPC environments.

## What is V0?

V0 focuses on implementing the core principles of HPC job scheduling from the ground up.

The development will progress incrementally:

1. **Single-node CPU scheduling**

    * Job submission
    * Job queues
    * Scheduling policies
    * CPU resource allocation
    * Job execution and state tracking

2. **Multi-node CPU scheduling**

    * Node-level resource management
    * Distributed job placement
    * Communication between scheduler and compute nodes

3. **GPU scheduling**

    * GPU resource representation
    * GPU-aware job allocation
    * Heterogeneous CPU/GPU workloads

The initial implementation will deliberately focus on the fundamental scheduling and resource-management mechanisms before introducing higher-level capabilities.

## Long-Term Direction

Aegis is intended to eventually evolve beyond conventional scheduling into an intelligent HPC orchestration system capable of:

* Generating execution/job scripts
* Monitoring workloads and system state
* Detecting failures and abnormal behavior
* Diagnosing failures
* Taking corrective actions
* Retrying or rescheduling workloads
* Learning from previous executions
* Providing agentic decision-making for workload management

These capabilities are **future stages of Aegis** and are not part of the initial V0 implementation.
