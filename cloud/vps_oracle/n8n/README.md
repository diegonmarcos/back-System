# n8n Orchestrator - Oracle VPS

Lightweight n8n deployment for the Multi-Agent RAG Orchestrator v4.2.

**Server**: 130.110.251.193 (EU-Marseille-1)
**Memory**: ~200-300 MB (optimized for 1GB VPS)

---

## Quick Start

### 1. SSH to Server

```bash
ssh -i ~/.ssh/matomo_key ubuntu@130.110.251.193
```

### 2. Clone Repository

```bash
cd ~
git clone git@github.com:diegonmarcos/ml-Agentic.git
```

### 3. Setup n8n

```bash
# Create directory
mkdir -p ~/n8n/workflows
cd ~/n8n

# Copy docker-compose (or create from back-System repo)
# Copy .env.example to .env and configure
cp .env.example .env
nano .env  # Set N8N_PASSWORD

# Start n8n
docker compose up -d

# Check status
docker compose ps
docker compose logs -f n8n
```

### 4. Configure Nginx Proxy

Add proxy host in Nginx Proxy Manager (http://130.110.251.193:81):

| Setting | Value |
|---------|-------|
| Domain | n8n.diegonmarcos.com |
| Scheme | http |
| Forward Host | n8n |
| Forward Port | 5678 |
| SSL | Request new certificate |
| Force SSL | Yes |
| Websockets | Yes |

---

## Access URLs

| Service | URL |
|---------|-----|
| **n8n Dashboard** | https://n8n.diegonmarcos.com |
| **n8n Direct** | http://130.110.251.193:5678 |
| **Nginx Admin** | http://130.110.251.193:81 |

---

## Architecture

This is a **lightweight deployment** of the Multi-Agent RAG Orchestrator v4.2:

```
┌─────────────────────────────────────────────────┐
│              Oracle VPS (1GB RAM)               │
├─────────────────────────────────────────────────┤
│                                                 │
│  ┌─────────────┐  ┌─────────────────────────┐  │
│  │   Nginx     │  │     Existing Stack      │  │
│  │   Proxy     │  │  (Matomo + MariaDB)     │  │
│  │   Manager   │  │     ~650 MB RAM         │  │
│  └──────┬──────┘  └─────────────────────────┘  │
│         │                                       │
│         │ Proxy                                 │
│         ▼                                       │
│  ┌─────────────────────────────────────────┐   │
│  │            n8n Orchestrator             │   │
│  │           ~200-300 MB RAM               │   │
│  │                                         │   │
│  │  ┌─────────────────────────────────┐   │   │
│  │  │     SQLite (embedded)           │   │   │
│  │  │     Workflows & Credentials     │   │   │
│  │  └─────────────────────────────────┘   │   │
│  │                                         │   │
│  │  External LLM APIs:                    │   │
│  │  - Claude (Tier 3)                     │   │
│  │  - Fireworks (Tier 1)                  │   │
│  │  - Together (Tier 1)                   │   │
│  │  - OpenAI (Tier 3)                     │   │
│  └─────────────────────────────────────────┘   │
│                                                 │
└─────────────────────────────────────────────────┘
```

**Note**: Ollama/local LLMs are NOT included (no GPU, insufficient RAM).
Use external LLM APIs configured directly in n8n nodes.

---

## Workflows

Import workflows from the ml-Agentic repository:

```bash
# Copy workflow files
cp ~/ml-Agentic/workflows/*.json ~/n8n/workflows/

# Import via n8n UI:
# 1. Go to https://n8n.diegonmarcos.com
# 2. Click "Workflows" → "Import from File"
# 3. Select workflow JSON files
```

---

## Configuration

### Environment Variables

| Variable | Description | Default |
|----------|-------------|---------|
| `N8N_USER` | Admin username | admin |
| `N8N_PASSWORD` | Admin password | changeme |
| `N8N_ENCRYPTION_KEY` | Credential encryption | auto-generated |
| `WEBHOOK_URL` | External webhook URL | https://n8n.diegonmarcos.com/ |
| `NODE_OPTIONS` | Node.js memory limit | --max-old-space-size=256 |

### Memory Optimization

The deployment is optimized for low memory:

- SQLite instead of PostgreSQL (~100MB saved)
- No Redis queue (~50MB saved)
- Main process execution (no workers)
- Execution data pruning (7 days retention)
- Node.js heap limited to 256MB

---

## Management Commands

```bash
# Start
docker compose up -d

# Stop
docker compose down

# Restart
docker compose restart

# View logs
docker compose logs -f n8n

# Shell access
docker exec -it n8n sh

# Backup data
docker cp n8n:/home/node/.n8n ./backup-$(date +%Y%m%d)

# Update n8n
docker compose pull
docker compose up -d
```

---

## Resource Usage

| Component | RAM | CPU |
|-----------|-----|-----|
| n8n | ~200-300 MB | 0.2-0.5 vCPU |
| Matomo | ~300 MB | 0.3 vCPU |
| MariaDB | ~200 MB | 0.2 vCPU |
| Nginx | ~50 MB | 0.1 vCPU |
| System | ~100 MB | 0.1 vCPU |
| **Total** | **~850-950 MB** | **~1.0 vCPU** |

**Available**: 1GB RAM, 2 vCPU - Within limits but tight.

---

## Troubleshooting

### n8n Won't Start

```bash
# Check logs
docker compose logs n8n

# Check memory
free -h

# Restart if OOM
docker compose restart
```

### Out of Memory

```bash
# Reduce n8n memory limit
# Edit docker-compose.yml: NODE_OPTIONS=--max-old-space-size=200

# Or stop Matomo temporarily
docker stop matomo-app
```

### Webhook Not Working

1. Check Nginx proxy configuration
2. Verify SSL certificate
3. Ensure WebSocket support is enabled

---

## Security

- Basic auth required for access
- SSL enforced via Nginx proxy
- Credentials encrypted at rest
- Execution data pruned after 7 days

---

## Related Documentation

- [Multi-Agent RAG Orchestrator Constitution](../../../ml-Agentic/0.spec/0.constitution_v4.2.md)
- [Full Specification](../../../ml-Agentic/0.spec/01-spec_v4.2.md)
- [Architecture](../../../ml-Agentic/0.spec/ARCHITECTURE.md)
- [Oracle VPS README](../README.md)

---

**Last Updated**: 2025-11-26
