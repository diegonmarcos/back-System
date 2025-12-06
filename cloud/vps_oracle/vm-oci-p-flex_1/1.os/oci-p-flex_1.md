# oci-p-flex_1

## Overview
| Property | Value |
|----------|-------|
| **ID** | oci-p-flex_1 |
| **Name** | OCI Paid Flex 1 |
| **Provider** | Oracle Cloud |
| **Instance Type** | VM.Standard.E4.Flex |
| **Status** | Wake-on-Demand |
| **Availability** | PAID (~$5.50/mo) |

## Specs
| Resource | Value |
|----------|-------|
| **CPU** | 1 OCPU (2 vCPU AMD) |
| **RAM** | 8 GB |
| **Storage** | 100 GB Boot |

## Network
| Property | Value |
|----------|-------|
| **Public IP** | 84.235.234.87 |
| **Private IP** | 10.0.0.x |
| **Region** | eu-marseille-1 |
| **Docker Network** | dev_network (172.24.0.0/24) |

## OS
| Property | Value |
|----------|-------|
| **Name** | Ubuntu |
| **Version** | 22.04 LTS |

## SSH Access
```bash
ssh ubuntu@84.235.234.87
```

## Services Running
| Service | Port | Status |
|---------|------|--------|
| n8n-infra-app | 5678 | ON |
| sync-app | 8384 | ON |
| cloud-app | 80 | ON |
| flask-app | 5000 | DEV |
| git-app | 3000 | DEV |
| vpn-app | 1194 | DEV |
| terminal-app | 7681 | DEV |
| cache-app | 6379 | DEV |

## Databases
| Database | Port | Status |
|----------|------|--------|
| cloud-db | 5432 | DEV |
| git-db | 5432 | DEV |

## Ports
**External:** 22, 80, 443, 22000, 21027, 1194, 2222
**Internal:** 5678, 8384, 5000, 3000, 7681, 6379, 5432

## Resource Usage
| Resource | Min | Max |
|----------|-----|-----|
| RAM | 2 GB | 6 GB |
| Storage | 10 GB | 50 GB |

## Wake-on-Demand Architecture
This VM is **NOT always-on** to save costs:
- Stays **dormant** by default
- Only started when services are needed
- Reduces monthly cost from ~$50+ to ~$5.50/mo
- Heavy services (n8n, sync, git, cloud) run here instead of free-tier VMs

## Notes
Wake-on-Demand development server for heavy workloads: n8n (Infra) + Syncthing + Cloud Dashboard + Git + VPN + Terminal + Cache
