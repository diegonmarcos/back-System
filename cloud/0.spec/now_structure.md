
# Cards View

- Product & Services
    - matomo-app                        # on
    - Syncthing                         # on
    - Cloud_Dashboard                   # dev
    - mailserver                        # dev
    - Web_Shell_Terminal                # dev
    - Agentic_Dashboard                 # hold
    - VPN                               # dev
    - Git-Server                        # dev




- Management
    - Cloud Providers
        - OCloud-Management                 # on
        - Gcloud_Management                 # on

    - SSH VMs
        - SSH-VM-Oracle_Services_Serv       # on
        - SSH-VM-Oracle_Web_Server_1        # on
        - SSH-VM-Oracle_Flex_ARM_Server     # hold
        - SSH-VM-GCloud_microe2Linux_1      # dev
        - SSH-VM-Generic_VPS                # dev

- Infra Services
    - NPMs
        - NPM-VM-Oracle_Services_Serv       # on
        - NPM-VM-Oracle_Web_Server_1        # on
        - NPM-VM-Oracle_Flex_ARM_Server     # hold
        - NPM-VM-Gcloud                     # dev
        - NPM-VM-Generic_VPS                # dev
    - Data Bases
        - matomo-db                         # on
        - mail-db                           # dev
        - Git_Server-db                     # dev
        - n8n_AI-db                         # hold
    - Others
        - n8n-AI-server                     # hold
        - Flask-server                      # dev




---

# Tree View

## Infra as Service VPS IaaS (Raw)
- Google Cloud
    - Gcloud_Management                     #
    - SSH-VM-GCloud_microe2Linux_1          #
        - NPM-VM-Gcloud
        - mailserver                        #
        - mail-db                           #
        - Web_Shell_Terminal                #

- Oracle Cloud
    - OCloud-Management                     #
    - SSH-VM-Oracle_Web_Server_1            #
        - NPM-VM-Oracle_Web_Server_1        #
        - n8n-server                        #
            - Infra                         #
        - Syncthing                         #
        - Flask-server                      #
            - Cloud_Dashboard.py            #
            - Cloud_Dashboard-db            #

    - SSH-VM-Oracle_Services_Serv           #
        - NPM-VM-Oracle_Services_Serv       #
        - matomo-app                        #
        - matomo-db                         #
        - Cloud_Dashboard-db                #

    - SSH-VM-Oracle_Flex_ARM_Server         # hold
        - NPM-VM-Oracle_Flex_ARM_Server     # hold
        - n8n-server                        # hold
            - AI Agentic                    # hold

- Generic VPS (TBD)
    - Generic_VPS_Management                # dev
    - SSH-VM-Generic_VPS                    # dev
        - NPM-VM-Generic_VPS                # dev
        - (services TBD)                    # dev

## Pay per use GPU VRAM and RAM
### WebAPP
- Python(Flask/Django)
    - Streamlit

### AI
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


---


# Architeture

## Infra_Servers

(add here mermaid code)


## AI_Servers

(add here mermaid code)


---


# Resources
## Basic
### Services

