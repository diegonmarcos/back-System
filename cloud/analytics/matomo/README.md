# Matomo Analytics Server

Self-hosted Matomo analytics infrastructure on Oracle Cloud for tracking portfolio website analytics.

---

## 📂 Directory Structure

```
matomo/
├── README.md                           # This file - navigation guide
├── DEPLOYMENT_STATUS.md                # Current deployment status
├── IMPLEMENTATION_SUMMARY.md           # GTM & cookie consent implementation
├── MATOMO_SERVER_DOCUMENTATION.md      # Complete technical documentation
├── TODO.md                             # Pending tasks
├── install-matomo.sh                   # Main installation script
├── matomo-setup.sh                     # Docker setup automation
├── matomo-login.sh                     # Quick SSH access
├── matomo-https-setup.sh               # Guided HTTPS configuration
├── matomo-https-auto.sh                # Automated HTTPS via API
└── matomo-manage.sh                    # Container management
```

---

## 📖 Documentation Guide

### For Quick Start
- **[DEPLOYMENT_STATUS.md](DEPLOYMENT_STATUS.md)** - Check current status and next steps

### For Operations
- **[MATOMO_SERVER_DOCUMENTATION.md](MATOMO_SERVER_DOCUMENTATION.md)** - Complete reference:
  - Server specifications
  - Network configuration
  - Docker stack details
  - Management commands
  - Backup/recovery procedures
  - Troubleshooting guide

### For Implementation History
- **[IMPLEMENTATION_SUMMARY.md](IMPLEMENTATION_SUMMARY.md)** - GTM tracking and cookie consent implementation details

### For Tasks
- **[TODO.md](TODO.md)** - Pending implementation tasks

---

## 🚀 Quick Commands

### SSH Access
```bash
./matomo-login.sh
# or
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
```

### Container Management
```bash
./matomo-manage.sh status      # Check status
./matomo-manage.sh logs        # View logs
./matomo-manage.sh restart     # Restart services
./matomo-manage.sh backup      # Create backup
```

### HTTPS Setup
```bash
./matomo-https-setup.sh        # Guided setup (recommended)
# or
./matomo-https-auto.sh         # Automated via API
```

---

## 🌐 Access URLs

| Service | URL |
|---------|-----|
| Matomo Analytics (HTTPS) | https://analytics.diegonmarcos.com |
| Nginx Proxy Manager | http://130.110.251.193:81 |
| Matomo Direct Access | http://130.110.251.193:8080 |

---

## 📊 Server Info

- **IP**: 130.110.251.193
- **Region**: EU-Marseille-1 (France)
- **Instance**: VM.Standard.E2.1.Micro (Always Free)
- **OS**: Ubuntu 24.04 Minimal
- **Resources**: 2 vCPUs, 1GB RAM, 50GB storage

---

## 🔐 Security Notes

1. SSH key-based authentication only
2. All passwords stored in `matomo-credentials.txt` (NOT in git)
3. SSL/TLS via Let's Encrypt (auto-renewal)
4. Firewall configured via Oracle Cloud Security Lists

---

**Last Updated**: 2025-11-25
