# Cloud Infrastructure Master Plan v2

**Project:** Diego's Cloud Infrastructure
**CTO:** Claude (Opus)
**Date:** 2025-12-11
**Status:** PLANNING COMPLETE - READY FOR IMPLEMENTATION

---

# Executive Summary

This master plan is a **Product-Engineer Handoff Document** defining Diego's cloud infrastructure:

```
┌────────────────────────────────────────────────────────────────────────────────────────────┐
│  A) HANDOFF                        WHAT we're building (Cloud architecture)                │
├────────────────────────────────────────────────────────────────────────────────────────────┤
│  A0) Products (FRIDGE)             - Name, Component, Stack, Purpose                       │
│      ├── Terminals                 - WebTerminal, IDE, AI Chat                             │
│      ├── User Productivity         - Mail, Calendar, Sync, Drive, Git, Photos, etc.        │
│      ├── User Security             - Vault, VPN                                            │
│      ├── User Portfolio            - Linktree, CV, Projects                                │
│      └── User AIs                  - Multi-Model, MyAI → MASTERPLAN_AI.md                  │
│  A1) Infra Services (KITCHEN)      - Name, Component, Stack, Purpose                       │
│      ├── Devs Cloud                - Cloud Portal, Analytics, Workflows                    │
│      ├── Devs Security             - Proxy (NPM), Authelia, OAuth2                         │
│      ├── Devs Infra                - API Gateway, Cache                                    │
│      └── Tech Definition           - DevOps, Security, WebDevs stack choices               │
│  A2) Infra Resources               - Resource Allocation, Maps/Topology, Costs             │
│      ├── A20) Resource Alloc       - VMs, IPs, ports, URLs                                 │
│      │       ├── A200) Resource Estimation       - RAM, Storage, Bandwidth                 │
│      │       ├── A201) VM Capacity & Headroom    - Capacity vs Allocated                   │
│      │       ├── A202) Cost Estimation           - Monthly costs breakdown                 │
│      │       └── A203) URL/Port Proxied          - Service URL mapping                     │
│      ├── A21) Maps & Topology      - Network diagrams, auth flow                           │
│      └── A22) Costs                - Monthly cost summary                                  │
│  A3) Tech Research                 - Framework comparisons supporting stack choices        │
│      ├── Framework Comparison      - Frontend (Vanilla vs Vue vs Svelte)                   │
│      ├── Templating Comparison     - Python/JS backend (Jinja2 vs Mako vs Handlebars)      │
│      └── When to Use               - Decision guide for each use case                      │
│  A4) Today                         - Current running state                                 │
│      ├── by Service                - Service status table                                  │
│      └── by VM                     - VM status table                                       │
└────────────────────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────────┐
│  B) ARCHITECTURE         HOW to build it (Technical Deep Dives)                 │
├─────────────────────────────────────────────────────────────────────────────────┤
│  B1) Security Architecture                                                      │
│      B11) Web Auth       - Dual auth flows, session mgmt, token handling        │
│      B12) Dev Access     - SSH patterns, key management, Vault integration      │
│      B13) Isolation      - Network segmentation, firewall rules, secrets        │
│  B2) Service Architecture                                                       │
│      B21) Containers     - Docker Compose patterns, orchestration               │
│      B22) Databases      - Schemas, migrations, backup strategies               │
│      B23) APIs           - Contracts, OpenAPI specs, versioning                 │
│  B3) Infrastructure Architecture                                                │
│      B31) Networking     - DNS, SSL, reverse proxy configs                      │
│      B32) Storage        - Volumes, backups, disaster recovery                  │
│      B33) Scaling        - Triggers, wake-on-demand, GPU provisioning           │
└─────────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────────┐
│  C) ROADMAP              WHEN to build it (Planning & Prioritization)           │
├─────────────────────────────────────────────────────────────────────────────────┤
│  C1) Phases              - Implementation milestones                            │
│  C2) Dependencies        - Service dependency graph                             │
│  C3) Backlog             - Prioritized task list                                │
└─────────────────────────────────────────────────────────────────────────────────┘

┌─────────────────────────────────────────────────────────────────────────────────┐
│  D) DEVOPS               HOW to operate it (Operations & Observability)         │
├─────────────────────────────────────────────────────────────────────────────────┤
│  D1) Portal              - Services access dashboard (Fridge/Kitchen)           │
│  D2) Monitoring          - Metrics, alerts, health checks                       │
│  D3) Knowledge Center    - Architecture docs, API docs, Wiki/FAQ                │
│  D4) Code Practices      - Python standards, Docker patterns, Jinja2            │
│  D5) System Practices    - Poetry, pipx, nvm, shell scripts, backups            │
└─────────────────────────────────────────────────────────────────────────────────┘
```

**Document Purpose:**
- **A = WHAT** → Complete service catalog + stack allocation (Product defines, Engineer validates)
- **B = HOW** → Technical specs for implementation (Engineer owns, Product reviews)
- **C = WHEN** → Roadmap and prioritization (Product + Engineer collaborate)
- **D = OPS** → Day-to-day operations (Engineer owns)


---



# A) HANDOFF - Services & Infrastructure Definition


## A0) Products (FRIDGE)

> **Layer 1** = Infrastructure tools (Terminals, Sync, etc.) - what you use to BUILD

### Terminals

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
terminals                | -                    | -                   | AI-Powered Dev Environment
  ↳ terminals-front      | Hub Landing          | SvelteKit 5 + SCSS  | Tool selector UI
                         |                      |                     |
  ├─ terminal            | -                    | -                   | Web Terminal (bash/zsh/fish)
  │    ↳ terminal-front  | Shell Selector       | SvelteKit 5 + SCSS  | Shell selector UI
  │    ↳ terminal-app    | Terminal Server      | ttyd / wetty        | Terminal server
  │    ↳ terminal-db0    | Storage              | Filesystem          | Shell history + dotfiles
                         |                      |                     |
  ├─ ide                 | -                    | -                   | Web IDE
  │    ↳ ide-front       | IDE Launcher         | SvelteKit 5 + SCSS  | IDE launcher + selector
  │    ↳ ide-app         | Code Server          | code-server         | Code server
  │    ↳ ide-db0         | Storage              | Filesystem          | Workspaces + extensions
                         |                      |                     |
  └─ ai-chat             | -                    | -                   | AI Chat Assistant
       ↳ ai-front        | Chat UI              | SvelteKit 5 + SCSS  | Chat interface
       ↳ ai-app          | Chat Backend         | Open WebUI          | Chat backend
       ↳ ai-api          | LLM API              | Ollama / OpenAI     | LLM API backend
       ↳ ai-db0          | Database             | SQL:PostgreSQL      | Chat history + users
```


### User Productivity

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
mail                     | -                    | -                   | Email Suite
  ↳ mail-front           | Reverse Proxy        | Nginx               | Nginx reverse proxy
  ↳ mail-admin           | Admin UI             | Mailu-Admin         | Admin web interface
  ↳ mail-imap            | IMAP Server          | Dovecot             | IMAP server
  ↳ mail-smtp            | SMTP Server          | Postfix             | SMTP server
  ↳ mail-webmail         | Webmail Client       | Roundcube           | Webmail client
  ↳ mail-db0             | Storage              | Maildir             | Mailboxes storage
                         |                      |                     |
calendar                 | -                    | -                   | Calendar & Contacts (CalDAV/CardDAV)
  ↳ calendar-front       | Web UI               | Radicale (built-in) | Radicale web interface
  ↳ calendar-app         | CalDAV Server        | Radicale            | CalDAV/CardDAV server
  ↳ calendar-db0         | Storage              | Filesystem          | Calendar/contact files
                         |                      |                     |
sync                     | -                    | -                   | File Synchronization Hub
  ↳ sync-front           | File Viewer          | SvelteKit 5 + SCSS  | File tree viewer (collapsible)
  ↳ sync-app             | Aggregator           | Python3             | Aggregates drive+git
                         |                      |                     |
  ├─ drive               | -                    | -                   | Cloud Drive (Filesystem Mount)
  │    ↳ drive-front     | File Browser         | SvelteKit 5 + SCSS  | File browser display
  │    ↳ drive-app       | Mount Daemon         | Rclone              | Bisync / FUSE mount daemon
  │    ↳ drive-db0       | Storage              | Filesystem          | Mount configs + cache
                         |                      |                     |
  └─ git                 | -                    | -                   | Git Hosting
       ↳ git-front       | Login UI             | SvelteKit 5 + SCSS  | Login + repo display
       ↳ git-app         | Git Server           | Gitea               | Git server + web UI
       ↳ git-db0         | Database             | SQL:SQLite          | Users, issues, PRs
       ↳ git-db_obj0     | Storage              | Filesystem          | Git repositories (.git objects)
                         |                      |                     |
photos                   | -                    | -                   | Photo Library Management
  ↳ photo-front          | Login UI             | SvelteKit 5 + SCSS  | Login + Front from Photoprism
  ↳ photo-app            | Photo Engine         | Photoprism          | Photo viewer + AI tagging
  ↳ photo-db0            | Database             | SQL:MariaDB         | Metadata (EXIF, location, AI)
  ↳ photo-db_obj0        | Storage              | Filesystem          | Photo files storage
                         |                      |                     |
slides                   | -                    | -                   | Presentation Builder
  ↳ slides-front         | Editor UI            | SvelteKit 5 + SCSS  | Slide editor + preview
  ↳ slides-app           | Converter            | Marp                | Markdown to slides converter
                         |                      |                     |
  ├─ slidev              | -                    | -                   | Fast Slides (Dev-focused)
  │    ↳ slidev-app      | Slides Engine        | Sli.dev             | Interactive slides engine
  │    ↳ slidev-db0      | Storage              | Filesystem          | Slide source files (.md)
                         |                      |                     |
  └─ reveal              | -                    | -                   | Deep Slides (Rich presentations)
       ↳ reveal-app      | Slides Engine        | Reveal.js           | Full-featured slides engine
       ↳ reveal-db0      | Storage              | Filesystem          | Slide source files (.md/.html)
                         |                      |                     |
sheets                   | -                    | -                   | Spreadsheet & Data Processing
  ↳ sheets-front         | Query UI             | SvelteKit 5 + SCSS  | Data viewer + query UI
  ↳ sheets-app           | Orchestrator         | Python3             | Data processing orchestrator
                         |                      |                     |
  ├─ pandas              | -                    | -                   | Standard Data Jobs
  │    ↳ pandas-app      | DataFrame Engine     | Python:Pandas       | DataFrame processing
  │    ↳ pandas-db0      | Storage              | Filesystem          | Data files (.csv, .xlsx, .parquet)
                         |                      |                     |
  └─ xsv                 | -                    | -                   | Heavy Lift & Speed
       ↳ xsv-app         | CSV Engine           | xsv (Rust)          | High-perf CSV processing
       ↳ xsv-db0         | Storage              | Filesystem          | Large data files
                         |                      |                     |
dashboards               | -                    | -                   | Data Dashboards & Notebooks
  ↳ dashboards-front     | Selector UI          | SvelteKit 5 + SCSS  | Dashboard selector UI
  ↳ dashboards-app       | Orchestrator         | Python3             | Dashboard orchestrator
                         |                      |                     |
  ├─ jupyter             | -                    | -                   | Interactive Notebooks
  │    ↳ jupyter-front   | Notebook UI          | JupyterLab (built-in)| JupyterLab interface
  │    ↳ jupyter-app     | Notebook Server      | JupyterLab          | Notebook server + kernels
  │    ↳ jupyter-db0     | Storage              | Filesystem          | Notebooks + workspace
                         |                      |                     |
  └─ dash                | -                    | -                   | Python Dashboards
       ↳ dash-app        | Dashboard Server     | Plotly Dash         | Dashboard server
       ↳ dash-db0        | Storage              | Filesystem          | Dashboard configs + data
```

