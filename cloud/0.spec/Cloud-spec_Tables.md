# Cloud Dashboard - Frontend Specification

> **Document Type**: Frontend Design Specification
> **Parent Document**: Cloud-spec_.md (Main Specification)
> **Data Source**: cloud_dash.json (cloud-infrastructure.json)
> **Version**: 3.2.0 | **Updated**: 2025-12-04

## Overview

This document specifies the **frontend structure** of the Cloud Dashboard. It serves as:

1. **Design Blueprint**: Defines the UI layout, views, and components
2. **Mermaid Source of Truth**: Contains authoritative Mermaid diagrams for architecture visualization
3. **Data Mapping**: Specifies which JSON fields populate which UI elements

### Relationship to Other Documents

```
Cloud-spec_.md (Main Spec)
├── Sections 1-14: Infrastructure, Security, Network, API
├── Section 15: Dashboard Architecture (Flask API ↔ JS ↔ HTML)
└── Section 16: Frontend Views (references THIS document)

Cloud-spec_Tables.md (THIS FILE)
├── Page Structure: index.html navigation
├── Services Views: Front/Back, Cards/Lists
├── Architecture Views: Mermaid diagrams
└── Monitoring Views: Status tables and trees

cloud_dash.json
└── Data consumed by both Flask API and frontend JS
```

---








# Index.html
- Services
    - Cards Front
    - Cards Back

- Architeture
    - Resources
    - Server
    - AI

- Monitoring
    - Backlog
    - Status (Tree)
    - Status (List)






---





# Services
## Cards

Front
`3 collumns  User vs Coder vs AI`
    User
    - Sync
    - Mail
    - VPN

    Coder
    - Web IDE (OS_Shell|Flask)
    - Gitlab
    - Analytics

    AI
    - AI WebChat
    - AI CLI



Back
    `2 collumns Root vs Infra`
    Root
    - Cloud Providers (CLI SSH)
        - OCloud-Management
        - Gcloud_Management

    - VMs (SSH)
        - SSH-VM-Oracle_Services_Serv
        - SSH-VM-Oracle_Web_Server_1
        - SSH-VM-Oracle_Flex_ARM_Server
        - SSH-VM-GCloud_microe2Linux_1
        - SSH-VM-Generic_VPS_0_Infra
        - SSH-VM-Generic_VPS_1_AI

    Infra
    - User Services (SSH)
        - sync-app
        - mail-app
        - vpn-app
        - terminal-app
        - git-app
        - analytics-app

    - Data Bases (SSH)
        - sync-index-db
        - sync-files-db
        - sync-obj-db
        - mail-db
        - git-db
        - git-repos
        - analytics-db
        - cloud-db
        - n8n-ai-db
        - n8n-infra-db

    - Infra Services (SSH)
        - n8n-ai-app
        - n8n-infra-app
        - cloud-api
        - cache-app

    - Proxies (Web and SSH)
        - npm-oracle-services
        - npm-oracle-web
        - npm-oracle-arm
        - npm-gcloud










---













---





# Architeture

## Resources

    User
    - Sync
    - Mail
    - VPN

    Coder
    - Web IDE (OS_Shell|Flask)
    - Gitlab
    - Analytics

    AI
    - AI WebChat
    - AI CLI


### User and Coder

#### Services

##### User

| Mode | Service | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|------|---------|-----------|---------------|-----------------|-------|
| on | **sync** | **128-256 MB** | **5.2-106 GB** | **10-50 GB/mo** | Syncthing file sync |
|  | ↳ sync-app | 128-256 MB | 100-500 MB | 10-50 GB/mo | App + config |
|  | ↳ sync-index-db | - | 100-500 MB | - | File metadata index |
|  | ↳ sync-files-db | - | ~100 GB | - | Synced files storage |
|  | ↳ sync-obj-db | - | ~5 GB | - | Object/blob storage |
| dev | **mail** | **520 MB-1 GB** | **5-50 GB** | **1-10 GB/mo** | Email stack |
|  | ↳ mail-app | 512 MB - 1 GB | 100-500 MB | 1-10 GB/mo | App + config |
|  | ↳ mail-db | 8-32 MB | 5-50 GB | - | SQLite - Mailboxes + indexes |
| dev | **vpn** | **64-128 MB** | **50-100 MB** | **5-50 GB/mo** | OpenVPN server |
|  | ↳ vpn-app | 64-128 MB | 50-100 MB | 5-50 GB/mo | Client configs + certs |




