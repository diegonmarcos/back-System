# Matomo Analytics Server - Deployment Status

**Last Updated**: 2025-11-18
**Status**: ✅ Infrastructure Ready - Awaiting SSH Access

---

## 📊 What's Been Completed

### ✅ 1. Oracle Cloud Infrastructure
- **Region**: EU-Marseille-1 (France)
- **VCN**: matomo-vcn (10.0.0.0/16)
- **Subnet**: matomo-subnet (10.0.1.0/24)
- **Internet Gateway**: Configured
- **Security Lists**: Ports 22 (SSH), 80 (HTTP), 443 (HTTPS), 81 (NPM), 8080 (Matomo)

### ✅ 2. Compute Instance
- **Name**: matomo-server
- **Shape**: VM.Standard.E2.1.Micro (Always Free ✅)
- **OS**: Ubuntu 24.04 Minimal
- **Resources**: 2 vCPUs, 1GB RAM, 50GB storage
- **Public IP**: **130.110.251.193**
- **Status**: RUNNING ✅

### ✅ 3. Management Scripts Created
All scripts are POSIX-compliant and ready to use in `1.ops/`:

| Script | Purpose |
|--------|---------|
| `matomo-setup.sh` | Automated Docker + Matomo installation |
| `matomo-login.sh` | Quick SSH access |
| `matomo-manage.sh` | Container management (start/stop/logs/backup) |
| `matomo-https-setup.sh` | Guided HTTPS/SSL configuration |
| `matomo-https-auto.sh` | Automated HTTPS via NPM API |

### ✅ 4. Web Assets
- **Analytics Landing Page**: `5.analytics/index.html`
- **Domain**: analytics.diegonmarcos.com (configured for HTTPS)

### ✅ 5. Documentation
- **Server Setup**: `5.analytics/MATOMO_SERVER_SETUP.md`
- **Operations Guide**: `1.ops/MATOMO_OPS.md`
- **This Status**: `5.analytics/DEPLOYMENT_STATUS.md`

---

## ⚠️ Current Issue: SSH Access

**Problem**: Ubuntu iptables firewall is blocking SSH access by default.

**Solution**: Use Oracle Cloud Console to configure firewall:

1. Visit: https://cloud.oracle.com/
2. Go to: Compute → Instances → **matomo-server**
3. Click: **"Console Connection"** → **"Create connection"**
4. In web console, run:
   ```bash
   sudo iptables -I INPUT 1 -p tcp --dport 22 -j ACCEPT
   sudo iptables-save | sudo tee /etc/iptables/rules.v4
   ```
5. Test SSH:
   ```bash
   ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
   ```

---

## 🚀 Next Steps (After SSH Access Works)

### Step 1: Install Docker & Matomo
```bash
cd 1.ops
./matomo-setup.sh
```

**This script will:**
- Install Docker and Docker Compose
- Deploy Matomo + MariaDB + Nginx Proxy Manager
- Generate secure database passwords
- Save credentials to `matomo-credentials.txt`

### Step 2: Configure DNS
Point your DNS to the server:

**A Record:**
- **Name**: analytics
- **Value**: 130.110.251.193
- **TTL**: 300 (or auto)

**Result**: analytics.diegonmarcos.com → 130.110.251.193

### Step 3: Enable HTTPS

**Option A - Guided Setup (Recommended):**
```bash
./matomo-https-setup.sh
```
Follow interactive instructions to configure Nginx Proxy Manager with Let's Encrypt SSL.

**Option B - Automated API:**
```bash
./matomo-https-auto.sh
```
Fully automated SSL configuration (requires NPM credentials).

**What this does:**
- ✅ Requests Let's Encrypt SSL certificate
- ✅ Enables force HTTPS redirect
- ✅ Enables HTTP/2
- ✅ Enables HSTS security headers

### Step 4: Complete Matomo Installation
1. Visit: **https://analytics.diegonmarcos.com**
2. Follow Matomo installation wizard:
   - Database Server: mariadb
   - Database User: matomo
   - Database Password: (from matomo-credentials.txt)
   - Database Name: matomo
3. Create admin account
4. Add website: diegonmarcos.github.io

