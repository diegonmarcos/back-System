# Cloud Infrastructure Master Plan v2

**Project:** Diego's Cloud Infrastructure
**CTO:** Claude (Opus)
**Date:** 2025-12-09
**Status:** PLANNING COMPLETE - READY FOR IMPLEMENTATION

---

## Executive Summary

This master plan defines Diego's cloud infrastructure through a hierarchical system:

```
A) Services          - Complete list of all cloud services
B) Architecture      - Infrastructure specifications
   B1) Security      - Authentication & access control
       B11) Web Architecture (Dual Auth)
       B12) Dev Access (SSH/Vault)
       B13) Servers Security (Isolation)
   B2) Resources     - Capacity planning & estimation
       B20) THE DEMAND (Strategy & Requirements)
       B21) TABLE (Storage/RAM/VRAM/CPU/Bandwidth)
       B22) TBD
   B3) Providers     - Oracle, GCloud, Cloudflare
   B4) Cost          - Cost estimation & optimization
C) Monitoring        - Python collectors + Flask API
D) Webfront          - SvelteKit 5 + SCSS dashboard
   D1) Services Access
   D2) Dashboard (Online/Offline modes)
```

Jinja2 templating

---

## Infrastructure Overview

```
┌─────────────────────────────────────────────────────────────────────────┐
│                        CLOUD INFRASTRUCTURE                              │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  ┌─────────────────┐        ┌─────────────────────────────────────────┐│
│  │   CLOUDFLARE    │───────▶│          GCP VM (gcp-f-micro_1)         ││
│  │  (DNS + CDN)    │        │              34.55.55.234               ││
│  └─────────────────┘        │  ┌───────────────────────────────────┐  ││
│                             │  │      NPM (Reverse Proxy)           │  ││
│                             │  │      Authelia (2FA Gateway)        │  ││
│                             │  └───────────────────────────────────┘  ││
│                             └──────────────────┬──────────────────────┘│
│                                                │                        │
│                    ┌───────────────────────────┼───────────────────┐   │
│                    │                           │                   │   │
│                    ▼                           ▼                   ▼   │
│  ┌─────────────────────────┐  ┌─────────────────────────┐  ┌─────────┐│
│  │  OCI oci-f-micro_1      │  │  OCI oci-f-micro_2      │  │  OCI    ││
│  │    130.110.251.193      │  │    129.151.228.66       │  │  p-flex ││
│  │                         │  │                         │  │  84.235.││
│  │  • Stalwart Mail        │  │  • Matomo Analytics     │  │  234.87 ││
│  │                         │  │                         │  │         ││
│  │  FREE TIER 24/7         │  │  FREE TIER 24/7         │  │ • n8n   ││
│  └─────────────────────────┘  └─────────────────────────┘  │ • Gitea ││
│                                                            │ • Sync  ││
│                                                            │ • Vault ││
│                                                            │ • Photos││
│                                                            │         ││
│                                                            │ PAID    ││
│                                                            │ WAKE-ON ││
│                                                            └─────────┘│
└─────────────────────────────────────────────────────────────────────────┘
```

---

## A) Services - Stack & Features Definition

```
Pattern: SERVICE → front (our GUI) + app (forked/custom) + db(s)

Container          | Purpose                         | Stack
───────────────────┼─────────────────────────────────┼──────────────────────────
```

### FRIDGE
#### Terminals

```
terminals          | AI-Powered Dev Environment      | -
  ↳ terminals-front| Hub landing + tool selector     | SvelteKit 5 + SCSS
  │
  ├─ terminal      | Web Terminal (bash/zsh/fish)    | -
  │  ↳ terminal-front | Shell selector UI            | SvelteKit 5 + SCSS
  │  ↳ terminal-app   | Terminal server              | ttyd / wetty
  │  ↳ terminal-db0   | Shell history + dotfiles     | Filesystem
  │
  ├─ jupyter       | JupyterLab Notebooks            | -
  │  ↳ jupyter-front  | (uses JupyterLab UI)         | JupyterLab (built-in)
  │  ↳ jupyter-app    | Notebook server + kernels    | JupyterLab
  │  ↳ jupyter-db0    | Notebooks + workspace        | Filesystem
  │
  ├─ ide           | Web IDE                         | -
  │  ↳ ide-front      | IDE launcher + selector      | SvelteKit 5 + SCSS
  │  ↳ ide-app        | Code server                  | code-server / Cursor / Windsurf
  │  ↳ ide-db0        | Workspaces + extensions      | Filesystem
  │
  └─ ai-chat       | AI Chat Assistant               | -
     ↳ ai-front       | Chat UI                      | SvelteKit 5 + SCSS
     ↳ ai-app         | Chat backend                 | Open WebUI / LibreChat
     ↳ ai-api         | LLM API backend              | Ollama / OpenAI API
     ↳ ai-db0         | Chat history + users         | SQL:PostgreSQL
```


