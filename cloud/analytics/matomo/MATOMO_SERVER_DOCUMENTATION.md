# Matomo Analytics Server Documentation

Complete documentation for the self-hosted Matomo analytics infrastructure running on Oracle Cloud.

---

## Table of Contents

1. [Infrastructure Overview](#infrastructure-overview)
2. [Server Specifications](#server-specifications)
3. [Network Configuration](#network-configuration)
4. [Docker Stack](#docker-stack)
5. [Matomo Configuration](#matomo-configuration)
6. [HTTPS/SSL Setup](#httpssl-setup)
7. [DNS Configuration](#dns-configuration)
8. [Access & Credentials](#access--credentials)
9. [Management Commands](#management-commands)
10. [Monitoring & Maintenance](#monitoring--maintenance)
11. [Troubleshooting](#troubleshooting)
12. [Backup & Recovery](#backup--recovery)

---

## Infrastructure Overview

### Architecture

```
Internet
    ↓
DNS (analytics.diegonmarcos.com)
    ↓
Oracle Cloud Load Balancer
    ↓
Oracle Cloud Instance (130.110.251.193)
    ↓
Docker Compose Stack:
    - Nginx Proxy Manager (Ports 80, 443, 81)
    - Matomo App (Port 8080)
    - MariaDB Database (Internal)
```

### Technology Stack

- **Cloud Provider**: Oracle Cloud Infrastructure (OCI)
- **Operating System**: Ubuntu 24.04 LTS Minimal
- **Containerization**: Docker + Docker Compose V2
- **Web Server**: Nginx Proxy Manager
- **Analytics**: Matomo (latest)
- **Database**: MariaDB 10.11
- **SSL/TLS**: Let's Encrypt (via NPM)

---

## Server Specifications

### Oracle Cloud Instance

| Property | Value |
|----------|-------|
| **Instance Name** | web-server |
| **Shape** | VM.Standard.E2.1.Micro (Always Free) |
| **vCPUs** | 2 |
| **RAM** | 1 GB |
| **Storage** | 50 GB |
| **Region** | EU-Marseille-1 (France) |
| **Availability Domain** | bRpM:EU-MARSEILLE-1-AD-1 |
| **Public IP** | 130.110.251.193 |
| **Private IP** | 10.0.1.15 |
| **OS** | Ubuntu 24.04 Minimal |

### Instance OCID

```
ocid1.instance.oc1.eu-marseille-1.anwxeljruadvczacbwylmkqr253ay7binepapgsyopllfayovkzaky6oigbq
```

---

## Network Configuration

### Virtual Cloud Network (VCN)

| Property | Value |
|----------|-------|
| **VCN Name** | web-server-vcn |
| **CIDR Block** | 10.0.0.0/16 |
| **Subnet Name** | web-server-subnet |
| **Subnet CIDR** | 10.0.1.0/24 |
| **Internet Gateway** | web-server-igw |

### Security List - Ingress Rules

| Port | Protocol | Source | Purpose |
|------|----------|--------|---------|
| 22 | TCP | 0.0.0.0/0 | SSH |
| 80 | TCP | 0.0.0.0/0 | HTTP |
| 443 | TCP | 0.0.0.0/0 | HTTPS |
| 8080 | TCP | 0.0.0.0/0 | Matomo Direct Access |
| 81 | TCP | 0.0.0.0/0 | Nginx Proxy Manager Admin |

### Firewall Configuration

**Note**: Ubuntu on Oracle Cloud has iptables configured to ACCEPT all traffic after running the setup script.

```bash
# View current rules
sudo iptables -L -n -v

# All chains are set to ACCEPT policy
Chain INPUT (policy ACCEPT)
Chain FORWARD (policy ACCEPT)
Chain OUTPUT (policy ACCEPT)
```

---

## Docker Stack

### Installed Components

- **Docker Engine**: v27.4.0 (installed via get.docker.com)
- **Docker Compose**: v2.40.3 (plugin)

### Container Architecture

```yaml
services:
  mariadb:      # Database backend
  matomo:       # Analytics application
  nginx-proxy:  # Reverse proxy + SSL
```

### Docker Compose Configuration

**Location**: `~/matomo/docker-compose.yml`

```yaml
version: '3'

services:
  mariadb:
    image: mariadb:10.11
    container_name: matomo-db
    restart: always
    environment:
      - MYSQL_ROOT_PASSWORD=<redacted>
      - MYSQL_DATABASE=matomo
      - MYSQL_USER=matomo
      - MYSQL_PASSWORD=<redacted>
    volumes:
      - ./db:/var/lib/mysql

  matomo:
    image: matomo:latest
    container_name: matomo-app
    restart: always
    depends_on:
      - mariadb
    environment:
      - MATOMO_DATABASE_HOST=mariadb
      - MATOMO_DATABASE_ADAPTER=mysql
      - MATOMO_DATABASE_TABLES_PREFIX=matomo_
      - MATOMO_DATABASE_USERNAME=matomo
      - MATOMO_DATABASE_PASSWORD=<redacted>
      - MATOMO_DATABASE_DBNAME=matomo
    volumes:
      - ./matomo:/var/www/html
    ports:
      - "8080:80"

  nginx-proxy:
    image: jc21/nginx-proxy-manager:latest
    container_name: nginx-proxy
    restart: always
    ports:
      - "80:80"
      - "443:443"
      - "81:81"
    volumes:
      - ./npm/data:/data
      - ./npm/letsencrypt:/etc/letsencrypt
```

### Data Persistence

All data is stored in: `~/matomo/`

```
~/matomo/
├── docker-compose.yml          # Container definitions
├── db/                         # MariaDB data
├── matomo/                     # Matomo files
└── npm/                        # Nginx Proxy Manager
    ├── data/                   # NPM configuration
    └── letsencrypt/            # SSL certificates
```

---

## Matomo Configuration

### Database Connection

| Parameter | Value |
|-----------|-------|
| **Host** | mariadb |
| **Database** | matomo |
| **User** | matomo |
| **Password** | *stored in docker-compose.yml* |
| **Tables Prefix** | matomo_ |

### Site Configuration

| Property | Value |
|----------|-------|
| **Site ID** | 1 |
| **Site Name** | Diego N Marcos Portfolio |
| **Site URL** | https://diegonmarcos.github.io |
| **Timezone** | America/New_York |

### Tracking Configuration

**Tracking URL**: `https://analytics.diegonmarcos.com/matomo.php`

**JavaScript Tracking Code**:
```html
<!-- Matomo -->
<script>
  var _paq = window._paq = window._paq || [];
  _paq.push(['trackPageView']);
  _paq.push(['enableLinkTracking']);
  (function() {
    var u="//analytics.diegonmarcos.com/";
    _paq.push(['setTrackerUrl', u+'matomo.php']);
    _paq.push(['setSiteId', '1']);
    var d=document, g=d.createElement('script'), s=d.getElementsByTagName('script')[0];
    g.async=true; g.src=u+'matomo.js'; s.parentNode.insertBefore(g,s);
  })();
</script>
<!-- End Matomo Code -->
```

### Privacy Settings

- **Cookie-less tracking**: Enabled
- **Do Not Track**: Respected
- **IP Anonymization**: Enabled
- **GDPR Compliance**: Yes

---

## HTTPS/SSL Setup

### Nginx Proxy Manager Configuration

**Admin Interface**: http://130.110.251.193:81

**Default Credentials**:
- Email: `admin@example.com`
- Password: `changeme` (changed on first login)

### Proxy Host Configuration

**Domain**: analytics.diegonmarcos.com

**Settings**:
```
Domain Names: analytics.diegonmarcos.com
Scheme: http
Forward Hostname/IP: matomo-app
Forward Port: 80
Block Common Exploits: ✓
Websockets Support: ✓
```

**SSL Configuration**:
```
SSL Certificate: Let's Encrypt
Force SSL: ✓
HTTP/2 Support: ✓
HSTS Enabled: ✓
Email: me@diegonmarcos.com
```

### SSL Certificate Details

- **Provider**: Let's Encrypt
- **Type**: Domain Validation (DV)
- **Renewal**: Automatic (every 90 days)
- **Protocol**: TLS 1.2, TLS 1.3

---

## DNS Configuration

### Required DNS Records

```
Type: A
Name: analytics
Value: 130.110.251.193
TTL: 300
```

**Full Domain**: analytics.diegonmarcos.com

### Verification

```bash
# Test DNS resolution
nslookup analytics.diegonmarcos.com

# Test HTTP connectivity
curl -I http://analytics.diegonmarcos.com

# Test HTTPS connectivity
curl -I https://analytics.diegonmarcos.com
```

---

## Access & Credentials

### Access URLs

| Service | URL | Port |
|---------|-----|------|
| **Matomo (HTTPS)** | https://analytics.diegonmarcos.com | 443 |
| **Matomo (HTTP)** | http://130.110.251.193:8080 | 8080 |
| **Nginx Proxy Manager** | http://130.110.251.193:81 | 81 |

### SSH Access

```bash
# From local machine
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193

# From Oracle Cloud Shell
# (requires console SSH key configuration)
```

**SSH Key Location**: `~/.ssh/matomo_key` (private key)

### User Accounts

**Server User**: `ubuntu`
- Full sudo access
- Member of docker group

**Matomo Super User**: Configured during installation
- Full admin access to Matomo dashboard

**Note**: Passwords are not stored in this documentation for security reasons.

---

## Management Commands

### Docker Container Management

```bash
# Navigate to project directory
cd ~/matomo

# Start all services
sudo docker compose up -d

# Stop all services
sudo docker compose stop

# Restart all services
sudo docker compose restart

# View logs (all services)
sudo docker compose logs -f

# View logs (specific service)
sudo docker compose logs -f matomo
sudo docker compose logs -f mariadb
sudo docker compose logs -f nginx-proxy

# Check container status
sudo docker compose ps

# Update containers to latest images
sudo docker compose pull
sudo docker compose up -d

# Remove containers (keeps data)
sudo docker compose down

# Remove containers and data (DANGEROUS)
sudo docker compose down -v
```

### Matomo Management

```bash
# Access Matomo container shell
sudo docker exec -it matomo-app bash

# Run Matomo console commands
sudo docker exec -it matomo-app php /var/www/html/console

# Clear Matomo cache
sudo docker exec -it matomo-app php /var/www/html/console core:clear-cache

# Update Matomo
sudo docker exec -it matomo-app php /var/www/html/console core:update
```

### Database Management

```bash
# Access MariaDB shell
sudo docker exec -it matomo-db mysql -u matomo -p

# Backup database
sudo docker exec matomo-db mysqldump -u matomo -p matomo > backup_$(date +%Y%m%d).sql

# Restore database
cat backup.sql | sudo docker exec -i matomo-db mysql -u matomo -p matomo

# Check database size
sudo docker exec -it matomo-db mysql -u matomo -p -e "SELECT table_schema AS 'Database', ROUND(SUM(data_length + index_length) / 1024 / 1024, 2) AS 'Size (MB)' FROM information_schema.TABLES WHERE table_schema = 'matomo';"
```

### Server Maintenance

```bash
# Update system packages
sudo apt update && sudo apt upgrade -y

# Check disk usage
df -h

# Check memory usage
free -h

# Check Docker disk usage
sudo docker system df

# Clean up Docker (remove unused images, containers, volumes)
sudo docker system prune -a

# Restart Docker daemon
sudo systemctl restart docker

# View system logs
sudo journalctl -u docker -f
```

---

## Monitoring & Maintenance

### Health Checks

**Container Health**:
```bash
sudo docker compose ps
```

**Service Accessibility**:
```bash
# Test Matomo
curl -I https://analytics.diegonmarcos.com

# Test direct access
curl -I http://localhost:8080

# Test Nginx Proxy Manager
curl -I http://localhost:81
```

**Database Health**:
```bash
sudo docker exec -it matomo-db mysql -u matomo -p -e "SHOW DATABASES;"
```

### Performance Monitoring

```bash
# Container resource usage
sudo docker stats

# Disk usage by container
sudo docker system df -v

# View container processes
sudo docker top matomo-app
sudo docker top matomo-db
sudo docker top nginx-proxy
```

### Log Monitoring

**Important Log Locations**:
- Matomo: `~/matomo/matomo/tmp/logs/`
- Nginx: Inside container at `/data/logs/`
- MariaDB: Inside container at `/var/lib/mysql/`

```bash
# Real-time log monitoring
sudo docker compose logs -f --tail=100

# Check for errors
sudo docker compose logs | grep -i error
sudo docker compose logs | grep -i warning
```

### Automatic Updates

**Docker Images**: Update manually using `docker compose pull`

**Matomo**:
- Update via web interface: Settings → System Check
- Or via CLI: `sudo docker exec -it matomo-app php /var/www/html/console core:update`

**Let's Encrypt Certificates**: Auto-renewal via Nginx Proxy Manager

---

## Troubleshooting

### Common Issues

#### 1. SSH Connection Timeout

**Symptom**: Cannot connect via SSH

**Solution**:
```bash
# Check if instance is running
oci compute instance get --instance-id <INSTANCE_OCID>

# Check security list allows port 22
oci network security-list get --security-list-id <SL_OCID>

# Access via Oracle Cloud Console
# Use Instance Console Connection
```

#### 2. Containers Not Starting

**Symptom**: `docker compose up -d` fails

**Diagnosis**:
```bash
sudo docker compose logs
sudo docker ps -a
```

**Solution**:
```bash
# Remove containers and try again
sudo docker compose down
sudo docker compose up -d

# Check for port conflicts
sudo ss -tlnp | grep -E ':(80|443|81|8080)'
```

#### 3. Matomo Shows Database Connection Error

**Symptom**: Matomo cannot connect to MariaDB

**Diagnosis**:
```bash
# Check if MariaDB is running
sudo docker compose ps mariadb

# Check MariaDB logs
sudo docker compose logs mariadb

# Test connection from matomo container
sudo docker exec -it matomo-app ping mariadb
```

**Solution**:
```bash
# Restart MariaDB
sudo docker compose restart mariadb

# Verify environment variables in docker-compose.yml
cat ~/matomo/docker-compose.yml
```

#### 4. SSL Certificate Not Renewing

**Symptom**: Certificate expiration warning

**Solution**:
```bash
# Check certificate expiry
sudo docker exec nginx-proxy cat /data/letsencrypt/live/analytics.diegonmarcos.com/cert.pem | openssl x509 -noout -dates

# Force renewal via Nginx Proxy Manager UI
# Go to http://130.110.251.193:81 → SSL Certificates → Force Renew

# Check Nginx Proxy Manager logs
sudo docker compose logs nginx-proxy | grep -i certificate
```

#### 5. High Disk Usage

**Symptom**: Running out of disk space

**Diagnosis**:
```bash
df -h
sudo docker system df
du -sh ~/matomo/*
```

**Solution**:
```bash
# Clean Docker system
sudo docker system prune -a

# Archive old Matomo logs
sudo docker exec -it matomo-app php /var/www/html/console core:archive --force-all-websites

# Purge old database logs
sudo docker exec -it matomo-db mysql -u matomo -p -e "PURGE BINARY LOGS BEFORE DATE(NOW() - INTERVAL 7 DAY);"
```

---

## Backup & Recovery

### What to Backup

1. **Database** (`~/matomo/db/`)
2. **Matomo Files** (`~/matomo/matomo/`)
3. **Nginx Proxy Manager Config** (`~/matomo/npm/data/`)
4. **SSL Certificates** (`~/matomo/npm/letsencrypt/`)
5. **Docker Compose File** (`~/matomo/docker-compose.yml`)

### Backup Procedures

#### Full Backup

```bash
# Create backup directory
mkdir -p ~/backups

# Backup everything
cd ~
tar -czf ~/backups/matomo-backup-$(date +%Y%m%d-%H%M%S).tar.gz matomo/

# Verify backup
ls -lh ~/backups/
```

#### Database Only Backup

```bash
# Create backup
sudo docker exec matomo-db mysqldump -u matomo -p matomo | gzip > ~/backups/matomo-db-$(date +%Y%m%d).sql.gz

# Verify
zcat ~/backups/matomo-db-*.sql.gz | head -20
```

#### Automated Backup Script

Create `~/backup-matomo.sh`:

```bash
#!/bin/bash
BACKUP_DIR=~/backups
DATE=$(date +%Y%m%d-%H%M%S)

# Create backup directory
mkdir -p $BACKUP_DIR

# Full system backup
tar -czf $BACKUP_DIR/matomo-full-$DATE.tar.gz -C ~ matomo/

# Database backup
sudo docker exec matomo-db mysqldump -u matomo -p<PASSWORD> matomo | gzip > $BACKUP_DIR/matomo-db-$DATE.sql.gz

# Keep only last 7 backups
ls -t $BACKUP_DIR/matomo-full-* | tail -n +8 | xargs -r rm
ls -t $BACKUP_DIR/matomo-db-* | tail -n +8 | xargs -r rm

echo "Backup completed: $DATE"
```

Make executable:
```bash
chmod +x ~/backup-matomo.sh
```

Add to crontab (daily at 2 AM):
```bash
crontab -e
# Add line:
0 2 * * * /home/ubuntu/backup-matomo.sh >> /home/ubuntu/backup.log 2>&1
```

### Recovery Procedures

#### Full System Recovery

```bash
# Stop services
cd ~/matomo
sudo docker compose down

# Restore from backup
cd ~
tar -xzf ~/backups/matomo-backup-YYYYMMDD-HHMMSS.tar.gz

# Start services
cd ~/matomo
sudo docker compose up -d
```

#### Database Recovery

```bash
# Stop Matomo (keep database running)
sudo docker compose stop matomo

# Restore database
zcat ~/backups/matomo-db-YYYYMMDD.sql.gz | sudo docker exec -i matomo-db mysql -u matomo -p matomo

# Restart services
sudo docker compose up -d
```

---

## Installation Scripts

### Main Installation Script

**Location**: Repository `/1.ops/install-matomo.sh`

**Purpose**: Automated installation of Docker, Matomo, and Nginx Proxy Manager

**Usage**:
```bash
# Download and run
curl -fsSL https://raw.githubusercontent.com/diegonmarcos/diegonmarcos.github.io/claude/review-analytics-matomo-01AfDPW6dLDgTW5qRkCDh5Mj/1.ops/install-matomo.sh -o install-matomo.sh
chmod +x install-matomo.sh
./install-matomo.sh
```

### Management Scripts

All located in repository `/1.ops/`:

1. **matomo-setup.sh** - Initial Docker and Matomo installation
2. **matomo-login.sh** - Quick SSH access
3. **matomo-manage.sh** - Container management (start/stop/restart/logs/backup)
4. **matomo-https-setup.sh** - Guided HTTPS configuration
5. **matomo-https-auto.sh** - Automated HTTPS via NPM API

---

## Security Considerations

### Best Practices

1. **SSH Keys**: Use key-based authentication only, disable password auth
2. **Firewall**: Keep security list restrictive, only open necessary ports
3. **Updates**: Regularly update Ubuntu, Docker, and containers
4. **Backups**: Automated daily backups with off-site storage
5. **SSL/TLS**: Always use HTTPS, enforce TLS 1.2+
6. **Passwords**: Use strong, unique passwords stored securely
7. **Monitoring**: Regular log review and security audits

### Sensitive Information

**Never commit to git**:
- Database passwords
- Matomo super user credentials
- SSH private keys
- NPM admin credentials
- API tokens

### Security Updates

```bash
# Update Ubuntu
sudo apt update && sudo apt upgrade -y

# Update Docker images
cd ~/matomo
sudo docker compose pull
sudo docker compose up -d

# Check for Matomo updates
# Via web interface: Settings → System Check
```

---

## Related Documentation

- [Oracle Cloud Documentation](https://docs.oracle.com/en-us/iaas/)
- [Docker Documentation](https://docs.docker.com/)
- [Matomo Documentation](https://matomo.org/docs/)
- [Nginx Proxy Manager Documentation](https://nginxproxymanager.com/guide/)
- [Let's Encrypt Documentation](https://letsencrypt.org/docs/)

---

## Support & Maintenance

### Quick Reference

| Item | Value |
|------|-------|
| **Server IP** | 130.110.251.193 |
| **Domain** | analytics.diegonmarcos.com |
| **SSH User** | ubuntu |
| **Docker Directory** | ~/matomo |
| **Region** | EU-Marseille-1 |

### Emergency Contacts

- Oracle Cloud Support: [cloud.oracle.com/support](https://cloud.oracle.com/support)
- Matomo Forums: [forum.matomo.org](https://forum.matomo.org/)

---

**Last Updated**: 2025-11-18
**Version**: 1.0
**Maintainer**: Diego Nepomuceno Marcos
