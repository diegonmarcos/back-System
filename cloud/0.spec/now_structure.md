CLOUD DASHBOARD

---








# Index.html
- Services
    - Cards
    - Tree

- Architeture
    - Resources
    - Server
    - AI

- Monitoring
    - Backlog
    - Status (live)






---





# Services
## Cards

Front
`3 collumns  User vs Coder`
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
        - Sync-app
        - Mail-app
        - VPN-app
        - Web_ide-app
        - Gitlab-app
        - Analytics-app

    - Data Bases (SSH)
        - sync_server-db
        - sync_files-db
        - sync_obj-db
        - mail-server-db
        - mail-obj-db
        - git_server-db
        - git_repo-db
        - matomo-db
        - n8n_ai-db
        - n8n_infra-db

    - Infra Services (SSH)
        - n8n-AI-server
        - n8n-Infra-server
        - Flask-server
        - Redis-server

    - Proxies (Web and SSH)
        - NPM-VM-Oracle_Services_Serv
        - NPM-VM-Oracle_Web_Server_1
        - NPM-VM-Oracle_Flex_ARM_Server
        - NPM-VM-Gcloud
        - NPM-VM-Generic_VPS










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
| on | **Sync** | **128-256 MB** | **5.2-106 GB** | **10-50 GB/mo** | File sync |
|  | ↳ syncthing | 128-256 MB | 100-500 MB | 10-50 GB/mo | App + config |
|  | ↳ sync-index-db | - | 100-500 MB | - | File metadata index |
|  | ↳ sync-files-db | - | ~100 GB | - | Synced files storage |
|  | ↳ sync-obj-db | - | ~5 GB | - | Object/blob storage |
| dev | **Mail Server** | **520 MB-1 GB** | **5-50 GB** | **1-10 GB/mo** | Email stack |
|  | ↳ mailserver | 512 MB - 1 GB | 100-500 MB | 1-10 GB/mo | App + config |
|  | ↳ mail-db (SQLite) | 8-32 MB | 5-50 GB | - | Mailboxes + indexes |
| dev | **OpenVPN** | **64-128 MB** | **50-100 MB** | **5-50 GB/mo** | VPN server |
|  | ↳ openvpn | 64-128 MB | 50-100 MB | 5-50 GB/mo | Client configs + certs |




##### Coder

| Mode | Service | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|------|---------|-----------|---------------|-----------------|-------|
| dev | **Web Terminal** | **64-128 MB** | **50-100 MB** | **500 MB-2 GB/mo** | Browser shell |
|  | ↳ wetty/ttyd | 64-128 MB | 50-100 MB | 500 MB-2 GB/mo | Session-based |
| on | **Cloud Dashboard** | **64-128 MB** | **50-100 MB** | **100-500 MB/mo** | Cloud Dashboard |
|  | ↳ front_web | - | ~5 MB | 50-200 MB/mo | Static HTML/CSS/JS |
|  | ↳ flask-py | 64-128 MB | 50-100 MB | 100-500 MB/mo | Flask API server |
| on | **Matomo** | **512 MB-1 GB** | **3-15 GB** | **500 MB-2 GB/mo** | Analytics platform |
|  | ↳ matomo-app | 256-512 MB | 2-5 GB | 500 MB-2 GB/mo | PHP FPM Alpine |
|  | ↳ matomo-db (MariaDB) | 256-512 MB | 1-10 GB | - | Grows with analytics data |
| dev | **Gitea** | **264-544 MB** | **11-15 GB** | **2-10 GB/mo** | Git hosting |
|  | ↳ gitea | 256-512 MB | 1-5 GB | 2-10 GB/mo | Web + Git server |
|  | ↳ gitea-db (SQLite) | 8-32 MB | Variable | - | Embedded DB |
|  | ↳ gitea-repos-db | - | ~10 GB | - | Git repositories storage |
| on | **n8n (Infra)** | **256-512 MB** | **500 MB-2 GB** | **1-5 GB/mo** | Workflow automation |
|  | ↳ n8n | 256-512 MB | 500 MB - 2 GB | 1-5 GB/mo | Workflows + execution logs |
| on | **NPM** | **512 MB-1 GB** | **400 MB-2 GB** | **20-80 GB/mo** | Reverse proxy (4 instances) |
|  | ↳ npm-oracle-web | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Web Server 1 |
|  | ↳ npm-oracle-services | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Services Server 1 |
|  | ↳ npm-oracle-arm | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle ARM (hold) |
|  | ↳ npm-gcloud | 128-256 MB | 100-500 MB | 5-20 GB/mo | GCloud (dev) |
| hold | **Redis** | **64-256 MB** | **100 MB-1 GB** | **-** | In-memory store |
|  | ↳ redis | 64-256 MB | 100 MB - 1 GB | - | Session/cache data |


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
| on | Oracle Web Server 1 | n8n, Syncthing, Flask, NPM, VPN, Gitea | ~800 MB - 1.5 GB | ~5-15 GB | ~20-80 GB/mo |
| on | Oracle Services Server 1 | Matomo, MariaDB, NPM | ~600 MB - 1.2 GB | ~5-15 GB | ~5-20 GB/mo |
| dev | GCloud Arch 1 | Mail, Terminal, NPM, SQLite | ~800 MB - 1.5 GB | ~10-50 GB | ~5-15 GB/mo |
| dev | Generic VPS | Variable services | ~1-4 GB | ~20-100 GB | ~10-50 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total ON** | | **~1.4-2.7 GB** | **~10-30 GB** | **~25-100 GB/mo** |
| | **Total DEV** | | **~1.8-5.5 GB** | **~30-150 GB** | **~15-65 GB/mo** |
| | **TOTAL Non-AI** | | **~3.2-8.2 GB** | **~40-180 GB** | **~40-165 GB/mo** |



