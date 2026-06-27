# Aegis

> **An AI-Augmented Workload Intelligence Platform for HPC and AI Clusters**

[![License: Apache-2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](#license)
![Status](https://img.shields.io/badge/status-active%20development-orange)
![Language](https://img.shields.io/badge/language-Rust-orange)
![AI](https://img.shields.io/badge/AI-Augmented-blue)

---

## Overview

Aegis is an open-source workload intelligence platform designed for High Performance Computing (HPC) and Artificial Intelligence (AI) infrastructure.

Rather than attempting to replace traditional schedulers, Aegis introduces an intelligent layer that makes workload scheduling **predictable, explainable, and data-driven**.

Modern schedulers excel at allocating computational resources, but they provide limited insight into why scheduling decisions occur, when workloads will begin execution, whether resource requests are optimal, or how failures can be prevented before execution.

Aegis combines deterministic scheduling with predictive analytics, machine learning, retrieval-augmented generation (RAG), and interactive visualization to improve both user experience and infrastructure utilization.

---

# Problem Statement

Current HPC workload managers primarily focus on execution and resource allocation.

However, users and administrators continue to face several challenges:

* Queue waiting times are unpredictable.
* Runtime estimates are unreliable.
* Resource requests are frequently overestimated.
* Scheduler decisions lack transparency.
* Diagnosing failed workloads requires manual log analysis.
* Cluster congestion cannot be easily forecasted.
* Existing monitoring tools are fragmented across multiple platforms.

These challenges become increasingly significant as AI workloads grow in scale and complexity.

Aegis aims to bridge this gap by transforming workload management into an intelligent, explainable, and predictive platform.

---

# Vision

The vision of Aegis is to become an intelligent operating platform for AI and HPC workloads.

Instead of simply scheduling jobs, Aegis assists users throughout the complete workload lifecycle by answering questions such as:

* Why is my job waiting?
* When will it begin execution?
* How long will it run?
* Am I requesting too many resources?
* Will my job likely fail?
* What happens if I modify my resource request?
* How can cluster utilization be improved?

Artificial intelligence is used to augment scheduling—not replace it.

Scheduling decisions remain deterministic, while AI provides prediction, recommendation, diagnostics, and explainability.

---

# Key Features

## Core Scheduling

* First Come First Serve (FCFS)
* Priority Scheduling *(planned)*
* Fair Share Scheduling *(planned)*
* Backfilling *(planned)*
* GPU-aware Scheduling *(planned)*

---

## AI Intelligence

* Runtime Prediction
* Queue Waiting Time Prediction
* Failure Prediction
* Resource Recommendation
* Workload Classification
* Congestion Forecasting

---

## Explainability

Every scheduling decision can be inspected.

Example:

```
Job Status: Pending

Reason:
• Waiting for available GPU resources
• Highest priority queue currently occupied
• Estimated wait time: 14 minutes
```

---

## AI Copilot (RAG)

A retrieval-augmented assistant capable of answering operational questions using:

* Historical jobs
* Scheduler logs
* Execution logs
* Cluster metrics
* Documentation
* Previous failures

Example:

> Why did my PyTorch training fail?

Instead of generating a generic response, the assistant retrieves relevant evidence before producing an explanation.

---

## Interactive Dashboard *(Planned)*

* Live Queue Monitoring
* GPU Utilization
* Resource Heatmaps
* Timeline Visualization
* Historical Analytics
* Cluster Health
* Job Lifecycle Tracking

---

# Architecture

```
                        User
                          │
                          ▼
                 Web Dashboard
                          │
              REST / WebSocket API
                          │
                          ▼
                 Aegis Backend (Rust)
                          │
        ┌─────────────────┼─────────────────┐
        │                 │                 │
        ▼                 ▼                 ▼
   Scheduler        Executor         Monitoring
        │
        ▼
     Job Queue
        │
        ▼
    PostgreSQL
        │
        ▼
AI Intelligence Services (Python)
        │
        ├──────── Runtime Prediction
        ├──────── Queue Prediction
        ├──────── Failure Prediction
        ├──────── Resource Recommendation
        └──────── AI Copilot (RAG)
```

---

# Repository Structure

```
aegis/

├── backend/
├── frontend/
├── ai/
├── docs/
├── database/
├── monitoring/
├── deployments/
├── examples/
├── scripts/
├── tests/
│
├── README.md
├── ROADMAP.md
├── LICENSE
└── docker-compose.yml
```

---

# Technology Stack

## Backend

* Rust
* Tokio
* Tonic (gRPC)
* PostgreSQL
* SQLx
* Serde
* Tracing

---

## Artificial Intelligence

* Python
* PyTorch
* Scikit-Learn
* XGBoost
* FastAPI
* Sentence Transformers

---

## Retrieval-Augmented Generation

* pgvector
* PostgreSQL
* LangChain *(optional)*
* LlamaIndex *(optional)*

---

## Frontend

* Next.js
* React
* TypeScript
* Tailwind CSS
* Apache ECharts

---

## Infrastructure

* Docker
* Docker Compose
* Prometheus
* Grafana (Development)
* NVIDIA NVML

---

# Development Roadmap

## Phase 1

Core Scheduler Engine

* Job Model
* Queue Manager
* Scheduler
* Executor
* State Machine
* FCFS Scheduling

---

## Phase 2

Persistence

* PostgreSQL
* Repository Layer
* Job History

---

## Phase 3

Monitoring

* CPU Metrics
* Memory Metrics
* GPU Metrics
* Cluster Health

---

## Phase 4

Dashboard

* Interactive Web Interface
* Live Queue
* Job Monitoring
* Analytics

---

## Phase 5

Prediction Engine

* Runtime Prediction
* Queue Prediction
* Resource Recommendation
* Failure Prediction

---

## Phase 6

Explainability Engine

* Scheduling Explanations
* Resource Bottleneck Analysis
* Decision Tracing

---

## Phase 7

AI Copilot

* Retrieval-Augmented Generation
* Log Analysis
* Documentation Search
* Failure Diagnostics

---

## Phase 8

Digital Twin

* Cluster Simulation
* What-if Scheduling
* Capacity Planning
* Policy Comparison

---

# Design Principles

Aegis is built around several engineering principles:

* Deterministic scheduling
* AI-assisted decision support
* Modular architecture
* Thread safety
* Strong type safety
* Explainability by design
* Production-oriented engineering
* Extensibility

---

# Project Goals

The long-term objective is to develop an intelligent workload management platform capable of:

* Predicting workload behavior before execution.
* Explaining scheduling decisions.
* Optimizing infrastructure utilization.
* Assisting users through AI-powered diagnostics.
* Providing complete observability over cluster operations.

---

# Current Status

The project is currently under active development.

Initial milestones include:

* Job representation
* Thread-safe queue management
* Core scheduling engine
* Executor
* State management

---

# Contributing

Contributions, discussions, issue reports, and feature proposals are welcome.

Please ensure that all contributions:

* Follow the existing project architecture.
* Include appropriate documentation.
* Maintain thread safety.
* Include tests where applicable.

---

# License

This project is licensed under the Apache License 2.0.

See the `LICENSE` file for details.

---

# Acknowledgements

Aegis is inspired by decades of research in distributed systems, operating systems, high-performance computing, and modern AI infrastructure.

The project aims to explore how deterministic scheduling can be augmented with machine learning and retrieval-based intelligence to improve the usability, transparency, and efficiency of future compute platforms.
