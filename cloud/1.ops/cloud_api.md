# Cloud Infrastructure API Reference

> **Version**: 1.0.0
> **Generated**: 2025-12-23 16:44
> **Source**: `cloud_api.json`

This document is auto-generated from `cloud_api.json` using `cloud_json_md.py`.
Do not edit manually - changes will be overwritten.

---


## API Overview

**Title**: Cloud Infrastructure API

**Version**: 1.0.0

**Description**: REST API endpoints for cloud_architecture.json and cloud_control.json data. Equivalent to cloud_json_md.py but for web/programmatic access.


### Servers

| Environment | Base URL                     | Description                         |
| ----------- | ---------------------------- | ----------------------------------- |
| production  | https://api.diegonmarcos.com | Production API via NPM proxy        |
| internal    | http://127.0.0.1:5000        | Direct Flask access (internal only) |
| dev         | http://localhost:5000        | Local development                   |

### Authentication

**Type**: bearer

**Provider**: authelia

**Token Endpoint**: `https://auth.diegonmarcos.com/api/oidc/token`


### Auth Scopes

| Scope | Description                               |
| ----- | ----------------------------------------- |
| read  | Read-only access to all data              |
| write | Modify runtime status and trigger actions |
| admin | Full access including VM control          |

## Endpoints Summary

| Category     | Description                                                             | Endpoints |
| ------------ | ----------------------------------------------------------------------- | --------- |
| health       | API health and status checks                                            | 2         |
| architecture | Access cloud_architecture.json data (static infrastructure definitions) | 8         |
| vms          | Virtual machine operations                                              | 6         |
| services     | Service and container operations                                        | 6         |
| domains      | Domain and SSL operations                                               | 4         |
| topology     | Infrastructure topology data (for cloud_control_topology.md)            | 8         |
| cost         | Cost and billing data (for cloud_control_cost.md)                       | 6         |
| monitor      | Runtime monitoring data (for cloud_control_monitor.md)                  | 12        |
| actions      | Administrative actions                                                  | 3         |
| index        | API discovery and metadata                                              | 3         |


**Total Endpoints**: 46

## Endpoints Detail

### HEALTH

*API health and status checks*


| Method | Path            | Auth | Description                             |
| ------ | --------------- | ---- | --------------------------------------- |
| `GET`  | `/health`       | none | Simple health check                     |
| `GET`  | `/health/ready` | none | Readiness check (DB, cache connections) |

### ARCHITECTURE

*Access cloud_architecture.json data (static infrastructure definitions)*

**Source**: `cloud_architecture.json`


| Method | Path                           | Auth | Description                           |
| ------ | ------------------------------ | ---- | ------------------------------------- |
| `GET`  | `/architecture`                | read | Get complete architecture.json        |
| `GET`  | `/architecture/overview`       | read | Get partI_overview section            |
| `GET`  | `/architecture/infrastructure` | read | Get partII_infrastructure section     |
| `GET`  | `/architecture/security`       | read | Get partIII_security section          |
| `GET`  | `/architecture/data`           | read | Get partIV_data section               |
| `GET`  | `/architecture/operations`     | read | Get partV_operations section          |
| `GET`  | `/architecture/reference`      | read | Get partVI_reference section          |
| `GET`  | `/architecture/version`        | none | Get architecture version and metadata |

### VMS

*Virtual machine operations*

**Source**: `cloud_architecture.partII_infrastructure.virtualMachines + cloud_control.monitor.vmStatus`


| Method | Path                 | Auth  | Description                              |
| ------ | -------------------- | ----- | ---------------------------------------- |
| `GET`  | `/vms`               | read  | List all virtual machines                |
| `GET`  | `/vms/{vmId}`        | read  | Get single VM details                    |
| `GET`  | `/vms/{vmId}/status` | read  | Get live VM status (runtime data)        |
| `POST` | `/vms/{vmId}/start`  | admin | Start a stopped VM (wake-on-demand only) |
| `POST` | `/vms/{vmId}/stop`   | admin | Stop a running VM (wake-on-demand only)  |
| `GET`  | `/vms/{vmId}/ssh`    | read  | Get SSH connection command for VM        |

### SERVICES

*Service and container operations*

**Source**: `cloud_architecture.partII_infrastructure.services + cloud_control.topology.containers`


| Method | Path                               | Auth  | Description                            |
| ------ | ---------------------------------- | ----- | -------------------------------------- |
| `GET`  | `/services`                        | read  | List all services                      |
| `GET`  | `/services/{serviceId}`            | read  | Get single service details             |
| `GET`  | `/services/{serviceId}/health`     | read  | Check service health                   |
| `GET`  | `/services/{serviceId}/containers` | read  | List containers for a service          |
| `POST` | `/services/{serviceId}/restart`    | admin | Restart all containers for a service   |
| `GET`  | `/services/{serviceId}/logs`       | read  | Get recent logs for service containers |