### AI
#### Services

| Mode | Service | Category | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| hold | **n8n (AI)** | ML | **1.3-48 GB** | **3-20 GB** | **5-20 GB/mo** | AI Agentic workflows |
|  | ↳ n8n-ai | | 1-48 GB | 2-10 GB | 5-20 GB/mo | LLM context + workflows |
|  | ↳ n8n-ai-db (PostgreSQL) | | 256-512 MB | 1-10 GB | - | Varies by usage |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| | **Total HOLD** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | On hold (ARM 6-24GB avail) |
| | **TOTAL AI** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | All AI services |


#### VMs

| Mode | VM | Services | Total RAM (Est) | Total Storage (Est) | Bandwidth (Est) |
|--------|-----|----------|-----------------|---------------------|-----------------|
| hold | Oracle ARM Server | n8n (AI), NPM, PostgreSQL | ~6-24 GB | ~5-20 GB | ~10-40 GB/mo |
| dev | Generic VPS (AI) | LLM inference, AI workloads | ~8-32 GB | ~50-200 GB | ~20-100 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total HOLD** | | **~6-24 GB** | **~5-20 GB** | **~10-40 GB/mo** |
| | **Total DEV** | | **~8-32 GB** | **~50-200 GB** | **~20-100 GB/mo** |
| | **TOTAL AI** | | **~14-56 GB** | **~55-220 GB** | **~30-140 GB/mo** |



## Servers

`use the .html that already exists, dont lose it!! arch.html`

`(add here mermaid code of the architeture design)`

## AI
 `   (add here mermaid code of ach design) `
`use the .html that already exists, dont lose it!! ai-arch.html`




---


# Monitoring
## Status (live|list view)

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

##### User

`ADJUST ALL THIS TABLES TO BE THE FRAME FOR .PY AND WEB DASHBOARD`

| Mode | Service |IP:port| URL| SSH  | RAM | Storage| | Status |
|------|---------|-----------|---------------|-----------------|-------|
| on | **Sync** | **128-256 MB** | **5.2-106 GB** | **10-50 GB/mo** | File sync |
|  | ↳ syncthing | 128-256 MB | 100-500 MB | 10-50 GB/mo | App + config |
|  | ↳ sync-index-db | - | 100-500 MB | - | File metadata index |
|  | ↳ sync-files-db | - | ~100 GB | - | Synced files storage |
|  | ↳ sync-obj-db | - | ~5 GB | - | Object/blob storage |
| dev | **Mail Server** | **520 MB-1 GB** | **5-50 GB** | **1-10 GB/mo** | Email stack |
|  | ↳ mailserver | 512 MB - 1 GB | 100-500 MB | 1-10 GB/mo | App + config |
|  | ↳ mail-db (SQLite) | 8-32 MB | 5-50 GB | - | Mailboxes + indexes |
| dev | **OpenVPN** | **64-128 MB** | **50-100 MB** | **5-50 GB/mo** | VPN server |
|  | ↳ openvpn | 64-128 MB | 50-100 MB | 5-50 GB/mo | Client configs + certs |




