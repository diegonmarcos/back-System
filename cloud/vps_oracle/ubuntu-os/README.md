# Ubuntu OS Configuration

Base operating system configuration and system files for the VPS.

---

## 🖥️ System Information

- **OS**: Ubuntu 24.04 LTS Minimal
- **Kernel**: Latest (auto-updated)
- **Architecture**: x86_64 (amd64)
- **Init System**: systemd

---

## ⚙️ Current Configuration

### System Packages

**Essential Packages Installed**:
```bash
# Core utilities
apt-transport-https
ca-certificates
curl
wget
gnupg
lsb-release

# Docker
docker-ce
docker-ce-cli
containerd.io
docker-buildx-plugin
docker-compose-plugin

# Monitoring
htop
iotop (optional)
```

### System Services

| Service | Status | Purpose |
|---------|--------|---------|
| **ssh** | ✅ Enabled | Remote access |
| **docker** | ✅ Enabled | Container runtime |
| **cron** | ✅ Enabled | Scheduled tasks |
| **systemd-timesyncd** | ✅ Enabled | Time synchronization |
| **ufw** | ❌ Disabled | Firewall (using Oracle Security Lists) |

---

## 🔧 Configuration Files

### SSH Configuration

**File**: `/etc/ssh/sshd_config`

**Key Settings**:
```bash
# Authentication
PermitRootLogin no
PubkeyAuthentication yes
PasswordAuthentication no

# Security
X11Forwarding no
MaxAuthTries 3
MaxSessions 10

# Performance
UseDNS no
```

### Crontab

**File**: `/var/spool/cron/crontabs/ubuntu` (view with `crontab -l`)

**Current Jobs**:
```cron
# Matomo archiving (hourly)
5 * * * * docker exec matomo-app php /var/www/html/console core:archive --url=https://analytics.diegonmarcos.com/ > /tmp/matomo-archive.log 2>&1
```

### Timezone

```bash
# Set timezone
sudo timedatectl set-timezone America/New_York

# Verify
timedatectl
```

---

## 📦 Installed Software

### Docker

**Version**: 27.4.0
**Install Date**: 2025-11-25

**Configuration**: `/etc/docker/daemon.json`
```json
{
  "log-driver": "json-file",
  "log-opts": {
    "max-size": "10m",
    "max-file": "3"
  }
}
```

### Python

**Version**: Python 3 (system default)
**Packages**: Minimal (OS-provided only)

### Node.js

**Status**: Not installed (use Docker for Node.js apps)

---

## 🔐 Security Configuration

### User Management

**Primary User**: `ubuntu`
- Sudo access: ✅ Yes
- SSH key: ✅ ~/.ssh/authorized_keys
- Groups: sudo, docker

**Root Account**:
- Direct login: ❌ Disabled
- Access: Via `sudo su -` only

### SSH Keys

**Location**: `/home/ubuntu/.ssh/authorized_keys`

**Permissions**:
```bash
~/.ssh/                 700 (drwx------)
~/.ssh/authorized_keys  600 (-rw-------)
```

### Automatic Updates

**Status**: Configured for security updates

**File**: `/etc/apt/apt.conf.d/20auto-upgrades`
```bash
APT::Periodic::Update-Package-Lists "1";
APT::Periodic::Unattended-Upgrade "1";
```

---

## 📊 Resource Monitoring

### Check System Resources

```bash
# CPU and memory
htop

# Disk usage
df -h

# Disk I/O
iotop

# Network connections
ss -tunap

# Process list
ps aux --sort=-%mem | head -10
```

### System Logs

```bash
# All system logs
sudo journalctl -xe

# SSH logs
sudo journalctl -u ssh

# Docker logs
sudo journalctl -u docker

# Kernel messages
dmesg | tail -50
```

---

## 🛠️ Maintenance Tasks

### Daily (Automated)

- ✅ Matomo archiving (via cron)
- ✅ Security updates (unattended-upgrades)

### Weekly

```bash
# Check disk space
df -h

# Review logs for errors
sudo journalctl -p err..emerg --since "1 week ago"

# Check Docker disk usage
docker system df
```

### Monthly

```bash
# Full system update
sudo apt update && sudo apt upgrade -y

# Clean old packages
sudo apt autoremove -y
sudo apt autoclean

# Docker cleanup
docker system prune -a

# Review cron logs
grep CRON /var/log/syslog
```

---

## 📁 Directory Structure

### Important Directories