##### Coder

| Mode | Service | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|------|---------|-----------|---------------|-----------------|-------|
| dev | **terminal** | **64-128 MB** | **50-100 MB** | **500 MB-2 GB/mo** | Web terminal |
|  | ↳ terminal-app | 64-128 MB | 50-100 MB | 500 MB-2 GB/mo | wetty/ttyd session-based |
| on | **cloud** | **64-128 MB** | **55-105 MB** | **150-700 MB/mo** | Cloud Dashboard |
|  | ↳ cloud-app | - | ~5 MB | 50-200 MB/mo | Static HTML/CSS/JS |
|  | ↳ cloud-api | 64-128 MB | 50-100 MB | 100-500 MB/mo | Flask API server |
| on | **analytics** | **512 MB-1 GB** | **3-15 GB** | **500 MB-2 GB/mo** | Matomo Analytics platform |
|  | ↳ analytics-app | 256-512 MB | 2-5 GB | 500 MB-2 GB/mo | PHP FPM Alpine |
|  | ↳ analytics-db | 256-512 MB | 1-10 GB | - | MariaDB - grows with data |
| dev | **git** | **264-544 MB** | **11-15 GB** | **2-10 GB/mo** | Gitea hosting |
|  | ↳ git-app | 256-512 MB | 1-5 GB | 2-10 GB/mo | Web + Git server |
|  | ↳ git-db | 8-32 MB | Variable | - | SQLite embedded |
|  | ↳ git-repos | - | ~10 GB | - | Git repositories storage |
| on | **n8n-infra** | **256-512 MB** | **500 MB-2 GB** | **1-5 GB/mo** | Workflow automation |
|  | ↳ n8n-infra-app | 256-512 MB | 500 MB - 2 GB | 1-5 GB/mo | Workflows + execution logs |
| on | **npm** | **512 MB-1 GB** | **400 MB-2 GB** | **20-80 GB/mo** | Reverse proxy (4 instances) |
|  | ↳ npm-oracle-web | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Web Server 1 |
|  | ↳ npm-oracle-services | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Services Server 1 |
|  | ↳ npm-oracle-arm | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle ARM (hold) |
|  | ↳ npm-gcloud | 128-256 MB | 100-500 MB | 5-20 GB/mo | GCloud (dev) |
| dev | **cache** | **64-256 MB** | **100 MB-1 GB** | **-** | Redis in-memory store |
|  | ↳ cache-app | 64-256 MB | 100 MB - 1 GB | - | Session/cache data |


Totals

| | | RAM | Storage | Bandwidth | |
|------|---------|-----------|---------------|-----------------|-------|
| | **Total ON** | **~1.4-2.8 GB** | **~9-125 GB** | **~32-135 GB/mo** | Active services |
| | **Total DEV** | **~900 MB-1.8 GB** | **~66-165 GB** | **~8-72 GB/mo** | In development |
| | **Total HOLD** | **~64-256 MB** | **~100 MB-1 GB** | **-** | On hold |
| | **TOTAL Non-AI** | **~2.4-4.9 GB** | **~75-291 GB** | **~40-207 GB/mo** | All Non-AI services |

#### VMs