| Status | Service | Category | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| dev | **Mail Server** | Productivity | **520 MB-1 GB** | **5-50 GB** | **1-10 GB/mo** | Email stack |
|  | ↳ mailserver | | 512 MB - 1 GB | 100-500 MB | 1-10 GB/mo | App + config |
|  | ↳ mail-db (SQLite) | | 8-32 MB | 5-50 GB | - | Mailboxes + indexes |
| on | **NPM** | Infrastructure | **512 MB-1 GB** | **400 MB-2 GB** | **20-80 GB/mo** | Reverse proxy (4 instances) |
|  | ↳ npm-oracle-web | | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Web Server 1 |
|  | ↳ npm-oracle-services | | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle Services Server 1 |
|  | ↳ npm-oracle-arm | | 128-256 MB | 100-500 MB | 5-20 GB/mo | Oracle ARM (hold) |
|  | ↳ npm-gcloud | | 128-256 MB | 100-500 MB | 5-20 GB/mo | GCloud (dev) |
| on | **Matomo** | Web | **512 MB-1 GB** | **3-15 GB** | **500 MB-2 GB/mo** | Analytics platform |
|  | ↳ matomo-app | | 256-512 MB | 2-5 GB | 500 MB-2 GB/mo | PHP FPM Alpine |
|  | ↳ matomo-db (MariaDB) | | 256-512 MB | 1-10 GB | - | Grows with analytics data |
| dev | **Gitea** | Productivity | **264-544 MB** | **11-15 GB** | **2-10 GB/mo** | Git hosting |
|  | ↳ gitea | | 256-512 MB | 1-5 GB | 2-10 GB/mo | Web + Git server |
|  | ↳ gitea-db (SQLite) | | 8-32 MB | Variable | - | Embedded DB |
|  | ↳ gitea-repos-db | | - | ~10 GB | - | Git repositories storage |
| on | **n8n (Infra)** | Automation | **256-512 MB** | **500 MB-2 GB** | **1-5 GB/mo** | Workflow automation |
|  | ↳ n8n | | 256-512 MB | 500 MB - 2 GB | 1-5 GB/mo | Workflows + execution logs |
| on | **Sync** | Productivity | **128-256 MB** | **5.2-106 GB** | **10-50 GB/mo** | File sync |
|  | ↳ syncthing | | 128-256 MB | 100-500 MB | 10-50 GB/mo | App + config |
|  | ↳ sync-index-db | | - | 100-500 MB | - | File metadata index |
|  | ↳ sync-files-db | | - | ~100 GB | - | Synced files storage |
|  | ↳ sync-obj-db | | - | ~5 GB | - | Object/blob storage |
| hold | **Redis** | Cache | **64-256 MB** | **100 MB-1 GB** | **-** | In-memory store |
|  | ↳ redis | | 64-256 MB | 100 MB - 1 GB | - | Session/cache data |
| dev | **OpenVPN** | Infrastructure | **64-128 MB** | **50-100 MB** | **5-50 GB/mo** | VPN server |
|  | ↳ openvpn | | 64-128 MB | 50-100 MB | 5-50 GB/mo | Client configs + certs |
| dev | **Flask Server** | Infrastructure | **64-128 MB** | **50-100 MB** | **100-500 MB/mo** | Cloud Dashboard API |
|  | ↳ flask-server | | 64-128 MB | 50-100 MB | 100-500 MB/mo | Lightweight API |
| dev | **Web Terminal** | Productivity | **64-128 MB** | **50-100 MB** | **500 MB-2 GB/mo** | Browser shell |
|  | ↳ wetty/ttyd | | 64-128 MB | 50-100 MB | 500 MB-2 GB/mo | Session-based |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| | **Total ON** | | **~1.4-2.8 GB** | **~9-125 GB** | **~32-135 GB/mo** | Active services |
| | **Total DEV** | | **~900 MB-1.8 GB** | **~66-165 GB** | **~8-72 GB/mo** | In development |
| | **Total HOLD** | | **~64-256 MB** | **~100 MB-1 GB** | **-** | On hold |
| | **TOTAL Non-AI** | | **~2.4-4.9 GB** | **~75-291 GB** | **~40-207 GB/mo** | All Non-AI services |

### VMs

| Status | VM | Services | Total RAM (Est) | Total Storage (Est) | Bandwidth (Est) |
|--------|-----|----------|-----------------|---------------------|-----------------|
| on | Oracle Web Server 1 | n8n, Syncthing, Flask, NPM, VPN, Gitea | ~800 MB - 1.5 GB | ~5-15 GB | ~20-80 GB/mo |
| on | Oracle Services Server 1 | Matomo, MariaDB, NPM | ~600 MB - 1.2 GB | ~5-15 GB | ~5-20 GB/mo |
| dev | GCloud Arch 1 | Mail, Terminal, NPM, SQLite | ~800 MB - 1.5 GB | ~10-50 GB | ~5-15 GB/mo |
| dev | Generic VPS | Variable services | ~1-4 GB | ~20-100 GB | ~10-50 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total ON** | | **~1.4-2.7 GB** | **~10-30 GB** | **~25-100 GB/mo** |
| | **Total DEV** | | **~1.8-5.5 GB** | **~30-150 GB** | **~15-65 GB/mo** |
| | **TOTAL Non-AI** | | **~3.2-8.2 GB** | **~40-180 GB** | **~40-165 GB/mo** |

## AI
### Services

| Status | Service | Category | RAM (Avg) | Storage (Avg) | Bandwidth (Avg) | Notes |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| hold | **n8n (AI)** | ML | **1.3-48 GB** | **3-20 GB** | **5-20 GB/mo** | AI Agentic workflows |
|  | ↳ n8n-ai | | 1-48 GB | 2-10 GB | 5-20 GB/mo | LLM context + workflows |
|  | ↳ n8n-ai-db (PostgreSQL) | | 256-512 MB | 1-10 GB | - | Varies by usage |
|--------|---------|----------|-----------|---------------|-----------------|-------|
| | **Total HOLD** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | On hold (ARM 6-24GB avail) |
| | **TOTAL AI** | | **~1.3-48.5 GB** | **~3-20 GB** | **~5-20 GB/mo** | All AI services |


### VMs

| Status | VM | Services | Total RAM (Est) | Total Storage (Est) | Bandwidth (Est) |
|--------|-----|----------|-----------------|---------------------|-----------------|
| hold | Oracle ARM Server | n8n (AI), NPM, PostgreSQL | ~6-24 GB | ~5-20 GB | ~10-40 GB/mo |
| dev | Generic VPS (AI) | LLM inference, AI workloads | ~8-32 GB | ~50-200 GB | ~20-100 GB/mo |
|--------|---------|----------|-----------|---------------|-----------------|
| | **Total HOLD** | | **~6-24 GB** | **~5-20 GB** | **~10-40 GB/mo** |
| | **Total DEV** | | **~8-32 GB** | **~50-200 GB** | **~20-100 GB/mo** |
| | **TOTAL AI** | | **~14-56 GB** | **~55-220 GB** | **~30-140 GB/mo** |

---

