# Matomo Analytics

Self-hosted web analytics platform for tracking website usage.

---

## 📦 Container Details

- **Container Name**: `matomo-app`
- **Image**: `matomo:latest`
- **Status**: Running on matomo-server

---

## 🌐 Access

- **HTTPS (Production)**: https://analytics.diegonmarcos.com
- **Direct Access**: http://130.110.251.193:8080

---

## 📊 Tracking Configuration

- **Site ID**: 1
- **Site Name**: Diego N Marcos Portfolio
- **Site URL**: https://diegonmarcos.github.io
- **Tracking URL**: https://analytics.diegonmarcos.com/matomo.php

---

## 🗄️ Database

- **Host**: mariadb (Docker container)
- **Database**: matomo
- **User**: matomo
- **Tables Prefix**: matomo_

---

## 🛠️ Management

### View Logs
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
cd ~/matomo
sudo docker logs -f matomo-app
```

### Access Container Shell
```bash
sudo docker exec -it matomo-app bash
```

### Run Matomo Console Commands
```bash
sudo docker exec -it matomo-app php /var/www/html/console
```

### Clear Cache
```bash
sudo docker exec -it matomo-app php /var/www/html/console core:clear-cache
```

---

## 📁 Data Location

- **Container Volume**: `~/matomo/matomo:/var/www/html`
- **Logs**: `~/matomo/matomo/tmp/logs/`

---

## 📖 Full Documentation

See [../../../analytics/matomo/README.md](../../../analytics/matomo/README.md) for complete documentation including:
- Setup instructions
- Management scripts
- Backup procedures
- Troubleshooting

---

**Last Updated**: 2025-11-25