### User Security

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
vault                    | -                    | -                   | Password Manager
  ↳ vault-front          | Login UI             | Vaultwarden (built-in)| Vaultwarden web interface
  ↳ vault-app            | Password Server      | Vaultwarden         | Bitwarden self-hosted
  ↳ vault-db0            | Database             | SQL:SQLite          | Encrypted credentials
                         |                      |                     |
vpn                      | -                    | -                   | VPN Server
  ↳ vpn-front            | Client UI            | wg-easy (built-in)  | Web UI for client management
  ↳ vpn-app              | VPN Server           | Wireguard           | VPN tunnel server
  ↳ vpn-db0              | Storage              | Filesystem          | Client configs + keys
```

> **Layer 2** = Built solutions - what you CREATE with those tools

### User Profile/Developments/Portfolio

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
linktree                 | -                    | -                   | Personal Portfolio & Link Aggregator
  ↳ linktree-front       | Link Hub UI          | Vanilla HTML+CSS+JS | Animated link hub (glassmorphic)
  ↳ linktree-app         | Static Host          | GitHub Pages        | Static site (no backend)
  ↳ linktree-db0         | Storage              | JSON / Markdown     | Links config
                         |                      |                     |
  Sections:              |                      |                     |
    • Professional       | -                    | -                   | LinkedIn, GitHub, CV, Ventures
    • Repos              | -                    | -                   | CS, ML, DevOps, Cybersec
    • Personal           | -                    | -                   | Social, Music, Fitness, Travel
    • Tools              | -                    | -                   | Cloud Dash, Health, Markets, Maps
    • Circus             | -                    | -                   | Games, Music, Movies
                         |                      |                     |
  Features:              |                      |                     |
    • Dual carousel      | -                    | -                   | Professional/Personal toggle
    • Gallery/Lite mode  | -                    | -                   | Multiple display modes
    • Navigation         | -                    | -                   | Keyboard/gesture support
```

### User AIs Models

> **Detailed Spec:** `0.spec/MASTERPLAN_AI.md` (separate infrastructure - performance-focused)
> **Status:** Premium project (will merge when ready)

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
ai-chat (Terminals)      | -                    | -                   | AI Chat Interface
  ↳ Mode 1: API Keys     | External APIs        | OpenAI/Claude/etc   | Connect external APIs
  ↳ Mode 2: Multi-Model  | Self-hosted          | → MASTERPLAN_AI.md  | Frontend for AI infrastructure
                         |                      |                     |
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
; MASTERPLAN_AI.md contains:                                          |
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
multimodel               | -                    | -                   | Multi-Model Inference & Routing
  ↳ routing              | Model Router         | Open WebUI          | Choose best model per task
  ↳ gateway              | API Gateway          | Ollama              | Unified interface
  ↳ context              | RAG Engine           | pgvector            | Context management with your data
                         |                      |                     |
myai                     | -                    | -                   | Train & Deploy Your Own Models
  ↳ data                 | Data Pipeline        | Python3             | Collect, store, embed your data
  ↳ train                | Training Engine      | PyTorch + MLflow    | Fine-tune or train (GPU on-demand)
  ↳ deploy               | Model Server         | FastAPI             | Serve model (private/shared/public)
                         |                      |                     |
infrastructure           | -                    | -                   | Own Cloud Stack
  ↳ oci-f-arm_1          | Brain API            | Oracle ARM (24GB)   | Vector DB, 24/7 FREE
  ↳ tensordock-inference | Inference VM         | TensorDock GPU      | Ollama, $0.35/hr
  ↳ tensordock-training  | Training VM          | TensorDock GPU      | PyTorch, $0.35/hr
  ↳ local-collectors     | Ingestion            | Python3             | Data ingestion pipelines
```

---

## A1) Infra Services (KITCHEN)

### Devs Cloud Portal

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
cloud                    | -                    | -                   | Cloud Portal (Central Hub)
  ↳ cloud-front          | Portal Landing       | SvelteKit 5 + SCSS  | Portal landing + navigation
  ↳ cloud-app            | Backend              | Python3             | Backend logic + collectors
  ↳ cloud-db0            | Storage              | Only JSON           | Config + metrics storage
                         |                      |                     |
  ├─ fridge              | -                    | -                   | Solutions Access (User Services)
  │    ↳ fridge-front    | Services Launcher    | SvelteKit 5 + SCSS  | Services launcher + status cards
                         |                      |                     |
  └─ kitchen             | -                    | -                   | Infrastructure Dashboard
       ↳ kitchen-front   | Arch Dashboard       | SvelteKit 5 + SCSS  | Architecture diagrams + monitoring
                         |                      |                     |
analytics                | -                    | -                   | Web Analytics Platform
  ↳ analytics-front      | Stats UI             | Matomo (built-in)   | Login + stats display
  ↳ analytics-app        | Analytics Engine     | Matomo (PHP-FPM)    | Analytics processing
  ↳ analytics-db0        | Database             | SQL:MariaDB         | Visits, events, reports
                         |                      |                     |
workflows                | -                    | -                   | Workflow Automation Hub
  ↳ workflows-front      | Selector UI          | SvelteKit 5 + SCSS  | Hub landing + workflow selector
                         |                      |                     |
  ├─ temporal            | -                    | -                   | Infrastructure Workflows
  │    ↳ temporal-front  | Workflow UI          | Temporal UI (built-in)| Workflow dashboard
  │    ↳ temporal-app    | Workflow Engine      | Temporal            | Workflow engine
  │    ↳ temporal-db0    | Database             | SQL:PostgreSQL      | Workflow state, history
                         |                      |                     |
  └─ langgraph           | -                    | -                   | AI Agentic Workflows
       ↳ langgraph-front | Agent Monitor        | SvelteKit 5 + SCSS  | Agent monitor UI
       ↳ langgraph-app   | Agent Orchestrator   | LangGraph + FastAPI | Agent orchestration
       ↳ langgraph-db0   | Database             | SQL:PostgreSQL      | Checkpoints, chat history
       ↳ langgraph-vec   | Vector DB            | pgvector            | Vector embeddings
       ↳ langgraph-gpu   | GPU Runtime          | Vast.ai / Lambda    | GPU compute runtime
```

### Devs Security

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
webserver                | -                    | -                   | Central Proxy & Web Serving
  ↳ proxy-front          | Admin UI             | NPM (built-in)      | Login + NPM admin UI
  ↳ proxy-app            | Reverse Proxy        | NPM (Nginx Proxy Manager)| Reverse proxy + SSL termination
  ↳ proxy-db0            | Database             | SQL:SQLite          | Proxy configs + certs
                         |                      |                     |
oauth2                   | -                    | -                   | GitHub OAuth2 Authentication
  ↳ oauth2-front         | Login Page           | OAuth2-Proxy (built-in)| Login redirect page
  ↳ oauth2-app           | OAuth Server         | OAuth2-Proxy        | OAuth2 proxy server
  ↳ oauth2-db0           | Session Store        | Redis / Memory      | Session tokens
                         |                      |                     |
