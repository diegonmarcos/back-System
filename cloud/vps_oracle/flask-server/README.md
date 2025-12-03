# Cloud Dashboard Flask Server

REST API backend and web dashboard for Cloud Infrastructure monitoring.

**Live**: https://dashboard.diegonmarcos.com/

## Features

- **Web Dashboard**: Live HTML dashboard with auto-refresh (60s)
- **VM Status**: Check ping, SSH connectivity, RAM usage
- **Service Health**: HTTP endpoint checks
- **Container Status**: Docker container info via SSH
- **Configuration**: Load/reload infrastructure config

## Web Routes

| Route | Description |
|-------|-------------|
| `GET /` | Live HTML dashboard |
| `GET /dashboard` | Same as above |

## API Endpoints

### Health
- `GET /api/health` - API health check

### Configuration
- `GET /api/config` - Full infrastructure configuration
- `POST /api/config/reload` - Reload config from disk

### VMs
- `GET /api/vms` - List all VMs
- `GET /api/vms?category=services` - List VMs by category
- `GET /api/vms/categories` - List VM categories
- `GET /api/vms/<vm_id>` - Get VM details
- `GET /api/vms/<vm_id>/status` - Get VM health (ping, SSH, RAM)
- `GET /api/vms/<vm_id>/details` - Get remote system info
- `GET /api/vms/<vm_id>/containers` - Get Docker containers

### Services
- `GET /api/services` - List all services
- `GET /api/services?category=products` - List services by category
- `GET /api/services/categories` - List service categories
- `GET /api/services/<svc_id>` - Get service details
- `GET /api/services/<svc_id>/status` - Get service health

### Dashboard
- `GET /api/dashboard/summary` - Full status summary (slow)
- `GET /api/dashboard/quick-status` - Config-only status (fast)

### Other
- `GET /api/providers` - List cloud providers
- `GET /api/domains` - List domains

## Local Development

```bash
# Create virtual environment
python3 -m venv venv
source venv/bin/activate

# Install dependencies
pip install -r requirements.txt

# Set config path
export CLOUD_CONFIG_PATH=/path/to/cloud-infrastructure.json

# Run development server
python run.py
```

## Docker Deployment

```bash
# Build and run
docker compose up -d

# View logs
docker compose logs -f

# Stop
docker compose down
```

## Configuration

The server reads from `cloud-infrastructure.json`. Set the path via:
- Environment variable: `CLOUD_CONFIG_PATH`
- Default: `/app/cloud-infrastructure.json` (in container)

## Requirements

- Python 3.10+
- SSH access to VMs (for status checks)
- `curl`, `ping` commands available
