# Cloud Control Monitor

> **Source**: `cloud_control.html`
> **Generated**: 2025-12-23
> **Dashboard**: https://cloud.diegonmarcos.com/cloud_control.html

---

## VM Overview

| VM | CPU | RAM | Storage | VRAM | Status |
|----|-----|-----|---------|------|--------|
| OCI Paid Flex 1 | 2 vCPU | 3.6 / 8 GB | 165 / 242 GB | - | Active |
| OCI Free Micro 1 | 1 OCPU | 0.6 / 1 GB | 13 / 47 GB | - | Active |
| OCI Free Micro 2 | 1 OCPU | 0.55 / 1 GB | 9 / 47 GB | - | Active |
| GCP Free Micro 1 | 0.25 vCPU | 0.7 / 1 GB | 6 / 30 GB | - | Active |

---

## Service Breakdown by VM

### OCI Paid Flex 1 (2 vCPU, 8 GB RAM, 242 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 15% | 45% | 68% |
| ↳ photoprism | 5% | 15% | 21% |
| ↳ calendar | <1% | 1% | <1% |
| ↳ radicale | <1% | 1% | <1% |
| ↳ cloud-api | 1% | 2% | <1% |
| ↳ openvpn | <1% | <1% | <1% |
| ↳ redis | 1% | <1% | <1% |

### OCI Free Micro 1 (1 OCPU, 1 GB RAM, 47 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 5% | 60% | 27% |
| ↳ mailu-front | 1% | 8% | 2% |
| ↳ mailu-admin | 1% | 12% | 1% |
| ↳ mailu-imap | 2% | 20% | 15% |
| ↳ mailu-smtp | 1% | 10% | 5% |
| ↳ mailu-webmail | <1% | 10% | 4% |

### OCI Free Micro 2 (1 OCPU, 1 GB RAM, 47 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 10% | 55% | 20% |
| ↳ matomo-app | 5% | 25% | 5% |
| ↳ matomo-db | 5% | 30% | 15% |

### GCP Free Micro 1 (0.25 vCPU, 1 GB RAM, 30 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 20% | 70% | 35% |
| ↳ npm | 8% | 25% | 10% |
| ↳ authelia | 3% | 15% | 5% |
| ↳ authelia-redis | 1% | 10% | 3% |
| ↳ wireguard | 5% | 10% | 1% |
| ↳ oauth2-proxy | 3% | 10% | 1% |
| ↳ flask-api | 1% | 10% | 1% |

---

## Audit Analytics

| Service | URL | Status |
|---------|-----|--------|
| Matomo Analytics | https://analytics.diegonmarcos.com | Online |

---

## Audit Logs Metrics

| Metric | Value |
|--------|-------|
| Total Events (24h) | 1,247 |
| Success Rate | 94.2% |
| Blocked Attempts | 47 |
| Warnings | 12 |

### Event Type Distribution

| Type | Percentage |
|------|------------|
| Authentication | 45% |
| System | 25% |
| Network | 20% |
| Security | 10% |

### Status Breakdown

| Status | Count | Percentage |
|--------|-------|------------|
| Success | 1,175 | 94.2% |
| Blocked | 47 | 3.8% |
| Warning | 12 | 1.0% |
| Info | 13 | 1.0% |

### Recent Audit Events

| Timestamp | Event | Source | User/IP | Status |
|-----------|-------|--------|---------|--------|
| 2024-12-22 14:32:18 | SSH Login | arch-1 (GCP) | diego@192.168.1.100 | SUCCESS |
| 2024-12-22 14:28:45 | OAuth2 Token Refresh | auth.diegonmarcos.com | github:diegonmarcos | SUCCESS |
| 2024-12-22 14:15:02 | NPM Proxy Access | proxy.diegonmarcos.com | 185.220.101.45 | ALLOWED |
| 2024-12-22 13:58:33 | Failed SSH Attempt | oci-flex-1 | root@45.155.205.233 | BLOCKED |
| 2024-12-22 13:45:12 | Docker Container Start | arch-1 (GCP) | system | SUCCESS |
| 2024-12-22 13:30:00 | SSL Certificate Renewal | npm-proxy | letsencrypt | SUCCESS |
| 2024-12-22 13:12:44 | Authelia 2FA Verify | auth.diegonmarcos.com | diego@192.168.1.100 | SUCCESS |
| 2024-12-22 12:55:21 | Firewall Rule Update | GCP VPC | terraform | APPLIED |
| 2024-12-22 12:30:08 | Rate Limit Triggered | cloudflare | 91.121.45.78 | WARN |
| 2024-12-22 12:00:00 | System Health Check | monitoring | cron | PASS |

---

## Orchestrate (Docker Management)

| VM | IP | Description | Dockge URL |
|----|-----|-------------|------------|
| OCI Paid Flex 1 | 130.110.251.193 | Main production server | https://dockge.diegonmarcos.com |
| GCP Free Micro 1 | 34.55.55.234 | NPM Proxy & Services | https://dockge-gcp.diegonmarcos.com |

---

## Cloud Infrastructure Costs

### Cost Summary

| Metric | Value |
|--------|-------|
| Total Cloud Spend (All Time) | €0.83 |
| This Month (Dec 2025) | €0.83 |
| Projected (Full Month) | €3.22 |
| Year to Date (2025) | €0.83 |
| Savings vs Market | €44.17 (98%) |

### Provider Cost Distribution

| Provider | Cost | Percentage |
|----------|------|------------|
| Oracle Cloud (OCI) | €0.83 | 100% |
| Google Cloud (GCP) | €0.00 | 0% |

---

## Free Tier Utilization

### Oracle Cloud (OCI) - Always Free Tier

| Resource | Usage | Limit | Notes |
|----------|-------|-------|-------|
| Compute (ARM) | 0% | 4 OCPU + 24 GB | Available |
| Block Storage | 25% | 200 GB | ~94 GB used (2x47 GB free micro) |
| Object Storage | 1% | 20 GB | < 1 GB used |
| VCN Egress | 0% | 10 TB/month | < 1 GB used |

### Google Cloud (GCP) - Free Tier

| Resource | Usage | Limit | Notes |
|----------|-------|-------|-------|
| Compute Engine | 100% | 1 e2-micro | 730 hrs/mo |
| Cloud Storage | 10% | 5 GB | < 1 GB used |
| Cloud DNS | 4% | 25 zones | 1 zone |
| Network Egress | 50% | 1 GB/month | ~0.5 GB used |

---

## Market Comparison

| Provider | Cost | Equivalent Specs |
|----------|------|------------------|
| **Your Cost** | €0.83/mo | OCI + GCP Free Tier |
| AWS Equivalent | €45.00/mo | t3.medium + 50GB EBS |
| Azure Equivalent | €42.00/mo | B2s + 50GB SSD |

**Savings**: €44.17/month (98% cost reduction) = €530/year saved

---

## SSH Commands

| VM | Command |
|----|---------|
| OCI Paid Flex 1 | `ssh -i ~/.ssh/id_rsa ubuntu@130.110.251.193` |
| OCI Free Micro 1 | `ssh -i ~/.ssh/id_rsa ubuntu@129.151.228.66` |
| OCI Free Micro 2 | `ssh -i ~/.ssh/id_rsa ubuntu@84.235.234.87` |
| GCP Free Micro 1 | `gcloud compute ssh arch-1 --zone=us-central1-a` |

---

## Cloud Console Links

| Provider | Console URL |
|----------|-------------|
| Oracle Cloud | https://cloud.oracle.com/compute/instances |
| Google Cloud | https://console.cloud.google.com/compute/instances |