| Mode | VM | Services | Total RAM (Est) | Total Storage (Est) | Bandwidth (Est) |
|--------|-----|----------|-----------------|---------------------|-----------------|
| on | Oracle Web Server 1 | n8n-infra-app, sync-app, cloud-app, cloud-api, npm-oracle-web, vpn-app, git-app, cache-app | ~800 MB - 1.5 GB | ~5-15 GB | ~20-80 GB/mo |
| on | Oracle Services Server 1 | analytics-app, analytics-db, cloud-db, npm-oracle-services | ~600 MB - 1.2 GB | ~5-15 GB | ~5-20 GB/mo |
| dev | GCloud Arch 1 | mail-app, mail-db, terminal-app, npm-gcloud | ~800 MB - 1.5 GB | ~10-50 GB | ~5-15 GB/mo |
| tbd | Generic VPS | Variable services | ~1-4 GB | ~20-100 GB | ~10-50 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total ON** | | **~1.4-2.7 GB** | **~10-30 GB** | **~25-100 GB/mo** |
| | **Total DEV** | | **~1.8-5.5 GB** | **~30-150 GB** | **~15-65 GB/mo** |
| | **TOTAL Non-AI** | | **~3.2-8.2 GB** | **~40-180 GB** | **~40-165 GB/mo** |



### AI
#### Services

| Mode | Service | Category | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| hold | **n8n-ai** | ML | **1.3-48 GB** | **3-20 GB** | **5-20 GB/mo** | AI Agentic workflows |
|  | ↳ n8n-ai-app | | 1-48 GB | 2-10 GB | 5-20 GB/mo | LLM context + workflows |
|  | ↳ n8n-ai-db | | 256-512 MB | 1-10 GB | - | PostgreSQL - varies by usage |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| | **Total HOLD** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | On hold (ARM 6-24GB avail) |
| | **TOTAL AI** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | All AI services |


#### VMs

| Mode | VM | Services | Total RAM (Est) | Total Storage (Est) | Bandwidth (Est) |
|--------|-----|----------|-----------------|---------------------|-----------------|
| hold | Oracle ARM Server | n8n-ai-app, n8n-ai-db, npm-oracle-arm | ~6-24 GB | ~5-20 GB | ~10-40 GB/mo |
| tbd | Generic VPS (AI) | LLM inference, AI workloads | ~8-32 GB | ~50-200 GB | ~20-100 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total HOLD** | | **~6-24 GB** | **~5-20 GB** | **~10-40 GB/mo** |
| | **Total TBD** | | **~8-32 GB** | **~50-200 GB** | **~20-100 GB/mo** |
| | **TOTAL AI** | | **~14-56 GB** | **~55-220 GB** | **~30-140 GB/mo** |



## Servers

`use the .html that already exists, dont lose it!! arch.html`

`(add here mermaid code of the architeture design)`

## AI
 `   (add here mermaid code of ach design) `
`use the .html that already exists, dont lose it!! ai-arch.html`




---


# Monitoring
## Status (list)

`Cloud_Dashboard.py from flask`

`htop to retrieve RAM Usage`

In Web:
`IP:port click to copy`
`| URL| buttom to clikc and open in a new window `
`SSH made a buttom to just copy the data`

In the Srcipt:
`IP:port keep visible`
`| URL| keep visible `
`SSH keep visible`

##### User Services

| Mode | Service | IP:port | URL | SSH | RAM | Storage | Status |
|------|---------|---------|-----|-----|-----|---------|--------|
| on | **sync-app** | 130.110.251.193:8384 | sync.diegonmarcos.com | ssh ubuntu@130.110.251.193 | 128-256 MB | 5-106 GB | on |
| dev | **mail-app** | [pending]:25,587 | mail.diegonmarcos.com | gcloud compute ssh arch-1 | 520 MB-1 GB | 5-50 GB | dev |
| dev | **vpn-app** | 130.110.251.193:1194 | - | ssh ubuntu@130.110.251.193 | 64-128 MB | 50-100 MB | dev |

##### Coder Services