##### Coder

| Mode | Service |IP:port| URL| SSH  | RAM | Storage| | Status |
|------|---------|-----------|---------------|-----------------|-------|
| dev | **Web Terminal** | **64-128 MB** | **50-100 MB** | **500 MB-2 GB/mo** | Browser shell |
|  | ↳ wetty/ttyd | 64-128 MB | 50-100 MB | 500 MB-2 GB/mo | Session-based |
| on | **Cloud Dashboard** | **64-128 MB** | **50-100 MB** | **100-500 MB/mo** | Cloud Dashboard |
|  | ↳ front_web | - | ~5 MB | 50-200 MB/mo | Static HTML/CSS/JS |
|  | ↳ flask-py | 64-128 MB | 50-100 MB | 100-500 MB/mo | Flask API server |
| on | **Matomo** | **512 MB-1 GB** | **3-15 GB** | **500 MB-2 GB/mo** | Analytics platform |
|  | ↳ matomo-app | 256-512 MB | 2-5 GB | 500 MB-2 GB/mo | PHP FPM Alpine |
|  | ↳ matomo-db (MariaDB) | 256-512 MB | 1-10 GB | - | Grows with analytics data |
| dev | **Gitea** | **264-544 MB** | **11-15 GB** | **2-10 GB/mo** | Git hosting |
|  | ↳ gitea | 256-512 MB | 1-5 GB | 2-10 GB/mo | Web + Git server |
|  | ↳ gitea-db (SQLite) | 8-32 MB | Variable | - | Embedded DB |
|  | ↳ gitea-repos-db | - | ~10 GB | - | Git repositories storage |
| on | **n8n (Infra)** | **256-512 MB** | **500 MB-2 GB** | **1-5 GB/mo** | Workflow automation |
|  | ↳ n8n | 256-512 MB | 500 MB - 2 GB | 1-5 GB/mo | Workflows + execution logs |
| on | **NPM** | **512 MB-1 GB** | **400 MB-2 GB** | **20-80 GB/mo** | Reverse proxy (4 instances) |
|  | ↳ npm-oracle-web | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Web Server 1 |
|  | ↳ npm-oracle-services | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Services Server 1 |
|  | ↳ npm-oracle-arm | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle ARM (hold) |
|  | ↳ npm-gcloud | 128-256 MB | 100-500 MB | 5-20 GB/mo | GCloud (dev) |
| hold | **Redis** | **64-256 MB** | **100 MB-1 GB** | **-** | In-memory store |
|  | ↳ redis | 64-256 MB | 100 MB - 1 GB | - | Session/cache data |


Totals

| | | RAM | Storage | Bandwidth | |
|------|---------|-----------|---------------|-----------------|-------|
| | **Total ON** | **~1.4-2.8 GB** | **~9-125 GB** | **~32-135 GB/mo** | Active services |
| | **Total DEV** | **~900 MB-1.8 GB** | **~66-165 GB** | **~8-72 GB/mo** | In development |
| | **Total HOLD** | **~64-256 MB** | **~100 MB-1 GB** | **-** | On hold |
| | **TOTAL Non-AI** | **~2.4-4.9 GB** | **~75-291 GB** | **~40-207 GB/mo** | All Non-AI services |

#### VMs