### DOMAINS

*Domain and SSL operations*

**Source**: `cloud_architecture.partIII_security.domains + cloud_control.monitor.endpointStatus`


| Method | Path                       | Auth | Description                            |
| ------ | -------------------------- | ---- | -------------------------------------- |
| `GET`  | `/domains`                 | read | List all domains and subdomains        |
| `GET`  | `/domains/{domain}`        | read | Get domain configuration               |
| `GET`  | `/domains/{domain}/status` | read | Check domain DNS, SSL, and HTTP status |
| `GET`  | `/domains/{domain}/ssl`    | read | Get SSL certificate details            |

### TOPOLOGY

*Infrastructure topology data (for cloud_control_topology.md)*

**Source**: `cloud_control.topology`


| Method | Path                       | Auth | Description                                     |
| ------ | -------------------------- | ---- | ----------------------------------------------- |
| `GET`  | `/topology`                | read | Get complete topology data                      |
| `GET`  | `/topology/vms`            | read | Get VM topology table                           |
| `GET`  | `/topology/services-by-vm` | read | Get services grouped by VM                      |
| `GET`  | `/topology/service-types`  | read | Get services grouped by type (A120, A121, etc.) |
| `GET`  | `/topology/containers`     | read | Get all containers by VM                        |
| `GET`  | `/topology/databases`      | read | Get database allocations by VM                  |
| `GET`  | `/topology/networks`       | read | Get Docker networks                             |
| `GET`  | `/topology/summaries`      | read | Get storage and container summaries             |

### COST

*Cost and billing data (for cloud_control_cost.md)*

**Source**: `cloud_control.cost`


| Method | Path                   | Auth | Description                                   |
| ------ | ---------------------- | ---- | --------------------------------------------- |
| `GET`  | `/cost`                | read | Get complete cost data                        |
| `GET`  | `/cost/summary`        | read | Get cost summary (this month, projected, YTD) |
| `GET`  | `/cost/breakdown`      | read | Get cost breakdown by provider/VM             |
| `GET`  | `/cost/free-tier`      | read | Get free tier utilization                     |
| `GET`  | `/cost/resource-usage` | read | Get resource usage by VM                      |
| `GET`  | `/cost/comparison`     | read | Get market price comparison                   |

### MONITOR

*Runtime monitoring data (for cloud_control_monitor.md)*

**Source**: `cloud_control.monitor`


| Method | Path                         | Auth  | Description                                                  |
| ------ | ---------------------------- | ----- | ------------------------------------------------------------ |
| `GET`  | `/monitor`                   | read  | Get complete monitoring data                                 |
| `GET`  | `/monitor/summary`           | read  | Get monitoring summary (VMs online, endpoints healthy, etc.) |
| `GET`  | `/monitor/vms`               | read  | Get VM overview with resource usage                          |
| `GET`  | `/monitor/vm-status`         | read  | Get live VM status (ping, SSH, latency)                      |
| `GET`  | `/monitor/endpoints`         | read  | Get endpoint status (HTTP, SSL)                              |
| `GET`  | `/monitor/containers`        | read  | Get container status by VM                                   |
| `GET`  | `/monitor/service-breakdown` | read  | Get service resource breakdown by VM                         |
| `GET`  | `/monitor/audit`             | read  | Get recent audit events                                      |
| `GET`  | `/monitor/audit/metrics`     | read  | Get audit metrics (total events, success rate, blocked)      |
| `GET`  | `/monitor/alerts`            | read  | Get active alerts                                            |
| `GET`  | `/monitor/orchestrate`       | read  | Get Dockge instances for container management                |
| `POST` | `/monitor/refresh`           | admin | Trigger a full status refresh                                |

### ACTIONS

*Administrative actions*


| Method | Path                   | Auth  | Description                                              |
| ------ | ---------------------- | ----- | -------------------------------------------------------- |
| `POST` | `/actions/refresh-all` | admin | Refresh all monitoring data (VMs, endpoints, containers) |
| `POST` | `/actions/generate-md` | admin | Regenerate cloud_control_*.md files from JSON            |
| `POST` | `/actions/backup`      | admin | Backup architecture and control JSON files               |

### INDEX

*API discovery and metadata*