authelia                 | -                    | -                   | 2FA / SSO Gateway
  ↳ authelia-front       | Login UI             | Authelia (built-in) | Login + 2FA prompt
  ↳ authelia-app         | Auth Server          | Authelia            | Auth server + session mgmt
  ↳ authelia-db0         | Database             | SQL:PostgreSQL      | Users, sessions, TOTP seeds
```

### Devs Infrastructure

```
Name                     | Component            | Stack               | Purpose
─────────────────────────┼──────────────────────┼─────────────────────┼────────────────────────────────
api                      | -                    | -                   | Central API Gateway
  ↳ api-front            | API Docs             | SvelteKit 5 + SCSS  | API docs / Swagger UI
  ↳ api-app              | API Server           | Python:Flask        | Flask API server
  ↳ api-db0              | Storage              | Hybrid:JSON/SQLite  | Aggregated JSONs from all apps
                         |                      |                     |
cache                    | -                    | -                   | In-Memory Cache
  ↳ cache-app            | Cache Server         | Redis               | Session/cache data store
```

### Tech Definition

#### DevOps Stack
```
Category             | Provider                 | Purpose
─────────────────────┼──────────────────────────┼────────────────────────────────
Code Repository      | GitHub                   | Version control, collaboration
Database Host        | Oracle Cloud             | SQLite / MariaDB / PostgreSQL
CI/CD Pipeline       | GitHub Actions           | Build, test, deploy automation
Web Hosting          | GitHub Pages             | Static site hosting (free)
Analytics            | Matomo (self-hosted)     | Privacy-focused web analytics
DNS + CDN            | Cloudflare               | DNS, SSL, caching, DDoS protection
```

#### Security Stack
```
Component            | Stack                    | Purpose
─────────────────────┼──────────────────────────┼────────────────────────────────
Authelia             | Authelia + Redis         | 2FA Gateway, SSO, Session Mgmt
OAuth2 Providers     | OAuth2-Proxy             | Social Login Integration
  ↳ GitHub           | GitHub OAuth App         | Primary (dev-focused)
  ↳ Google           | Google OAuth             | Backup option
  ↳ Facebook         | Meta OAuth               | Future option
  ↳ X (Twitter)      | X OAuth                  | Future option
```

#### WebDevs Stack
```
Project Type         | Stack                    | Output                  | Render
─────────────────────┼──────────────────────────┼─────────────────────────┼────────────

## Frontend (Browser)
Static Landing       | Vanilla HTML + CSS       | Single .html file       | None (static)
Service Fronts       | SvelteKit 5 + SCSS       | HTML + minimal JS       | SSR + Hydration
Cloud Dashboard      | SvelteKit 5 + SCSS       | HTML + JS chunks        | SSR + CSR
GitHub Pages         | SvelteKit 5 (static)     | Pre-rendered HTML       | Static export

## Templating (Python Backend)
Project              | Stack              | Data Input     | Template         | Output
─────────────────────┼────────────────────┼────────────────┼──────────────────┼──────────────────
Email Notifications  | Jinja2 + Python    | JSON/dict      | .html.j2         | .html (email)
PDF Reports          | Jinja2 + WeasyPrint| JSON/dict      | .html.j2         | .pdf
Markdown Docs        | Jinja2 + Markdown  | JSON/dict      | .md.j2           | .md → .html
Config Files         | Jinja2             | JSON/dict      | .yaml.j2/.toml.j2| .yaml/.toml
Spec Docs (ArchSpecs)| Jinja2             | .spec.json     | .md.j2           | .md
```

---

## A2) Infra Resources

### A20) Resource Allocation

#### A200) Resource Estimation
```
Service              | RAM      | Storage   | GPU    | Bandwidth/mo | VM
─────────────────────┼──────────┼───────────┼────────┼──────────────┼────────────────

## FRIDGE

Terminals
↳ terminal-app       | 64 MB    | 100 MB    | -      | 5 GB         | oci-p-flex_1
↳ ide-app            | 512 MB   | 2 GB      | -      | 10 GB        | oci-p-flex_1
↳ ai-app             | 512 MB   | 2 GB      | -      | 30 GB        | oci-p-flex_1

User Productivity
↳ mail-* (suite)     | 512 MB   | 10 GB     | -      | 5 GB         | oci-f-micro_1
↳ calendar-app       | 64 MB    | 500 MB    | -      | 1 GB         | oci-p-flex_1
↳ sync-front         | 64 MB    | 100 MB    | -      | 5 GB         | oci-p-flex_1
  ↳ drive (Rclone)   | 128 MB   | 2 GB      | -      | 200 GB       | oci-p-flex_1
  ↳ git (Gitea)      | 256 MB   | 5 GB      | -      | 10 GB        | oci-p-flex_1
↳ photo-app          | 256 MB   | 20 GB     | -      | 50 GB        | oci-p-flex_1
↳ slides-app (Marp)  | 64 MB    | 200 MB    | -      | 2 GB         | oci-p-flex_1
  ↳ slidev (Sli.dev) | 128 MB   | 500 MB    | -      | 5 GB         | oci-p-flex_1
  ↳ reveal (Reveal.js)| 128 MB  | 500 MB    | -      | 5 GB         | oci-p-flex_1
↳ sheets-app         | 64 MB    | 100 MB    | -      | 2 GB         | oci-p-flex_1
  ↳ pandas (Python)  | 256 MB   | 2 GB      | -      | 10 GB        | oci-p-flex_1
  ↳ xsv (Rust)       | 64 MB    | 1 GB      | -      | 10 GB        | oci-p-flex_1
↳ dashboards-app     | 64 MB    | 100 MB    | -      | 2 GB         | oci-p-flex_1
  ↳ jupyter          | 512 MB   | 2 GB      | -      | 10 GB        | oci-p-flex_1
  ↳ dash (Plotly)    | 256 MB   | 1 GB      | -      | 10 GB        | oci-p-flex_1

User Security
↳ vault-app          | 128 MB   | 500 MB    | -      | 1 GB         | oci-p-flex_1
↳ vpn-app            | 64 MB    | 50 MB     | -      | 100 GB       | oci-p-flex_1

─────────────────────┼──────────┼───────────┼────────┼──────────────┼────────────────
FRIDGE TOTALS        | 4.1 GB   | 49.6 GB   | -      | 483 GB       |

## KITCHEN

Devs Cloud Portal
↳ analytics-app      | 256 MB   | 5 GB      | -      | 100 GB       | oci-f-micro_2
↳ cloud-app          | 128 MB   | 500 MB    | -      | 5 GB         | oci-p-flex_1
  ↳ fridge-front     | 64 MB    | 100 MB    | -      | 10 GB        | oci-p-flex_1
  ↳ kitchen-front    | 64 MB    | 100 MB    | -      | 5 GB         | oci-p-flex_1
↳ workflows-app      | 64 MB    | 100 MB    | -      | 2 GB         | oci-p-flex_1
  ↳ temporal         | 512 MB   | 2 GB      | -      | 20 GB        | oci-p-flex_1
  ↳ langgraph        | 512 MB   | 2 GB      | -      | 30 GB        | oci-p-flex_1

Devs Security
↳ proxy-app          | 256 MB   | 1 GB      | -      | 50 GB        | gcp-f-micro_1
↳ authelia-app       | 128 MB   | 100 MB    | -      | 10 GB        | gcp-f-micro_1
↳ oauth2-app         | 64 MB    | 50 MB     | -      | 5 GB         | gcp-f-micro_1

Devs Infrastructure
↳ api-app            | 128 MB   | 1 GB      | -      | 20 GB        | gcp-f-micro_1
↳ cache-app          | 256 MB   | 1 GB      | -      | -            | oci-p-flex_1

─────────────────────┼──────────┼───────────┼────────┼──────────────┼────────────────
KITCHEN TOTALS       | 2.4 GB   | 12.9 GB   | -      | 257 GB       |

═════════════════════╪══════════╪═══════════╪════════╪══════════════╪════════════════
GRAND TOTALS         | 6.5 GB   | 62.5 GB   | -      | 740 GB       |
```

#### A201) VM Capacity & Headroom
```
Host       | VM             | RAM    | Alloc  | HD     | Alloc  | Headroom | Services Running
───────────┼────────────────┼────────┼────────┼────────┼────────┼──────────┼─────────────────────────────────────────
GCloud     | gcp-f-micro_1  | 1 GB   | 576 MB | 30 GB  | 2.2 GB | 42% RAM  | proxy, authelia, oauth2, api, flask
Oracle     | oci-f-micro_1  | 1 GB   | 512 MB | 47 GB  | 10 GB  | 49% RAM  | mail-* (8 containers)
Oracle     | oci-f-micro_2  | 1 GB   | 256 MB | 47 GB  | 5 GB   | 74% RAM  | analytics
Oracle     | oci-p-flex_1   | 8 GB   | 5.1 GB | 100 GB | 45 GB  | 36% RAM  | sync, drive, git, photos, vault, vpn, cal, slides, sheets, dashboards, cloud-portal, workflows, cache
───────────┼────────────────┼────────┼────────┼────────┼────────┼──────────┼─────────────────────────────────────────
TOTALS     |                | 11 GB  | 6.4 GB | 224 GB | 62 GB  | 42% RAM  |
```

#### A202) Cost Estimation
```
Item                   | Provider   | Monthly Cost  | Notes
───────────────────────┼────────────┼───────────────┼─────────────────────────────
gcp-f-micro_1          | GCloud     | $0            | Free Tier (e2-micro)
oci-f-micro_1          | Oracle     | $0            | Free Tier (Always Free)
oci-f-micro_2          | Oracle     | $0            | Free Tier (Always Free)
oci-p-flex_1           | Oracle     | ~$5.50        | Flex (wake-on-demand)
Cloudflare             | Cloudflare | $0            | Free Plan (DNS + CDN)
Domain (annual/12)     | Cloudflare | ~$1           | ~$10/year
───────────────────────┼────────────┼───────────────┼─────────────────────────────
TOTAL                  |            | ~$6.50/mo     | Cloud infrastructure
```




#### A203) URL/Port Proxied

**URL Pattern:** `service.diegonmarcos.com` = Login/Landing → redirects to `/app` after auth success

**Services:**

```
Service           | URL (Public and Private AUTH)                   | VM             | Container        | Private | IP:Port
──────────────────┼─────────────────────────────────────────────────┼────────────────┼──────────────────┼─────────┼─────────────────────
## FRIDGE

