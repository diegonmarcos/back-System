# AI Infrastructure Master Plan

**Project:** Diego's AI/ML System
**Parent:** `MASTERPLAN_CLOUD.md` → A0) Service Catalog → User AIs Models
**CTO:** Claude (Opus)
**Date:** 2025-12-11
**Status:** PLANNING (Premium Project - Will merge when ready)

---

## Executive Summary

This is a **sub-document** of MASTERPLAN_CLOUD.md, defining the AI-specific infrastructure.
**Two independent GPU VMs:** Multi-Model (inference) + MyAI (training) - both pay-per-use.

```
┌────────────────────────────────────────────────────────────────────────────────────────────┐
│  A) HANDOFF                        WHAT we're building (AI Infrastructure)                 │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  A0) Products                      - Name, Component, Stack, Purpose                       │
│      ├── A00) Multi-Model          - Open WebUI + Ollama (VM1: inference)                  │
│      └── A01) MyAI Platform        - Train & deploy your own models (VM2: training)        │
│  A1) Infra Services                - Service, Stack and Component Definition               │
│      ├── A10) Inference            - Ollama (DeepSeek, Llama, Mistral) on VM1              │
│      ├── A11) RAG & Knowledge      - Built into Open WebUI (VM1)                           │
│      └── A12) Training             - PyTorch, MLflow on VM2                                │
│  A2) Infra Resources               - Resource Allocation, Maps/Topology, Costs             │
│      ├── A20) Resource Alloc       - Two GPU VMs (TensorDock)                              │
│      │       ├── A200) Resource Estimation       - RAM, Storage, GPU per service           │
│      │       ├── A201) VM Capacity & Headroom    - Capacity vs Allocated per VM            │
│      │       ├── A202) Cost Estimation           - $24-$120/mo (pay-per-use)               │
│      │       └── A203) URL/Port Proxied          - chat + myai URLs                        │
│      ├── A21) Maps & Topology      - Two VM architecture diagram                           │
│      └── A22) Costs                - All variable, no fixed costs                          │
│  A3) Tech Research                 - Framework comparisons, model benchmarks               │
│      ├── A30) LLM Models           - Model comparisons (size, VRAM, quality)               │
│      ├── A31) GPU Providers        - Cloud GPU pricing and availability                    │
│      ├── A32) Vector DBs           - (using Open WebUI built-in ChromaDB)                  │
│      └── A33) Embeddings           - (using Open WebUI built-in sentence-transformers)     │
│  A4) Today                         - Current running state                                 │
│      ├── A40) Status               - Current deployment status                             │
│      └── A41) Quick Ref            - VM access, service URLs                               │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  B) ARCHITECTURE                   HOW we're building it (Technical Deep Dives)            │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  B1) Model Architecture            - Model routing, RAG pipeline                           │
│  B2) Training Pipeline             - Data collection → Training → Deployment               │
│  B3) Infrastructure Architecture   - GPU provisioning, data flow                           │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  C) ROADMAP                        WHEN we're building it (Planning & Prioritization)      │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  C1) Phases                        - Phase 1: Inference → Phase 2: RAG → Phase 3: Training │
│  C2) Dependencies                  - Service dependency graph                              │
│  C3) Backlog                       - Prioritized task list                                 │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  D) DEVOPS                         WHO operates it (Operations & Observability)            │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  D1) Dashboard                     - AI services access UI                                 │
│  D2) Monitoring                    - GPU metrics, cost alerts, health checks               │
│  D3) Knowledge Center              - Documentation, runbooks, quick commands               │
└────────────────────────────────────────────────────────────────────────────────────────────┘
```

**Connection to MASTERPLAN_CLOUD:**
```
MASTERPLAN_CLOUD.md
└── A0) Service Catalog
    └── User AIs Models
        └── AI Chat (Terminals)
            ├── Mode 1: API Keys Only (OpenAI, Claude, etc.)
            └── Mode 2: Multi-Model Orchestration → THIS DOCUMENT
```

---

# A) HANDOFF - AI Infrastructure Definition




## A0) Products (Service, Stack and Component Definition)

### A00) Multi-Model Orchestration (VM1: Inference)

> **Independent VM:** `tensordock-inference` - Dedicated to chat/inference workloads.

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
ai-chat                  | -                    | -                   | AI Chat System (VM1)
  ↳ openwebui            | Chat UI + RAG        | Open WebUI          | UI, model switching, built-in RAG
  ↳ ollama-app           | LLM Server           | Ollama              | Local model serving
                         |                      |                     |
models                   | Model Library        | -                   | Available Models (in Ollama)
  ↳ deepseek-coder-v2    | Code Model           | DeepSeek-v2 14B Q4  | Code generation
  ↳ llama-3.1-8b         | General Model        | Llama 3.1 8B Q4     | General chat
  ↳ mistral-7b           | Fast Model           | Mistral 7B Q4       | Fast inference
                         |                      |                     |
external-apis            | External Models      | -                   | Pay-per-token APIs (optional)
  ↳ openai               | External API         | OpenAI API          | GPT-4 (via Open WebUI)
  ↳ anthropic            | External API         | Claude API          | Claude 3 (via Open WebUI)
