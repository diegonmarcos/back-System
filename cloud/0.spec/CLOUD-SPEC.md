# Cloud Infrastructure Specification

> **Single Source of Truth**: `cloud-infrastructure.json`
> **Dashboard**: `cloud-dashboard.sh`
> **Version**: 2.1.0 | **Updated**: 2025-12-02

---

## Table of Contents

1. [Quick Reference](#1-quick-reference)
2. [Infrastructure Overview](#2-infrastructure-overview)
3. [Virtual Machines](#3-virtual-machines)
4. [Services](#4-services)
5. [Network Architecture](#5-network-architecture)
6. [Docker Network Isolation](#6-docker-network-isolation)
7. [Security Architecture](#7-security-architecture)
8. [Volume & Storage Strategy](#8-volume--storage-strategy)
9. [Database Strategy](#9-database-strategy)
10. [SSH & Access Commands](#10-ssh--access-commands)
11. [Front-End Integration](#11-front-end-integration)
12. [Operations & Maintenance](#12-operations--maintenance)
13. [Diagrams](#13-diagrams)

---

## 1. Quick Reference

### Active Services
| Service | URL | Status |
|---------|-----|--------|
| Matomo Analytics | https://analytics.diegonmarcos.com | Active |
| Syncthing | https://sync.diegonmarcos.com | Active |
| n8n Automation | https://n8n.diegonmarcos.com | Active |
| Cloud | https://cloud.diegonmarcos.com | Active |

### Proxy Admin Panels
| Server | URL |
|--------|-----|
| Oracle Web Server 1 | http://130.110.251.193:81 |
| Oracle Services Server 1 | http://129.151.228.66:81 |

### Cloud Consoles
| Provider | URL |
|----------|-----|
| Oracle Cloud | https://cloud.oracle.com |
| Google Cloud | https://console.cloud.google.com |

### SSH Quick Commands
```bash
# Oracle Web Server 1 (Matomo, Syncthing)
ssh ubuntu@130.110.251.193

# Oracle Services Server 1 (n8n)
ssh ubuntu@129.151.228.66
```

---

## 2. Infrastructure Overview

```
+-------------------------------------------------------------------------+
|                        CLOUD INFRASTRUCTURE                              |
+-------------------------------------------------------------------------+
|                                                                          |
|  +-------------------------------------------------------------------+  |
|  |                    ORACLE CLOUD (Always Free)                      |  |
|  |                                                                    |  |
|  |  +-------------------------+    +-------------------------+        |  |
|  |  |  Oracle Web Server 1    |    |  Oracle Services Srv 1  |        |  |
|  |  |  130.110.251.193        |    |  129.151.228.66         |        |  |
|  |  |  VM.Standard.E2.1.Micro |    |  VM.Standard.E2.1.Micro |        |  |
|  |  |  1 OCPU | 1GB RAM       |    |  1 OCPU | 1GB RAM       |        |  |
|  |  |                         |    |                         |        |  |
|  |  |  Services:              |    |  Services:              |        |  |
|  |  |  - Matomo Analytics     |    |  - n8n Automation       |        |  |
|  |  |  - Syncthing            |    |  - NPM (proxy)          |        |  |
|  |  |  - NPM (proxy)          |    |                         |        |  |
|  |  |                         |    |  Status: ONLINE         |        |  |
|  |  |  Status: ONLINE         |    +-------------------------+        |  |
|  |  +-------------------------+                                       |  |
|  |                                                                    |  |
|  |  +-------------------------+                                       |  |
|  |  |  Oracle ARM Server      |    (VM.Standard.A1.Flex)              |  |
|  |  |  IP: pending            |    4 OCPU | 24GB RAM | 200GB          |  |
|  |  |                         |                                       |  |
|  |  |  Planned Services:      |    Status: CAPACITY WAITLIST          |  |
|  |  |  - Cloud (Nextcloud)    |                                       |  |
|  |  |  - Mail Server          |                                       |  |
|  |  |  - OS Terminal          |                                       |  |
|  |  +-------------------------+                                       |  |
|  |                                                                    |  |
|  |  +-------------------------+    +-------------------------+        |  |
|  |  |  ML VM1                 |    |  ML VM2                 |        |  |
|  |  |  IP: pending            |    |  IP: pending            |        |  |
|  |  |  Status: PLANNED        |    |  Status: PLANNED        |        |  |
|  |  +-------------------------+    +-------------------------+        |  |
|  +-------------------------------------------------------------------+  |
|                                                                          |
|  +-------------------------------------------------------------------+  |
|  |                    GOOGLE CLOUD (Free Tier)                        |  |
|  |                                                                    |  |
|  |  +-------------------------+                                       |  |
|  |  |  GCloud Arch Linux 1    |    (e2-micro)                         |  |
|  |  |  IP: pending            |    0.25-2 vCPU | 1GB RAM              |  |
|  |  |                         |                                       |  |
|  |  |  Status: PENDING        |                                       |  |
|  |  +-------------------------+                                       |  |
|  +-------------------------------------------------------------------+  |
|                                                                          |
+-------------------------------------------------------------------------+
```

---

## 3. Virtual Machines

### 3.1 VM Categories

| Category | Description |
|----------|-------------|
| **Services** | General purpose VMs for web services and applications |
| **Machine Learning** | VMs dedicated to ML workloads and automation |

### 3.2 Services VMs

#### Oracle Web Server 1
| Property | Value |
|----------|-------|
| **ID** | oracle-web-server-1 |
| **Provider** | Oracle Cloud |
| **IP** | 130.110.251.193 |
| **Type** | VM.Standard.E2.1.Micro |
| **Specs** | 1 OCPU (AMD), 1GB RAM, 47GB Boot |
| **OS** | Ubuntu 24.04 LTS |
| **Services** | Matomo, Syncthing, NPM |
| **Ports** | 22, 80, 443, 81, 22000, 21027 |
| **Status** | Active |

#### Oracle Services Server 1
| Property | Value |
|----------|-------|
| **ID** | oracle-services-server-1 |
| **Provider** | Oracle Cloud |
| **IP** | 129.151.228.66 |
| **Type** | VM.Standard.E2.1.Micro |
| **Specs** | 1 OCPU (AMD), 1GB RAM, 47GB Boot |
| **OS** | Ubuntu 24.04 LTS |
| **Services** | n8n, NPM |
| **Ports** | 22, 80, 443, 81 |
| **Status** | Active |

#### GCloud Arch Linux 1
| Property | Value |
|----------|-------|
| **ID** | gcloud-arch-1 |
| **Provider** | Google Cloud |
| **IP** | pending |
| **Type** | e2-micro |
| **Specs** | 0.25-2 vCPU, 1GB RAM, 30GB |
| **OS** | Arch Linux (rolling) |
| **Status** | Pending |

### 3.3 Machine Learning VMs

#### Oracle ARM Server
| Property | Value |
|----------|-------|
| **ID** | oracle-arm-server |
| **Provider** | Oracle Cloud |
| **IP** | pending |
| **Type** | VM.Standard.A1.Flex |
| **Specs** | 4 OCPU (ARM64 Ampere), 24GB RAM, 200GB |
| **OS** | Ubuntu 24.04 LTS |
| **Planned Services** | Cloud, Mail, Terminal, Dashboard |
| **Status** | Capacity Waitlist |

#### ML VM1 & ML VM2
| Property | Value |
|----------|-------|
| **Status** | Planned |
| **Purpose** | Future ML workloads |

---

## 4. Services

### 4.1 Service Categories

| Category | Description |
|----------|-------------|
| **Infrastructure** | Core infrastructure services (storage, proxy) |
| **Productivity** | Productivity and communication tools |
| **Web** | Web analytics and monitoring |
| **Machine Learning** | ML and automation services |

### 4.2 Infrastructure Services

#### NPM (Web Server)
| Property | Value |
|----------|-------|
| **VM** | Oracle Web Server 1 |
| **Admin URL** | http://130.110.251.193:81 |
| **Technology** | jc21/nginx-proxy-manager |
| **Features** | SSL termination, Let's Encrypt, Access lists |
| **Status** | Active |

#### NPM (Services Server)
| Property | Value |
|----------|-------|
| **VM** | Oracle Services Server 1 |
| **Admin URL** | http://129.151.228.66:81 |
| **Technology** | jc21/nginx-proxy-manager |
| **Status** | Active |

#### Cloud
| Property | Value |
|----------|-------|
| **Domain** | cloud.diegonmarcos.com |
| **Technology** | GitHub Pages (static) |
| **Status** | Active |

### 4.3 Web Services

#### Matomo Analytics
| Property | Value |
|----------|-------|
| **VM** | Oracle Web Server 1 |
| **Domain** | analytics.diegonmarcos.com |
| **Internal Port** | 8080 |
| **Technology** | matomo:fpm-alpine + mariadb:11.4 |
| **Container** | matomo-app, matomo-db |
| **Features** | Anti-blocker proxy, Tag Manager, Custom events |
| **Status** | Active |

### 4.4 Machine Learning Services

#### n8n Automation
| Property | Value |
|----------|-------|
| **VM** | Oracle Services Server 1 |
| **Domain** | n8n.diegonmarcos.com |
| **Internal Port** | 5678 |
| **Technology** | n8nio/n8n |
| **Container** | n8n |
| **Features** | Workflow automation, 400+ integrations, Webhooks |
| **Status** | Active |

### 4.5 Productivity Services

#### Syncthing
| Property | Value |
|----------|-------|
| **VM** | Oracle Web Server 1 |
| **Domain** | sync.diegonmarcos.com |
| **Internal Port** | 8384 |
| **Sync Port** | 22000/TCP, 21027/UDP |
| **Technology** | syncthing/syncthing |
| **Container** | syncthing |
| **Status** | Active |

#### Mail Server
| Property | Value |
|----------|-------|
| **VM** | Oracle ARM Server (planned) |
| **Domain** | mail.diegonmarcos.com |
| **Technology** | docker-mailserver |
| **Features** | DKIM, SPF, DMARC, Fail2Ban |
| **Status** | Development |

#### OS Terminal Web
| Property | Value |
|----------|-------|
| **VM** | Oracle ARM Server (planned) |
| **Technology** | wetty or ttyd |
| **Status** | Development |

---

## 5. Network Architecture

### 5.1 Traffic Flow

```
+-------------------------------------------------------------------------+
|                              INTERNET                                    |
|    HTTP(80) | HTTPS(443) | SSH(22) | SMTP(25,587) | IMAP(993)           |
+------+------+------+------+----+----+------+-------+------+--------------+
       |            |           |           |              |
       v            v           v           v              v
+-------------------------------------------------------------------------+
|                    UFW FIREWALL (Default: DROP)                          |
|   OK: 22/tcp  OK: 80/tcp  OK: 443/tcp  OK: 25/tcp  OK: 587/tcp          |
|   OK: 993/tcp  BLOCKED: 8080  BLOCKED: 3306  BLOCKED: 5432              |
+------+----------------+----------+----------------+----------------------+
       |                |          |                |
       |                v          |                v
       |      +-----------------+  |      +-----------------+
       |      |  NGINX PROXY    |  |      |   MAIL SERVER   |
       |      |  (Host Level)   |  |      |   (Docker)      |
       |      |  Listen: 80,443 |  |      |   Listen: 25,   |
       |      +--------+--------+  |      |   587, 993      |
       |               |           |      +-----------------+
       |               v           |
       |      +--------------------------------------+
       |      |         DOCKER ENVIRONMENT          |
       |      |  +------------+  +------------+     |
       |      |  | PUBLIC     |  | PRIVATE    |     |
       |      |  | NETWORK    |  | NETWORK    |     |
       |      |  | :8080      |  | :8082      |     |
       |      |  | :8081      |  | internal   |     |
       |      |  +------------+  +------------+     |
       |      +--------------------------------------+
       |
       v
+-----------------+
|   HOST OS       |
|   (SSH Direct)  |
|   Ubuntu 24.04  |
+-----------------+
```

### 5.2 External Ports (Internet-Facing)

| Port | Protocol | Service | VM |
|------|----------|---------|-----|
| 22 | TCP | SSH | All |
| 80 | TCP | HTTP (redirect to HTTPS) | All |
| 443 | TCP | HTTPS | All |
| 81 | TCP | NPM Admin | Web Server 1, Services Server 1 |
| 22000 | TCP | Syncthing Sync | Web Server 1 |
| 21027 | UDP | Syncthing Discovery | Web Server 1 |

### 5.3 Internal Ports (localhost only, proxied via NPM)

| Port | Service | VM |
|------|---------|-----|
| 8080 | Matomo | Web Server 1 |
| 8384 | Syncthing GUI | Web Server 1 |
| 5678 | n8n | Services Server 1 |
| 3306 | MariaDB | Web Server 1 |

### 5.4 Key Design Decisions

1. **NGINX on Host (not Docker)**
   - SSL termination at host level
   - Direct access to Let's Encrypt
   - Survives container restarts

2. **Localhost Binding**
   - All containers bind to `127.0.0.1:port`
   - Prevents Docker UFW bypass vulnerability
   - Internet cannot reach containers directly

3. **SSH Direct Path**
   - SSH bypasses NGINX and Docker
   - Direct access to host OS
   - Emergency access even if containers fail

---

## 6. Docker Network Isolation

### 6.1 Network Topology

```yaml
networks:
  # Public services - internet accessible via NGINX
  public_net:
    driver: bridge
    subnet: 172.20.0.0/24
    purpose: Public services accessible via NGINX

  # Private services - requires authentication
  private_net:
    driver: bridge
    internal: true  # No external access
    subnet: 172.21.0.0/24
    purpose: Private services requiring authentication

  # Mail services - isolated email stack
  mail_net:
    driver: bridge
    subnet: 172.22.0.0/24
    purpose: Isolated email stack

  # Database bridge - backup agent only
  db_bridge:
    driver: bridge
    internal: true
    subnet: 172.23.0.0/24
    purpose: Database backup agent access
```

### 6.2 Network Membership Matrix

| Container | public_net | private_net | mail_net | db_bridge |
|-----------|:----------:|:-----------:|:--------:|:---------:|
| web-server | X | | | |
| matomo-app | X | | | |
| matomo-db | X | | | X |
| nextcloud-app | | X | | |
| nextcloud-db | | X | | X |
| redis | | X | | |
| mailserver | | | X | |
| mail-db | | | X | X |
| backup-agent | | | | X |

### 6.3 Isolation Verification

```bash
# From matomo-app, verify cannot reach private network
docker exec matomo-app ping -c 1 172.21.0.2  # Should fail

# From nextcloud-app, verify cannot reach public network
docker exec nextcloud-app ping -c 1 172.20.0.2  # Should fail

# Verify internal network has no external access
docker exec nextcloud-db curl -s http://google.com  # Should fail
```

---

## 7. Security Architecture

### 7.1 Architecture Philosophy

**"Blast Radius Containment"** - Assume any public-facing service can be compromised. Design the infrastructure so that a breach in one service cannot spread to others.

### 7.2 Defense in Depth Model

```
Layer 1: Network Edge
├── Oracle Cloud Security Lists
├── UFW Firewall (host level)
└── Fail2Ban (brute force protection)

Layer 2: Traffic Routing
├── NGINX TLS termination
├── HTTP → HTTPS redirect
├── Rate limiting
└── Security headers

Layer 3: Application Isolation
├── Docker networks (no cross-talk)
├── Container user namespaces
├── Read-only filesystems
└── Resource limits (CPU, memory)

Layer 4: Data Protection
├── Separate volumes per service
├── LUKS encryption at rest
├── Database per service
└── Backup encryption
```

### 7.3 UFW Configuration

```bash
# Reset to defaults
sudo ufw --force reset
sudo ufw default deny incoming
sudo ufw default allow outgoing

# Allow specific ports
sudo ufw allow 22/tcp comment 'SSH'
sudo ufw allow 80/tcp comment 'HTTP redirect'
sudo ufw allow 443/tcp comment 'HTTPS'
sudo ufw allow 25/tcp comment 'SMTP'
sudo ufw allow 587/tcp comment 'SMTP Submission'
sudo ufw allow 993/tcp comment 'IMAPS'

# Enable firewall
sudo ufw enable
sudo ufw status verbose
```

### 7.4 SSH Hardening

```bash
# /etc/ssh/sshd_config
PermitRootLogin no
PasswordAuthentication no
PubkeyAuthentication yes
MaxAuthTries 3
AllowUsers ubuntu
```

### 7.5 NGINX Security Headers

```nginx
# /etc/nginx/conf.d/security.conf
add_header Strict-Transport-Security "max-age=31536000; includeSubDomains" always;
add_header X-Content-Type-Options "nosniff" always;
add_header X-Frame-Options "SAMEORIGIN" always;
add_header X-XSS-Protection "1; mode=block" always;
add_header Referrer-Policy "strict-origin-when-cross-origin" always;
```

### 7.6 Docker Hardening

```yaml
services:
  web-server:
    security_opt:
      - no-new-privileges:true
    read_only: true
    tmpfs:
      - /tmp
    deploy:
      resources:
        limits:
          cpus: '0.5'
          memory: 256M
```

---

## 8. Volume & Storage Strategy

### 8.1 Storage Partitions (ARM Server - Future)

```
Host Filesystem:
├── / (Boot Volume - 47GB)
│   ├── /etc/nginx/          # NGINX configs
│   ├── /opt/docker/         # Docker compose files
│   └── /home/ubuntu/        # User home
│
├── /mnt/public (Block Volume 1 - 50GB)
│   ├── matomo-db/           # MariaDB data
│   ├── matomo-files/        # Matomo uploads
│   └── web-static/          # Static website files
│
├── /mnt/private (Block Volume 2 - 50GB) [LUKS ENCRYPTED]
│   ├── nextcloud-db/        # PostgreSQL data
│   ├── nextcloud-files/     # User files
│   └── redis-data/          # Persistent cache
│
└── /mnt/mail (Block Volume 3 - 50GB) [LUKS ENCRYPTED]
    ├── mailboxes/           # Maildir storage
    ├── mail-config/         # Server configuration
    └── dkim-keys/           # DKIM signing keys
```

### 8.2 LUKS Encryption Setup

```bash
# Create encrypted partition
sudo cryptsetup luksFormat /dev/sdb1
sudo cryptsetup open /dev/sdb1 private_crypt

# Format and mount
sudo mkfs.ext4 /dev/mapper/private_crypt
sudo mount /dev/mapper/private_crypt /mnt/private

# Auto-unlock at boot (with keyfile)
sudo dd if=/dev/urandom of=/root/.luks-keyfile bs=4096 count=1
sudo chmod 400 /root/.luks-keyfile
sudo cryptsetup luksAddKey /dev/sdb1 /root/.luks-keyfile

# /etc/crypttab
private_crypt /dev/sdb1 /root/.luks-keyfile luks
```

---

## 9. Database Strategy

### 9.1 SQL vs NoSQL Decision Matrix

| Use Case | Type | Database | Reason |
|----------|------|----------|--------|
| Analytics (Matomo) | SQL | MariaDB | Complex queries, time-series |
| User Files (NextCloud) | SQL | PostgreSQL | Metadata, relations |
| Mail Accounts | SQL | SQLite | Simple, lightweight |
| Session Cache | NoSQL | Redis | Fast, ephemeral |
| Search Index | NoSQL | Redis | Key-value lookups |
| Email Storage | Files | Maildir | Standard format |

### 9.2 Isolation Rule

```
+-------------------------------------------------------------+
|                    RULE: ONE DB PER SERVICE                  |
|                                                              |
|  WRONG: Single MariaDB for Matomo + NextCloud               |
|  RIGHT: Separate MariaDB (Matomo) + PostgreSQL (NC)         |
|                                                              |
|  Reason: Prevents privilege escalation between services     |
+-------------------------------------------------------------+
```

---

## 10. SSH & Access Commands

### 10.1 SSH Access

```bash
# Oracle Web Server 1 (Matomo, Syncthing)
ssh ubuntu@130.110.251.193

# Oracle Services Server 1 (n8n)
ssh ubuntu@129.151.228.66

# Google Cloud (when active)
gcloud compute ssh arch-1 --zone us-central1-a
```

### 10.2 Docker Commands (after SSH)

```bash
# View all containers
sudo docker ps

# View logs
sudo docker logs --tail 100 matomo-app
sudo docker logs --tail 100 -f matomo-db

# Execute shell in container
sudo docker exec -it matomo-app bash
sudo docker exec -it matomo-db bash
sudo docker exec -it syncthing sh
sudo docker exec -it n8n sh

# Restart container
sudo docker restart matomo-app

# View resource usage
sudo docker stats --no-stream
```

### 10.3 System Commands

```bash
# Disk usage
df -h

# Memory usage
free -h

# Check swap
swapon --show

# Create swap (if needed - for 1GB VMs)
sudo fallocate -l 1G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile
sudo swapon /swapfile
echo '/swapfile none swap sw 0 0' | sudo tee -a /etc/fstab
```

---

## 11. Front-End Integration

### 11.1 Data Source

The front-end dashboard reads from `cloud-infrastructure.json`:

- **Services list** → `services` object
- **VM cards** → `virtualMachines` object
- **Provider cards** → `providers` object
- **URLs & commands** → Each service/VM contains its URLs
- **Status indicators** → `status` field on each entity

### 11.2 JSON Structure Overview

```json
{
  "providers": {
    "oracle": { "consoleUrl": "...", "cli": {...} },
    "gcloud": { "consoleUrl": "...", "cli": {...} }
  },
  "vmCategories": {
    "services": { "name": "Services", "description": "..." },
    "ml": { "name": "Machine Learning", "description": "..." }
  },
  "virtualMachines": {
    "oracle-web-server-1": { "ip": "...", "ssh": {...}, "services": [...] },
    "oracle-services-server-1": { "ip": "...", "ssh": {...}, "services": [...] }
  },
  "serviceCategories": {
    "infra": { "name": "Infrastructure" },
    "productivity": { "name": "Productivity" },
    "web": { "name": "Web" },
    "ml": { "name": "Machine Learning" }
  },
  "services": {
    "matomo": { "urls": {...}, "docker": {...}, "status": "active" },
    "n8n": { "urls": {...}, "docker": {...}, "status": "active" }
  },
  "domains": { "primary": "diegonmarcos.com", "subdomains": {...} },
  "firewallRules": { "oracle-web-server-1": [...] }
}
```

### 11.3 TypeScript Types (suggested)

```typescript
interface CloudInfrastructure {
  providers: Record<string, Provider>;
  vmCategories: Record<string, VMCategory>;
  virtualMachines: Record<string, VirtualMachine>;
  serviceCategories: Record<string, ServiceCategory>;
  services: Record<string, Service>;
  domains: DomainConfig;
  firewallRules: Record<string, FirewallRule[]>;
  dockerNetworks: Record<string, DockerNetwork>;
  quickCommands: QuickCommands;
}
```

### 11.4 Front-End Card Mapping

| Card | JSON Path | Click Action |
|------|-----------|--------------|
| Matomo Analytics | `services.matomo` | Open `urls.gui` |
| Syncthing | `services.syncthing` | Open `urls.gui` |
| n8n Automation | `services.n8n` | Open `urls.gui` |
| Oracle Cloud | `providers.oracle` | Open `consoleUrl` |
| Google Cloud | `providers.gcloud` | Open `consoleUrl` |

### 11.5 Status Values

| Status | Display | Card Style |
|--------|---------|------------|
| `active` | Online | Green indicator |
| `pending` | Pending | Yellow indicator |
| `development` | In Development | Blue indicator |
| `planned` | Planned | Gray indicator |
| `offline` | Offline | Red indicator |

---

## 12. Operations & Maintenance

### 12.1 Daily Operations

```bash
# Check service health
docker ps --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"

# View logs
docker logs --tail 100 matomo-app
docker logs --tail 100 -f mailserver

# Check disk usage
df -h /mnt/*
docker system df
```

### 12.2 Weekly Operations

```bash
# Update containers
docker compose pull
docker compose up -d

# Clean old images
docker image prune -a --filter "until=168h"

# Verify backups
ls -la /backup/
```

### 12.3 Monthly Operations

```bash
# OS updates
sudo apt update && sudo apt upgrade -y

# SSL certificate check
sudo certbot certificates

# Review firewall rules
sudo ufw status verbose

# Audit Docker networks
docker network ls
docker network inspect public_net
```

### 12.4 Dashboard Usage

```bash
# Launch interactive TUI
./cloud-dashboard.sh

# Quick status check
./cloud-dashboard.sh status

# Help
./cloud-dashboard.sh help
```

### 12.5 Incident Response

**If container compromised**:
```bash
# 1. Isolate container
docker network disconnect public_net compromised-container
docker stop compromised-container

# 2. Preserve evidence
docker commit compromised-container evidence:$(date +%s)
docker logs compromised-container > /tmp/incident-logs.txt

# 3. Restore from backup
docker compose down compromised-service
rm -rf /mnt/public/compromised-data/*
# Restore from backup...
docker compose up -d compromised-service

# 4. Post-incident
# - Review logs
# - Update passwords
# - Patch vulnerabilities
# - Update monitoring
```

---

## 13. Diagrams

### 13.1 High-Level Service Flow

```
User Request
     |
     v
+-----------+
|    DNS    | analytics.diegonmarcos.com → 130.110.251.193
+-----+-----+
      |
      v
+-----------+
| NPM (:443)| SSL Termination + Routing
+-----+-----+
      |
      v
+-----------+
|  Matomo   | localhost:8080 (Docker)
|  (:8080)  |
+-----------+
```

### 13.2 Mermaid: Infrastructure Tree

```mermaid
graph TD
    subgraph CLOUD["Cloud Infrastructure"]

        subgraph ORACLE["Oracle Cloud - Always Free"]
            subgraph WEB["Web Server 1 - 130.110.251.193"]
                subgraph DOCKER1["Docker Engine"]
                    NGINX1["NPM :80, :443, :81"]
                    MATOMO["Matomo :8080"]
                    MARIADB["MariaDB :3306"]
                    SYNC["Syncthing :8384"]
                end
            end
            subgraph SVC["Services Server 1 - 129.151.228.66"]
                subgraph DOCKER2["Docker Engine"]
                    NGINX2["NPM :80, :443, :81"]
                    N8N["n8n :5678"]
                end
            end
            subgraph ARM["ARM Server - Pending"]
                MAIL["Mail Server"]
                NEXTCLOUD["Cloud"]
                TERMINAL["Terminal"]
            end
        end

        subgraph GCLOUD["Google Cloud - Free Tier"]
            ARCH["Arch Linux 1"]
        end

    end

    subgraph EXTERNAL["External Access"]
        INTERNET["Internet"]
        ANALYTICS["analytics.diegonmarcos.com"]
        SYNCDOM["sync.diegonmarcos.com"]
        N8NDOM["n8n.diegonmarcos.com"]
    end

    INTERNET --> ANALYTICS
    INTERNET --> SYNCDOM
    INTERNET --> N8NDOM
    ANALYTICS --> NGINX1
    SYNCDOM --> NGINX1
    N8NDOM --> NGINX2
    NGINX1 --> MATOMO
    NGINX1 --> SYNC
    NGINX2 --> N8N
    MATOMO --> MARIADB
```

### 13.3 Mermaid: Budget Protection Flow (GCloud)

```mermaid
sequenceDiagram
    participant GCP as GCP Services
    participant Budget as Budget Alert
    participant PubSub as Pub/Sub
    participant Function as Cloud Function
    participant Billing as Billing API

    GCP->>Budget: Spending reaches limit
    Budget->>PubSub: Publish alert message
    PubSub->>Function: Trigger billing-disabler
    Function->>Billing: Disable project billing
    Billing-->>GCP: Services stopped
    Note over GCP: Manual re-enable required
```

---

## Changelog

| Date | Change |
|------|--------|
| 2025-12-02 | Consolidated HANDOFF.md, spec_infra.md, SPEC.md, VPS_ARCHITECTURE_SPEC.md into single CLOUD-SPEC.md |
| 2025-12-02 | Reorganized VMs and services with categories |
| 2025-12-01 | Migrated to JSON data source, deprecated CSV |
| 2025-11-27 | Added services-server-1 with n8n |
| 2025-11-26 | Initial infrastructure documentation |

---

## File Structure

```
0.spec/
├── cloud-infrastructure.json   ← PRIMARY DATA SOURCE
├── cloud-dashboard.sh          ← POSIX TUI Dashboard (v5.0.0)
├── CLOUD-SPEC.md               ← This file (consolidated documentation)
└── archive/
    └── csv/                    ← Legacy CSV files (deprecated)
```

---

**Maintainer**: Diego Nepomuceno Marcos
**Last Updated**: 2025-12-02
