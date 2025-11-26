# Web Hosting Server

Static and dynamic website hosting service.

---

## 📋 Status

- **Status**: ⏳ Planned
- **Purpose**: Host personal projects, portfolios, and web applications
- **Target**: Multiple websites/domains on single VPS

---

## 🎯 Planned Features

### Hosting Types

1. **Static Sites**:
   - HTML/CSS/JS
   - Jekyll/Hugo/11ty builds
   - React/Vue/Angular SPAs

2. **Dynamic Sites**:
   - Node.js applications
   - Python (Flask/Django)
   - PHP applications

3. **Databases** (if needed):
   - PostgreSQL
   - MySQL/MariaDB (already available)
   - MongoDB

### Domains to Host

- `projects.diegonmarcos.com` - Project showcase
- `blog.diegonmarcos.com` - Personal blog
- `api.diegonmarcos.com` - API endpoints
- Custom domains for clients/projects

---

## 🛠️ Technology Stack (Proposed)

### Option 1: Nginx + Static Files

**Best for**: Static sites, SPAs

**Setup**:
```
Nginx Proxy Manager
    ↓
Static file directories
```

**Pros**:
- Lightweight
- Fast
- Simple deployment
- Low resource usage

**Cons**:
- No server-side logic
- Manual deployments

### Option 2: Docker Containers per Site

**Best for**: Multiple diverse projects

**Setup**:
```
Nginx Proxy Manager
    ↓
Container 1 (Node.js app)
Container 2 (Python app)
Container 3 (Static site)
```

**Pros**:
- Isolated environments
- Easy scaling
- Multiple tech stacks

**Cons**:
- Higher resource usage
- More complex management

### Option 3: Coolify / CapRover

**Best for**: Self-hosted PaaS experience

**Coolify Features**:
- Git-based deployments
- Automatic SSL
- Docker-based
- Web UI management

**Pros**:
- Heroku-like experience
- Easy deployments
- Built-in monitoring

**Cons**:
- ~500MB RAM overhead
- Learning curve

---

## 📊 Resource Requirements

| Solution | RAM | CPU | Disk |
|----------|-----|-----|------|
| **Nginx Static** | ~20 MB | 0.05 vCPU | ~100 MB |
| **Docker per Site** | ~100 MB/site | 0.1 vCPU/site | ~200 MB/site |
| **Coolify** | ~500 MB + apps | 0.3 vCPU | ~1 GB |

---

## 🌐 Planned Sites & Architecture

### Site 1: Project Portfolio (Static)

```
projects.diegonmarcos.com
    ↓
Nginx serves /var/www/projects/
```

**Tech**: HTML/CSS/JS or React build
**Deployment**: Git push → build → rsync

### Site 2: Personal Blog (Static)

```
blog.diegonmarcos.com
    ↓
Nginx serves /var/www/blog/
```

**Tech**: Jekyll or Hugo
**Deployment**: GitHub Actions → build → deploy

### Site 3: API Service (Dynamic)

```
api.diegonmarcos.com
    ↓
Node.js/Express container
    ↓
MariaDB (shared)
```

**Tech**: Node.js + Express
**Deployment**: Docker Compose

---

## 🚀 Deployment Workflows

### Git-based Deployment

**Option A - Manual**:
```bash
# On local machine
git push origin main

# On VPS
ssh vps
cd /var/www/site
git pull
npm run build  # if needed
```

**Option B - GitHub Actions** (recommended):
```yaml
name: Deploy
on:
  push:
    branches: [main]
jobs:
  deploy:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - run: npm run build
      - uses: appleboy/scp-action@master
        with:
          host: 130.110.251.193
          username: ubuntu
          key: ${{ secrets.SSH_KEY }}
          source: "dist/*"
          target: "/var/www/site/"
```

---

## 🔐 Security Considerations

### SSL/TLS

- All sites must use HTTPS
- Let's Encrypt via Nginx Proxy Manager
- Auto-renewal enabled