```

**Architecture (VM1 - Inference):**
```
┌──────────────────────────────────────────────────────────────────────┐
│                 VM1: TENSORDOCK-INFERENCE (On-Demand)                 │
│                       RTX 4090 24GB | $0.35/hr                        │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Open WebUI (:3000)                                          │    │
│  │  • Chat interface                                            │    │
│  │  • Model selector (switch between models)                    │    │
│  │  • Built-in RAG (upload docs, PDFs, code)                    │    │
│  │  • Chat history & users                                      │    │
│  └─────────────────────────┬───────────────────────────────────┘    │
│                            │                                         │
│                            ▼                                         │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Ollama (:11434)                                             │    │
│  │  • DeepSeek-Coder-v2 14B (code)                              │    │
│  │  • Llama 3.1 8B (general)                                    │    │
│  │  • Mistral 7B (fast)                                         │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
```

**Why Open WebUI:**
- **No custom code** - Handles RAG, embeddings, document storage
- **Upload docs directly** - PDFs, code, notes via UI
- **Pay-per-use** - Only pay when chatting ($0.35/hr)

---

### A01) MyAI Platform - Train Your Own Models (VM2: Training)

> **Independent VM:** `tensordock-training` - Dedicated to training/fine-tuning workloads.

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
myai                     | -                    | -                   | Train & Deploy Your Own AI (VM2)
  ↳ myai-dashboard       | Dashboard            | SvelteKit 5 + SCSS  | AI management UI
  ↳ myai-api             | Backend              | FastAPI             | Orchestration backend
                         |                      |                     |
data                     | Data Layer           | -                   | Your Data Pipeline
  ↳ data-ingest          | Ingestion            | Python3             | Data collection pipelines
  ↳ data-store           | Storage              | pgvector + S3       | Vector DB + document store
  ↳ data-prep            | Preprocessing        | LangChain           | Cleaning, chunking, embedding
  ↳ data-version         | Versioning           | DVC                 | Dataset versioning
                         |                      |                     |
train                    | Model Layer          | -                   | Your Training Pipeline
  ↳ train-base           | Base Models          | PyTorch / HF        | HuggingFace models
  ↳ train-finetune       | Fine-tuning          | LoRA / QLoRA        | Fine-tuning pipelines
  ↳ train-scratch        | From Scratch         | PyTorch             | Train from scratch (expensive)
  ↳ train-track          | Tracking             | MLflow              | Experiment tracking
                         |                      |                     |
deploy                   | Deployment Layer     | -                   | Your Serving Pipeline
  ↳ deploy-model         | Model Serving        | Ollama / vLLM       | Model inference server
  ↳ deploy-api           | API Gateway          | FastAPI             | API for your model
```

**Architecture (VM2 - Training):**
```
┌──────────────────────────────────────────────────────────────────────┐
│                  VM2: TENSORDOCK-TRAINING (On-Demand)                 │
│                       RTX 4090 24GB | $0.35/hr                        │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  MyAI Dashboard (:8080)                                      │    │
│  │  • Dataset management                                        │    │
│  │  • Training job launcher                                     │    │
│  │  • Model deployment UI                                       │    │
│  └─────────────────────────┬───────────────────────────────────┘    │
│                            │                                         │
│                            ▼                                         │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Training Stack                                              │    │
│  │  • PyTorch + HuggingFace Transformers                        │    │
│  │  • LoRA/QLoRA fine-tuning                                    │    │
│  │  • MLflow (:5001) experiment tracking                        │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                            │                                         │
│                            ▼                                         │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │  Model Serving (after training)                              │    │
│  │  • Ollama / vLLM for your trained models                     │    │
│  │  • FastAPI endpoint (:8000)                                  │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
```

**Access Modes:**
- **Private:** Your use only (via Authelia from CLOUD)
- **Shared:** Invite-only access (API keys)
- **Public:** Open API endpoint (rate-limited)

**Independence from VM1:**
- Can train while VM1 is running inference
- Separate storage for datasets and trained models
- Deploy trained models to VM1 (Ollama) or serve directly on VM2

---





## A1) Infra Services (Service, Stack and Component Definition)

> **Two independent VMs:** VM1 for inference (A00), VM2 for training (A01).

### A10) Inference Services (VM1: tensordock-inference)

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
ollama                   | LLM Server           | Ollama              | Local model serving & management
                         |                      |                     |
models (in Ollama)       | Model Library        | -                   | Downloaded models
  ↳ deepseek-coder-v2    | Code Model           | 14B Q4 (~10 GB)     | Code generation
  ↳ llama-3.1-8b         | General Model        | 8B Q4 (~6 GB)       | General chat
  ↳ mistral-7b           | Fast Model           | 7B Q4 (~5 GB)       | Fast inference
```

### A11) RAG & Knowledge (VM1: Built into Open WebUI)

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
; NO SEPARATE SERVICES - Open WebUI handles all of this on VM1:
openwebui-rag            | Built-in RAG         | Open WebUI          | Document upload, chunking, search
openwebui-embeddings     | Built-in Embeddings  | sentence-transform  | Text → vector (local, free)
openwebui-vectordb       | Built-in Vector DB   | ChromaDB            | Vector storage (SQLite backend)
```

> **Why Open WebUI:** No custom brain-api, brain-db, pgvector, LangChain, collectors needed.

### A12) Training Services (VM2: tensordock-training)

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
training                 | -                    | -                   | Model Fine-tuning (VM2)
  ↳ training-jobs        | Training Runner      | PyTorch + HF        | Fine-tuning jobs (LoRA/QLoRA)
  ↳ mlflow               | Experiment Tracking  | MLflow (self-host)  | Track experiments, models
  ↳ data-store           | Data Storage         | pgvector + S3       | Training datasets, vectors
