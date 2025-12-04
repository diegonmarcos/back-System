# Oracle ARM Server

## Overview
| Property | Value |
|----------|-------|
| **ID** | oracle-arm-server |
| **Provider** | Oracle Cloud |
| **Instance Type** | VM.Standard.A1.Flex |
| **Status** | HOLD (Pending) |

## Specs
| Resource | Value |
|----------|-------|
| **CPU** | 4 OCPU (ARM64 Ampere) |
| **RAM** | 24 GB |
| **Storage** | 200 GB |

## Network
| Property | Value |
|----------|-------|
| **Public IP** | pending |
| **Private IP** | pending |
| **Region** | eu-marseille-1 |

## OS
| Property | Value |
|----------|-------|
| **Name** | Ubuntu |
| **Version** | 24.04 LTS |

## SSH Access
```bash
ssh -i ~/.ssh/arm_key ubuntu@<pending>
```

## OCI Instance ID
```
pending
```

## Services Planned
| Service | Port | Status |
|---------|------|--------|
| n8n-ai-app | 5678 | HOLD |
| n8n-ai-db | - | HOLD |
| npm-oracle-arm | 81 | HOLD |

## Ports
**External:** 22, 80, 443, 81
**Internal:** 5678

## Resource Usage
| Resource | Min | Max |
|----------|-----|-----|
| RAM | 6 GB | 24 GB |
| Storage | 5 GB | 20 GB |
| Bandwidth | 10 GB/mo | 40 GB/mo |

## Notes
n8n-server (AI Agentic) - Waiting for Oracle ARM availability