Terminals
↳ Terminals Hub   | terminal.diegonmarcos.com                       | oci-p-flex_1   | terminals-front  | -       | 84.235.234.87:3000
  ↳ WebTerminal   | terminal.diegonmarcos.com/terminal              | oci-p-flex_1   | terminal-app     | x       | 84.235.234.87:7681
  ↳ IDE           | terminal.diegonmarcos.com/ide                   | oci-p-flex_1   | ide-app          | x       | 84.235.234.87:8080
  ↳ AI Chat       | terminal.diegonmarcos.com/chat                  | oci-p-flex_1   | ai-app           | x       | 84.235.234.87:8501

User Productivity
↳ Mail            | mail.diegonmarcos.com                           | oci-f-micro_1  | mail-front       | -       | 130.110.251.193:443
  ↳ Webmail       | mail.diegonmarcos.com/webmail                   | oci-f-micro_1  | mail-webmail     | x       | 130.110.251.193:443
↳ Calendar        | cal.diegonmarcos.com                            | oci-p-flex_1   | calendar-front   | -       | 84.235.234.87:5232
  ↳ Radicale      | cal.diegonmarcos.com/radicale                   | oci-p-flex_1   | calendar-app     | x       | 84.235.234.87:5232
↳ Sync            | sync.diegonmarcos.com                           | oci-p-flex_1   | sync-front       | -       | 84.235.234.87:8384
  ↳ Drive         | sync.diegonmarcos.com/drive                     | oci-p-flex_1   | drive-app        | x       | 84.235.234.87:5572
  ↳ Git           | sync.diegonmarcos.com/git                       | oci-p-flex_1   | git-app          | x       | 84.235.234.87:3001
↳ Photos          | photos.diegonmarcos.com                         | oci-p-flex_1   | photo-front      | -       | 84.235.234.87:2342
  ↳ Photoprism    | photos.diegonmarcos.com/photoprism              | oci-p-flex_1   | photo-app        | x       | 84.235.234.87:2342
↳ Slides          | slides.diegonmarcos.com                         | oci-p-flex_1   | slides-front     | -       | 84.235.234.87:3002
  ↳ Slidev        | slides.diegonmarcos.com/slidev                  | oci-p-flex_1   | slidev-app       | x       | 84.235.234.87:3030
  ↳ Reveal        | slides.diegonmarcos.com/reveal                  | oci-p-flex_1   | reveal-app       | x       | 84.235.234.87:3031
↳ Sheets          | sheets.diegonmarcos.com                         | oci-p-flex_1   | sheets-front     | -       | 84.235.234.87:3003
  ↳ Pandas        | sheets.diegonmarcos.com/pandas                  | oci-p-flex_1   | pandas-app       | x       | 84.235.234.87:8502
  ↳ XSV           | sheets.diegonmarcos.com/xsv                     | oci-p-flex_1   | xsv-app          | x       | 84.235.234.87:8503
↳ Dashboards      | dashboards.diegonmarcos.com                     | oci-p-flex_1   | dashboards-front | -       | 84.235.234.87:3004
  ↳ Jupyter       | dashboards.diegonmarcos.com/jupyter             | oci-p-flex_1   | jupyter-app      | x       | 84.235.234.87:8888
  ↳ Dash          | dashboards.diegonmarcos.com/dash                | oci-p-flex_1   | dash-app         | x       | 84.235.234.87:8050

User Security
↳ Vault           | vault.diegonmarcos.com                          | oci-p-flex_1   | vault-front      | -       | 84.235.234.87:8080
  ↳ Vaultwarden   | vault.diegonmarcos.com/vaultwarden              | oci-p-flex_1   | vault-app        | x       | 84.235.234.87:8080
↳ VPN             | vpn.diegonmarcos.com                            | oci-p-flex_1   | vpn-front        | -       | 84.235.234.87:51821
  ↳ WG-Easy       | vpn.diegonmarcos.com/wg-easy                    | oci-p-flex_1   | vpn-app          | x       | 84.235.234.87:51820

## KITCHEN

Devs Cloud Portal
↳ Analytics       | analytics.diegonmarcos.com                      | oci-f-micro_2  | analytics-front  | -       | 129.151.228.66:8080
  ↳ Matomo        | analytics.diegonmarcos.com/matomo               | oci-f-micro_2  | analytics-app    | x       | 129.151.228.66:8080
↳ Cloud Portal    | cloud.diegonmarcos.com                          | oci-p-flex_1   | cloud-front      | -       | 84.235.234.87:3005
  ↳ Fridge        | cloud.diegonmarcos.com/fridge                   | oci-p-flex_1   | fridge-front     | x       | 84.235.234.87:3005
  ↳ Kitchen       | cloud.diegonmarcos.com/kitchen                  | oci-p-flex_1   | kitchen-front    | x       | 84.235.234.87:3005
↳ Workflows       | workflow.diegonmarcos.com                       | oci-p-flex_1   | workflows-front  | -       | 84.235.234.87:3006
  ↳ Temporal      | workflow.diegonmarcos.com/temporal              | oci-p-flex_1   | temporal-app     | x       | 84.235.234.87:8233
  ↳ LangGraph     | workflow.diegonmarcos.com/langgraph             | oci-p-flex_1   | langgraph-app    | x       | 84.235.234.87:8123

Devs Security
↳ Proxy Admin     | proxy.diegonmarcos.com                          | gcp-f-micro_1  | proxy-front      | -       | 34.55.55.234:81
  ↳ NPM           | proxy.diegonmarcos.com/npm                      | gcp-f-micro_1  | proxy-app        | x       | 34.55.55.234:81
↳ Auth (Authelia) | auth.diegonmarcos.com                           | gcp-f-micro_1  | authelia-front   | -       | 34.55.55.234:9091
  ↳ Authelia      | auth.diegonmarcos.com/authelia                  | gcp-f-micro_1  | authelia-app     | -       | 34.55.55.234:9091
↳ OAuth2          | auth.diegonmarcos.com/oauth2                    | gcp-f-micro_1  | oauth2-app       | -       | 34.55.55.234:4180

Devs Infrastructure
↳ API Gateway     | api.diegonmarcos.com                            | oci-p-flex_1   | api-front        | -       | 84.235.234.87:5000
  ↳ Docs          | api.diegonmarcos.com/docs                       | oci-p-flex_1   | api-app          | x       | 84.235.234.87:5000
↳ Cache           | (internal)                                      | oci-p-flex_1   | cache-app        | -       | 84.235.234.87:6379
```

**VMs:**
```
Host       | VM Name        | IP              | Host SSH                                      | VM SSH
───────────┼────────────────┼─────────────────┼───────────────────────────────────────────────┼──────────────────────────────
GCloud     | gcp-f-micro_1  | 34.55.55.234    | gcloud compute ssh arch-1 --zone=us-central1-a | -
Oracle     | oci-f-micro_1  | 130.110.251.193 | -                                             | ssh ubuntu@130.110.251.193
Oracle     | oci-f-micro_2  | 129.151.228.66  | -                                             | ssh ubuntu@129.151.228.66
Oracle     | oci-p-flex_1   | 84.235.234.87   | -                                             | ssh ubuntu@84.235.234.87
```



### A21) Maps & Topology

#### Network Topology
```
                                    INTERNET
                                       │
                                       ▼
                          ┌────────────────────────┐
                          │      CLOUDFLARE        │
                          │   DNS + CDN + Proxy    │
                          │   diegonmarcos.com     │
                          └───────────┬────────────┘
                                      │
                    ┌─────────────────┼─────────────────┐
                    │                 │                 │
                    ▼                 ▼                 ▼
┌───────────────────────────────────────────────────────────────────────────────┐
│                              GOOGLE CLOUD                                      │
│  ┌─────────────────────────────────────────────────────────────────────────┐  │
│  │  gcp-f-micro_1 (us-central1-a)              34.55.55.234                │  │
│  │  e2-micro | 1 GB RAM | 30 GB | FREE 24/7                                │  │
│  │  ┌─────────────────┐  ┌─────────────────┐  ┌─────────────────┐          │  │
│  │  │  NPM :80/:443   │  │ Authelia :9091  │  │  Flask API      │          │  │
│  │  │  Reverse Proxy  │  │  2FA Gateway    │  │  :5000          │          │  │
│  │  └────────┬────────┘  └────────┬────────┘  └─────────────────┘          │  │
│  │           │                    │                                         │  │
│  │           └────────────────────┘                                         │  │
│  │                    │ Forward Auth                                        │  │
│  └────────────────────┼─────────────────────────────────────────────────────┘  │
└───────────────────────┼────────────────────────────────────────────────────────┘
                        │
        ┌───────────────┼───────────────┬───────────────┐
        │               │               │               │
        ▼               ▼               ▼               ▼