```

> **Independence:** VM2 runs separately from VM1, can train while VM1 is serving inference.

---







## A2) Infra Resources

> **Philosophy:** Performance-focused, not GUI-pretty.


### A20) Resource Allocation

#### A200) Resource Estimation

```
Service                  | RAM (active) | Storage | GPU (active) | VM
─────────────────────────┼──────────────┼─────────┼──────────────┼─────────────────────
; VM1: TENSORDOCK-INFERENCE - Multi-Model Chat (A00)
openwebui                | 1 GB         | 10 GB   | -            | tensordock-inference
ollama-app               | 4 GB         | 5 GB    | 20 GB        | tensordock-inference
deepseek-coder-v2        | -            | 10 GB   | (in 20 GB)   | tensordock-inference
llama-3.1-8b             | -            | 6 GB    | (in 20 GB)   | tensordock-inference
mistral-7b               | -            | 5 GB    | (in 20 GB)   | tensordock-inference
─────────────────────────┼──────────────┼─────────┼──────────────┼─────────────────────
SUBTOTAL VM1             | 5 GB         | 36 GB   | 20 GB        |
                         |              |         |              |
; VM2: TENSORDOCK-TRAINING - MyAI Platform (A01)
myai-dashboard           | 0.5 GB       | 2 GB    | -            | tensordock-training
myai-api                 | 1 GB         | 1 GB    | -            | tensordock-training
training-jobs            | 8 GB         | 20 GB   | 24 GB        | tensordock-training
mlflow-tracking          | 1 GB         | 5 GB    | -            | tensordock-training
data-store (pgvector)    | 2 GB         | 30 GB   | -            | tensordock-training
─────────────────────────┼──────────────┼─────────┼──────────────┼─────────────────────
SUBTOTAL VM2             | 12.5 GB      | 58 GB   | 24 GB        |
                         |              |         |              |
─────────────────────────┼──────────────┼─────────┼──────────────┼─────────────────────
TOTAL (parallel)         | 17.5 GB      | 94 GB   | 44 GB        | (if both running)
```

> **Resource columns show capacity needed when active** (not cumulative over time).
> - **RAM/GPU (active):** Memory required while service is running
> - **Storage:** Disk space (persistent)
> - **TOTAL (parallel):** Capacity needed if both VMs running simultaneously (e.g., dedicated hardware)
> - For **cost calculations** (hrs × $0.35), see **A202) Cost Estimation**

#### A201) VM Capacity & Headroom

```
Provider   | VM                   | CPU        | RAM Cap | RAM Alloc | RAM Head | HD Cap | HD Alloc | HD Head | GPU Cap | GPU Alloc | GPU Head
───────────┼──────────────────────┼────────────┼─────────┼───────────┼──────────┼────────┼──────────┼─────────┼─────────┼───────────┼──────────
TensorDock | tensordock-inference | 4 vCPU x86 | 16 GB   | 5 GB      | 69%      | 70 GB  | 36 GB    | 49%     | 24 GB   | 20 GB     | 17%
TensorDock | tensordock-training  | 4 vCPU x86 | 16 GB   | 12.5 GB   | 22%      | 100 GB | 58 GB    | 42%     | 24 GB   | 24 GB     | 0%
```

**Headroom Analysis (VM1 - Inference):**
```
| VM                   | Resource | Capacity | Allocated | Free   | Headroom | Status |
|----------------------|----------|----------|-----------|--------|----------|--------|
| tensordock-inference | RAM      | 16 GB    | 5 GB      | 11 GB  | 69%      | OK     |
| tensordock-inference | GPU VRAM | 24 GB    | 20 GB     | 4 GB   | 17%      | OK     |
| tensordock-inference | Storage  | 70 GB    | 36 GB     | 34 GB  | 49%      | OK     |

**Headroom Analysis (VM2 - Training):**

| VM                   | Resource | Capacity | Allocated | Free   | Headroom | Status |
|----------------------|----------|----------|-----------|--------|----------|--------|
| tensordock-training  | RAM      | 16 GB    | 12.5 GB   | 3.5 GB | 22%      | TIGHT  |
| tensordock-training  | GPU VRAM | 24 GB    | 24 GB     | 0 GB   | 0%       | FULL   |
| tensordock-training  | Storage  | 100 GB   | 58 GB     | 42 GB  | 42%      | OK     |

**Services per VM:**

| VM                   | Product | Services Running                                          |
|----------------------|---------|-----------------------------------------------------------|
| tensordock-inference | A00     | openwebui, ollama (+ loaded model)                        |
| tensordock-training  | A01     | myai-dashboard, myai-api, training-jobs, mlflow, pgvector |
```


#### A202) Cost Estimation

```
Resource                  | Type          | Unit Cost     | Usage Est      | Monthly Low | Monthly High
──────────────────────────┼───────────────┼───────────────┼────────────────┼─────────────┼─────────────
; VM1: TENSORDOCK-INFERENCE (A00 Multi-Model)
tensordock-inference      | Pay-per-use   | $0.35/hr      | 35-120 hrs/mo  | $12         | $42
tensordock-inference-ssd  | Included      | $0/mo         | 70 GB          | $0          | $0
                          |               |               |                |             |
; VM2: TENSORDOCK-TRAINING (A01 MyAI)
tensordock-training       | Pay-per-use   | $0.35/hr      | 15-60 hrs/mo   | $5          | $21
tensordock-training-ssd   | Included      | $0/mo         | 100 GB         | $0          | $0
                          |               |               |                |             |
