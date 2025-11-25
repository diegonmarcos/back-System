# VM: matomo-server

Oracle Cloud VM running Docker services for analytics and web infrastructure.

---

## 🖥️ VM Specifications

- **Name**: matomo-server
- **IP**: 130.110.251.193
- **OS**: Ubuntu 24.04 Minimal
- **Resources**: 2 vCPUs, 1GB RAM, 50GB storage
- **Region**: EU-Marseille-1 (France)

## SSH Access
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
```

---

## 🐳 Docker Services

### [nginx-proxy/](nginx-proxy/)
Nginx Proxy Manager - Reverse proxy with SSL/TLS
- **Port 80**: HTTP
- **Port 443**: HTTPS
- **Port 81**: Admin UI
- **Access**: http://130.110.251.193:81

### [matomo/](matomo/)
Matomo Analytics - Web analytics platform
- **Port 8080**: Direct access
- **Domain**: https://analytics.diegonmarcos.com
- **Purpose**: Website tracking and analytics

### [mariadb/](mariadb/)
MariaDB Database - Backend for Matomo
- **Port 3306**: Internal only
- **Database**: matomo
- **Purpose**: Data storage for analytics

---

## 📊 Service Status

Check all services:
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193 'cd ~/matomo && sudo docker compose ps'
```

---

## 🔗 Related Documentation

- [VM Spec](../spec.md) - Full VM specifications
- [Matomo Documentation](../../analytics/matomo/README.md) - Service documentation

---

**Last Updated**: 2025-11-25