┌─────────────────────────────────────────────────────────────────────────────────┐
│                                 ORACLE CLOUD                                     │
│                                                                                  │
│  ┌────────────────────────┐  ┌────────────────────────┐                         │
│  │  oci-f-micro_1         │  │  oci-f-micro_2         │                         │
│  │  130.110.251.193       │  │  129.151.228.66        │                         │
│  │  1 GB | 47 GB          │  │  1 GB | 47 GB          │                         │
│  │  FREE 24/7             │  │  FREE 24/7             │                         │
│  │  ─────────────────     │  │  ─────────────────     │                         │
│  │  • mail-* (8 cont)     │  │  • analytics (Matomo)  │                         │
│  │    - IMAP/SMTP         │  │    - PHP-FPM           │                         │
│  │    - Webmail           │  │    - MariaDB           │                         │
│  │    - Admin             │  │                        │                         │
│  └────────────────────────┘  └────────────────────────┘                         │
│                                                                                  │
│  ┌──────────────────────────────────────────────────────────────────────────┐   │
│  │  oci-p-flex_1 (eu-frankfurt-1)                      84.235.234.87        │   │
│  │  A1.Flex | 8 GB RAM | 100 GB | PAID (wake-on-demand) ~$5.50/mo           │   │
│  │  ────────────────────────────────────────────────────────────────────    │   │
│  │  FRIDGE (Solutions)                  │  KITCHEN (Infrastructure)         │   │
│  │  • terminal, ide, ai-chat            │  • cloud-portal                   │   │
│  │  • sync, drive (Rclone), git (Gitea) │    - /fridge (services access)    │   │
│  │  • photos (Photoprism), calendar     │    - /kitchen (arch + monitoring) │   │
│  │  • slides (Marp/Slidev/Reveal)       │  • workflows                      │   │
│  │  • sheets (Pandas/XSV)               │    - temporal, langgraph          │   │
│  │  • dashboards (Jupyter/Dash)         │  • cache (Redis)                  │   │
│  │  • vault (Vaultwarden), vpn (WG)     │                                   │   │
│  └──────────────────────────────────────────────────────────────────────────┘   │
│                                                                                  │
└──────────────────────────────────────────────────────────────────────────────────┘
```

#### Auth Flow
```
User Request → Cloudflare → NPM (gcp-f-micro_1)
                              │
                              ▼
                      ┌───────────────┐
                      │   Authelia    │
                      │   2FA Check   │
                      └───────┬───────┘
                              │
            ┌─────────────────┼─────────────────┐
            ▼                 ▼                 ▼
      ┌──────────┐      ┌──────────┐      ┌──────────┐
      │  GitHub  │      │   TOTP   │      │ Passkey  │
      │  OAuth2  │      │  (Local) │      │ WebAuthn │
      └────┬─────┘      └────┬─────┘      └────┬─────┘
           └─────────────────┼─────────────────┘
                             ▼
                   Session Cookie Created
                   (.diegonmarcos.com)
                             │
                             ▼
                   Access Granted → Backend VM
```

### A22) Costs
```
┌─────────────────────────────────────────────────────────────────┐
│  MONTHLY COSTS                                                   │
├─────────────────────────────────────────────────────────────────┤
│  GCloud gcp-f-micro_1      │  FREE        │  24/7 gateway       │
│  Oracle oci-f-micro_1      │  FREE        │  24/7 mail          │
│  Oracle oci-f-micro_2      │  FREE        │  24/7 analytics     │
│  Oracle oci-p-flex_1       │  ~$5.50      │  wake-on-demand     │
│  Cloudflare                │  FREE        │  DNS + CDN          │
│  Domain                    │  ~$1         │  annual/12          │
├─────────────────────────────────────────────────────────────────┤
│  TOTAL CLOUD               │  ~$6.50/mo   │                     │
└─────────────────────────────────────────────────────────────────┘
```

---

## A3) Tech Research

#### Framework Comparison (Frontend)
```
Criteria        | Vanilla (HTML+CSS+JS)    | Vue3 + Nuxt3 (SSR)       | SvelteKit 5 (SSR)
────────────────┼──────────────────────────┼──────────────────────────┼──────────────────────────
SEO             | ★★★★★ Excellent          | ★★★★★ Excellent (SSR)    | ★★★★★ Excellent (SSR)
Performance     | ★★★★★ Best (no overhead) | ★★★★☆ Good (Vue runtime) | ★★★★★ Excellent (compiles)
Complexity      | ★☆☆☆☆ Hard at scale      | ★★★☆☆ Medium             | ★★★★☆ Low-Medium
Consistency     | ★☆☆☆☆ No patterns        | ★★★★☆ Good (SFC)         | ★★★★★ Opinionated
Bundle Size     | 0 KB (no framework)      | ~50 KB (Vue runtime)     | ~5 KB (compiles away)
Learning Curve  | Low (basics)             | Medium-High              | Low-Medium
SSR Support     | Manual only              | Built-in (Nuxt3)         | Built-in
Static Export   | Native                   | Built-in (Nuxt3)         | Built-in
```

#### Framework Comparison (Templating - Python/JS Backend)
```
Criteria        | Jinja2 (Python)          | Mako (Python)            | Handlebars (JS)
────────────────┼──────────────────────────┼──────────────────────────┼──────────────────────────
Performance     | ★★★★☆ Fast               | ★★★★★ Fastest            | ★★★★☆ Fast
Syntax          | ★★★★★ Clean {{ }}        | ★★★☆☆ ${} + Python       | ★★★★☆ Clean {{ }}
Logic Support   | ★★★★★ Full (loops, if)   | ★★★★★ Full + Python      | ★★☆☆☆ Logic-less
Learning Curve  | ★★★★★ Easy               | ★★★☆☆ Medium             | ★★★★★ Easy
Ecosystem       | ★★★★★ Flask, Ansible     | ★★★☆☆ SQLAlchemy         | ★★★★☆ Node.js, Mustache
Inheritance     | ★★★★★ Extends + Blocks   | ★★★★★ Extends + Blocks   | ★★★☆☆ Partials only
Debug           | ★★★★★ Clear errors       | ★★★☆☆ Verbose            | ★★★★☆ Good
```

#### When to Use
```
Use Case             | Best Choice              | Why
─────────────────────┼──────────────────────────┼────────────────────────────────────────

## Static / SEO Pages (minimal JS, SEO-first, some dynamic)
 - Landing pages        | Vanilla or SvelteKit     | SEO matters, minimal JS needed
 - Login/Auth pages     | Vanilla                  | Simple forms, no framework needed
 - Dashboards           | SvelteKit                | Reactive data, SSR for initial load

## Documentation (Markdown → HTML, Obsidian-like workflow)
 - Docs / Knowledge Base| SvelteKit (static)       | Markdown support, fast builds
 - API Docs             | SvelteKit + OpenAPI      | Auto-generated from specs

## Web Apps (interactive, component-based)
 - Data Apps            | SvelteKit or Nuxt3       | Forms, lists, CRUD operations
 - Media Apps           | SvelteKit or Nuxt3       | Maps, music, photos, video players
 - Games                | Vanilla + Phaser/Three.js| Direct Canvas/WebGL, no overhead

## MVPs / Prototypes (fast iteration, throwaway code)
 - Quick prototypes     | Vue3 + Vite              | Fast HMR, familiar syntax
 - Hackathons           | Vue3 + Vite              | Speed over architecture

## Server-Side Templating (Python backend, no JS)
 - Email templates      | Jinja2                   | Dynamic emails from Python
 - PDF/HTML reports     | Jinja2                   | Generate from data + template
 - Config generation    | Jinja2                   | YAML/JSON/TOML from templates
 - Batch HTML pages     | Jinja2                   | Bulk generate static pages
 - Flask views          | Jinja2                   | Server-rendered HTML (no SPA)
```

---

## A4) Today (Current State)

### by Service
```
Service           | Public URL                      | VM             | Container       | IP:Port             | Status
──────────────────┼─────────────────────────────────┼────────────────┼─────────────────┼─────────────────────┼────────

## FRIDGE

Terminals
↳ WebTerminal     | terminal.diegonmarcos.com       | oci-p-flex_1   | terminal-app    | 84.235.234.87:7681  | dev

User Productivity
↳ Mail            | mail.diegonmarcos.com           | oci-f-micro_1  | mailu-front     | 130.110.251.193:443 | on
↳ Sync            | sync.diegonmarcos.com           | oci-p-flex_1   | sync-app        | 84.235.234.87:8384  | on
↳ Git             | git.diegonmarcos.com            | oci-p-flex_1   | git-app         | 84.235.234.87:3000  | dev
↳ Photos          | photos.diegonmarcos.com         | oci-p-flex_1   | photoprism-app  | 84.235.234.87:2342  | on
↳ Calendar        | cal.diegonmarcos.com            | oci-p-flex_1   | radicale-app    | 84.235.234.87:5232  | on