; EXTERNAL APIS (optional)
openai-gpt4               | Pay-per-use   | $30/1M tok    | ~100k tok/mo   | $0          | $3
anthropic-claude          | Pay-per-use   | $15/1M tok    | ~100k tok/mo   | $0          | $2
──────────────────────────┼───────────────┼───────────────┼────────────────┼─────────────┼─────────────
                          |               |               | TOTAL          | $17/mo      | $68/mo
```

**Cost Tiers (Combined):**

| Tier        | VM1 (Inf) | VM2 (Train) | APIs   | Total      | Use Case                        |
|-------------|-----------|-------------|--------|------------|---------------------------------|
| **Minimal** | 35h ($12) | 0h ($0)     | $0     | **$12/mo** | Chat only, no training          |
| **Light**   | 60h ($21) | 15h ($5)    | $0     | **$26/mo** | Regular use + occasional train  |
| **Medium**  | 90h ($32) | 30h ($10)   | $5     | **$47/mo** | Daily dev + weekly training     |
| **Heavy**   | 120h ($42)| 60h ($21)   | $5     | **$68/mo** | Full-time dev + active training |
| **Parallel**| 150h ($52)| 100h ($35)  | $10    | **$97/mo** | Both VMs running simultaneously |

**Cost by Product:**

| Product     | VM                   | Low     | High    | Notes                          |
|-------------|----------------------|---------|---------|--------------------------------|
| A00 Chat    | tensordock-inference | $12/mo  | $42/mo  | Open WebUI + Ollama            |
| A01 MyAI    | tensordock-training  | $5/mo   | $35/mo  | Training + MLflow              |
| External    | -                    | $0/mo   | $5/mo   | Optional OpenAI/Claude APIs    |

#### A203) URL/Port Proxied

**URL Pattern:** `service.diegonmarcos.com` = Login/Landing → redirects to `/app` after auth success

```
Service              | URL (Public)                    | VM                   | Container      | Port  | Auth
─────────────────────┼─────────────────────────────────┼──────────────────────┼────────────────┼───────┼──────────
; VM1: TENSORDOCK-INFERENCE (A00 Multi-Model)
openwebui            | chat.diegonmarcos.com           | tensordock-inference | openwebui      | 3000  | authelia
ollama-api           | (internal only)                 | tensordock-inference | ollama-app     | 11434 | internal
                     |                                 |                      |                |       |
; VM2: TENSORDOCK-TRAINING (A01 MyAI)
myai-dashboard       | myai.diegonmarcos.com           | tensordock-training  | myai-dashboard | 8080  | authelia
myai-api             | myai.diegonmarcos.com/api       | tensordock-training  | myai-api       | 8000  | authelia
mlflow-ui            | mlflow.diegonmarcos.com         | tensordock-training  | mlflow-tracking| 5001  | authelia
```

**Proxy Chains:**
```
; VM1 (Inference)
User → Cloudflare → NPM (gcp-f-micro_1) → Auth (Authelia) → tensordock-inference

