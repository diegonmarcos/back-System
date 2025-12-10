# AI Infrastructure Master Plan

**Project:** Diego's AI/ML Brain System
**CTO:** Claude (Opus)
**Date:** 2025-12-10
**Status:** PLANNING

---

## Executive Summary

This master plan defines Diego's AI infrastructure through a multi-model orchestration system:

```
A) Services          - AI orchestration components
B) Infrastructure    - VM specifications (GPU + Free Tier)
C) Costs             - Monthly usage estimation
```

---

## A) Services - AI Orchestration System

```
Pattern: SERVICE → components + models + collectors

Container          | Purpose                              | Stack
───────────────────┼──────────────────────────────────────┼──────────────────────────
```

### AI Multi-Model System

```
ai-multimodel        | AI Orchestration System          | -
  ↳ tensordock-gpu   | DeepSeek 14B Inference          | TensorDock
    ↳ ollama-app     | LLM API Server                  | Ollama
    ↳ deepseek-model | Code LLM (14B Q4)               | DeepSeek-Coder-v2
  ↳ oracle-brain     | ML Brain Knowledge System       | Oracle Free
    ↳ brain-api      | Knowledge API Server            | Flask/Python
    ↳ brain-db       | Knowledge Database              | SQLite
    ↳ embeddings     | Vector Embeddings               | OpenAI API
  ↳ local-collect    | Data Collection (runs locally)  | -
    ↳ claude-collector | Claude Code logs              | Python
    ↳ browser-collector| Browser history              | Python
    ↳ files-collector  | Local code files             | Python
```

---

## B) Infrastructure

### GPU VM (TensorDock)

```
tensordock-vm        | GPU VM (Pay-per-use)            | -
  ↳ gpu              | RTX 4090 24GB VRAM              | NVIDIA
  ↳ cpu              | 4 vCPU                          | x86_64
  ↳ ram              | 16 GB                           | DDR4
  ↳ storage          | 70 GB SSD                       | NVMe
  ↳ location         | EU (DE/FR/NL)                   | TensorDock
  ↳ cost             | $0.35/hr                        | Pay-per-use
```

### Brain VM (Oracle Free)

```
oracle-free-vm       | ARM VM (Always Free)            | -
  ↳ cpu              | 4 OCPU ARM64                    | Ampere
  ↳ ram              | 24 GB                           | DDR4
  ↳ storage          | 100 GB                          | Block
  ↳ location         | eu-frankfurt-1                  | Oracle
  ↳ cost             | $0/mo                           | Free Tier
```

### Infrastructure Diagram

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        AI INFRASTRUCTURE                                  │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────────────────┐     ┌─────────────────────────────┐   │
│  │    LOCAL MACHINE            │     │    TENSORDOCK GPU VM        │   │
│  │                             │     │    RTX 4090 24GB            │   │
│  │  • claude-collector         │     │                             │   │
│  │  • browser-collector        │     │  ┌───────────────────────┐  │   │
│  │  • files-collector          │────▶│  │  Ollama + DeepSeek    │  │   │
│  │                             │     │  │  14B Q4 Inference     │  │   │
│  └─────────────────────────────┘     │  └───────────────────────┘  │   │
│                │                     │                             │   │
│                │                     │  $0.35/hr (on-demand)       │   │
│                │                     └──────────────┬──────────────┘   │
│                │                                    │                  │
│                ▼                                    ▼                  │
│  ┌─────────────────────────────────────────────────────────────────┐  │
│  │              ORACLE FREE ARM VM (24GB RAM)                       │  │
│  │              eu-frankfurt-1 | 4 OCPU Ampere                      │  │
│  │                                                                  │  │
│  │  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐  │  │
│  │  │   brain-api     │  │    brain-db     │  │   embeddings    │  │  │
│  │  │   Flask/Python  │  │     SQLite      │  │   OpenAI API    │  │  │
│  │  └─────────────────┘  └─────────────────┘  └─────────────────┘  │  │
│  │                                                                  │  │
│  │  24/7 FREE TIER                                                  │  │
│  └─────────────────────────────────────────────────────────────────┘  │
│                                                                         │
└─────────────────────────────────────────────────────────────────────────┘
```

---

## C) Costs (Monthly)

```
costs                | Total Monthly                   | -
  ↳ gpu-weekend      | 32h x $0.35                     | $11/mo
  ↳ gpu-light        | 60h x $0.35                     | $21/mo
  ↳ gpu-medium       | 120h x $0.35                    | $42/mo
  ↳ oracle-brain     | Always Free                     | $0/mo
  ↳ embeddings-api   | ~30k items                      | ~$1/mo
```

### Cost Tiers Summary

| Usage Pattern | GPU Hours/mo | GPU Cost | Oracle | Embeddings | **Total** |
|---------------|--------------|----------|--------|------------|-----------|
| **Weekend**   | 32h (8h x 4) | $11      | $0     | $1         | **$12/mo** |
| **Light**     | 60h          | $21      | $0     | $1         | **$22/mo** |
| **Medium**    | 120h         | $42      | $0     | $1         | **$43/mo** |

---

## Data Flow

```
┌──────────────────────────────────────────────────────────────────────┐
│                           DATA FLOW                                    │
├──────────────────────────────────────────────────────────────────────┤
│                                                                      │
│  LOCAL COLLECTORS                                                    │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │ claude-collector → Claude Code session logs                  │    │
│  │ browser-collector → Browser history (Chrome/Firefox)         │    │
│  │ files-collector → Local code files (.py, .ts, .md, etc)      │    │
│  └─────────────────────────────────┬───────────────────────────┘    │
│                                    │                                 │
│                                    ▼                                 │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │                    ORACLE BRAIN VM                           │    │
│  │                                                              │    │
│  │  1. Raw data → brain-api (Flask)                             │    │
│  │  2. Text → embeddings (OpenAI API)                           │    │
│  │  3. Vectors + metadata → brain-db (SQLite)                   │    │
│  │                                                              │    │
│  └─────────────────────────────────┬───────────────────────────┘    │
│                                    │                                 │
│                                    ▼                                 │
│  ┌─────────────────────────────────────────────────────────────┐    │
│  │                   TENSORDOCK GPU VM                          │    │
│  │                   (On-demand inference)                      │    │
│  │                                                              │    │
│  │  Query → Retrieve relevant context → DeepSeek inference      │    │
│  │                                                              │    │
│  └─────────────────────────────────────────────────────────────┘    │
│                                                                      │
└──────────────────────────────────────────────────────────────────────┘
```

---

## Quick Reference

### VM Access

```bash
# Oracle Brain VM (24/7)
ssh -i ~/.ssh/oci_arm ubuntu@<oracle-arm-ip>

# TensorDock GPU VM (on-demand)
ssh root@<tensordock-ip>
```

### Service URLs

| Service | Location | Port | Status |
|---------|----------|------|--------|
| brain-api | Oracle ARM | 5000 | 24/7 |
| ollama-app | TensorDock | 11434 | On-demand |

---

*Generated by Claude (Opus) - CTO*
*Last Updated: 2025-12-10*
