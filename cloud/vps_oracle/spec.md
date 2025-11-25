# Oracle Cloud VPS Infrastructure

## 🌐 Oracle Cloud Access
- **Console**: https://cloud.oracle.com/
- **Region**: EU-Marseille-1 (France)
- **Tenancy**: Your Oracle Cloud account

## 🖥️ Virtual Machines

### VM: matomo-server
- **Instance Name**: matomo-server
- **Shape**: VM.Standard.E2.1.Micro (Always Free ✅)
- **OS**: Ubuntu 24.04 Minimal
- **Resources**:
  - 2 vCPUs (AMD EPYC 7742)
  - 1 GB RAM
  - 50 GB Boot Volume
- **Public IP**: `130.110.251.193`
- **Private IP**: `10.0.1.154`
- **Status**: ✅ RUNNING

#### SSH Connection
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
```

#### Network Configuration
- **VCN**: matomo-vcn (10.0.0.0/16)
- **Subnet**: matomo-subnet (10.0.1.0/24)
- **Internet Gateway**: Configured
- **Security Lists**:
  - Port 22 (SSH)
  - Port 80 (HTTP)
  - Port 443 (HTTPS)
  - Port 81 (Nginx Proxy Manager Admin)
  - Port 8080 (Matomo Direct Access)

---

## 🐳 Docker Services on matomo-server

### Service Tree
```
matomo-server (130.110.251.193)
├── nginx-proxy (Nginx Proxy Manager)
│   ├── Port 80 (HTTP)
│   ├── Port 443 (HTTPS)
│   └── Port 81 (Admin UI)
│
├── matomo-app (Matomo Analytics)
│   ├── Port 8080 → 80 (internal)
│   └── Domain: analytics.diegonmarcos.com
│
└── matomo-db (MariaDB 10.11)
    └── Port 3306 (internal only)
```

### 1. Nginx Proxy Manager
- **Container Name**: `nginx-proxy`
- **Image**: `jc21/nginx-proxy-manager:latest`
- **Purpose**: Reverse proxy with SSL/TLS termination
- **Access URLs**:
  - Admin: http://130.110.251.193:81
  - HTTP: http://130.110.251.193:80
  - HTTPS: https://130.110.251.193:443
- **Proxy Hosts**:
  - analytics.diegonmarcos.com → matomo-app:80

### 2. Matomo Analytics
- **Container Name**: `matomo-app`
- **Image**: `matomo:latest`
- **Purpose**: Self-hosted web analytics platform
- **Access URLs**:
  - HTTPS: https://analytics.diegonmarcos.com
  - Direct: http://130.110.251.193:8080
- **Database**: matomo-db (MariaDB)
- **Data Volume**: `~/matomo/matomo:/var/www/html`

### 3. MariaDB Database
- **Container Name**: `matomo-db`
- **Image**: `mariadb:10.11`
- **Purpose**: Database backend for Matomo
- **Database Name**: matomo
- **User**: matomo
- **Data Volume**: `~/matomo/db:/var/lib/mysql`
- **Access**: Internal only (Docker network)

---

## 🛠️ Oracle CLI Tools

### Installation
```bash
# Install OCI CLI
bash -c "$(curl -L https://raw.githubusercontent.com/oracle/oci-cli/master/scripts/install/install.sh)"
```

### Configuration
```bash
# Configure OCI CLI (interactive)
oci setup config

# Test connection
oci iam region list
```

### Common Commands
```bash
# List compute instances
oci compute instance list --compartment-id <compartment-ocid>

# Get instance details
oci compute instance get --instance-id <instance-ocid>

# Start instance
oci compute instance action --action START --instance-id <instance-ocid>

# Stop instance
oci compute instance action --action STOP --instance-id <instance-ocid>

# List VCNs
oci network vcn list --compartment-id <compartment-ocid>
```

---

## 📊 Resource Usage

| Component | RAM | CPU | Disk |
|-----------|-----|-----|------|
| Nginx Proxy Manager | ~50 MB | 0.1 vCPU | ~100 MB |
| Matomo Application | ~300 MB | 0.3 vCPU | ~500 MB |
| MariaDB Database | ~200 MB | 0.2 vCPU | ~200 MB |
| **Total Used** | **~550 MB** | **~0.6 vCPU** | **~800 MB** |
| **Available** | 1 GB | 2 vCPUs | 50 GB |
| **Headroom** | 45% free | 70% free | 98% free |

---

## 🔐 Security

### SSH Access
- **Authentication**: SSH key only (no passwords)
- **Key Location**: `~/.ssh/matomo_key`
- **User**: `ubuntu`
- **Command**: `ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193`

### Firewall
- Oracle Cloud Security Lists (virtual firewall)
- Ubuntu iptables (set to ACCEPT all after setup)
- Nginx Proxy Manager handles SSL/TLS

### SSL Certificates
- **Provider**: Let's Encrypt
- **Renewal**: Automatic via Nginx Proxy Manager
- **Domains**: analytics.diegonmarcos.com

---

## 📁 File Structure on VM

```
~/matomo/
├── docker-compose.yml          # Container orchestration
├── db/                         # MariaDB data
├── matomo/                     # Matomo application files
└── npm/                        # Nginx Proxy Manager
    ├── data/                   # NPM configuration
    └── letsencrypt/            # SSL certificates
```

---

## 🔗 Quick Links

- **Oracle Cloud Console**: https://cloud.oracle.com/
- **Matomo Analytics**: https://analytics.diegonmarcos.com
- **Nginx Proxy Manager**: http://130.110.251.193:81
- **Matomo Documentation**: [../analytics/matomo/README.md](../analytics/matomo/README.md)

---

## 📝 Management Scripts

Located in `../analytics/matomo/`:

```bash
# SSH access
./matomo-login.sh

# Container management
./matomo-manage.sh status
./matomo-manage.sh logs
./matomo-manage.sh restart
./matomo-manage.sh backup

# HTTPS setup
./matomo-https-setup.sh
```

---

**Last Updated**: 2025-11-25