| Mode | Service | IP:port | URL | SSH | RAM | Storage | Status |
|------|---------|---------|-----|-----|-----|---------|--------|
| dev | **terminal-app** | [pending]:7681 | terminal.diegonmarcos.com | gcloud compute ssh arch-1 | 64-128 MB | 50-100 MB | dev |
| dev | **git-app** | 130.110.251.193:3000 | git.diegonmarcos.com | ssh ubuntu@130.110.251.193 | 264-544 MB | 11-15 GB | dev |
| on | **analytics-app** | 129.151.228.66:8080 | analytics.diegonmarcos.com | ssh ubuntu@129.151.228.66 | 512 MB-1 GB | 3-15 GB | on |

##### Infra Services

| Mode | Service | IP:port | URL | SSH | RAM | Storage | Status |
|------|---------|---------|-----|-----|-----|---------|--------|
| on | **n8n-infra-app** | 130.110.251.193:5678 | n8n.diegonmarcos.com | ssh ubuntu@130.110.251.193 | 256-512 MB | 500 MB-2 GB | on |
| hold | **n8n-ai-app** | [pending]:5678 | ai.diegonmarcos.com | ssh ubuntu@[ARM IP] | 1-48 GB | 3-20 GB | hold |
| on | **cloud-api** | 130.110.251.193:5000 | dashboard.diegonmarcos.com | ssh ubuntu@130.110.251.193 | 64-128 MB | 50-100 MB | on |
| hold | **cache-app** | 130.110.251.193:6379 | - | ssh ubuntu@130.110.251.193 | 64-256 MB | 100 MB-1 GB | hold |

##### Proxies (NPM)

| Mode | Service | IP:port | URL | SSH | RAM | Storage | Status |
|------|---------|---------|-----|-----|-----|---------|--------|
| on | **npm-oracle-services** | 129.151.228.66:81 | - | ssh ubuntu@129.151.228.66 | 128-256 MB | 100-500 MB | on |
| on | **npm-oracle-web** | 130.110.251.193:81 | - | ssh ubuntu@130.110.251.193 | 128-256 MB | 100-500 MB | on |
| hold | **npm-oracle-arm** | [pending]:81 | - | ssh ubuntu@[ARM IP] | 128-256 MB | 100-500 MB | hold |
| dev | **npm-gcloud** | [pending]:81 | - | gcloud compute ssh arch-1 | 128-256 MB | 100-500 MB | dev |
| tbd | **npm-generic-vps** | [pending]:81 | - | - | 128-256 MB | 100-500 MB | tbd |

##### VMs

| Mode | VM | IP | SSH | Services | RAM | Storage | Status |
|------|----|----|-----|----------|-----|---------|--------|
| on | oracle-web-server-1 | 130.110.251.193 | ssh ubuntu@130.110.251.193 | n8n-infra-app, sync-app, cloud-api, npm-oracle-web, vpn-app, git-app, cache-app | 800 MB-1.5 GB | 5-15 GB | on |
| on | oracle-services-server-1 | 129.151.228.66 | ssh ubuntu@129.151.228.66 | analytics-app, analytics-db, cloud-db, npm-oracle-services | 600 MB-1.2 GB | 5-15 GB | on |
| hold | oracle-arm-server | [pending] | ssh ubuntu@[ARM IP] | n8n-ai-app, n8n-ai-db, npm-oracle-arm | 6-24 GB | 5-20 GB | hold |
| dev | gcloud-arch-1 | [pending] | gcloud compute ssh arch-1 | mail-app, mail-db, terminal-app, npm-gcloud | 800 MB-1.5 GB | 10-50 GB | dev |
| tbd | generic-vps-infra | [pending] | - | TBD | 1-4 GB | 20-100 GB | tbd |
| tbd | generic-vps-ai | [pending] | - | TBD | 8-32 GB | 50-200 GB | tbd |



## Status (Tree)

`in tree view only show one card under each and if is healthy or off plus the name of it and a buttom to copy ssh command and/or link to url admin`

### Mermaid Baseline (Source of Truth)