### Access Control

- SSH keys only (no passwords)
- Separate deploy user (optional)
- File permissions: 644 for files, 755 for directories

### Updates

- Regular OS updates
- Docker image updates
- Dependency updates (npm, pip, etc.)

---

## 📝 Implementation Plan

### Phase 1: Basic Static Hosting
- [ ] Create web hosting directory structure
- [ ] Configure Nginx for static files
- [ ] Set up first static site
- [ ] Configure SSL certificate

### Phase 2: Git Deployment
- [ ] Set up Git repositories
- [ ] Create deployment scripts
- [ ] Configure GitHub Actions
- [ ] Test automated deployments

### Phase 3: Dynamic Applications
- [ ] Deploy first Node.js app
- [ ] Configure database connections
- [ ] Set up environment variables
- [ ] Enable logging/monitoring

### Phase 4: Multiple Sites
- [ ] Add additional domains
- [ ] Implement site isolation
- [ ] Configure resource limits
- [ ] Set up backup procedures

---

## 🌐 Directory Structure (Proposed)

```
/var/www/
├── projects/               # projects.diegonmarcos.com
│   └── dist/              # Built static files
├── blog/                   # blog.diegonmarcos.com
│   └── public/            # Jekyll/Hugo output
└── api/                    # api.diegonmarcos.com
    ├── docker-compose.yml
    └── app/               # Node.js application
```

**Alternatively with Docker**:
```
~/web-hosting/
├── docker-compose.yml
├── projects/
│   └── Dockerfile
├── blog/
│   └── Dockerfile
└── api/
    ├── Dockerfile
    └── src/
```

---

## 📊 Monitoring & Analytics

### Site Monitoring

- **Uptime**: UptimeRobot or self-hosted
- **Analytics**: Matomo (already installed)
- **Logs**: Centralized logging (optional)

### Resource Monitoring

```bash
# Docker stats
docker stats

# Disk usage
du -sh /var/www/*

# Nginx access logs
docker logs nginx-proxy | grep projects.diegonmarcos.com
```

---

## 🔧 Nginx Configuration Example

**Static Site** (`/etc/nginx/sites-available/projects.conf`):
```nginx
server {
    listen 80;
    server_name projects.diegonmarcos.com;
    root /var/www/projects/dist;
    index index.html;

    location / {
        try_files $uri $uri/ /index.html;
    }
}
```

**Node.js Reverse Proxy** (via Nginx Proxy Manager UI):
- Domain: api.diegonmarcos.com
- Forward to: nodejs-app:3000
- SSL: Let's Encrypt
- Websockets: Enabled

---

## 📚 Related Documentation

- **Main VPS Spec**: [`../README.md`](../README.md)
- **Nginx Proxy**: [`../nginx-proxy/README.md`](../nginx-proxy/README.md)
- **Coolify**: https://coolify.io/
- **CapRover**: https://caprover.com/

---

## 💡 Recommendations

### Start Simple

1. **Begin with static sites** - Lowest resource usage
2. **Use Git-based deployment** - Version control + rollback
3. **GitHub Actions for CI/CD** - Automated, reliable
4. **Add dynamic apps gradually** - Monitor resource usage

### Consider External Services

For high-traffic or critical sites:
- **Cloudflare Pages** - Free static hosting + CDN
- **Vercel/Netlify** - Free tier, excellent performance
- **Self-host only** - Personal projects, learning, privacy

### Resource Management

Current VPS (1GB RAM) can handle:
- 3-5 static sites (negligible resources)
- 2-3 small Node.js apps (~150MB each)
- 1 larger application (~400MB)

**If more needed**: Upgrade to higher tier or use multiple VPS instances.

---

**Status**: ⏳ Planning Stage
**Priority**: High (next after Matomo optimization complete)
**Est. Setup Time**: 1-2 days for basic static hosting
**Last Updated**: 2025-11-25
