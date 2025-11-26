# Nginx Proxy Manager

Reverse proxy with SSL/TLS termination for all web services.

---

## 📦 Container Details

- **Container Name**: `nginx-proxy`
- **Image**: `jc21/nginx-proxy-manager:latest`
- **Status**: Running on matomo-server

---

## 🌐 Access

- **Admin UI**: http://130.110.251.193:81
- **HTTP Port**: 80
- **HTTPS Port**: 443

### Default Credentials (Change on first login)
- **Email**: admin@example.com
- **Password**: changeme

---

## 🔧 Configuration

### Proxy Hosts
| Domain | Forward To | SSL |
|--------|-----------|-----|
| analytics.diegonmarcos.com | matomo-app:80 | ✅ Let's Encrypt |

### SSL Certificates
- **Provider**: Let's Encrypt
- **Auto-Renewal**: ✅ Enabled
- **Domains**: analytics.diegonmarcos.com

---

## 🛠️ Management

### View Logs
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
cd ~/matomo
sudo docker logs -f nginx-proxy
```

### Restart Service
```bash
sudo docker restart nginx-proxy
```

---

## 📖 Documentation

- **Official Docs**: https://nginxproxymanager.com/guide/
- **Docker Hub**: https://hub.docker.com/r/jc21/nginx-proxy-manager

---

**Last Updated**: 2025-11-25