; VM2 (Training)
User → Cloudflare → NPM (gcp-f-micro_1) → Auth (Authelia) → tensordock-training
```

**URLs by Product:**

| Product | URL                           | Purpose                  |
|---------|-------------------------------|--------------------------|
| A00     | chat.diegonmarcos.com         | Open WebUI chat          |
| A01     | myai.diegonmarcos.com         | MyAI dashboard           |
| A01     | mlflow.diegonmarcos.com       | MLflow experiment UI     |

---

### A21) Maps & Topology

```
┌─────────────────────────────────────────────────────────────────────────────────────────────┐
│                            AI INFRASTRUCTURE (Two Independent VMs)                           │
├─────────────────────────────────────────────────────────────────────────────────────────────┤
│                                                                                             │
│  ┌─────────────────────────────────────┐    ┌─────────────────────────────────────┐        │
│  │   VM1: TENSORDOCK-INFERENCE          │    │   VM2: TENSORDOCK-TRAINING          │        │
│  │   RTX 4090 24GB | $0.35/hr           │    │   RTX 4090 24GB | $0.35/hr           │        │
│  │   (A00 Multi-Model Chat)             │    │   (A01 MyAI Platform)                │        │
│  ├─────────────────────────────────────┤    ├─────────────────────────────────────┤        │
│  │                                     │    │                                     │        │
│  │  ┌───────────────────────────────┐  │    │  ┌───────────────────────────────┐  │        │
│  │  │  Open WebUI (:3000)            │  │    │  │  MyAI Dashboard (:8080)       │  │        │
│  │  │  • Chat interface              │  │    │  │  • Dataset management         │  │        │
│  │  │  • Model selector              │  │    │  │  • Training job launcher      │  │        │
│  │  │  • Built-in RAG                │  │    │  │  • Model deployment           │  │        │
│  │  │  • Local embeddings            │  │    │  └───────────────┬───────────────┘  │        │
│  │  └───────────────┬───────────────┘  │    │                  │                  │        │
│  │                  │                  │    │                  ▼                  │        │
│  │                  ▼                  │    │  ┌───────────────────────────────┐  │        │
│  │  ┌───────────────────────────────┐  │    │  │  Training Stack               │  │        │
│  │  │  Ollama (:11434)               │  │    │  │  • PyTorch + HuggingFace      │  │        │
│  │  │  • DeepSeek-Coder-v2 14B      │  │    │  │  • LoRA/QLoRA fine-tuning     │  │        │
│  │  │  • Llama 3.1 8B               │  │    │  │  • MLflow (:5001)             │  │        │
│  │  │  • Mistral 7B                 │  │    │  └───────────────┬───────────────┘  │        │
│  │  └───────────────────────────────┘  │    │                  │                  │        │
│  │                                     │    │                  ▼                  │        │
│  │                                     │    │  ┌───────────────────────────────┐  │        │
│  │                                     │    │  │  Data Store                   │  │        │
│  │                                     │    │  │  • pgvector (datasets)        │  │        │
│  │                                     │    │  │  • S3/MinIO (models)          │  │        │
│  │                                     │    │  └───────────────────────────────┘  │        │
│  │                                     │    │                                     │        │
│  └─────────────────────────────────────┘    └─────────────────────────────────────┘        │
│                   │                                          │                              │
│                   │              ┌────────────────┐          │                              │
│                   └──────────────┤  Model Export  ├──────────┘                              │
│                                  │  (optional)    │                                         │
│                                  └────────────────┘                                         │
│                                          │                                                  │
│                                          ▼                                                  │
│  ┌─────────────────────────────────────────────────────────────────────────────────────┐   │
│  │  MASTERPLAN_CLOUD (Proxy + Auth)                                                     │   │
│  │  Cloudflare → NPM (gcp-f-micro_1) → Authelia                                         │   │
│  │  • chat.diegonmarcos.com  → VM1                                                      │   │
│  │  • myai.diegonmarcos.com  → VM2                                                      │   │
│  │  • mlflow.diegonmarcos.com → VM2                                                     │   │
│  └─────────────────────────────────────────────────────────────────────────────────────┘   │
│                                                                                             │
└─────────────────────────────────────────────────────────────────────────────────────────────┘
```

**Independence:**
- VM1 and VM2 run completely independently
- Can chat (VM1) while training (VM2) simultaneously
- Model export: trained models on VM2 can be deployed to VM1's Ollama

---

### A22) Costs

> See **A202) Cost Estimation** for detailed breakdown.

#### Cost Summary by Tier (Two VMs)

| Tier        | VM1 (Inf) | VM2 (Train) | APIs   | Total      | Use Case                        |
|-------------|-----------|-------------|--------|------------|---------------------------------|
| **Minimal** | 35h ($12) | 0h ($0)     | $0     | **$12/mo** | Chat only, no training          |
| **Light**   | 60h ($21) | 15h ($5)    | $0     | **$26/mo** | Regular use + occasional train  |
| **Medium**  | 90h ($32) | 30h ($10)   | $5     | **$47/mo** | Daily dev + weekly training     |
| **Heavy**   | 120h ($42)| 60h ($21)   | $5     | **$68/mo** | Full-time dev + active training |
| **Parallel**| 150h ($52)| 100h ($35)  | $10    | **$97/mo** | Both VMs running simultaneously |

#### All Costs are Variable (Pay-per-Use)

| Type         | Resource                | Cost        | Notes                          |
|--------------|-------------------------|-------------|--------------------------------|
| **Variable** | VM1 (tensordock-infer)  | $0.35/hr    | Only when chatting             |
| **Variable** | VM2 (tensordock-train)  | $0.35/hr    | Only when training             |
| **Variable** | OpenAI/Claude APIs      | Pay-per-use | Optional external models       |
| **Fixed**    | -                       | $0          | No 24/7 infrastructure needed  |

#### Cost by Product

| Product     | VM                   | Low     | High    | Notes                          |
|-------------|----------------------|---------|---------|--------------------------------|
| A00 Chat    | tensordock-inference | $12/mo  | $52/mo  | Open WebUI + Ollama            |
| A01 MyAI    | tensordock-training  | $0/mo   | $35/mo  | Training + MLflow (optional)   |

---








## A3) Tech Research

> Framework comparisons and benchmarks supporting stack choices.

### A30) LLM Model Comparison

```
Name                | Component   | Stack        | Purpose                        | Quality
────────────────────┼─────────────┼──────────────┼────────────────────────────────┼────────────
DeepSeek-Coder-v2   | Code LLM    | 14B Q4 ~10GB | Code generation                | ★★★★★
Llama 3.1           | General LLM | 8B Q4 ~6GB   | General chat                   | ★★★★☆
Mistral             | Fast LLM    | 7B Q4 ~5GB   | Fast inference                 | ★★★★☆
CodeLlama           | Code LLM    | 13B Q4 ~9GB  | Code (older)                   | ★★★☆☆
Qwen 2.5            | General LLM | 7B Q4 ~5GB   | Multilingual                   | ★★★★☆
```

### A31) GPU Provider Comparison

```
Name                | Component   | Stack        | Purpose                        | Cost/hr
────────────────────┼─────────────┼──────────────┼────────────────────────────────┼──────────
TensorDock ★        | GPU Cloud   | RTX 4090 24GB| Good availability (EU)         | $0.35
Vast.ai             | GPU Cloud   | RTX 4090 24GB| Variable availability          | $0.30-40
RunPod              | GPU Cloud   | RTX 4090 24GB| Good availability              | $0.44
Lambda Labs         | GPU Cloud   | A10G 24GB    | Limited availability           | $0.60
```

> **Our choice:** TensorDock (★) - Best price, good EU availability, RTX 4090 24GB.

### A32) Vector Database Comparison

```
Name                | Component   | Stack        | Purpose                        | Cost
────────────────────┼─────────────┼──────────────┼────────────────────────────────┼──────────
ChromaDB ★          | Vector DB   | SQLite       | Embedded, Open WebUI built-in  | FREE
pgvector            | Vector DB   | PostgreSQL   | Self-hosted, full SQL          | FREE
Pinecone            | Vector DB   | Managed      | Serverless, easy setup         | $0.08/1M
Weaviate            | Vector DB   | Self-host    | GraphQL, multimodal            | FREE
Qdrant              | Vector DB   | Self-host    | High performance, Rust         | FREE
```

> **Our choice:** ChromaDB (★) - Built into Open WebUI, no setup needed.

### A33) Embeddings Provider Comparison

```
Name                | Component   | Stack        | Purpose                        | Cost
────────────────────┼─────────────┼──────────────┼────────────────────────────────┼──────────
sentence-transform ★| Embeddings  | Local        | Open WebUI built-in, no cost   | FREE
OpenAI              | Embeddings  | text-embed-3 | Best quality, easy API         | $0.02/1M
Cohere              | Embeddings  | embed-v3     | Multilingual, good quality     | $0.10/1M
```

> **Our choice:** sentence-transformers (★) - Built into Open WebUI, runs locally on CPU, no API costs.

---







## A4) Today (Current State)

### A40) Current Status

```
Name                 | Component            | Stack                    | Status
─────────────────────┼──────────────────────┼──────────────────────────┼────────────────────────────────
; VM1: TENSORDOCK-INFERENCE (A00 Multi-Model)
tensordock-inference | GPU VM               | RTX 4090 24GB            | (pending) On-demand, not active
openwebui            | Chat UI + RAG        | VM1 :3000                | tbd
ollama-app           | LLM Server           | VM1 :11434               | tbd
deepseek-coder-v2    | Code Model           | Ollama (14B Q4)          | tbd
llama-3.1-8b         | General Model        | Ollama (8B Q4)           | tbd
mistral-7b           | Fast Model           | Ollama (7B Q4)           | tbd
                     |                      |                          |