#### User Productivity

```
mail               | Email Suite                     | -
  ↳ mail-front     | Nginx reverse proxy             | Nginx
  ↳ mail-admin     | Admin web interface             | Mailu-Admin
  ↳ mail-imap      | IMAP server                     | Dovecot
  ↳ mail-smtp      | SMTP server                     | Postfix
  ↳ mail-webmail   | Webmail client                  | Roundcube
  ↳ mail-db0       | Mailboxes storage               | Maildir

sync               | File Synchronization Hub        | -
  ↳ sync-front     | File tree viewer (collapsible)  | SvelteKit 5 + SCSS
  ↳ sync-app       | Aggregates drive+git            | Python3
  │
  ├─ drive         | Cloud Drive (Filesystem Mount)  | -
  │  ↳ drive-front | File browser display            | SvelteKit 5 + SCSS
  │  ↳ drive-app   | Bisync / FUSE mount daemon      | Rclone
  │  ↳ drive-db0   | Mount configs + cache           | Filesystem
  │
  └─ git           | Git Hosting                     | -
     ↳ git-front   | Login + repo display            | SvelteKit 5 + SCSS
     ↳ git-app     | Git server + web UI             | Gitea
     ↳ git-db0| Users, issues, PRs              | SQL:SQLite
     ↳ git-db_obj0 | Git repositories (.git objects) | Filesystem

photos             | Photo Library Management         | -
  ↳ photo-front    | Login Ours+Front from Photoprism | SvelteKit 5 + SCSS
  ↳ photo-app      | Photo viewer + AI tagging        | Photoprism
  ↳ photo-db0 | Metadata (EXIF, location, AI)         | SQL:MariaDB
  ↳ photo-db_obj0  | Photo files storage              | Filesystem
```

#### User Security

```
vault              | Password Manager                     | -
  ↳ vault-front    | Login (uses Vaultwarden UI)          | Vaultwarden (built-in)
  ↳ vault-app      | Vaultwarden (Bitwarden self hosted)  | Vaultwarden
  ↳ vault-db0      | Encrypted credentials                | SQL:SQLite

vpn                | VPN Server                           | -
  ↳ vpn-front      | Web UI for client management         | wg-easy (built-in)
  ↳ vpn-app        | VPN tunnel server                    | Wireguard
  ↳ vpn-db0        | Client configs + keys                | Filesystem
```

---

### KITCHEN
#### Devs Cloud Dashboard

```
cloud              | Cloud Dashboard & Monitoring    | -
  ↳ cloud-front    | Dashboard UI                    | SvelteKit 5 + SCSS
  ↳ cloud-app      | Backend logic + collectors      | Python3
    ↳ cloud-db0      | Config + metrics storage        | Only JSON

analytics          | Web Analytics Platform          | -
  ↳ analytics-front| Login + stats display           | Matomo (bult-in)
  ↳ analytics-app  | Analytics engine                | Matomo (PHP-FPM)
  ↳ analytics-db0  | Visits, events, reports         | SQL:MariaDB

workflows          | Workflow Automation Hub         | -
  ↳ workflows-front| Hub landing + workflow selector | SvelteKit 5 + SCSS
  │
  ├─ temporal      | Infrastructure Workflows         | -
  │  ↳ temporal-front  | Workflow dashboard           | Temporal UI (built-in)
  │  ↳ temporal-app    | Workflow engine              | Temporal
  │  ↳ temporal-db0    | Workflow state, history      | SQL:PostgreSQL
  │
  └─ langgraph     | AI Agentic Workflows             | -
     ↳ langgraph-front | Agent monitor UI             | SvelteKit 5 + SCSS
     ↳ langgraph-app   | Agent orchestration          | LangGraph + FastAPI
     ↳ langgraph-db0   | Checkpoints, chat history    | SQL:PostgreSQL
     ↳ langgraph-vec   | Vector embeddings            | pgvector
     ↳ langgraph-gpu   | GPU compute runtime          | Vast.ai / Lambda
```