```
/
├── /home/ubuntu/           # User home
│   ├── /matomo/           # Matomo Docker stack
│   ├── /backups/          # System backups
│   └── /scripts/          # Management scripts
│
├── /var/www/              # Web hosting (future)
│
├── /etc/
│   ├── /ssh/              # SSH configuration
│   ├── /docker/           # Docker configuration
│   └── /systemd/          # System services
│
├── /var/log/              # Log files
│   ├── auth.log          # Authentication logs
│   ├── syslog            # System logs
│   └── docker/           # Docker logs
│
└── /tmp/                  # Temporary files
    └── matomo-archive.log # Matomo cron output
```

---

## 🚀 System Optimization

### Applied Optimizations

1. **Swappiness** (default is fine for 1GB RAM):
   ```bash
   # Check current value
   cat /proc/sys/vm/swappiness  # Usually 60

   # If needed to reduce (not currently needed)
   # sudo sysctl vm.swappiness=10
   ```

2. **File Descriptors** (increased for Docker):
   ```bash
   # Check limits
   ulimit -n

   # /etc/security/limits.conf (if needed)
   # * soft nofile 65536
   # * hard nofile 65536
   ```

3. **Kernel Parameters** (optimized for web serving):
   ```bash
   # /etc/sysctl.conf
   net.core.somaxconn = 1024
   net.ipv4.tcp_max_syn_backlog = 2048
   ```

---

## 🔧 Configuration Management

### Backup Configuration Files

**Script**: `~/scripts/backup-configs.sh`

```bash
#!/bin/bash
# Backup system configuration files

BACKUP_DIR=~/config-backups/$(date +%Y%m%d)
mkdir -p $BACKUP_DIR

# SSH config
sudo cp /etc/ssh/sshd_config $BACKUP_DIR/

# Crontab
crontab -l > $BACKUP_DIR/crontab

# Docker config
sudo cp /etc/docker/daemon.json $BACKUP_DIR/ 2>/dev/null

# System info
uname -a > $BACKUP_DIR/system-info.txt
df -h > $BACKUP_DIR/disk-usage.txt
free -h > $BACKUP_DIR/memory.txt

echo "Config backup saved to: $BACKUP_DIR"
```

### Restore from Backup

```bash
# SSH config
sudo cp backup/sshd_config /etc/ssh/sshd_config
sudo systemctl restart ssh

# Crontab
crontab backup/crontab

# Docker config
sudo cp backup/daemon.json /etc/docker/daemon.json
sudo systemctl restart docker
```

---

## 📚 Configuration Files Reference

### Essential Files to Track

```bash
# System
/etc/ssh/sshd_config          # SSH configuration
/etc/systemd/system/*.service # Custom services
/etc/hosts                     # Host mappings
/etc/hostname                  # System hostname

# User
~/.bashrc                      # Bash configuration
~/.profile                     # User profile
~/.ssh/authorized_keys         # SSH keys

# Cron
/var/spool/cron/crontabs/ubuntu  # User crontab
/etc/cron.d/*                    # System cron jobs

# Docker
/etc/docker/daemon.json        # Docker daemon config
~/matomo/docker-compose.yml    # Matomo stack
```

---

## 🔍 Troubleshooting

### System Won't Boot

**Access via Oracle Cloud Console**:
1. Go to: https://cloud.oracle.com/
2. Compute → Instances → web-server
3. Click: "Console Connection"
4. Use web-based serial console

### High Resource Usage

```bash
# Find memory hogs
ps aux --sort=-%mem | head -10

# Find CPU hogs
ps aux --sort=-%cpu | head -10

# Check Docker containers
docker stats
```

### Disk Space Issues

```bash
# Find large directories
du -sh /* | sort -h

# Clean Docker
docker system prune -a

# Clean logs
sudo journalctl --vacuum-time=7d
```

---

## 📚 Related Documentation

- **Main VPS Spec**: [`../README.md`](../README.md)
- **Ubuntu Server Guide**: https://ubuntu.com/server/docs
- **systemd Documentation**: https://www.freedesktop.org/software/systemd/man/
- **Docker on Ubuntu**: https://docs.docker.com/engine/install/ubuntu/

---

## 📝 Quick Reference

### Common Commands

```bash
# System info
uname -a
lsb_release -a
hostnamectl

# Service management
sudo systemctl status <service>
sudo systemctl restart <service>
sudo journalctl -u <service>

# User management
sudo adduser <username>
sudo usermod -aG docker <username>
sudo deluser <username>

# Package management
sudo apt update
sudo apt upgrade
sudo apt install <package>
sudo apt remove <package>
```

---

**Last Updated**: 2025-11-25
**OS Version**: Ubuntu 24.04 LTS
**Kernel**: Auto-updated via unattended-upgrades