; VM2: TENSORDOCK-TRAINING (A01 MyAI)
tensordock-training  | GPU VM               | RTX 4090 24GB            | (pending) On-demand, not active
myai-dashboard       | Dashboard            | VM2 :8080                | tbd
myai-api             | Backend              | VM2 :8000                | tbd
training-jobs        | Training Runner      | VM2 (PyTorch)            | tbd
mlflow-tracking      | Experiment Tracking  | VM2 :5001                | tbd
data-store           | Data Storage         | VM2 (pgvector)           | tbd
```

**Current Phase:** Planning complete, infrastructure not yet deployed.

> **Two Independent VMs:** Can run simultaneously (chat while training).
> - VM1: Open WebUI + Ollama (inference)
> - VM2: MyAI + Training stack (training)

### A41) Quick Reference

#### VM Access

```bash
# VM1: TensorDock Inference (on-demand)
ssh root@<tensordock-inference-ip>

# VM2: TensorDock Training (on-demand)
ssh root@<tensordock-training-ip>
```

#### Service URLs

| Service        | VM   | Port  | Status    | URL                         |
|----------------|------|-------|-----------|-----------------------------|
| openwebui      | VM1  | 3000  | On-demand | chat.diegonmarcos.com       |
| ollama         | VM1  | 11434 | On-demand | (internal)                  |
| myai-dashboard | VM2  | 8080  | On-demand | myai.diegonmarcos.com       |
| myai-api       | VM2  | 8000  | On-demand | myai.diegonmarcos.com/api   |
| mlflow         | VM2  | 5001  | On-demand | mlflow.diegonmarcos.com     |

#### Docker Compose - VM1 (Inference)

```yaml
# docker-compose.yml (tensordock-inference)
services:
  openwebui:
    image: ghcr.io/open-webui/open-webui:main
    ports:
      - "3000:8080"
    volumes:
      - ./data:/app/backend/data
    environment:
      - OLLAMA_BASE_URL=http://ollama:11434
    depends_on:
      - ollama

  ollama:
    image: ollama/ollama:latest
    ports:
      - "11434:11434"
    volumes:
      - ./ollama:/root/.ollama
    deploy:
      resources:
        reservations:
          devices:
            - driver: nvidia
              count: 1
              capabilities: [gpu]
```

#### Docker Compose - VM2 (Training)

```yaml
# docker-compose.yml (tensordock-training)
services:
  myai-dashboard:
    build: ./myai-dashboard
    ports:
      - "8080:8080"
    depends_on:
      - myai-api

  myai-api:
    build: ./myai-api
    ports:
      - "8000:8000"
    volumes:
      - ./data:/app/data
    environment:
      - DATABASE_URL=postgresql://postgres:postgres@pgvector:5432/myai

  mlflow:
    image: ghcr.io/mlflow/mlflow:latest
    ports:
      - "5001:5000"
    volumes:
      - ./mlflow:/mlflow
    command: mlflow server --host 0.0.0.0 --backend-store-uri sqlite:///mlflow/mlflow.db

  pgvector:
    image: pgvector/pgvector:pg16
    environment:
      POSTGRES_DB: myai
      POSTGRES_PASSWORD: postgres
    volumes:
      - ./pgdata:/var/lib/postgresql/data