#### Devs Security

```
webserver          | Central Proxy & Web Serving     | -
  ↳ proxy-front    | Lggin+NPM admin UI                    | NPM (built-in)
  ↳ proxy-app      | Reverse proxy + SSL termination | NPM (Nginx Proxy Manager)
  ↳ proxy-db0      | Proxy configs + certs           | SQL:SQLite

oauth2             | GitHub OAuth2 Authentication    | -
  ↳ oauth2-front   | Login redirect page             | OAuth2-Proxy (built-in)
  ↳ oauth2-app     | OAuth2 proxy server             | OAuth2-Proxy
  ↳ oauth2-db0     | Session tokens                  | Redis / Memory

authelia           | 2FA / SSO Gateway               | -
  ↳ authelia-front | Login + 2FA prompt              | Authelia (built-in)
  ↳ authelia-app   | Auth server + session mgmt      | Authelia
  ↳ authelia-db0   | Users, sessions, TOTP seeds     | SQL:PostgreSQL
```

#### Devs Infrastructure

```
api                | Central API Gateway             | -
  ↳ api-front      | API docs / Swagger UI           | SvelteKit 5 + SCSS
  ↳ api-app        | Flask API server                | Python:Flask
  ↳ api-db0        | Aggregated JSONs from all apps  | Hybrid:JSON/SQLite

cache              | In-Memory Cache                 | -
  ↳ cache-app      | Session/cache data store        | Redis
```




### Service URLs (Proxied)



### Plan
#### by service
```
Service           | Public URL                      | VM             | Container       | IP:Port
──────────────────┼─────────────────────────────────┼────────────────┼─────────────────┼────────────────────────

## FRIDGE

Terminals
↳ WebTerminal     | terminal.diegonmarcos.com       | oci-p-flex_1   | terminal-app    |
↳ Jupyterlab      | jupyter.diegonmarcos.com        | oci-p-flex_1   | jupyter-app     |
↳ IDE             | ide.diegonmarcos.com            | oci-p-flex_1   | ide-app         |
↳ AI Chat         | chat.diegonmarcos.com           | oci-p-flex_1   | ai-app          |

User Productivity
↳ Mail            | mail.diegonmarcos.com           | oci-f-micro_1  | mail-front      |
↳ Sync            | sync.diegonmarcos.com           | oci-p-flex_1   | sync-app        |
↳ Drive           | drive.diegonmarcos.com          | oci-p-flex_1   | drive-app       |
↳ Git             | git.diegonmarcos.com            | oci-p-flex_1   | git-app         |
↳ Photos          | photos.diegonmarcos.com         | oci-p-flex_1   | photo-app       |

User Security
↳ Vault           | vault.diegonmarcos.com          | oci-p-flex_1   | vault-app       |
↳ VPN             | vpn.diegonmarcos.com            | oci-p-flex_1   | vpn-app         |

## KITCHEN

Devs Cloud Dashboard
↳ Analytics           | analytics.diegonmarcos.com      | oci-f-micro_2  | analytics-app   |
↳ Cloud Dashboard     | cloud.diegonmarcos.com          | oci-p-flex_1   | cloud-app       |
↳ Temporal            | temporal.diegonmarcos.com       | oci-p-flex_1   | temporal-app    |
↳ LangGraph           | langgraph.diegonmarcos.com      | oci-p-flex_1   | langgraph-app   |

Devs Security
↳ Proxy Admin     | proxy.diegonmarcos.com          | gcp-f-micro_1  | proxy-app       |
↳ Auth (Authelia) | auth.diegonmarcos.com           | gcp-f-micro_1  | authelia-app    |
↳ OAuth2          | auth.diegonmarcos.com/oauth2    | gcp-f-micro_1  | oauth2-app      |

Devs Infrastructure
↳ API Gateway     | api.diegonmarcos.com            | oci-p-flex_1   | api-app         |
↳ Cache           | (internal)                      | oci-p-flex_1   | cache-app       |
```