User Security
↳ Vault           | vault.diegonmarcos.com          | oci-p-flex_1   | vault-app       | 84.235.234.87:80    | dev
↳ VPN (OpenVPN)   | (UDP direct)                    | oci-p-flex_1   | vpn-app         | 84.235.234.87:1194  | dev

## KITCHEN

Devs Cloud Dashboard
↳ Analytics       | analytics.diegonmarcos.com      | oci-f-micro_2  | matomo-app      | 129.151.228.66:8080 | on
↳ Cloud Dashboard | cloud.diegonmarcos.com          | squarespace    | (external)      | 198.49.23.144       | on
↳ Flask API       | (internal)                      | gcp-f-micro_1  | flask-app       | 34.55.55.234:5000   | on
↳ n8n Infra       | n8n.diegonmarcos.com            | oci-p-flex_1   | n8n-infra-app   | 84.235.234.87:5678  | on

Devs Security
↳ Proxy Admin     | proxy.diegonmarcos.com          | gcp-f-micro_1  | npm-gcloud      | 34.55.55.234:81     | on
↳ Auth (Authelia) | auth.diegonmarcos.com           | gcp-f-micro_1  | authelia-app    | 34.55.55.234:9091   | on
↳ Authelia Redis  | (internal)                      | gcp-f-micro_1  | authelia-redis  | 34.55.55.234:6379   | on

Devs Infrastructure
↳ Cache           | (internal)                      | oci-p-flex_1   | cache-app       | 84.235.234.87:6379  | on
```

### by VM
```
Host   | VM             | RAM   | VRAM | Storage | IP              | Services Running                          | Notes
───────┼────────────────┼───────┼──────┼─────────┼─────────────────┼───────────────────────────────────────────┼─────────────────
GCloud | gcp-f-micro_1  | 1 GB  | -    | 30 GB   | 34.55.55.234    | npm, authelia, redis, flask-app           | 24/7 FREE
Oracle | oci-f-micro_1  | 1 GB  | -    | 47 GB   | 130.110.251.193 | mailu-* (8 containers)                    | 24/7 FREE
Oracle | oci-f-micro_2  | 1 GB  | -    | 47 GB   | 129.151.228.66  | matomo-app, matomo-db                     | 24/7 FREE
Oracle | oci-p-flex_1   | 8 GB  | -    | 100 GB  | 84.235.234.87   | sync, photos, n8n, git, cal, cache...     | WAKE $5.5/mo
```



---

---

---

---

# B) Architecture - Technical Deep Dives

## B1) Security Architecture

### B11) Web Auth - Dual Authentication

**Plan:** `0.spec/Task_Security2faOAuth20/PLAN_DualAuth_Security.md`

```
┌─────────────────────────────────────────────────────────────────┐
│                         DUAL AUTH FLOW                           │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  User Request → NPM → auth_request → Authelia                   │
│                                          │                      │
│                          ┌───────────────┼───────────────┐      │
│                          │               │               │      │
│                          ▼               ▼               ▼      │
│                    ┌──────────┐   ┌──────────┐   ┌──────────┐  │
│                    │  GitHub  │   │   TOTP   │   │ Passkey  │  │
│                    │  OAuth2  │   │  (Local) │   │ (WebAuthn)│  │
│                    └────┬─────┘   └────┬─────┘   └────┬─────┘  │
│                         │              │              │         │
│                         └──────────────┴──────────────┘         │
│                                        │                        │
│                                        ▼                        │
│                              Session Cookie Created             │
│                              (.diegonmarcos.com)                │
│                                        │                        │
│                                        ▼                        │
│                              Access Granted to Service          │
└─────────────────────────────────────────────────────────────────┘
```

**Authentication Paths (Either grants access):**
- **Path 1:** GitHub OAuth2 - Passwordless, uses GitHub's 2FA
- **Path 2:** Local TOTP - Authelia internal user + TOTP app
- **Path 3:** Passkey/WebAuthn - Hardware key or biometric

**Key Components:**
- Authelia on GCP VM (central gateway)
- NPM forward auth for all services
- SSO via session cookie (domain: `.diegonmarcos.com`)

---

### B12) Dev Access - SSH & Vault Management

**Secrets Storage Tiers:**

| Tier | Location | Purpose | Access Method |
|------|----------|---------|---------------|
| **LOCAL_KEYS** | `/home/diego/Documents/Git/LOCAL_KEYS/` | SSH keys, API tokens, infra creds | Terminal/CLI |
| **Bitwarden** | Cloud (bitwarden.com) | Browser passwords, TOTP seeds | Browser extension |
| **Vaultwarden** | vault.diegonmarcos.com | Full backup, privacy-sensitive | Self-hosted web |

**SSH Access Configuration:**

```bash
# LOCAL_KEYS structure
LOCAL_KEYS/
├── 00_terminal/
│   └── ssh/
│       ├── id_rsa              # Default key
│       ├── gcp_arch1           # GCloud VM
│       └── oci_*               # Oracle VMs
├── README.md                   # All credentials reference
└── ...

# Symlinked to ~/.ssh/
~/.ssh/ → LOCAL_KEYS/00_terminal/ssh/
```

**VM Access Commands:**

```bash
# GCP (NPM + Authelia)
gcloud compute ssh arch-1 --zone=us-central1-a

# Oracle VMs
ssh -i ~/.ssh/id_rsa ubuntu@130.110.251.193  # Mail
ssh -i ~/.ssh/id_rsa ubuntu@129.151.228.66   # Analytics
ssh -i ~/.ssh/id_rsa ubuntu@84.235.234.87    # Dev (p-flex)
```

**Vault Workflow:**
1. **Daily use:** Bitwarden Cloud (browser extension)
2. **Sensitive items:** Vaultwarden (self-hosted, Authelia protected)
3. **Infra credentials:** LOCAL_KEYS/README.md (terminal reference)

---

### B13) Isolation - Network Segmentation & Hardening

**Defense Layers:**

```
┌─────────────────────────────────────────────────────────────────┐
│                      SECURITY LAYERS                             │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  LAYER 1: Network Edge                                          │
│  ├── Cloudflare Proxy (DDoS, WAF)                              │
│  └── UFW Firewall (allow only 80, 443, 22)                     │
│                                                                 │
│  LAYER 2: Reverse Proxy                                         │
│  ├── NGINX Security Headers                                     │
│  │   ├── X-Frame-Options: DENY                                 │
│  │   ├── X-Content-Type-Options: nosniff                       │
│  │   ├── Content-Security-Policy                               │
│  │   └── Strict-Transport-Security                             │
│  └── NPM Forward Auth → Authelia                               │
│                                                                 │
│  LAYER 3: Network Isolation                                     │
│  ├── Wireguard VPN (inter-VM traffic)                          │
│  ├── Docker Network (bridge isolation)                         │
│  └── No exposed ports (internal only)                          │
│                                                                 │
│  LAYER 4: Container Security                                    │
│  ├── Docker Compose: no "ports:" (use networks)                │
│  ├── Read-only containers where possible                       │
│  └── Non-root user in containers                               │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

**UFW Rules (per VM):**

```bash
# Default deny
ufw default deny incoming
ufw default allow outgoing

# Allow SSH (restrict to known IPs if possible)
ufw allow 22/tcp

# Allow HTTP/HTTPS (only on proxy VM)
ufw allow 80/tcp
ufw allow 443/tcp

# Wireguard (inter-VM)
ufw allow 51820/udp
```

**Docker Compose Pattern (no exposed ports):**

```yaml
# SECURE: Internal network only
services:
  app:
    networks:
      - internal
    # NO "ports:" section - accessed via reverse proxy

networks:
  internal:
    driver: bridge
```

**NGINX Security Headers:**

```nginx
# Add to NPM Advanced config
add_header X-Frame-Options "SAMEORIGIN" always;
add_header X-Content-Type-Options "nosniff" always;
add_header X-XSS-Protection "1; mode=block" always;
add_header Referrer-Policy "strict-origin-when-cross-origin" always;
add_header Permissions-Policy "geolocation=(), microphone=(), camera=()" always;
```

---

## B2) Service Architecture

### B21) Containers - Docker Compose Patterns

**Standard Service Pattern:**

```yaml
# Pattern: service-name/docker-compose.yml
version: "3.8"
services:
  app:
    image: ${SERVICE_IMAGE}
    container_name: ${SERVICE_NAME}-app
    restart: unless-stopped
    networks:
      - internal
      - proxy
    volumes:
      - ./data:/data
    environment:
      - TZ=Europe/Berlin
    labels:
      - "com.centurylinklabs.watchtower.enable=true"

networks:
  internal:
    driver: bridge
  proxy:
    external: true
    name: npm_network
```

**Multi-Container Service Pattern:**

```yaml
# Pattern: service with frontend + backend + database
services:
  front:
    build: ./frontend
    depends_on: [app]

  app:
    image: ${APP_IMAGE}
    depends_on: [db]
    environment:
      - DATABASE_URL=postgresql://db:5432/${DB_NAME}

  db:
    image: postgres:15-alpine
    volumes:
      - db_data:/var/lib/postgresql/data

volumes:
  db_data:
```

---

### B22) Databases - Schemas & Migrations

**Database Distribution:**

| Service | Database | Location | Backup Strategy |
|---------|----------|----------|-----------------|
| mail-* | Maildir | oci-f-micro_1 | Syncthing → local |
| analytics | MariaDB | oci-f-micro_2 | Daily SQL dump |
| authelia | PostgreSQL | gcp-f-micro_1 | Persistent volume |
| git | SQLite | oci-p-flex_1 | File backup |
| photos | SQLite | oci-p-flex_1 | File backup |
| workflows | PostgreSQL | oci-p-flex_1 | Daily SQL dump |