```mermaid
graph TD
    subgraph IaaS["IaaS - Self-Hosted VPS"]

        subgraph GCloud["Google Cloud"]
            GCloud_CLI["gcloud CLI"]
            subgraph VM_GCloud["VM: gcloud-arch-1"]
                GC_NPM["npm-gcloud"]
                subgraph GC_Services["Services"]
                    GC_Mail["mail-app"]
                    GC_WebIDE["terminal-app"]
                end
                subgraph GC_Data["Data Stores"]
                    GC_MailDB["mail-db"]
                end
            end
        end

        subgraph Oracle["Oracle Cloud"]
            OCI_CLI["oci CLI"]

            subgraph VM_Web["VM: oracle-web-server-1"]
                OW_NPM["npm-oracle-web"]
                subgraph OW_Services["Services"]
                    OW_Sync["sync-app"]
                    OW_n8n["n8n-infra-app"]
                    OW_Flask["cloud-api"]
                    OW_Gitea["git-app"]
                    OW_VPN["vpn-app"]
                    OW_Redis["cache-app"]
                end
                subgraph OW_Data["Data Stores"]
                    OW_SyncDB["sync-index-db"]
                    OW_GiteaDB["git-db"]
                    OW_n8nDB["n8n-infra-db"]
                end
                subgraph OW_Front["Frontends"]
                    OW_Dashboard["cloud-app"]
                end
            end

            subgraph VM_Services["VM: oracle-services-server-1"]
                OS_NPM["npm-oracle-services"]
                subgraph OS_Services["Services"]
                    OS_Matomo["analytics-app"]
                end
                subgraph OS_Data["Data Stores"]
                    OS_MatomoDB["analytics-db"]
                    OS_DashDB["cloud-db"]
                end
            end

            subgraph VM_ARM["VM: oracle-arm-server"]
                OA_NPM["npm-oracle-arm"]
                subgraph OA_Services["Services"]
                    OA_n8nAI["n8n-ai-app"]
                end
                subgraph OA_Data["Data Stores"]
                    OA_n8nDB["n8n-ai-db"]
                end
            end
        end

        subgraph Generic["Generic VPS (TBD)"]
            subgraph VM_Infra["VM: generic-vps-infra"]
                GI_NPM["npm-generic-vps"]
                GI_Services["Services TBD"]
                GI_Data["Data TBD"]
            end
            subgraph VM_AI["VM: generic-vps-ai"]
                GA_NPM["NPM Proxy"]
                GA_Services["Services TBD"]
                GA_Data["Data TBD"]
            end
        end
    end

    subgraph PaaS["PaaS - Pay-per-Use"]
        subgraph PyHost["Python Hosting"]
            Streamlit
            Railway
        end
        subgraph AIaaS["AI Services"]
            HuggingFace["HuggingFace"]
            Groq
            Modal
        end
    end
```

### Tree Structure (derived from Mermaid)