#### by VM
```
Host   | VM             | RAM   | VRAM | Storage | IP              | Services Running                          | Notes
───────┼────────────────┼───────┼──────┼─────────┼─────────────────┼───────────────────────────────────────────┼─────────────────
GCloud | gcp-f-micro_1  | 1 GB  | -    | 30 GB   |                 | npm, authelia, redis                      | 24/7 FREE
Oracle | oci-f-micro_1  | 1 GB  | -    | 47 GB   |                 | mailu-* (8 containers)                    | 24/7 FREE
Oracle | oci-f-micro_2  | 1 GB  | -    | 47 GB   |                 | matomo-app, matomo-db                     | 24/7 FREE
Oracle | oci-p-flex_1   | 8 GB  | -    | 100 GB  |                 | sync, photos, n8n, git, cal, terminal...  | WAKE $5.5/mo
Oracle | oci-f-arm_1    | 24 GB | -    | 200 GB  |                 |                                           | 24/7 Free
```



### Today (Actual Running)

#### by service
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

#### by VM
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

## B) Architecture

### B1) Security

#### B11) Web Architecture - Dual Authentication

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

#### B12) Dev Access - SSH & Vault Management

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

#### B13) Servers Security - Isolation & Hardening

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

### B2) Resources

#### B20) THE DEMAND - Strategy & Requirements

**Storage Strategy:**

| Type | Strategy | Services |
|------|----------|----------|
| **24/7 Always-On** | Free tier VMs | Mail, Analytics, NPM, Authelia |
| **On-Demand** | Wake when needed | n8n, Gitea, Sync, Vault, Photos |
| **Pay-per-Use** | Cloud GPU instances | AI/ML workloads (future) |

**Resource Demands:**

| Resource | Demand Source | Strategy |
|----------|---------------|----------|
| **Storage** | Photos, Mail, Sync | Local NVMe + cloud backup |
| **VRAM** | AI models (future) | Pay-per-use GPU VPS (Vast.ai, Lambda) |
| **Bandwidth** | Matomo tracking, VPN | Monitor with quotas, Cloudflare caching |
| **RAM** | Multiple containers | Optimize per service, swap for burst |

**24/7 vs On-Demand Decision Matrix:**

| Service | Traffic Pattern | Decision | Reason |
|---------|-----------------|----------|--------|
| Mail | Continuous | 24/7 | Email must be always available |
| Analytics | Continuous | 24/7 | Tracking scripts always active |
| NPM/Authelia | Continuous | 24/7 | Gateway for all services |
| n8n | Scheduled | On-demand | Workflows run at specific times |
| Gitea | Sporadic | On-demand | Dev access only when coding |
| Photos | Sporadic | On-demand | Personal use, not critical |

---

#### B21) TABLE - Resource Estimation

**VM Capacity:**

| VM ID | vCPU | RAM | Storage | Bandwidth | Tier |
|-------|------|-----|---------|-----------|------|
| gcp-f-micro_1 | 0.25 | 1 GB | 30 GB | 1 GB/day | Free |
| oci-f-micro_1 | 1 | 1 GB | 47 GB | 10 TB/mo | Free |
| oci-f-micro_2 | 1 | 1 GB | 47 GB | 10 TB/mo | Free |
| oci-p-flex_1 | 2 | 12 GB | 100 GB | 10 TB/mo | Paid |

**Service Resource Allocation:**