| Method | Path          | Auth | Description                                      |
| ------ | ------------- | ---- | ------------------------------------------------ |
| `GET`  | `/`           | none | API root - returns available endpoints           |
| `GET`  | `/api/docs`   | none | Get this API specification                       |
| `GET`  | `/api/schema` | none | Get JSON schemas for request/response validation |

## Curl Examples

### health

| Endpoint | Curl Command                               |
| -------- | ------------------------------------------ |
| ping     | `curl https://api.diegonmarcos.com/health` |

### architecture

| Endpoint | Curl Command                                                                       |
| -------- | ---------------------------------------------------------------------------------- |
| full     | `curl -H 'Authorization: Bearer $TOKEN' https://api.diegonmarcos.com/architecture` |

### vms

| Endpoint | Curl Command                                                                                         |
| -------- | ---------------------------------------------------------------------------------------------------- |
| list     | `curl -H 'Authorization: Bearer $TOKEN' https://api.diegonmarcos.com/vms`                            |
| get      | `curl -H 'Authorization: Bearer $TOKEN' https://api.diegonmarcos.com/vms/oci-p-flex_1`               |
| start    | `curl -X POST -H 'Authorization: Bearer $TOKEN' https://api.diegonmarcos.com/vms/oci-p-flex_1/start` |

## Schemas

### VirtualMachine

| Property     | Type                       | Required | Description |
| ------------ | -------------------------- | -------- | ----------- |
| id           | string                     | Yes      |             |
| name         | string                     | Yes      |             |
| displayName  | string                     | No       |             |
| provider     | enum: oracle, gcloud       | Yes      |             |
| category     | enum: services, ml         | No       |             |
| instanceType | string                     | No       |             |
| specs        | object                     | No       |             |
| network      | object                     | Yes      |             |
| availability | enum: 24/7, wake-on-demand | No       |             |
| cost         | object                     | No       |             |

### Service

| Property     | Type    | Required | Description |
| ------------ | ------- | -------- | ----------- |
| id           | string  | Yes      |             |
| displayName  | string  | Yes      |             |
| category     | string  | Yes      |             |
| vmId         | string  | Yes      |             |
| containers   | array   | No       |             |
| technology   | object  | No       |             |
| urls         | object  | No       |             |
| authRequired | boolean | No       |             |
| resources    | object  | No       |             |

### Domain

| Property | Type                         | Required | Description |
| -------- | ---------------------------- | -------- | ----------- |
| service  | string                       | Yes      |             |
| vmId     | string                       | No       |             |
| proxyVia | string                       | No       |             |
| ssl      | boolean                      | Yes      |             |
| auth     | enum: none, authelia, native | No       |             |

### VmStatus

| Property  | Type    | Required | Description |
| --------- | ------- | -------- | ----------- |
| ip        | string  | No       |             |
| pingable  | boolean | No       |             |
| sshable   | boolean | No       |             |
| latencyMs | integer | No       |             |
| lastCheck | string  | No       |             |

### EndpointStatus

| Property     | Type    | Required | Description |
| ------------ | ------- | -------- | ----------- |
| url          | string  | No       |             |
| httpCode     | integer | No       |             |
| sslValid     | boolean | No       |             |
| sslExpiry    | string  | No       |             |
| wakeOnDemand | boolean | No       |             |

### ApiError

| Property | Type   | Required | Description |
| -------- | ------ | -------- | ----------- |
| error    | string | No       |             |
| code     | string | No       |             |
| message  | string | No       |             |
| details  | object | No       |             |

## Error Codes

| HTTP Code | Error Code          | Message                                            |
| --------- | ------------------- | -------------------------------------------------- |
| 400       | BAD_REQUEST         | Invalid request parameters                         |
| 401       | UNAUTHORIZED        | Missing or invalid authentication token            |
| 403       | FORBIDDEN           | Insufficient permissions for this action           |
| 404       | NOT_FOUND           | Resource not found                                 |
| 409       | CONFLICT            | Resource state conflict (e.g., VM already running) |
| 429       | RATE_LIMITED        | Too many requests, please slow down                |
| 500       | INTERNAL_ERROR      | Internal server error                              |
| 502       | UPSTREAM_ERROR      | Cloud provider API error                           |
| 503       | SERVICE_UNAVAILABLE | Service temporarily unavailable                    |

### Rate Limits

| Category | Requests | Window |
| -------- | -------- | ------ |
| default  | 100      | 1m     |
| auth     | 10       | 1m     |
| actions  | 5        | 1m     |

## Data Sources Mapping

### cloud_architecture.json

- `architecture.*`

- `vms.list`

- `vms.get`

- `services.list`

- `services.get`

- `domains.list`

- `domains.get`


### cloud_control.json

- `topology.*`

- `cost.*`

- `monitor.*`