```
Cloud Infrastructure
├── IaaS (Self-Hosted VPS)
│   │
│   ├── Google Cloud
│   │   ├── [CLI] gcloud
│   │   └── VM: gcloud-arch-1 [dev]
│   │       ├── npm-gcloud [dev]
│   │       ├── Services
│   │       │   ├── mail-app [dev]
│   │       │   └── terminal-app [dev]
│   │       └── Data
│   │           └── mail-db [dev]
│   │
│   ├── Oracle Cloud
│   │   ├── [CLI] oci
│   │   │
│   │   ├── VM: oracle-web-server-1 [on]
│   │   │   ├── npm-oracle-web [on]
│   │   │   ├── Services
│   │   │   │   ├── sync-app [on]
│   │   │   │   ├── n8n-infra-app [on]
│   │   │   │   ├── cloud-api [on]
│   │   │   │   ├── git-app [dev]
│   │   │   │   ├── vpn-app [dev]
│   │   │   │   └── cache-app [hold]
│   │   │   ├── Data
│   │   │   │   ├── sync-index-db [on]
│   │   │   │   ├── git-db [dev]
│   │   │   │   └── n8n-infra-db [on]
│   │   │   └── Frontends
│   │   │       └── cloud-app [on]
│   │   │
│   │   ├── VM: oracle-services-server-1 [on]
│   │   │   ├── npm-oracle-services [on]
│   │   │   ├── Services
│   │   │   │   └── analytics-app [on]
│   │   │   └── Data
│   │   │       ├── analytics-db [on]
│   │   │       └── cloud-db [dev]
│   │   │
│   │   └── VM: oracle-arm-server [hold]
│   │       ├── npm-oracle-arm [hold]
│   │       ├── Services
│   │       │   └── n8n-ai-app [hold]
│   │       └── Data
│   │           └── n8n-ai-db [hold]
│   │
│   └── Generic VPS (TBD)
│       ├── VM: generic-vps-infra [tbd]
│       │   ├── npm-generic-vps
│       │   ├── Services (TBD)
│       │   └── Data (TBD)
│       └── VM: generic-vps-ai [tbd]
│           ├── NPM Proxy
│           ├── Services (TBD)
│           └── Data (TBD)
│
└── PaaS (Pay-per-Use)
    ├── Python Hosting
    │   ├── Streamlit
    │   └── Railway/Render
    └── AI Services
        ├── HuggingFace Spaces/API
        ├── Groq
        ├── Modal/RunPod
        └── Together AI/OpenRouter
```


## Backlog




---


# Architecture Reference Tables

## Service Registry (Master List)

| Service ID | Display Name | Category | VM | Docker Network | Status |
|------------|--------------|----------|-----|----------------|--------|
| sync-app | Syncthing | user | oracle-web-server-1 | web_network | on |
| mail-app | Mail Server | user | gcloud-arch-1 | mail_network | dev |
| vpn-app | OpenVPN | user | oracle-web-server-1 | web_network | dev |
| terminal-app | Web Terminal | coder | gcloud-arch-1 | bridge | dev |
| cloud-app | Cloud Dashboard | coder | oracle-web-server-1 | - | on |
| cloud-api | Cloud API | infra-services | oracle-web-server-1 | web_network | dev |
| analytics-app | Matomo Analytics | coder | oracle-services-server-1 | matomo_network | on |
| git-app | Gitea | coder | oracle-web-server-1 | web_network | dev |
| n8n-infra-app | n8n (Infra) | infra-services | oracle-web-server-1 | web_network | on |
| n8n-ai-app | n8n (AI) | ai | oracle-arm-server | ai_network | hold |
| cache-app | Redis Cache | infra-services | oracle-web-server-1 | web_network | dev |
| npm-oracle-web | NPM (Oracle Web) | infra-proxy | oracle-web-server-1 | web_network | on |
| npm-oracle-services | NPM (Oracle Services) | infra-proxy | oracle-services-server-1 | matomo_network | on |
| npm-oracle-arm | NPM (Oracle ARM) | infra-proxy | oracle-arm-server | ai_network | hold |
| npm-gcloud | NPM (GCloud) | infra-proxy | gcloud-arch-1 | mail_network | dev |

## Database Registry

| DB ID | Display Name | Technology | Parent Service | VM | Status |
|-------|--------------|------------|----------------|-----|--------|
| sync-index-db | Sync Index DB | LevelDB (embedded) | sync-app | oracle-web-server-1 | on |
| sync-files-db | Sync Files | File Storage | sync-app | oracle-web-server-1 | on |
| sync-obj-db | Sync Objects | Blob Storage | sync-app | oracle-web-server-1 | on |
| analytics-db | Matomo DB | MariaDB 11.4 | analytics-app | oracle-services-server-1 | on |
| cloud-db | Cloud Dashboard DB | SQLite/PostgreSQL | cloud-api | oracle-services-server-1 | dev |
| git-db | Gitea DB | SQLite | git-app | oracle-web-server-1 | dev |
| git-repos | Git Repositories | File Storage | git-app | oracle-web-server-1 | dev |
| mail-db | Mail DB | SQLite | mail-app | gcloud-arch-1 | dev |
| n8n-infra-db | n8n Infra DB | SQLite | n8n-infra-app | oracle-web-server-1 | on |
| n8n-ai-db | n8n AI DB | PostgreSQL | n8n-ai-app | oracle-arm-server | hold |

