# MyPhotos App Deployment Specification

> **Service**: PhotoView Photo Gallery
> **URL**: https://photos.diegonmarcos.com
> **Version**: 1.0.0 | **Updated**: 2025-12-07

---

## 1. Overview

Self-hosted Google Photos alternative using PhotoView, secured with Authelia 2FA authentication, serving photos from Oracle Object Storage.

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                         MYPHOTOS ARCHITECTURE                               │
├─────────────────────────────────────────────────────────────────────────────┤
│                                                                             │
│  Internet                                                                   │
│      │                                                                      │
│      ▼                                                                      │
│  ┌───────────────────────────────────────────────────────┐                  │
│  │  GCP VM (arch-1) - Nginx Proxy Manager                │                  │
│  │  34.55.55.234                                         │                  │
│  │  ┌─────────────────────────────────────────────────┐  │                  │
│  │  │  photos.diegonmarcos.com                        │  │                  │
│  │  │  ├── SSL Termination (Let's Encrypt)            │  │                  │
│  │  │  ├── Authelia 2FA (auth_request)                │  │                  │
│  │  │  └── Lua Auto-Login (inject PhotoView token)    │  │                  │
│  │  └─────────────────────────────────────────────────┘  │                  │
│  └───────────────────────────────────────────────────────┘                  │
│      │ WireGuard VPN (10.0.0.0/24)                                          │
│      ▼                                                                      │
│  ┌───────────────────────────────────────────────────────┐                  │
│  │  Oracle VM (oci-p-flex_1) - PhotoView                 │                  │
│  │  10.0.0.2 (WG) / 84.235.234.87 (Public)               │                  │
│  │  ┌─────────────────────────────────────────────────┐  │                  │
│  │  │  photoview (viktorstrate/photoview:latest)      │  │                  │
│  │  │  ├── Port: 10.0.0.2:8080                        │  │                  │
│  │  │  ├── DB: MySQL 8.0 (photoview-db)               │  │                  │
│  │  │  └── Photos: /home/photoview/photos             │  │                  │
│  │  └─────────────────────────────────────────────────┘  │                  │
│  └───────────────────────────────────────────────────────┘                  │
│      │                                                                      │
│      ▼                                                                      │
│  ┌───────────────────────────────────────────────────────┐                  │
│  │  Oracle Object Storage (S3-compatible)                │                  │
│  │  oracle_s3:my-photos/                                 │                  │
│  │  ├── takeout/         (~204 GB) Google Takeout zips   │                  │
│  │  └── real-photos/     (extracted) Photos by year      │                  │
│  └───────────────────────────────────────────────────────┘                  │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

---

## 2. Security Architecture

### Authentication Flow

```
┌──────────────────────────────────────────────────────────────────────────┐
│                    AUTHENTICATION FLOW (2FA + Auto-Login)                │
├──────────────────────────────────────────────────────────────────────────┤
│                                                                          │
│  User ──► photos.diegonmarcos.com ──► NPM (GCP)                          │
│                                          │                               │
│                                          ▼                               │
│                                   ┌──────────────┐                       │
│                                   │ auth_request │                       │
│                                   │   Authelia   │                       │
│                                   └──────┬───────┘                       │
│                                          │                               │
│                         ┌────────────────┴────────────────┐              │
│                         ▼                                 ▼              │
│                   [Not Logged In]                  [Authelia OK]         │
│                         │                                 │              │
│                         ▼                                 ▼              │
│              ┌──────────────────┐              ┌──────────────────┐      │
│              │ Redirect to      │              │ Lua Auto-Login   │      │
│              │ auth.diegon...   │              │ inject_auth()    │      │
│              │                  │              │                  │      │
│              │ 1. Username/Pass │              │ 1. Get cached    │      │
│              │ 2. TOTP 2FA      │              │    PhotoView     │      │
│              │ 3. Cookie set    │              │    token         │      │
│              └──────────────────┘              │ 2. Or fetch new  │      │
│                                                │    via GraphQL   │      │
│                                                │ 3. Inject cookie │      │
│                                                │    auth-token=   │      │
│                                                └────────┬─────────┘      │
│                                                         │                │
│                                                         ▼                │
│                                               ┌──────────────────┐       │
│                                               │ PhotoView App    │       │
│                                               │ (auto logged in) │       │
│                                               └──────────────────┘       │
│                                                                          │
└──────────────────────────────────────────────────────────────────────────┘
```

### Security Layers

| Layer | Component | Purpose |
|-------|-----------|---------|
| 1 | SSL/TLS | Encryption in transit (Let's Encrypt) |
| 2 | Authelia | 2FA authentication (TOTP) |
| 3 | WireGuard | Encrypted tunnel GCP ↔ Oracle |
| 4 | Lua Auto-Login | Seamless PhotoView auth after 2FA |

---

## 3. Infrastructure

### Servers

| Server | IP | Role | Resources |
|--------|----|----|-----------|
| arch-1 (GCP) | 34.55.55.234 | Proxy, Auth, DNS | e2-micro, 30GB |
| oci-p-flex_1 (Oracle) | 84.235.234.87 / 10.0.0.2 | PhotoView, Storage | A1.Flex 4 OCPU, 24GB RAM, 100GB |

### Docker Containers (Oracle VM)

| Container | Image | Port | Purpose |
|-----------|-------|------|---------|
| photoview | viktorstrate/photoview:latest | 10.0.0.2:8080 | Photo gallery |
| photoview-db | mysql:8.0 | 3306 | PhotoView metadata |
| photos-db | postgres:16-alpine | 5432 | Future webhook processor |

### Storage

| Location | Type | Size | Contents |
|----------|------|------|----------|
| oracle_s3:my-photos/takeout/ | Object Storage | ~204 GB | Google Takeout ZIPs |
| oracle_s3:my-photos/real-photos/ | Object Storage | ~200 GB | Extracted photos |
| /tmp/test-photos | VM Local | Variable | PhotoView mounted photos |

---

## 4. Configuration Files

### 4.1 PhotoView Environment

```bash
PHOTOVIEW_MYSQL_URL=photoview:photoview@tcp(photoview-db:3306)/photoview
PHOTOVIEW_LISTEN_IP=0.0.0.0
PHOTOVIEW_LISTEN_PORT=80
PHOTOVIEW_PUBLIC_ENDPOINT=https://photos.diegonmarcos.com/
PHOTOVIEW_SERVE_UI=1
PHOTOVIEW_UI_PATH=/app/ui
PHOTOVIEW_FACE_RECOGNITION_MODELS_PATH=/app/data/models
PHOTOVIEW_MEDIA_CACHE=/home/photoview/media-cache
```

### 4.2 NPM Custom Location (photos.diegonmarcos.com)

```nginx
# Forward auth to Authelia
auth_request /authelia;
auth_request_set $target_url $scheme://$http_host$request_uri;
auth_request_set $user $upstream_http_remote_user;
auth_request_set $groups $upstream_http_remote_groups;
auth_request_set $name $upstream_http_remote_name;
auth_request_set $email $upstream_http_remote_email;

error_page 401 =302 https://auth.diegonmarcos.com/?rd=$target_url;

# Authelia endpoint
location /authelia {
    internal;
    proxy_pass http://authelia:9091/api/verify;
    proxy_pass_request_body off;
    proxy_set_header Content-Length "";
    proxy_set_header X-Original-URL $scheme://$http_host$request_uri;
    proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
    proxy_set_header X-Forwarded-Proto $scheme;
}

# Lua auto-login after Authelia passes
access_by_lua_block {
    local autologin = require "photoview_autologin"
    autologin.inject_auth()
}
```

### 4.3 Rclone Remotes (Oracle VM)

```bash
# List configured remotes
$ rclone listremotes
gdrive:
gdrive_photos:
oracle_s3:

# S3 bucket structure
oracle_s3:my-photos/
├── takeout/                    # Google Takeout zip files (~204 GB)
│   ├── takeout-*-001.zip      # ~50 GB
│   ├── takeout-*-002.zip      # ~50 GB
│   ├── takeout-*-003.zip      # ~50 GB
│   ├── takeout-*-004.zip      # ~50 GB
│   └── takeout-*-005.zip      # ~4 GB
├── real-photos/                # Extracted photos
│   └── Takeout/Google Photos/
│       ├── 2015/
│       ├── 2016/
│       ├── ...
│       └── 2024/
├── demo-photos/                # Test photos
└── test-photos/                # Development
```

---

## 5. Data Migration

### Google Takeout Extraction Process

```
┌─────────────────────────────────────────────────────────────────────────┐
│                    EXTRACTION FLOW (Streaming)                          │
├─────────────────────────────────────────────────────────────────────────┤
│                                                                         │
│  Oracle Object Storage          Oracle VM              Oracle Object    │
│  (S3)                           (Compute)              Storage (S3)     │
│                                                                         │
│  takeout/*.zip ──► rclone ──► unzip ──► rclone ──► real-photos/         │
│     (204 GB)      mount       extract    mount VFS    (extracted)       │
│                                                                         │
│                   ┌─────────────────┐                                   │
│                   │  VFS Cache      │                                   │
│                   │  (~10-15 GB)    │                                   │
│                   │  rotating       │                                   │
│                   └─────────────────┘                                   │
│                                                                         │
│  Why streaming?                                                         │
│  • Object Storage cannot execute code (dumb storage)                    │
│  • VM has limited disk (100GB) vs data (204GB)                          │
│  • VFS cache allows processing large data with small disk               │
└─────────────────────────────────────────────────────────────────────────┘
```

### Extraction Commands

```bash
# Mount S3 bucket
rclone mount oracle_s3:my-photos /tmp/s3mount \
    --daemon \
    --vfs-cache-mode full \
    --allow-non-empty

# Extract (streams through mount)
cd /tmp/s3mount/real-photos
unzip -o /tmp/s3mount/takeout/takeout-*.zip

# Monitor progress
tail -f /home/ubuntu/extract_all.log
rclone size oracle_s3:my-photos/real-photos/
```

---

## 6. Operations

### Start/Stop PhotoView

```bash
# SSH to Oracle VM
ssh ubuntu@84.235.234.87

# Check status
docker ps | grep photoview

# Restart
docker restart photoview photoview-db

# Logs
docker logs -f photoview
```

### Monitor Storage

```bash
# Check S3 bucket size
rclone size oracle_s3:my-photos/

# List extracted photos
rclone ls oracle_s3:my-photos/real-photos/ | wc -l

# Disk usage on VM
df -h
```

### Update PhotoView to Use S3 Photos

```bash
# After extraction, update mount path
docker stop photoview
# Edit compose to mount rclone path instead of /tmp/test-photos
docker-compose up -d photoview
```

---

## 7. Costs

| Resource | Provider | Monthly Cost |
|----------|----------|--------------|
| oci-p-flex_1 VM | Oracle | $5.50 |
| Object Storage (~200GB) | Oracle | ~$5.00 |
| arch-1 VM | GCP | Free tier |
| **Total** | | **~$10.50/mo** |

---

## 8. Future Enhancements

- [ ] Mount S3 photos directly to PhotoView container
- [ ] Set up automated backup of PhotoView database
- [ ] Configure face recognition models
- [ ] Add sharing functionality
- [ ] Mobile app integration (PhotoView PWA)
