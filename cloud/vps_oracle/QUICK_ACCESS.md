# Quick Access - Oracle VPS Services

## 🌐 Service URLs

### Production (HTTPS)
| Service | URL | Description |
|---------|-----|-------------|
| Matomo Analytics | https://analytics.diegonmarcos.com | Main analytics interface (via proxy) |

### Direct Access (HTTP)
| Service | URL | Port | Description |
|---------|-----|------|-------------|
| **Nginx Proxy Manager** | http://130.110.251.193:81 | 81 | Reverse proxy admin interface |
| **Matomo Direct** | http://130.110.251.193:8080 | 8080 | Direct access to Matomo (bypass proxy) |

### Management
| Service | URL | Description |
|---------|-----|-------------|
| Oracle Cloud Console | https://cloud.oracle.com/ | VM management & monitoring |
| SSH Access | `ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193` | Terminal access to VM |

---

## 🔌 Port Map

```
130.110.251.193
├── :80   → Nginx Proxy Manager (HTTP)
├── :443  → Nginx Proxy Manager (HTTPS)
├── :81   → Nginx Proxy Manager Admin UI
├── :8080 → Matomo Direct Access
└── :22   → SSH
```

---

## 🐳 Docker Services

### Access Container Logs
```bash
# SSH into VM
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193

# View all containers
cd ~/matomo && sudo docker compose ps

# View specific logs
sudo docker logs -f nginx-proxy    # Proxy logs
sudo docker logs -f matomo-app     # Matomo logs
sudo docker logs -f matomo-db      # Database logs
```

---

## 📊 Default Credentials

### Nginx Proxy Manager
- **URL**: http://130.110.251.193:81
- **Email**: admin@example.com
- **Password**: changeme
- ⚠️ **Change password on first login!**

### Matomo
- Set up during initial installation wizard
- Access via: https://analytics.diegonmarcos.com

---

## 🔗 Related Documentation

- [Infrastructure Spec](spec.md) - Full VM and Docker details
- [Matomo Management](../analytics/matomo/README.md) - Management scripts and operations
- [Cloud Dashboard](../front-cloud/index.html) - Web interface to all services

---

**Last Updated**: 2025-11-25