## VM Specifications

| VM ID | Provider | Instance Type | CPU | RAM | Storage | OS | Status |
|-------|----------|---------------|-----|-----|---------|-----|--------|
| oracle-web-server-1 | Oracle | VM.Standard.E2.1.Micro | 1 OCPU (AMD) | 1 GB | 47 GB | Ubuntu 24.04 | on |
| oracle-services-server-1 | Oracle | VM.Standard.E2.1.Micro | 1 OCPU (AMD) | 1 GB | 47 GB | Ubuntu 24.04 | on |
| oracle-arm-server | Oracle | VM.Standard.A1.Flex | 4 OCPU (ARM64) | 24 GB | 200 GB | Ubuntu 24.04 | hold |
| gcloud-arch-1 | GCloud | e2-micro | 0.25-2 vCPU | 1 GB | 30 GB | Arch Linux | dev |
| generic-vps-infra | TBD | TBD | TBD | 1-4 GB | 20-100 GB | TBD | tbd |
| generic-vps-ai | TBD | TBD | TBD | 8-32 GB | 50-200 GB | TBD | tbd |

## Network Configuration

### Public IPs

| VM | Public IP | Private IP | SSH Command |
|----|-----------|------------|-------------|
| oracle-web-server-1 | 130.110.251.193 | 10.0.0.x | `ssh ubuntu@130.110.251.193` |
| oracle-services-server-1 | 129.151.228.66 | 10.0.0.x | `ssh ubuntu@129.151.228.66` |
| oracle-arm-server | [pending] | [pending] | `ssh ubuntu@[ARM IP]` |
| gcloud-arch-1 | [pending] | [pending] | `gcloud compute ssh arch-1` |

### Docker Networks per VM

| VM | Network Name | Subnet | Purpose |
|----|--------------|--------|---------|
| oracle-web-server-1 | web_network | 172.20.0.0/24 | Main services (n8n, sync, git, vpn, cache) |
| oracle-services-server-1 | matomo_network | 172.21.0.0/24 | Analytics stack |
| oracle-arm-server | ai_network | 172.22.0.0/24 | AI services |
| gcloud-arch-1 | mail_network | 172.23.0.0/24 | Email stack |

### Firewall Rules Summary

| VM | External Ports | Internal Ports |
|----|----------------|----------------|
| oracle-web-server-1 | 22, 80, 443, 81, 22000, 21027, 1194, 2222 | 5678, 8384, 5000, 3000 |
| oracle-services-server-1 | 22, 80, 443, 81 | 8080, 3306 |
| oracle-arm-server | 22, 80, 443, 81 | 5678 |
| gcloud-arch-1 | 22, 80, 443, 81, 25, 587, 993 | 8025 |

## Domain Routing

| Domain | Service | VM | IP | SSL | Status |
|--------|---------|-----|-----|-----|--------|
| analytics.diegonmarcos.com | analytics-app | oracle-services-server-1 | 129.151.228.66 | ✓ | on |
| sync.diegonmarcos.com | sync-app | oracle-web-server-1 | 130.110.251.193 | ✓ | on |
| n8n.diegonmarcos.com | n8n-infra-app | oracle-web-server-1 | 130.110.251.193 | ✓ | on |
| cloud.diegonmarcos.com | cloud-app | oracle-web-server-1 | 130.110.251.193 | ✓ | on |
| git.diegonmarcos.com | git-app | oracle-web-server-1 | 130.110.251.193 | ✓ | dev |
| ai.diegonmarcos.com | n8n-ai-app | oracle-arm-server | [pending] | ✓ | hold |
| mail.diegonmarcos.com | mail-app | gcloud-arch-1 | [pending] | ✓ | dev |