| Container | RAM | CPU | Storage | Bandwidth/mo |
|-----------|-----|-----|---------|--------------|
| proxy-app | 256 MB | 0.1 | 1 GB | 50 GB |
| authelia-app | 128 MB | 0.1 | 100 MB | 10 GB |
| oauth2-app | 64 MB | 0.05 | 50 MB | 5 GB |
| mail-* (suite) | 512 MB | 0.2 | 10 GB | 5 GB |
| analytics-app | 256 MB | 0.1 | 5 GB | 100 GB |
| infra-app (n8n) | 512 MB | 0.2 | 2 GB | 20 GB |
| git-app | 256 MB | 0.1 | 5 GB | 10 GB |
| drive-app | 128 MB | 0.1 | 50 GB | 200 GB |
| vault-app | 128 MB | 0.1 | 500 MB | 1 GB |
| photo-app | 256 MB | 0.1 | 20 GB | 50 GB |
| cloud-front | 64 MB | 0.05 | 100 MB | 10 GB |
| cloud-app | 128 MB | 0.1 | 500 MB | 5 GB |
| api-app | 128 MB | 0.1 | 1 GB | 20 GB |
| chat-app | 512 MB | 0.2 | 2 GB | 30 GB |
| cache-app | 256 MB | 0.1 | 1 GB | - |

**Future AI/VRAM Requirements:**

| Workload | VRAM Needed | Provider Option | Est. Cost |
|----------|-------------|-----------------|-----------|
| Local LLM (7B) | 8 GB | Vast.ai RTX 3080 | $0.20/hr |
| Image Gen (SD) | 12 GB | Lambda A10 | $0.60/hr |
| Fine-tuning | 24 GB | RunPod A100 | $1.50/hr |

---

#### B22) TBD

*(Reserved for additional resource specifications)*

---

### B3) Providers

| Provider | Services | Cost Model | Region |
|----------|----------|------------|--------|
| **Cloudflare** | DNS, CDN, SSL, Proxy | Free (Pro features) | Global |
| **GCloud** | 1 VM (e2-micro) | Free Tier | us-central1 |
| **Oracle** | 4 VMs (2 free, 2 paid) | Free Tier + Flex | eu-frankfurt |
| **GitHub** | Pages hosting, OAuth App | Free | - |
| **Gmail** | SMTP relay | Free (App Password) | - |

---

### B4) Cost Estimation

**Monthly Cost Breakdown:**

| Item | Provider | Cost/Month |
|------|----------|------------|
| GCP e2-micro | GCloud | $0 (Free Tier) |
| OCI A1.Flex x2 (Free) | Oracle | $0 (Free Tier) |
| OCI A1.Flex (Paid) | Oracle | ~$15-20 |
| Cloudflare | Cloudflare | $0 (Free Plan) |
| Domain | Cloudflare | ~$10/year |
| **Total** | | **~$15-20/month** |

**Optimization Strategies:**
- Wake-on-demand for paid VM (oci-p-flex_1)
- Auto-shutdown when idle
- Monitor resource usage to avoid overages

---

## C) Monitoring

**Plan:** `0.spec/Task_Monitoring/PLAN_Monitoring.md`

### Architecture

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
                           │
              ┌────────────┼────────────┐
              ▼            ▼            ▼
         ┌────────┐  ┌────────┐  ┌────────┐
         │  JSON  │  │  CSV   │  │   MD   │
         │(export)│  │(export)│  │(export)│
         └────────┘  └────────┘  └────────┘
```

### Main Python Features

```python
# /opt/monitoring/main.py
class MonitoringMain:
    def collect_metrics()     # Gather from all VMs
    def check_alerts()        # Compare to thresholds
    def export_json()         # API + file export
    def export_csv()          # Spreadsheet export
    def export_markdown()     # Human-readable report
    def serve_api()           # Flask endpoints
