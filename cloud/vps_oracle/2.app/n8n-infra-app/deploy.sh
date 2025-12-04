#!/bin/bash

# n8n Deployment Script for Oracle VPS
# Usage: ./deploy.sh [password]

set -e

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== n8n Deployment for Oracle VPS ===${NC}"

# Configuration
N8N_DIR=~/n8n
N8N_PASSWORD="${1:-$(openssl rand -base64 12)}"
N8N_USER="admin"

# Check if running on the VPS
if [[ ! -f /etc/os-release ]]; then
    echo -e "${RED}Error: This script should be run on the VPS${NC}"
    exit 1
fi

# Create directory structure
echo -e "${YELLOW}Creating directories...${NC}"
mkdir -p $N8N_DIR/workflows
cd $N8N_DIR

# Create docker-compose.yml
echo -e "${YELLOW}Creating docker-compose.yml...${NC}"
cat > docker-compose.yml << 'EOF'
version: '3.8'

services:
  n8n:
    image: n8nio/n8n:latest
    container_name: n8n
    restart: unless-stopped
    ports:
      - "5678:5678"
    environment:
      - N8N_BASIC_AUTH_ACTIVE=true
      - N8N_BASIC_AUTH_USER=${N8N_USER:-admin}
      - N8N_BASIC_AUTH_PASSWORD=${N8N_PASSWORD:-changeme}
      - DB_TYPE=sqlite
      - DB_SQLITE_DATABASE=/home/node/.n8n/database.sqlite
      - WEBHOOK_URL=https://n8n.diegonmarcos.com/
      - N8N_HOST=n8n.diegonmarcos.com
      - N8N_PROTOCOL=https
      - EXECUTIONS_PROCESS=main
      - EXECUTIONS_MODE=regular
      - EXECUTIONS_DATA_PRUNE=true
      - EXECUTIONS_DATA_MAX_AGE=168
      - GENERIC_TIMEZONE=Europe/Paris
      - TZ=Europe/Paris
      - N8N_SECURE_COOKIE=true
      - NODE_OPTIONS=--max-old-space-size=256
    volumes:
      - n8n_data:/home/node/.n8n
      - ./workflows:/home/node/workflows
    networks:
      - orchestrator
    deploy:
      resources:
        limits:
          memory: 300M
        reservations:
          memory: 150M
    healthcheck:
      test: ["CMD", "wget", "--spider", "-q", "http://localhost:5678/healthz"]
      interval: 30s
      timeout: 10s
      retries: 3
      start_period: 30s

volumes:
  n8n_data:
    name: n8n_data

networks:
  orchestrator:
    name: orchestrator
    driver: bridge
EOF

# Create .env file
echo -e "${YELLOW}Creating .env file...${NC}"
cat > .env << EOF
N8N_USER=${N8N_USER}
N8N_PASSWORD=${N8N_PASSWORD}
EOF

# Pull and start n8n
echo -e "${YELLOW}Pulling n8n image...${NC}"
docker compose pull

echo -e "${YELLOW}Starting n8n...${NC}"
docker compose up -d

# Wait for startup
echo -e "${YELLOW}Waiting for n8n to start...${NC}"
sleep 10

# Check status
if docker compose ps | grep -q "Up"; then
    echo -e "${GREEN}=== n8n Deployment Successful ===${NC}"
    echo ""
    echo -e "Access URLs:"
    echo -e "  Direct: ${GREEN}http://130.110.251.193:5678${NC}"
    echo -e "  Proxy:  ${GREEN}https://n8n.diegonmarcos.com${NC} (after Nginx setup)"
    echo ""
    echo -e "Credentials:"
    echo -e "  Username: ${GREEN}${N8N_USER}${NC}"
    echo -e "  Password: ${GREEN}${N8N_PASSWORD}${NC}"
    echo ""
    echo -e "${YELLOW}IMPORTANT: Save these credentials!${NC}"
    echo ""
    echo -e "Next steps:"
    echo -e "  1. Add DNS A record: n8n.diegonmarcos.com -> 130.110.251.193"
    echo -e "  2. Add proxy host in Nginx Proxy Manager (port 81)"
    echo -e "  3. Import workflows from ~/ml-Agentic/workflows/"
else
    echo -e "${RED}=== Deployment Failed ===${NC}"
    docker compose logs
    exit 1
fi