### Step 5: Integrate with Website
1. Get Matomo tracking code from dashboard
2. Update GTM configuration to include Matomo
3. Test tracking on all pages

---

## 📝 Stack Details

### Docker Containers
| Container | Image | Port | Purpose |
|-----------|-------|------|---------|
| matomo-app | matomo:latest | 8080 | Analytics application |
| matomo-db | mariadb:10.11 | 3306 | Database backend |
| nginx-proxy | nginx-proxy-manager | 80, 443, 81 | Reverse proxy with SSL |

### Network Architecture
```
Internet → Oracle Cloud Security Lists (ports 22,80,443)
  ↓
Nginx Proxy Manager (SSL termination)
  ↓
Matomo Application (Docker)
  ↓
MariaDB Database (Docker)
```

---

## 🔒 Security Features

- ✅ **SSL/TLS**: Let's Encrypt certificates (auto-renewal)
- ✅ **Force HTTPS**: All HTTP redirects to HTTPS
- ✅ **HTTP/2**: Enabled for better performance
- ✅ **HSTS**: HTTP Strict Transport Security
- ✅ **SSH Key Auth**: No password authentication
- ✅ **Firewall**: Oracle Cloud Security Lists + UFW
- ✅ **Isolated Network**: Docker bridge networking
- ✅ **Random Passwords**: Auto-generated database credentials

---

## 📊 Resource Usage (Estimated)

| Service | RAM | CPU | Disk |
|---------|-----|-----|------|
| Matomo | ~300 MB | 0.3 vCPU | ~500 MB |
| MariaDB | ~200 MB | 0.2 vCPU | ~200 MB |
| Nginx Proxy | ~50 MB | 0.1 vCPU | ~100 MB |
| **Total** | **~550 MB / 1 GB** | **0.6 / 2 vCPUs** | **~800 MB / 50 GB** |

**Headroom**: ✅ Comfortable (45% RAM, 70% CPU available)

---

## 🛠️ Maintenance Commands

```bash
# Check status
./matomo-manage.sh status

# View logs
./matomo-manage.sh logs

# Create backup
./matomo-manage.sh backup

# Restart services
./matomo-manage.sh restart

# Update Matomo
./matomo-manage.sh update

# SSH access
./matomo-login.sh
```

---

## 🌐 URLs (After Completion)

| Service | URL | Status |
|---------|-----|--------|
| Matomo Analytics | https://analytics.diegonmarcos.com | ⏳ Pending DNS + SSL |
| NPM Admin | http://130.110.251.193:81 | ⏳ Pending installation |
| Matomo Direct | http://130.110.251.193:8080 | ⏳ Pending installation |

---

## 🎯 Progress Checklist

- [x] Oracle Cloud account setup
- [x] OCI CLI installed and authenticated
- [x] VCN and networking configured
- [x] Security lists configured
- [x] Compute instance created
- [x] SSH keys generated
- [x] Management scripts created
- [x] HTTPS scripts created
- [x] Documentation completed
- [x] Old instance cleanup initiated
- [ ] **SSH access enabled** ← **NEXT STEP**
- [ ] Docker + Matomo installed
- [ ] DNS configured
- [ ] HTTPS/SSL enabled
- [ ] Matomo setup completed
- [ ] GTM integration
- [ ] Tracking verified

---

## 💡 Tips

1. **Save Credentials**: The `matomo-credentials.txt` file contains all database passwords. Store it securely!
2. **Backup Regularly**: Use `./matomo-manage.sh backup` weekly
3. **Monitor Logs**: Use `./matomo-manage.sh logs` to watch for issues
4. **Update Often**: Matomo releases security updates regularly
5. **Test Tracking**: Verify events are being recorded after setup

---

## 📞 Support Resources

- **Matomo Docs**: https://matomo.org/docs/
- **Nginx Proxy Manager**: https://nginxproxymanager.com/guide/
- **Oracle Cloud**: https://docs.oracle.com/iaas/
- **Docker Compose**: https://docs.docker.com/compose/

---

**Current State**: Infrastructure provisioned ✅
**Waiting For**: SSH access configuration
**Time to Complete**: ~15 minutes after SSH access enabled