```

### Export Formats

| Format | Purpose | Location |
|--------|---------|----------|
| JSON | API responses, webfront consumption | `/data/metrics.json` |
| CSV | Spreadsheet analysis, historical data | `/data/metrics.csv` |
| MD | Human-readable reports, offline viewing | `/data/REPORT.md` |

---

## D) Webfront

**Plan:** `0.spec/Task_CloudDash_Webfront/PLAN_Webfront.md`
**Stack:** SvelteKit 5 + SCSS

### D1) Services Access

```
┌─────────────────────────────────────────────────────────────┐
│                    SERVICES DASHBOARD                        │
├─────────────────────────────────────────────────────────────┤
│  [Cards] [List]                              [Dark/Light]   │
├─────────────────────────────────────────────────────────────┤
│                                                             │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   📧 Mail   │  │  📊 Matomo  │  │   ⚙️ n8n    │         │
│  │   status:on │  │   status:on │  │   status:on │         │
│  │   [Access]  │  │   [Access]  │  │   [Access]  │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│                                                             │
│  ┌─────────────┐  ┌─────────────┐  ┌─────────────┐         │
│  │   🔒 Vault  │  │   📂 Sync   │  │   📷 Photos │         │
│  │   status:on │  │   status:on │  │   status:dev│         │
│  │   [Access]  │  │   [Access]  │  │   [Access]  │         │
│  └─────────────┘  └─────────────┘  └─────────────┘         │
│                                                             │
└─────────────────────────────────────────────────────────────┘
```

**Features:**
- Cards/List view toggle
- Auth redirect through Authelia
- Service status indicators (on/dev/hold/offline)
- Category grouping

---

### D2) Dashboard (Online/Offline)

**Online Mode:**
- Fetches live data via Flask API
- Auth required for commands (reboot, restart)
- Real-time metrics updates

**Offline Mode:**
- Loads from local `metrics.json`
- Works without API connection
- Read-only (no commands)

```svelte
<script lang="ts">
  // Mode detection (Svelte 5 runes)
  let apiAvailable = $state(true);

  let mode = $derived(
    typeof navigator !== 'undefined' && navigator.onLine && apiAvailable
      ? 'online'
      : 'offline'
  );

  // Data source
  let metrics = $derived(
    mode === 'online'
      ? fetchFromApi()
      : loadLocalJson()
  );
</script>
```

---

## Implementation Phases

### Phase 1: Security Foundation

1. Deploy Authelia on GCP VM
2. Configure GitHub OAuth App
3. Setup NPM forward auth
4. Test dual auth flow (GitHub + TOTP)
5. Document credentials in LOCAL_KEYS

### Phase 2: Architecture Specs

1. Create JSON schema for services
2. Write spec files for all services
3. Build Python generator (Jinja2 → MD)
4. Generate manifest.json
5. Create resources/cost data files

### Phase 3: Monitoring

1. Write Python collectors
2. Deploy to all VMs with cron
3. Setup Syncthing sync
4. Build Main Python (export JSON/CSV/MD)
5. Add Flask API endpoints
6. Configure email alerts

### Phase 4: Webfront

1. Setup SvelteKit 5 + SCSS project
2. Create service components
3. Implement auth redirect
4. Build monitoring dashboard
5. Add offline mode support
6. Deploy to GitHub Pages

---

## File Structure

```
/home/diego/Documents/Git/back-System/cloud/
├── 0.spec/
│   ├── MASTERPLAN.md                    # THIS FILE
│   ├── Task_Security2faOAuth20/
│   │   └── PLAN_DualAuth_Security.md    # B1) Security
│   ├── Task_ArchSpecs/
│   │   └── PLAN_ArchSpecs.md            # B2-B4) Resources/Providers/Cost
│   ├── Task_Monitoring/
│   │   └── PLAN_Monitoring.md           # C) Monitoring
│   └── Task_CloudDash_Webfront/
│       └── PLAN_Webfront.md             # D) Webfront
│
├── 1.ops/
│   ├── cloud_dash.json                  # Source of truth
│   ├── cloud_dash.py                    # Flask API
│   └── monitoring/                      # Monitoring scripts
│
├── vps_oracle/
│   ├── vm-oci-f-micro_1/               # Mail
│   ├── vm-oci-f-micro_2/               # Analytics
│   └── vm-oci-p-flex_1/                # Dev services
│
└── vps_gcloud/
    └── vm-gcp-f-micro_1/               # NPM + Authelia

/home/diego/Documents/Git/front-Github_io/cloud/
├── src/                                 # SvelteKit 5 source
│   ├── lib/                             # Components & utilities
│   └── routes/                          # Page routes
├── static/                              # Static assets
└── 1.ops/build.sh                       # Build script
```

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
*Last Updated: 2025-12-09*
