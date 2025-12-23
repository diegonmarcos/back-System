# Cloud Infrastructure Costs

> **Source**: `cloud_control.html`
> **Generated**: 2025-12-23

---

## Cost Summary

| Metric | Value |
|--------|-------|
| Total Cloud Spend (All Time) | €0.83 |
| This Month (Dec 2025) | €0.83 |
| Projected (Full Month) | €3.22 |
| Year to Date (2025) | €0.83 |
| Savings vs Market | €44.17 (98%) |

---

## Provider Cost Distribution

| Provider | Cost | Percentage |
|----------|------|------------|
| Oracle Cloud (OCI) | €0.83 | 100% |
| Google Cloud (GCP) | €0.00 | 0% |

---

## Resource Usage by VM

### OCI Paid Flex 1 (1 OCPU, 8 GB RAM, 242 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 15% | 45% | 68% |
| photoprism | 5% | 15% | 21% |
| radicale | <1% | 1% | <1% |
| cloud-api | 1% | 2% | <1% |
| openvpn | <1% | <1% | <1% |
| redis | 1% | <1% | <1% |

### OCI Free Micro 1 (1 OCPU, 1 GB RAM, 47 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 5% | 60% | 27% |
| mailu-front | 1% | 8% | 2% |
| mailu-admin | 1% | 12% | 1% |
| mailu-imap | 2% | 20% | 15% |
| mailu-smtp | 1% | 10% | 5% |
| mailu-webmail | <1% | 10% | 4% |

### OCI Free Micro 2 (1 OCPU, 1 GB RAM, 47 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 10% | 55% | 20% |
| matomo-app | 5% | 25% | 5% |
| matomo-db | 5% | 30% | 15% |

### GCP Free Micro 1 (0.25 vCPU, 1 GB RAM, 30 GB)

| Name | CPU | RAM | Storage |
|------|-----|-----|---------|
| **VM Total** | 20% | 70% | 35% |
| npm | 8% | 25% | 10% |
| authelia | 3% | 15% | 5% |
| authelia-redis | 1% | 10% | 3% |
| wireguard | 5% | 10% | 1% |
| oauth2-proxy | 3% | 10% | 1% |

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

### Savings Calculation

| Metric | Value |
|--------|-------|
| Monthly Savings | €44.17 |
| Percentage Saved | 98% |
| Annual Savings | €530 |

---

## Infrastructure Costs Breakdown

| Provider | VM | Tier | Cost |
|----------|-----|------|------|
| Oracle | oci-p-flex_1 | Paid (Flex) | €5.50/mo |
| Oracle | oci-f-micro_1 | Always Free | €0/mo |
| Oracle | oci-f-micro_2 | Always Free | €0/mo |
| Google | gcp-f-micro_1 | Free Tier | €0/mo |
| Cloudflare | DNS | Free | €0/mo |
| GitHub Pages | Hosting | Free | €0/mo |

---

## Cost Notes

- **OCI Paid Flex 1**: Only paid VM, used for PhotoPrism and high-memory workloads
- **Wake-on-Demand**: Flex VM sleeps when idle, reducing active hours and cost
- **Free Tier Optimization**: Maximizing free tier usage across both providers
- **No egress charges**: Staying within free tier limits for network traffic

