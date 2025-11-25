# MariaDB Database

Database backend for Matomo Analytics.

---

## 📦 Container Details

- **Container Name**: `matomo-db`
- **Image**: `mariadb:10.11`
- **Status**: Running on matomo-server

---

## 🗄️ Database Configuration

- **Database Name**: matomo
- **User**: matomo
- **Port**: 3306 (internal Docker network only)
- **Host**: mariadb (Docker DNS)

---

## 🛠️ Management

### Access Database Shell
```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
cd ~/matomo
sudo docker exec -it matomo-db mysql -u matomo -p
```

### View Logs
```bash
sudo docker logs -f matomo-db
```

### Check Database Size
```bash
sudo docker exec -it matomo-db mysql -u matomo -p -e "
SELECT
    table_schema AS 'Database',
    ROUND(SUM(data_length + index_length) / 1024 / 1024, 2) AS 'Size (MB)'
FROM information_schema.TABLES
WHERE table_schema = 'matomo';"
```

---

## 💾 Backup

### Create Backup
```bash
sudo docker exec matomo-db mysqldump -u matomo -p matomo > backup_$(date +%Y%m%d).sql
```

### Restore Backup
```bash
cat backup.sql | sudo docker exec -i matomo-db mysql -u matomo -p matomo
```

---

## 📁 Data Location

- **Container Volume**: `~/matomo/db:/var/lib/mysql`
- **Backup Recommendation**: Weekly automated backups

---

## 📖 Documentation

- **MariaDB Docs**: https://mariadb.com/kb/en/documentation/
- **Docker Hub**: https://hub.docker.com/_/mariadb

---

**Last Updated**: 2025-11-25