**Migration Strategy:**
1. Schema changes via numbered migration files
2. Backup before migration
3. Test in dev environment first
4. Rollback plan documented

---

### B23) APIs - Contracts & Versioning

**API Standards:**

| Aspect | Standard |
|--------|----------|
| Format | REST + JSON |
| Auth | Bearer token (from Authelia session) |
| Versioning | URL prefix `/api/v1/` |
| Docs | OpenAPI 3.0 spec |
| Errors | RFC 7807 Problem Details |

**Central API Gateway (api.diegonmarcos.com):**

```
/api/v1/
├── /services      # Service catalog
├── /metrics       # Monitoring data
├── /health        # Health checks
└── /auth          # Auth status
```

---

## B3) Infrastructure Architecture

### B31) Networking - DNS, SSL, Reverse Proxy

**DNS Configuration (Cloudflare):**

| Record | Type | Target | Proxy |
|--------|------|--------|-------|
| @ | A | 34.55.55.234 | Yes |
| * | CNAME | @ | Yes |
| mail | A | 130.110.251.193 | No (direct) |

**SSL Strategy:**
- Cloudflare Origin certificates (15 years)
- NPM manages Let's Encrypt for non-proxied
- Force HTTPS everywhere

**Reverse Proxy Rules (NPM):**

```
*.diegonmarcos.com → NPM (34.55.55.234)
  ├── Forward Auth → Authelia (9091)
  └── Proxy to backend VM:port
```

---

### B32) Storage - Volumes & Backups

**Volume Strategy:**

| Type | Mount | Backup |
|------|-------|--------|
| Config | `./config:/config` | Git repo |
| Data | `./data:/data` | Syncthing |
| Database | Named volume | SQL dump |
| Logs | `/var/log` | Rotate + archive |

**Backup Schedule:**

| Target | Frequency | Retention | Method |
|--------|-----------|-----------|--------|
| Configs | On change | Forever | Git push |
| User data | Real-time | 30 days | Syncthing |
| Databases | Daily 3AM | 7 days | pg_dump/mysqldump |
| Full VM | Weekly | 4 weeks | Cloud snapshot |

---

### B33) Scaling - Wake-on-Demand & GPU

**Wake-on-Demand (oci-p-flex_1):**

```
Request → NPM → Check if VM running
                    │
        ┌───────────┴───────────┐
        │ Running               │ Stopped
        ▼                       ▼
   Forward to VM          Wake VM via OCI API
                               │
                          Wait for ready
                               │
                          Forward request
```

**GPU Provisioning (TensorDock/Vast.ai):**

```bash
# On-demand GPU workflow
1. Request GPU workload
2. Provision cheapest available GPU VM
3. Pull model/data from cloud storage
4. Execute workload
5. Push results to cloud storage
6. Terminate GPU VM
```

---

# C) Roadmap - Planning & Prioritization

## C1) Phases - Implementation Milestones

### Phase 1: Security Foundation (PRIORITY)
**Status:** In Progress
**Dependencies:** None

| Step | Task | Status |
|------|------|--------|
| 1.1 | Deploy Authelia on GCP VM | Done |
| 1.2 | Configure GitHub OAuth App | Done |
| 1.3 | Setup NPM forward auth | Done |
| 1.4 | Test dual auth flow (GitHub + TOTP) | In Progress |
| 1.5 | Document credentials in LOCAL_KEYS | In Progress |

### Phase 2: Core Services
**Status:** Planned
**Dependencies:** Phase 1

| Step | Task | Status |
|------|------|--------|
| 2.1 | Mail (Mailu) deployment | Done |
| 2.2 | Sync (Syncthing) deployment | Done |
| 2.3 | Analytics (Matomo) deployment | Done |
| 2.4 | Vault (Vaultwarden) deployment | Planned |
| 2.5 | Photos (Photoprism) deployment | In Progress |

### Phase 3: DevOps Infrastructure
**Status:** Planned
**Dependencies:** Phase 1, Phase 2

| Step | Task | Status |
|------|------|--------|
| 3.1 | Monitoring collectors (Python) | Planned |
| 3.2 | Flask API endpoints | Planned |
| 3.3 | Cloud Portal (SvelteKit) | Planned |
| 3.4 | Architecture Specs system | Planned |

### Phase 4: Advanced Services
**Status:** Future
**Dependencies:** Phase 3

| Step | Task | Status |
|------|------|--------|
| 4.1 | Terminals (ttyd, code-server) | Future |
| 4.2 | Workflows (Temporal, LangGraph) | Future |
| 4.3 | AI Chat integration | Future |

---

## C2) Dependencies - Service Graph

```
┌─────────────────────────────────────────────────────────────────────┐
│                      SERVICE DEPENDENCY GRAPH                         │
├─────────────────────────────────────────────────────────────────────┤
│                                                                     │
│  LAYER 0: INFRASTRUCTURE (must be first)                            │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐                             │
│  │   NPM   │  │Authelia │  │  Redis  │                             │
│  │ (proxy) │→ │  (auth) │→ │ (cache) │                             │
│  └────┬────┘  └────┬────┘  └─────────┘                             │
│       │            │                                                │
│  LAYER 1: CORE SERVICES (24/7)                                      │
│       ▼            ▼                                                │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐                             │
│  │  Mail   │  │Analytics│  │Flask API│                             │
│  └─────────┘  └─────────┘  └────┬────┘                             │
│                                 │                                   │
│  LAYER 2: ON-DEMAND SERVICES                                        │
│                                 ▼                                   │
│  ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────┐               │
│  │  Sync   │  │ Photos  │  │  Vault  │  │   Git   │               │
│  └─────────┘  └─────────┘  └─────────┘  └─────────┘               │
│                                                                     │
│  LAYER 3: PORTAL & MONITORING                                       │
│  ┌─────────────────────────────────────────────────────────────┐   │
│  │  Cloud Portal (depends on: Flask API, all services)          │   │
│  │  Monitoring (depends on: all VMs running collectors)         │   │
│  └─────────────────────────────────────────────────────────────┘   │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

---

## C3) Backlog - Prioritized Tasks

### High Priority (Now)
- [ ] Complete Authelia TOTP setup
- [ ] Deploy Photoprism with proper auth
- [ ] Setup Vaultwarden
- [ ] Document all credentials in LOCAL_KEYS

### Medium Priority (Next)
- [ ] Build monitoring collectors
- [ ] Create Cloud Portal MVP
- [ ] Setup architecture specs system
- [ ] Configure email alerts

### Low Priority (Later)
- [ ] Terminal services (ttyd, code-server)
- [ ] Workflow engines (Temporal, LangGraph)
- [ ] AI Chat integration
- [ ] GPU on-demand provisioning

### Tech Debt
- [ ] Consolidate docker-compose files
- [ ] Standardize environment variables
- [ ] Create backup automation scripts
- [ ] Document disaster recovery procedures

---

# D) DevOps - Operations & Observability

## D1) Portal - Services Access Dashboard

**Plan:** `0.spec/Task_CloudDash_Webfront/PLAN_Webfront.md`
**Stack:** SvelteKit 5 + SCSS

```
┌─────────────────────────────────────────────────────────────┐
│                    SERVICES DASHBOARD                        │
├─────────────────────────────────────────────────────────────┤
│  [Cards] [List]                              [Dark/Light]   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  FRIDGE (Products)                                          │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   📧 Mail   │  │   📂 Sync   │  │   📷 Photos │         │
│  │   status:on │  │   status:on │  │   status:dev│         │
│  │   [Access]  │  │   [Access]  │  │   [Access]  │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│                                                             │
│  KITCHEN (Infrastructure)                                   │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │  📊 Matomo  │  │   ⚙️ n8n    │  │   🔒 Vault  │         │
│  │   status:on │  │   status:on │  │   status:on │         │
│  │   [Access]  │  │   [Access]  │  │   [Access]  │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

**Features:**
- Cards/List view toggle
- Auth redirect through Authelia
- Service status indicators (on/dev/hold/offline)
- Fridge/Kitchen category grouping

---

## D2) Monitoring - Metrics & Alerts

**Plan:** `0.spec/Task_Monitoring/PLAN_Monitoring.md`

### Monitoring Architecture

```
┌──────────────┐    ┌──────────────┐    ┌──────────────┐
│ VM Collector │    │ VM Collector │    │ VM Collector │
│ (Python)     │    │ (Python)     │    │ (Python)     │
└──────┬───────┘    └──────┬───────┘    └──────┬───────┘
       │                   │                   │
       └───────────────────┼───────────────────┘
                           │ Syncthing
                           ▼
              ┌──────────────────────────────┐
              │     Main Python (p-flex)      │
              │  • Aggregation                │
              │  • Alert checking             │
              │  • Export: JSON/CSV/MD        │
              │  • Flask API                  │
              └──────────────────────────────┘
```

### Export Formats

| Format | Purpose | Location |
|--------|---------|----------|
| JSON | API responses, webfront | `/data/metrics.json` |
| CSV | Spreadsheet analysis | `/data/metrics.csv` |
| MD | Human-readable reports | `/data/REPORT.md` |

### Alert Thresholds

