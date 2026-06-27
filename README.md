<div align="center">

# 🛡️ Aegis

### An AI-Augmented Workload Intelligence Platform for HPC and AI Clusters

[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg?style=for-the-badge)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Active%20Development-orange?style=for-the-badge)](#-current-status)
[![Rust](https://img.shields.io/badge/Rust-000000?style=for-the-badge&logo=rust&logoColor=white)](https://www.rust-lang.org/)
[![Python](https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white)](https://www.python.org/)
[![PostgreSQL](https://img.shields.io/badge/PostgreSQL-316192?style=for-the-badge&logo=postgresql&logoColor=white)](https://www.postgresql.org/)
[![Docker](https://img.shields.io/badge/Docker-2496ED?style=for-the-badge&logo=docker&logoColor=white)](https://www.docker.com/)

<br/>

**Deterministic Scheduling · Predictive Analytics · Explainable AI · Interactive Visualization**

[Overview](#-overview) •
[Features](#-key-features) •
[Architecture](#-architecture) •
[Tech Stack](#-technology-stack) •
[Roadmap](#-development-roadmap) •
[Contributing](#-contributing)

</div>

---

## 📖 Overview

**Aegis** is an open-source workload intelligence platform designed for High Performance Computing (HPC) and Artificial Intelligence (AI) infrastructure.

Rather than replacing traditional schedulers, Aegis introduces an intelligent layer that makes workload scheduling **predictable, explainable, and data-driven**.

Modern schedulers excel at resource allocation — but they provide limited insight into *why* scheduling decisions occur, *when* workloads will begin, *whether* resource requests are optimal, or *how* failures can be prevented. Aegis combines deterministic scheduling with predictive analytics, machine learning, retrieval-augmented generation (RAG), and interactive visualization to bridge that gap.

---

## ❓ Problem Statement

Current HPC workload managers primarily focus on execution and resource allocation. Users and administrators continue to face significant challenges:

| Challenge | Impact |
|:---|:---|
| Unpredictable queue wait times | Users cannot plan workflows effectively |
| Unreliable runtime estimates | Inaccurate scheduling and resource waste |
| Overestimated resource requests | Reduced cluster throughput |
| Opaque scheduler decisions | Difficult troubleshooting and debugging |
| Manual log analysis for failures | Slow incident response |
| No congestion forecasting | Reactive instead of proactive management |
| Fragmented monitoring tools | Scattered observability across platforms |

These challenges become increasingly significant as AI workloads grow in scale and complexity. Aegis transforms workload management into an **intelligent, explainable, and predictive platform**.

---

## 🔭 Vision

Aegis aims to become an **intelligent operating platform** for AI and HPC workloads. Instead of simply scheduling jobs, Aegis assists users throughout the complete workload lifecycle:

> *"Why is my job waiting? When will it start? How long will it run? Am I requesting too many resources? Will my job likely fail?"*

**AI augments scheduling — it does not replace it.** Scheduling decisions remain deterministic, while AI provides prediction, recommendation, diagnostics, and explainability.

---

## ✨ Key Features

### 🗓️ Core Scheduling

| Algorithm | Status |
|:---|:---:|
| First Come First Serve (FCFS) | ✅ Implemented |
| Priority Scheduling | 🔜 Planned |
| Fair Share Scheduling | 🔜 Planned |
| Backfilling | 🔜 Planned |
| GPU-aware Scheduling | 🔜 Planned |

### 🧠 AI Intelligence

- **Runtime Prediction** — Estimate job completion time before execution
- **Queue Wait Prediction** — Forecast how long a job will wait in queue
- **Failure Prediction** — Flag jobs likely to fail before they run
- **Resource Recommendation** — Suggest optimal CPU, memory, and GPU requests
- **Workload Classification** — Categorize jobs by behavior patterns
- **Congestion Forecasting** — Predict upcoming cluster bottlenecks

### 🔍 Explainability

Every scheduling decision can be inspected with transparent reasoning:

```
Job Status: Pending

Reason:
  • Waiting for available GPU resources
  • Highest priority queue currently occupied
  • Estimated wait time: 14 minutes
```

### 🤖 AI Copilot (RAG)

A retrieval-augmented assistant that answers operational questions using real evidence — not hallucinated responses:

> **User:** *"Why did my PyTorch training fail?"*
>
> The copilot retrieves relevant context from historical jobs, scheduler logs, execution logs, cluster metrics, documentation, and previous failures before producing an explanation.

### 📊 Interactive Dashboard *(Planned)*

- Live Queue Monitoring &nbsp;·&nbsp; GPU Utilization &nbsp;·&nbsp; Resource Heatmaps
- Timeline Visualization &nbsp;·&nbsp; Historical Analytics &nbsp;·&nbsp; Cluster Health
- Job Lifecycle Tracking

---

## 🏗️ Architecture

```
                          ┌──────────┐
                          │   User   │
                          └────┬─────┘
                               │
                          ┌────▼─────┐
                          │   Web    │
                          │Dashboard │
                          └────┬─────┘
                               │
                     REST / WebSocket API
                               │
                    ┌──────────▼──────────┐
                    │  Aegis Backend      │
                    │      (Rust)         │
                    └──┬───────┬───────┬──┘
                       │       │       │
                 ┌─────▼──┐ ┌─▼────┐ ┌▼─────────┐
                 │Scheduler│ │Exec- │ │Monitoring │
                 │         │ │utor  │ │           │
                 └────┬────┘ └──────┘ └───────────┘
                      │
                 ┌────▼────┐
                 │Job Queue│
                 └────┬────┘
                      │
                 ┌────▼──────┐
                 │PostgreSQL │
                 └────┬──────┘
                      │
        ┌─────────────▼─────────────┐
        │  AI Intelligence Services │
        │         (Python)          │
        ├───────────────────────────┤
        │ • Runtime Prediction      │
        │ • Queue Prediction        │
        │ • Failure Prediction      │
        │ • Resource Recommendation │
        │ • AI Copilot (RAG)        │
        └───────────────────────────┘
```

---

## 📁 Repository Structure

```
Aegis-Scheduler/
│
├── Aegis Core/              # Rust backend — scheduler, executor, queue, resources
│   ├── src/
│   │   ├── main.rs          # Application entry point
│   │   ├── job.rs           # Job model and state machine
│   │   ├── queue.rs         # Thread-safe job queue
│   │   ├── executor.rs      # Job execution engine
│   │   └── resources.rs     # Resource management
│   └── Cargo.toml
│
├── Aegis AI/                # Python AI services — prediction, RAG, recommendations
│   ├── src/
│   └── requirements.txt
│
├── proto/                   # gRPC protocol definitions
├── Cargo.toml               # Workspace configuration
└── README.md
```

---

## 🛠️ Technology Stack

<table>
<tr>
<td valign="top" width="50%">

### Backend
| Technology | Purpose |
|:---|:---|
| **Rust** | Core platform language |
| **Tokio** | Async runtime |
| **Tonic** | gRPC framework |
| **PostgreSQL** | Persistent storage |
| **SQLx** | Async database driver |
| **Serde** | Serialization |
| **Tracing** | Structured logging |

### AI & ML
| Technology | Purpose |
|:---|:---|
| **Python** | AI services language |
| **PyTorch** | Deep learning |
| **Scikit-Learn** | Classical ML |
| **XGBoost** | Gradient boosting |
| **FastAPI** | AI service API |
| **Sentence Transformers** | Embedding models |

</td>
<td valign="top" width="50%">

### RAG Pipeline
| Technology | Purpose |
|:---|:---|
| **pgvector** | Vector similarity search |
| **PostgreSQL** | Vector store backend |
| **LangChain** | Orchestration *(optional)* |
| **LlamaIndex** | Data indexing *(optional)* |

### Frontend
| Technology | Purpose |
|:---|:---|
| **Next.js** | React framework |
| **TypeScript** | Type-safe frontend |
| **Tailwind CSS** | Utility-first styling |
| **Apache ECharts** | Data visualization |

### Infrastructure
| Technology | Purpose |
|:---|:---|
| **Docker** | Containerization |
| **Docker Compose** | Multi-service orchestration |
| **Prometheus** | Metrics collection |
| **Grafana** | Monitoring dashboards |
| **NVIDIA NVML** | GPU telemetry |

</td>
</tr>
</table>

---

## 🗺️ Development Roadmap

| Phase | Milestone | Key Deliverables | Status |
|:---:|:---|:---|:---:|
| **1** | Core Scheduler Engine | Job Model · Queue Manager · Scheduler · Executor · State Machine · FCFS | 🟢 In Progress |
| **2** | Persistence | PostgreSQL · Repository Layer · Job History | ⬜ Planned |
| **3** | Monitoring | CPU / Memory / GPU Metrics · Cluster Health | ⬜ Planned |
| **4** | Dashboard | Interactive Web Interface · Live Queue · Job Monitoring · Analytics | ⬜ Planned |
| **5** | Prediction Engine | Runtime · Queue · Failure Prediction · Resource Recommendation | ⬜ Planned |
| **6** | Explainability Engine | Scheduling Explanations · Bottleneck Analysis · Decision Tracing | ⬜ Planned |
| **7** | AI Copilot | RAG · Log Analysis · Documentation Search · Failure Diagnostics | ⬜ Planned |
| **8** | Digital Twin | Cluster Simulation · What-if Scheduling · Capacity Planning · Policy Comparison | ⬜ Planned |

---

## 🧭 Design Principles

| Principle | Description |
|:---|:---|
| **Deterministic Scheduling** | Scheduling outcomes are reproducible and predictable |
| **AI-Assisted Decision Support** | Intelligence augments — never overrides — the scheduler |
| **Modular Architecture** | Each component is independently deployable and testable |
| **Thread Safety** | All shared state is protected by safe concurrency primitives |
| **Strong Type Safety** | Leveraging Rust's type system to eliminate entire categories of bugs |
| **Explainability by Design** | Every decision can be traced and inspected |
| **Production-Oriented** | Built for real-world scale and reliability from day one |
| **Extensibility** | Plugin-friendly interfaces for custom policies and algorithms |

---

## 📌 Current Status

> **🚧 Active Development — Phase 1**

The following foundational components have been implemented:

- [x] Job representation and state model
- [x] Thread-safe queue management
- [x] Core scheduling engine (FCFS)
- [x] Executor framework
- [x] State machine for job lifecycle
- [ ] Priority and fair-share scheduling
- [ ] PostgreSQL persistence
- [ ] AI prediction services

---

## 🤝 Contributing

Contributions, discussions, issue reports, and feature proposals are welcome.

Please ensure that all contributions:

- Follow the existing project architecture
- Include appropriate documentation
- Maintain thread safety guarantees
- Include tests where applicable

> See [`CONTRIBUTING.md`](CONTRIBUTING.md) for detailed guidelines *(coming soon)*.

---

## 📄 License

This project is licensed under the **Apache License 2.0**.

See the [`LICENSE`](LICENSE) file for full details.

---

## 🙏 Acknowledgements

Aegis is inspired by decades of research in distributed systems, operating systems, high-performance computing, and modern AI infrastructure. The project explores how deterministic scheduling can be augmented with machine learning and retrieval-based intelligence to improve the usability, transparency, and efficiency of future compute platforms.

---

<div align="center">

**Built with 🦀 Rust and 🐍 Python**

*Deterministic scheduling, augmented by intelligence.*

</div>