## Port Mapping Reference

| Service | Internal Port | External Port | Protocol | Notes |
|---------|---------------|---------------|----------|-------|
| npm-* | 81 | 81 | TCP | Admin UI |
| npm-* | 80 | 80 | TCP | HTTP redirect |
| npm-* | 443 | 443 | TCP | HTTPS termination |
| n8n-infra-app | 5678 | 443 (via NPM) | HTTPS | Workflow UI |
| n8n-ai-app | 5678 | 443 (via NPM) | HTTPS | AI Workflow UI |
| sync-app | 8384 | 443 (via NPM) | HTTPS | Sync GUI |
| sync-app | 22000 | 22000 | TCP | Sync protocol |
| sync-app | 21027 | 21027 | UDP | Discovery |
| analytics-app | 8080 | 443 (via NPM) | HTTPS | Analytics UI |
| git-app | 3000 | 443 (via NPM) | HTTPS | Git Web UI |
| git-app | 2222 | 2222 | TCP | Git SSH |
| vpn-app | 1194 | 1194 | UDP | VPN tunnel |
| mail-app | 25 | 25 | TCP | SMTP |
| mail-app | 587 | 587 | TCP | Submission |
| mail-app | 993 | 993 | TCP | IMAPS |
| cache-app | 6379 | - | TCP | Internal only |
| cloud-api | 5000 | - | TCP | Internal only |

## Docker Images

| Service | Image | Version |
|---------|-------|---------|
| analytics-app | matomo:fpm-alpine | latest |
| analytics-db | mariadb | 11.4 |
| sync-app | syncthing/syncthing | latest |
| n8n-infra-app | n8nio/n8n | latest |
| n8n-ai-app | n8nio/n8n | latest |
| git-app | gitea/gitea | latest |
| mail-app | docker-mailserver/docker-mailserver | latest |
| vpn-app | kylemanna/openvpn | latest |
| cache-app | redis | alpine |
| npm-* | jc21/nginx-proxy-manager | latest |

## Cloud Provider Summary

| Provider | Tier | Region | Console URL | CLI |
|----------|------|--------|-------------|-----|
| Oracle Cloud | Always Free | eu-marseille-1 | cloud.oracle.com | `oci` |
| Google Cloud | Free Tier | us-central1 | console.cloud.google.com | `gcloud` |

## Service Categories

| Category ID | Name | Description | Services |
|-------------|------|-------------|----------|
| user | User Services | End-user productivity | sync-app, mail-app, vpn-app |
| coder | Coder Services | Developer tools | terminal-app, cloud-app, analytics-app, git-app |
| ai | AI Services | AI and automation | n8n-ai-app |
| infra-proxy | Proxies | Nginx Proxy Managers | npm-oracle-web, npm-oracle-services, npm-oracle-arm, npm-gcloud |
| infra-db | Databases | Database services | All *-db services |
| infra-services | Infra Services | Infrastructure automation | n8n-infra-app, cloud-api, cache-app |

## Status Legend

| Status | Description | Color |
|--------|-------------|-------|
| on | Running and accessible | Green |
| dev | Under active development | Yellow |
| hold | Waiting for resources | Orange |
| tbd | Planned for future | Gray |

## Quick Commands Reference

### SSH Access
```bash
# Oracle Web Server 1
ssh ubuntu@130.110.251.193

# Oracle Services Server 1
ssh ubuntu@129.151.228.66

# GCloud Arch 1
gcloud compute ssh arch-1 --zone us-central1-a
```

### Docker Commands
```bash
# List running containers
sudo docker ps --format 'table {{.Names}}\t{{.Status}}\t{{.Ports}}'

# View container logs
sudo docker logs --tail 100 <container>

# Enter container shell
sudo docker exec -it <container> bash

# Container stats
docker stats --no-stream
```

### System Monitoring
```bash
# Disk usage
df -h

# Memory usage
free -h

# CPU usage
htop
```




---

