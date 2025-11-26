# Firewall Configuration

Firewall rules and security configuration for the VPS.

---

## 🛡️ Current Status

- **Status**: ✅ Active
- **Provider**: Oracle Cloud Security Lists
- **Local**: Ubuntu iptables (ACCEPT all - controlled by OCI)
- **Purpose**: Network security and access control

---

## 📊 Current Configuration

### Oracle Cloud Security Lists

**Ingress Rules** (Inbound):

| Port | Protocol | Source | Purpose |
|------|----------|--------|---------|
| 22 | TCP | 0.0.0.0/0 | SSH access |
| 80 | TCP | 0.0.0.0/0 | HTTP (redirects to HTTPS) |
| 443 | TCP | 0.0.0.0/0 | HTTPS (secure traffic) |
| 8080 | TCP | 0.0.0.0/0 | Matomo direct access |
| 81 | TCP | 0.0.0.0/0 | Nginx Proxy Manager admin |

**Egress Rules** (Outbound):
- All traffic allowed (default)

---

## 🔧 Ubuntu iptables

**Current State**: All chains set to ACCEPT policy

```bash
Chain INPUT (policy ACCEPT)
Chain FORWARD (policy ACCEPT)
Chain OUTPUT (policy ACCEPT)
```

**Rationale**: Security is enforced at Oracle Cloud level (Security Lists), which is more reliable and easier to manage than local iptables.

---

## 🔐 Security Best Practices

### Active Protections

✅ **Network Level**:
- Oracle Cloud Security Lists (stateful firewall)
- DDoS protection (built-in)
- Geographic filtering (optional)

✅ **Application Level**:
- Nginx Proxy Manager (rate limiting, common exploits blocked)
- SSH key-based authentication only
- Fail2ban (optional - not currently installed)

✅ **Service Level**:
- Docker internal networking (services isolated)
- No direct database access from internet
- SSL/TLS for all public services

---

## 🚨 Planned Improvements

### Priority 1: Fail2ban

Install fail2ban for SSH brute-force protection:

```bash
sudo apt install fail2ban -y
sudo systemctl enable fail2ban
```

**Configuration** (`/etc/fail2ban/jail.local`):
```ini
[sshd]
enabled = true
port = 22
maxretry = 3
bantime = 3600
findtime = 600
```

### Priority 2: IP Whitelisting

Restrict SSH access to known IPs:

**In Oracle Cloud Security List**:
- Remove: `0.0.0.0/0` for port 22
- Add: Your home/office IPs only

### Priority 3: Port Hardening

**Close unnecessary ports**:
- Port 8080 (Matomo direct) - Only allow via proxy
- Port 81 (NPM admin) - Restrict to management IPs

---

## 📝 Firewall Management Commands

### View Current Rules

```bash
# Oracle Cloud Security Lists
# View in console: https://cloud.oracle.com/ → Networking → VCN → Security Lists

# Local iptables
sudo iptables -L -n -v
```

### Modify Rules

**Oracle Cloud** (recommended):
1. Go to Oracle Cloud Console
2. Navigate to: Networking → Virtual Cloud Networks → web-server-vcn
3. Click: Security Lists → Default Security List
4. Add/Remove rules as needed

**Local iptables** (not recommended):
```bash
# Allow specific port
sudo iptables -A INPUT -p tcp --dport 9000 -j ACCEPT

# Block specific IP
sudo iptables -A INPUT -s 1.2.3.4 -j DROP

# Save rules
sudo iptables-save | sudo tee /etc/iptables/rules.v4
```

---

## 🔍 Monitoring & Logs

### Check for Suspicious Activity

```bash
# SSH login attempts
sudo journalctl -u ssh | grep "Failed password"

# Nginx access logs
sudo docker logs nginx-proxy | grep -E "40[0-9]|50[0-9]"

# System authentication logs
sudo cat /var/log/auth.log | tail -100
```

### Monitor Open Ports

```bash
# Listening ports
sudo ss -tlnp

# Active connections
sudo ss -anp | grep ESTABLISHED
```

---

## 🚨 Incident Response

### If Suspicious Activity Detected

1. **Block IP immediately**:
   ```bash
   # Via Oracle Cloud Security List
   # Add deny rule for specific IP
   ```

2. **Check active connections**:
   ```bash
   sudo ss -anp | grep ESTABLISHED
   ```

3. **Review logs**:
   ```bash
   sudo journalctl -xe
   sudo cat /var/log/auth.log | grep -i failed
   ```

4. **Restart services if needed**:
   ```bash
   sudo docker compose restart
   ```

---

## 📊 Planned Services & Ports

Future services will require additional firewall rules:

| Service | Port | Status |
|---------|------|--------|
| **Sync (Nextcloud/Syncthing)** | TBD | ⏳ Planned |
| **Mail Server (SMTP)** | 25, 587, 465 | ⏳ Planned |
| **Mail Server (IMAP)** | 143, 993 | ⏳ Planned |
| **Web Hosting** | 80, 443 (shared) | ⏳ Planned |

---

## 📚 Related Documentation

- **Main VPS Spec**: [`../README.md`](../README.md)
- **Oracle Cloud Security**: https://docs.oracle.com/iaas/Content/Network/Concepts/securitylists.htm
- **iptables Guide**: https://www.netfilter.org/documentation/
- **Fail2ban**: https://www.fail2ban.org/

---

**Last Updated**: 2025-11-25