```

#### Pull Models - VM1 (First Time)

```bash
# After docker compose up on VM1
docker exec -it ollama ollama pull deepseek-coder-v2:14b-instruct-q4_K_M
docker exec -it ollama ollama pull llama3.1:8b-instruct-q4_K_M
docker exec -it ollama ollama pull mistral:7b-instruct-q4_K_M
```

---

---

---

---

# B) Architecture - Technical Deep Dives

## B1) Model Architecture

### B11) Model Selection & Routing

```
┌─────────────────────────────────────────────────────────────────┐
│                      MODEL ROUTING FLOW                          │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  User Query → Open WebUI → Model Router                         │
│                               │                                 │
│               ┌───────────────┼───────────────┐                 │
│               ▼               ▼               ▼                 │
│         ┌──────────┐   ┌──────────┐   ┌──────────┐             │
│         │ DeepSeek │   │ Llama3.1 │   │ Mistral  │             │
│         │  Coder   │   │   8B     │   │   7B     │             │
│         │  (Code)  │   │ (General)│   │  (Fast)  │             │
│         └──────────┘   └──────────┘   └──────────┘             │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

**Routing Rules:**
| Query Type | Model | Why |
|------------|-------|-----|
| Code generation | DeepSeek Coder v2 | Best code quality |
| General chat | Llama 3.1 8B | Good balance |
| Quick answers | Mistral 7B | Fastest response |

### B12) RAG Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                      RAG PIPELINE                                │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  Documents → Chunking → Embeddings → Vector Store               │
│                              │                                  │
│                    sentence-transformers                        │
│                              │                                  │
│                              ▼                                  │
│  Query → Embed → Similarity Search → Top-K Chunks → LLM         │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

**RAG Config (Open WebUI built-in):**
- Embedding model: sentence-transformers (local)
- Chunk size: 1000 tokens
- Chunk overlap: 200 tokens
- Top-K retrieval: 5 chunks

---

## B2) Training Pipeline

### B21) MyAI Training Flow

```
┌─────────────────────────────────────────────────────────────────┐
│                      TRAINING PIPELINE                           │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. DATA COLLECTION                                             │
│     Local → Collectors → pgvector                               │
│                                                                 │
│  2. PREPROCESSING                                               │
│     Raw Data → Clean → Tokenize → Dataset                       │
│                                                                 │
│  3. TRAINING                                                    │
│     Dataset → PyTorch → Fine-tune → Checkpoints                 │
│         │                                                       │
│         └──→ MLflow (experiment tracking)                       │
│                                                                 │
│  4. EVALUATION                                                  │
│     Checkpoints → Eval Suite → Metrics → Dashboard              │
│                                                                 │
│  5. DEPLOYMENT                                                  │
│     Best Model → Export → Ollama/GGUF → Serve                   │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### B22) Experiment Tracking (MLflow)

| Metric | Description |
|--------|-------------|
| Loss | Training/validation loss curves |
| Perplexity | Model quality measure |
| BLEU/ROUGE | Text generation quality |
| Latency | Inference speed |
| Memory | GPU memory usage |

---

## B3) Infrastructure Architecture

### B31) GPU Provisioning

```
┌─────────────────────────────────────────────────────────────────┐
│                   ON-DEMAND GPU WORKFLOW                         │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  1. Request comes in (chat or training)                         │
│  2. Check if VM is running                                      │
│     ├── Running → Forward request                               │
│     └── Stopped → Provision VM via TensorDock API               │
│  3. Wait for VM ready (boot + docker up)                        │
│  4. Forward request                                             │
│  5. Auto-shutdown after idle timeout (30 min)                   │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### B32) Data Flow

```
Local Machine                    TensorDock VMs
─────────────                    ──────────────
  Documents ──┐
  Code repos ─┼──→ Collectors ──→ pgvector (VM2)
  Notes ──────┘                       │
                                      ▼
                              Embeddings + Metadata
                                      │
                    ┌─────────────────┴─────────────────┐
                    ▼                                   ▼
              VM1 (Inference)                    VM2 (Training)
              RAG queries                        Training data
```

---

# C) Roadmap - Planning & Prioritization

## C1) Phases - Implementation Milestones

### Phase 1: Basic Inference (PRIORITY)
**Status:** Planned
**Dependencies:** TensorDock account

| Step | Task | Status |
|------|------|--------|
| 1.1 | Create TensorDock account | Planned |
| 1.2 | Deploy VM1 with Docker | Planned |
| 1.3 | Setup Open WebUI + Ollama | Planned |
| 1.4 | Pull initial models | Planned |
| 1.5 | Test chat interface | Planned |

### Phase 2: RAG Integration
**Status:** Planned
**Dependencies:** Phase 1

| Step | Task | Status |
|------|------|--------|
| 2.1 | Configure document upload in Open WebUI | Planned |
| 2.2 | Test RAG with local documents | Planned |
| 2.3 | Tune chunk size and retrieval | Planned |

### Phase 3: Training Infrastructure
**Status:** Future
**Dependencies:** Phase 1

| Step | Task | Status |
|------|------|--------|
| 3.1 | Deploy VM2 with training stack | Future |
| 3.2 | Setup MLflow tracking | Future |
| 3.3 | Create data collection pipeline | Future |
| 3.4 | First fine-tuning experiment | Future |

### Phase 4: Custom Models
**Status:** Future
**Dependencies:** Phase 3

| Step | Task | Status |
|------|------|--------|
| 4.1 | Collect personal data corpus | Future |
| 4.2 | Fine-tune on personal data | Future |
| 4.3 | Deploy custom model to VM1 | Future |

---

## C2) Dependencies - Service Graph