| Mode | Service |IP:port| URL| SSH  | RAM | Storage| | Status |
|--------|-----|----------|-----------------|---------------------|-----------------|
| on | Oracle Web Server 1 | n8n, Syncthing, Flask, NPM, VPN, Gitea | ~800 MB - 1.5 GB | ~5-15 GB | ~20-80 GB/mo |
| on | Oracle Services Server 1 | Matomo, MariaDB, NPM | ~600 MB - 1.2 GB | ~5-15 GB | ~5-20 GB/mo |
| dev | GCloud Arch 1 | Mail, Terminal, NPM, SQLite | ~800 MB - 1.5 GB | ~10-50 GB | ~5-15 GB/mo |
| dev | Generic VPS | Variable services | ~1-4 GB | ~20-100 GB | ~10-50 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total ON** | | **~1.4-2.7 GB** | **~10-30 GB** | **~25-100 GB/mo** |
| | **Total DEV** | | **~1.8-5.5 GB** | **~30-150 GB** | **~15-65 GB/mo** |
| | **TOTAL Non-AI** | | **~3.2-8.2 GB** | **~40-180 GB** | **~40-165 GB/mo** |



### AI
#### Services

| Mode | Service |IP:port| URL| SSH  | RAM | Storage| | Status |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| hold | **n8n (AI)** | ML | **1.3-48 GB** | **3-20 GB** | **5-20 GB/mo** | AI Agentic workflows |
|  | ↳ n8n-ai | | 1-48 GB | 2-10 GB | 5-20 GB/mo | LLM context + workflows |
|  | ↳ n8n-ai-db (PostgreSQL) | | 256-512 MB | 1-10 GB | - | Varies by usage |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| | **Total HOLD** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | On hold (ARM 6-24GB avail) |
| | **TOTAL AI** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | All AI services |


#### VMs

| Mode | Service |IP:port| URL| SSH  | RAM | Storage| | Status |
|--------|-----|----------|-----------------|---------------------|-----------------|
| hold | Oracle ARM Server | n8n (AI), NPM, PostgreSQL | ~6-24 GB | ~5-20 GB | ~10-40 GB/mo |
| dev | Generic VPS (AI) | LLM inference, AI workloads | ~8-32 GB | ~50-200 GB | ~20-100 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total HOLD** | | **~6-24 GB** | **~5-20 GB** | **~10-40 GB/mo** |
| | **Total DEV** | | **~8-32 GB** | **~50-200 GB** | **~20-100 GB/mo** |
| | **TOTAL AI** | | **~14-56 GB** | **~55-220 GB** | **~30-140 GB/mo** |



## Status (live|tree view)

`in tree view only show one card under each and if is healthy or off plus the name of it and a buttom to copy ssh command and/or link to url admin`




### Infra as Service VPS IaaS (Raw)
- Google Cloud
    - Gcloud_Management
    - SSH-VM-GCloud_microe2Linux_1
        - NPM-VM-Gcloud
        - mailserver
        - mail-db
        - Web_Shell_Terminal

- Oracle Cloud
    - OCloud-Management
    - SSH-VM-Oracle_Web_Server_1
        - NPM-VM-Oracle_Web_Server_1
        - n8n-server
            - Infra
        - Syncthing
        - Flask-server
            - Cloud_Dashboard.py
            - Cloud_Dashboard-db

    - SSH-VM-Oracle_Services_Serv
        - NPM-VM-Oracle_Services_Serv
        - matomo-app
        - matomo-db
        - Cloud_Dashboard-db

    - SSH-VM-Oracle_Flex_ARM_Server
        - NPM-VM-Oracle_Flex_ARM_Server
        - n8n-server
            - AI Agentic

- Generic_VPS_INFRA (TBD)
    - Generic_VPS_Management
    - SSH-VM-Generic_VPS
        - NPM-VM-Generic_VPS
        - (services TBD)

- Generic_VPS_AI (TBD)
    - Generic_VPS_Management
    - SSH-VM-Generic_VPS
        - NPM-VM-Generic_VPS
        - (services TBD)

### Pay per use GPU VRAM and RAM
#### WebAPP
- Python(Flask/Django)
    - Streamlit

#### AI
- PaaS
    - Hugging Face Spaces
    - Koyeb/Railway/Render
- FaaS
    - Google Cloud Functions,
    - Modal,
    - Beam/RunPod
- MaaS
    - Hugging Face API,
    - Groq,
    - Together AI/OpenRouter
- AaaS
    - E2B,
    - Relevance AI


## Backlog






---