| Metric | Warning | Critical | Action |
|--------|---------|----------|--------|
| CPU | 70% | 90% | Email alert |
| RAM | 80% | 95% | Email + scale |
| Disk | 80% | 90% | Email + cleanup |
| Service Down | 1 min | 5 min | Email + restart |

---

## D3) Knowledge Center

### Architecture Docs
**Plan:** `0.spec/Task_ArchSpecs/PLAN_ArchSpecs.md`

| Document | Purpose | Format |
|----------|---------|--------|
| MASTERPLAN.md | This document | Markdown |
| Service specs | Per-service details | JSON + MD |
| Network diagrams | Topology visualization | Mermaid |

### API Docs
| Endpoint | Documentation |
|----------|---------------|
| `/api/v1/*` | OpenAPI 3.0 spec |
| Service APIs | Per-service Swagger |

### Wiki / FAQ
| Topic | Content |
|-------|---------|
| Getting Started | How to access services |
| Troubleshooting | Common issues & fixes |
| Runbooks | Operational procedures |

---

## D4) Code Practices

> Reference: `MASTERPLAN_LINKTREE.md → D8) Code Practices` (full details)

### Backend (Python)

```
Category          | Standard
──────────────────┼────────────────────────────────────────────────────────
Language          | Python 3.11+ with type hints
Package Manager   | Poetry (NOT pip install globally)
Framework         | Flask for APIs, FastAPI for async
Templating        | Jinja2 for HTML/email/config generation
Data Processing   | Pandas for DataFrames, xsv for heavy CSV
Testing           | pytest + pytest-cov
Linting           | ruff (replaces flake8, isort, black)
```

### Infrastructure Code

```
Category          | Standard
──────────────────┼────────────────────────────────────────────────────────
IaC               | Docker Compose (no Kubernetes for personal infra)
Config Management | Jinja2 templates → YAML/TOML
Secrets           | Environment variables, never in code
Shell Scripts     | Bash with shellcheck, set -euo pipefail
```

### Docker Compose Standards

```yaml
# Standard pattern for all services
version: "3.8"
services:
  app:
    image: ${IMAGE}:${VERSION:-latest}
    container_name: ${SERVICE}-app
    restart: unless-stopped
    networks:
      - internal
    volumes:
      - ./data:/data:rw
      - ./config:/config:ro
    environment:
      - TZ=${TZ:-Europe/Berlin}
    healthcheck:
      test: ["CMD", "curl", "-f", "http://localhost:${PORT}/health"]
      interval: 30s
      timeout: 10s
      retries: 3
    labels:
      - "com.centurylinklabs.watchtower.enable=true"

networks:
  internal:
    driver: bridge
```

---

## D5) System Practices

### Package Management

**Rule:** NEVER install packages system-wide. Use isolated environments.

```
Tool              | Purpose                    | Command
──────────────────┼────────────────────────────┼────────────────────────────────
Poetry            | Python dependencies        | poetry add <package>
pipx              | Python CLI tools           | pipx install <tool>
nvm               | Node.js versions           | nvm use 18
npm (local)       | JS dependencies            | npm install (in project)
Docker            | Service isolation          | docker compose up
```

### Poetry Workflow

```bash
# Initialize new project
cd /path/to/project
poetry init

# Add dependencies
poetry add flask jinja2 requests
poetry add --group dev pytest ruff

# Run commands in virtual environment
poetry run python script.py
poetry run pytest

# Install from pyproject.toml
poetry install

# Export requirements.txt (for Docker)
poetry export -f requirements.txt -o requirements.txt
```

### Project Structure (Python Backend)

```
/<service>/
├── pyproject.toml           # Poetry config + dependencies
├── poetry.lock              # Locked versions
├── src/
│   └── <service>/
│       ├── __init__.py
│       ├── main.py          # Entry point
│       ├── api/             # API routes
│       ├── services/        # Business logic
│       ├── models/          # Data models
│       └── utils/           # Helpers
├── tests/
│   └── test_*.py
├── templates/               # Jinja2 templates
├── config/
│   └── settings.py          # Pydantic settings
├── Dockerfile
├── docker-compose.yml
└── .env.example
```

### Shell Script Standards

```bash
#!/usr/bin/env bash
set -euo pipefail  # Exit on error, undefined vars, pipe failures

# Constants at top
readonly SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
readonly LOG_FILE="/var/log/script.log"

# Functions before main logic
log() { echo "[$(date +'%Y-%m-%d %H:%M:%S')] $*" | tee -a "$LOG_FILE"; }
die() { log "ERROR: $*"; exit 1; }

# Main logic
main() {
    log "Starting..."
    # ...
    log "Done."
}

main "$@"
```

### Environment Variables

```bash
# .env.example (committed to git)
SERVICE_NAME=myservice
SERVICE_PORT=8080
DATABASE_URL=postgresql://localhost:5432/mydb
# SECRET_KEY=  # Never commit actual secrets

# .env (NOT committed, in .gitignore)
SECRET_KEY=actual-secret-here
```

### Git Practices

```
Pattern           | Rule
──────────────────┼────────────────────────────────────────────────────────
.gitignore        | Always include: .env, __pycache__, node_modules, dist/
Commits           | Conventional: feat:, fix:, docs:, chore:, refactor:
Branches          | main (production), dev (integration), feature/*
Secrets           | NEVER commit, use .env + .gitignore
Large files       | Use Git LFS or external storage
```

### Systemd Services (for non-Docker)

```ini
# /etc/systemd/system/myservice.service
[Unit]
Description=My Service
After=network.target

[Service]
Type=simple
User=diego
WorkingDirectory=/home/diego/services/myservice
ExecStart=/home/diego/.local/bin/poetry run python -m myservice
Restart=always
RestartSec=5
Environment=PYTHONUNBUFFERED=1

[Install]
WantedBy=multi-user.target
```

### Backup Strategy

```
Data Type         | Method                     | Frequency     | Retention
──────────────────┼────────────────────────────┼───────────────┼─────────────
Configs           | Git push                   | On change     | Forever
User data         | Syncthing                  | Real-time     | 30 days
Databases         | pg_dump / mysqldump        | Daily 3AM     | 7 days
VM snapshots      | Cloud provider             | Weekly        | 4 weeks
LOCAL_KEYS        | Manual to encrypted USB    | Monthly       | Forever
```

---

## File Structure

```
/home/diego/Documents/Git/back-System/cloud/
├── 0.spec/
│   ├── MASTERPLAN_CLOUD.md              # THIS FILE (Product-Engineer Handoff)
│   │
│   ├── Task_Security2faOAuth20/         # B1) Security Architecture
│   │   └── PLAN_DualAuth_Security.md
│   │
│   ├── Task_ArchSpecs/                  # B2) Service Architecture
│   │   └── PLAN_ArchSpecs.md
│   │
│   ├── Task_Monitoring/                 # D2) Monitoring
│   │   └── PLAN_Monitoring.md
│   │
│   └── Task_CloudDash_Webfront/         # D1) Portal
│       └── PLAN_Webfront.md
│
├── 1.ops/
│   ├── cloud_dash.json                  # Services data (source of truth)
│   ├── cloud_dash.py                    # Flask API server
│   └── monitoring/                      # Python collectors & aggregators
│
├── vps_oracle/
│   ├── vm-oci-f-micro_1/               # Mail VM
│   ├── vm-oci-f-micro_2/               # Analytics VM
│   └── vm-oci-p-flex_1/                # Dev services VM
│
└── vps_gcloud/
    └── vm-gcp-f-micro_1/               # Proxy + Auth VM

/home/diego/Documents/Git/front-Github_io/cloud/
├── src/                                 # SvelteKit 5 source
│   ├── lib/                             # Components & utilities
│   └── routes/                          # Page routes
├── static/                              # Static assets
└── 1.ops/build.sh                       # Build script
```

---

## Document Map

| Section | Purpose | Owner |
|---------|---------|-------|
| **A) HANDOFF** | Complete service & stack definition | Product + Engineer |
| A0-A1 | Stack choices + Service catalog | Product defines |
| A2-A3 | Resources + Infrastructure | Engineer validates |
| A4-A5 | Tech research + Current state | Both collaborate |
| **B) ARCHITECTURE** | Technical deep dives | Engineer owns |
| B1 | Security patterns | Engineer |
| B2 | Service patterns | Engineer |
| B3 | Infrastructure patterns | Engineer |
| **C) ROADMAP** | Planning & prioritization | Product + Engineer |
| C1-C3 | Phases, dependencies, backlog | Both collaborate |
| **D) DEVOPS** | Operations & observability | Engineer owns |
| D1-D3 | Portal, monitoring, docs | Engineer |

---

## Quick Reference

### Service URLs

| Service | URL | Auth |
|---------|-----|------|
| NPM Admin | http://34.55.55.234:81 | Local |
| Authelia | https://auth.diegonmarcos.com | - |
| Mail | https://mail.diegonmarcos.com | Authelia |
| Analytics | https://analytics.diegonmarcos.com | Authelia |
| n8n | https://n8n.diegonmarcos.com | Authelia |
| Gitea | https://git.diegonmarcos.com | Authelia |
| Sync | https://sync.diegonmarcos.com | Authelia |
| Vault | https://vault.diegonmarcos.com | Authelia |
| Photos | https://photos.diegonmarcos.com | Authelia |
| Cloud | https://cloud.diegonmarcos.com | Authelia |

---

*Generated by Claude (Opus) - CTO*
*Last Updated: 2025-12-11*
