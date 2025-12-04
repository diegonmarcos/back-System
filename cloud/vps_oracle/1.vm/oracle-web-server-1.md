# Oracle Web Server 1

## Overview
| Property | Value |
|----------|-------|
| **ID** | oracle-web-server-1 |
| **Provider** | Oracle Cloud |
| **Instance Type** | VM.Standard.E2.1.Micro |
| **Status** | Active |

## Specs
| Resource | Value |
|----------|-------|
| **CPU** | 1 OCPU (AMD) |
| **RAM** | 1 GB |
| **Storage** | 47 GB Boot |

## Network
| Property | Value |
|----------|-------|
| **Public IP** | 130.110.251.193 |
| **Private IP** | 10.0.0.x |
| **Region** | eu-marseille-1 |

## OS
| Property | Value |
|----------|-------|
| **Name** | Ubuntu |
| **Version** | 24.04 LTS |

## SSH Access
```bash
ssh ubuntu@130.110.251.193
```

## OCI Instance ID
```
ocid1.instance.oc1.eu-marseille-1.anwxeljruadvczacbwylmkqr253ay7binepapgsyopllfayovkzaky6oigbq
```

## Services Running
| Service | Port | Status |
|---------|------|--------|
| n8n-infra-app | 5678 | ON |
| sync-app | 8384 | ON |
| cloud-app | - | ON |
| cloud-api | 5000 | ON |
| npm-oracle-web | 81 | ON |
| vpn-app | 1194 | DEV |
| git-app | 3000 | DEV |
| cache-app | 6379 | DEV |

## Ports
**External:** 22, 80, 443, 81, 22000, 21027, 1194, 2222
**Internal:** 5678, 8384, 5000, 3000

## Resource Usage
| Resource | Min | Max |
|----------|-----|-----|
| RAM | 800 MB | 1.5 GB |
| Storage | 5 GB | 15 GB |
| Bandwidth | 20 GB/mo | 80 GB/mo |

## Notes
n8n-server (Infra) + Syncthing + Flask-server (Cloud_Dashboard) + VPN + Git-Server