```
┌─────────────────────────────────────────────────────────────────────┐
│                    AI SERVICE DEPENDENCY GRAPH                       │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  LAYER 0: CLOUD INFRASTRUCTURE (from MASTERPLAN_CLOUD)              │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐                             │
│  │   NPM   │  │Authelia │  │   DNS   │                             │
│  │ (proxy) │→ │  (auth) │→ │(Cloudfl)│                             │
│  └────┬────┘  └────┬────┘  └─────────┘                             │
│       │            │                                                │
│  LAYER 1: AI INFERENCE (VM1)                                        │
│       ▼            ▼                                                │
│  ┌─────────────────────────────────────────────┐                   │
│  │  TensorDock VM1                              │                   │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐  │                   │
│  │  │Open WebUI│→ │  Ollama  │→ │  Models  │  │                   │
│  │  └──────────┘  └──────────┘  └──────────┘  │                   │
│  └─────────────────────────────────────────────┘                   │
│                                                                     │
│  LAYER 2: AI TRAINING (VM2)                                         │
│  ┌─────────────────────────────────────────────┐                   │
│  │  TensorDock VM2                              │                   │
│  │  ┌──────────┐  ┌──────────┐  ┌──────────┐  │                   │
│  │  │  MyAI    │→ │  MLflow  │→ │ pgvector │  │                   │
│  │  └──────────┘  └──────────┘  └──────────┘  │                   │
│  └─────────────────────────────────────────────┘                   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## C3) Backlog - Prioritized Tasks

### High Priority (Now)
- [ ] Setup TensorDock account and billing
- [ ] Create VM1 deployment script
- [ ] Test Open WebUI + Ollama locally first
- [ ] Document model pull commands

### Medium Priority (Next)
- [ ] Configure RAG with personal documents
- [ ] Setup auto-shutdown script for idle VMs
- [ ] Create VM2 deployment script
- [ ] Setup MLflow tracking

### Low Priority (Later)
- [ ] Build data collection pipelines
- [ ] First fine-tuning experiment
- [ ] Custom model deployment
- [ ] Multi-model routing optimization

### Tech Debt
- [ ] Automate VM provisioning via API
- [ ] Create backup scripts for model weights
- [ ] Document training procedures
- [ ] Setup cost monitoring alerts

---

# D) DevOps - Operations & Observability

## D1) Dashboard - AI Services Access

```
┌─────────────────────────────────────────────────────────────┐
│                    AI SERVICES DASHBOARD                      │
├─────────────────────────────────────────────────────────────┤
│  [VM1 Status: OFF]  [VM2 Status: OFF]          [Start VM1]  │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  INFERENCE (VM1)                    TRAINING (VM2)          │
│  ┌─────────────────┐               ┌─────────────────┐     │
│  │  💬 Open WebUI  │               │  🧠 MyAI        │     │
│  │  status: off    │               │  status: off    │     │
│  │  [Launch]       │               │  [Launch]       │     │
│  └─────────────────┘               └─────────────────┘     │
│  ┌─────────────────┐               ┌─────────────────┐     │
│  │  🤖 Ollama      │               │  📊 MLflow      │     │
│  │  Models: 3      │               │  Experiments: 0 │     │
│  │  [Manage]       │               │  [View]         │     │
│  └─────────────────┘               └─────────────────┘     │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

---

## D2) Monitoring - Metrics & Alerts

### GPU Monitoring

| Metric | Warning | Critical | Action |
|--------|---------|----------|--------|
| GPU Temp | 75°C | 85°C | Throttle/shutdown |
| GPU Memory | 80% | 95% | Alert |
| GPU Utilization | - | - | Info only |
| VM Cost/day | $5 | $10 | Alert + auto-shutdown |

### Cost Alerts

```
┌─────────────────────────────────────────────────────────────────┐
│  COST MONITORING                                                 │
├─────────────────────────────────────────────────────────────────┤
│  Daily budget: $5.00                                            │
│  Monthly budget: $50.00                                         │
│                                                                 │
│  Alerts:                                                        │
│  - 50% daily budget → Email warning                             │
│  - 80% daily budget → Email alert                               │
│  - 100% daily budget → Auto-shutdown VMs                        │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

### Health Checks

| Service | Endpoint | Method | Expected |
|---------|----------|--------|----------|
| Open WebUI | :3000/health | GET | 200 |
| Ollama | :11434/api/tags | GET | 200 |
| MyAI API | :8000/health | GET | 200 |
| MLflow | :5001/health | GET | 200 |

---

## D3) Knowledge Center

### AI Documentation

| Document | Purpose | Location |
|----------|---------|----------|
| MASTERPLAN_AI.md | This document | 0.spec/ |
| Model Cards | Model capabilities & limits | docs/models/ |
| Training Guides | How to fine-tune | docs/training/ |
| RAG Setup | Document ingestion | docs/rag/ |

### Runbooks

| Runbook | Purpose |
|---------|---------|
| vm-start.sh | Start GPU VM on-demand |
| vm-stop.sh | Stop VM and save state |
| model-pull.sh | Pull new models to Ollama |
| backup-models.sh | Backup model weights |
| cost-check.sh | Check current spending |

### Quick Commands

```bash
# Start VM1 (Inference)
./scripts/vm-start.sh inference

# Start VM2 (Training)
./scripts/vm-start.sh training

# Check costs
./scripts/cost-check.sh

# Pull new model
docker exec ollama ollama pull <model-name>

# Stop all VMs
./scripts/vm-stop.sh all
```

---

*Generated by Claude (Opus) - CTO*
*Sub-document of: MASTERPLAN_CLOUD.md*
*Last Updated: 2025-12-11*
