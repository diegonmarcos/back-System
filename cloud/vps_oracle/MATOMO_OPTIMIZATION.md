# Matomo Performance Optimization

Applied optimizations based on Matomo System Check warnings.

## Date: 2025-11-25

---

## ✅ Optimizations Completed

### 1. Automatic Archiving via Cron (Critical)

**Problem:** Browser-triggered archiving slows down report loading.

**Solution:**
```bash
# Added cron job
5 * * * * docker exec matomo-app php /var/www/html/console core:archive --url=https://analytics.diegonmarcos.com/ > /tmp/matomo-archive.log 2>&1
```

**Config Changed:**
```ini
[General]
enable_browser_archiving_triggering = 0
```

**Impact:**
- Reports load 10-100x faster
- No delays when viewing analytics
- Reduced server load during user visits

---

### 2. MySQL max_allowed_packet = 64MB

**Problem:** Default 16MB limit can cause issues with large queries.

**Solution:**
```bash
# Created /etc/mysql/conf.d/matomo.cnf in matomo-db container
[mysqld]
max_allowed_packet=67108864
```

**Impact:**
- Handles large data imports/exports
- Prevents query failures on high-traffic sites
- Required for bulk operations

---

### 3. Force SSL Connections

**Problem:** HTTP connections are insecure.

**Solution:**
```ini
[General]
force_ssl = 1
```

**Impact:**
- All connections forced to HTTPS
- Prevents man-in-the-middle attacks
- Protects analytics data in transit

---

### 4. MariaDB Schema Configuration

**Problem:** MySQL compatibility mode doesn't leverage MariaDB features.

**Solution:**
```ini
[database]
schema = Mariadb
```

**Impact:**
- Uses MariaDB-specific optimizations
- Better performance for database operations
- Proper feature detection

---

### 5. GeoIP2 Database (DBIP Lite)

**Problem:** Default location provider (browser language) is inaccurate.

**Solution:**
```bash
# Downloaded DBIP City Lite database (126MB)
/var/www/html/misc/dbip-city-lite-2025-11.mmdb

# Configured provider
[UserCountry]
location_provider = geoip2php

[GeoIP2]
geoip2_db_url = /var/www/html/misc/dbip-city-lite-2025-11.mmdb
```

**Impact:**
- Accurate country/city detection from IP addresses
- Better geographic reports
- Free alternative to MaxMind (updated monthly)

---

## System Check Results - Before vs After

| Check | Before | After |
|-------|--------|-------|
| Cron Archiving | ⚠️ Warning | ✅ OK |
| max_allowed_packet | ⚠️ 16MB | ✅ 64MB |
| Force SSL | ⚠️ Warning | ✅ Enabled |
| Database Schema | ⚠️ Warning | ✅ MariaDB |
| Geolocation | ⚠️ Language-based | ✅ GeoIP2 |

---

## Performance Improvements

**Expected improvements:**
- **Report Loading:** 10-100x faster (via cron archiving)
- **Geographic Accuracy:** ~95% country accuracy (was ~60%)
- **Security:** All traffic encrypted
- **Reliability:** No query failures on large operations

---

## Maintenance

### Monthly Tasks:

1. **Update GeoIP Database:**
```bash
ssh ubuntu@130.110.251.193 "docker exec matomo-app bash -c 'cd /var/www/html/misc && curl -L -o dbip-city-lite-YYYY-MM.mmdb.gz https://download.db-ip.com/free/dbip-city-lite-YYYY-MM.mmdb.gz && gunzip -f dbip-city-lite-YYYY-MM.mmdb.gz'"
```

2. **Check Cron Logs:**
```bash
ssh ubuntu@130.110.251.193 "cat /tmp/matomo-archive.log"
```

3. **Verify Archiving:**
- Go to Matomo → Administration → System → General Settings
- Check "Archive reports" section

---

## Configuration Files

**Docker Compose:** `/home/diego/matomo/docker-compose.yml`

**Matomo Config:**
- Container: `matomo-app:/var/www/html/config/config.ini.php`
- Local: Volume mounted from host

**MySQL Config:**
- Container: `matomo-db:/etc/mysql/conf.d/matomo.cnf`
- Persistent across container restarts

**Cron:**
- Host crontab: `crontab -l` on VPS

---

## Monitoring

### Check Archiving Status:
```bash
ssh ubuntu@130.110.251.193 "docker exec matomo-app ./console core:archive --force-date=today"
```

### View Cron Logs:
```bash
ssh ubuntu@130.110.251.193 "tail -f /tmp/matomo-archive.log"
```

### Check GeoIP Status:
- Matomo UI: Administration → System → Geolocation

---

## Troubleshooting

### Archiving Not Running:
```bash
# Check cron is active
ssh ubuntu@130.110.251.193 "systemctl status cron"

# Test manual archive
ssh ubuntu@130.110.251.193 "docker exec matomo-app ./console core:archive --force-all-websites"
```

### GeoIP Not Working:
```bash
# Verify database exists
ssh ubuntu@130.110.251.193 "docker exec matomo-app ls -lh /var/www/html/misc/*.mmdb"

# Test geolocation
ssh ubuntu@130.110.251.193 "docker exec matomo-app ./console usercountry:attribute --skip-ips-with-existing-locations"
```

### MySQL Issues:
```bash
# Check max_allowed_packet
ssh ubuntu@130.110.251.193 "docker exec matomo-db mysql -u root -pMatomoRoot2025! -e 'SHOW VARIABLES LIKE \"max_allowed_packet\";'"
```

---

## Next Steps (Optional)

1. **Enable Redis Cache** - Further performance boost
2. **Configure SMTP** - Email reports
3. **Set up Backup** - Automated backups to cloud storage
4. **Install Heatmaps Plugin** - Visual user behavior analysis

---

Created: 2025-11-25
Server: Oracle VPS (130.110.251.193)
Matomo Version: 5.5.2
