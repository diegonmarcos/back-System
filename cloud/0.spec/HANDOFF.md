# Cloud Infrastructure Handoff

> **For Web Designer**: This document provides the visual structure and relationships.
> **For Data**: See the CSV files for IPs, ports, commands, and service details.

---

## Quick Reference

| File | Purpose | Update By |
|------|---------|-----------|
| `infrastructure.csv` | VMs: IPs, regions, status | Cloud Engineer |
| `services.csv` | Services: ports, domains, categories | Cloud Engineer |
| `ports.csv` | Firewall rules, port mappings | Cloud Engineer |
| `commands.csv` | SSH, CLI commands | Cloud Engineer |
| `HANDOFF.md` | Architecture diagrams | Cloud Engineer |

---

## 1. High-Level Architecture

```mermaid
graph TB
    subgraph Internet
        USER[User Browser]
    end

    subgraph Oracle Cloud
        subgraph web-server-1 [web-server-1<br/>130.110.251.193]
            NPM1[Nginx Proxy Manager]
            MATOMO[Matomo Analytics]
            SYNC[Syncthing]
        end

        subgraph services-server-1 [services-server-1<br/>129.151.228.66]
            NPM2[Nginx Proxy Manager]
            N8N[n8n Automation]
        end

        subgraph arm-server [arm-server<br/>pending]
            FUTURE[Future Services]
        end
    end

    subgraph Google Cloud
        subgraph arch-1 [arch-1<br/>pending]
            DEV[Development]
        end
    end

    USER -->|HTTPS| NPM1
    USER -->|HTTPS| NPM2
    NPM1 --> MATOMO
    NPM1 --> SYNC
    NPM2 --> N8N
```

---

## 2. Network Topology

```mermaid
graph LR
    subgraph Public Internet
        DNS[DNS<br/>diegonmarcos.com]
    end

    subgraph Domains
        A1[analytics.diegonmarcos.com]
        A2[sync.diegonmarcos.com]
        A3[n8n.diegonmarcos.com]
    end

    subgraph web-server-1
        W_NPM[NPM :81]
        W_443[HTTPS :443]
        W_MATOMO[:8080]
        W_SYNC[:8384]
    end

    subgraph services-server-1
        S_NPM[NPM :81]
        S_443[HTTPS :443]
        S_N8N[:5678]
    end

    DNS --> A1 & A2 & A3
    A1 --> W_443 --> W_MATOMO
    A2 --> W_443 --> W_SYNC
    A3 --> S_443 --> S_N8N
```

---

## 3. Service Categories

```mermaid
graph TB
    subgraph Active Services
        S1[Matomo Analytics<br/>analytics.diegonmarcos.com]
        S2[Syncthing<br/>sync.diegonmarcos.com]
        S3[n8n Automation<br/>n8n.diegonmarcos.com]
    end

    subgraph VPS Providers
        V1[Oracle Cloud<br/>cloud.oracle.com]
        V2[Google Cloud<br/>console.cloud.google.com]
    end

    subgraph Virtual Machines
        VM1[web-server-1<br/>130.110.251.193]
        VM2[services-server-1<br/>129.151.228.66]
        VM3[arch-1<br/>pending]
    end

    subgraph Under Development
        D1[Mail Server]
        D2[OS Terminal]
        D3[DevOps Dashboard]
    end

    V1 --> VM1 & VM2
    V2 --> VM3
    VM1 --> S1 & S2
    VM2 --> S3
```

---

## 4. Dashboard Card Structure

```mermaid
graph TB
    subgraph Cards Tab
        subgraph Services Section
            C1[Matomo Analytics<br/>Click: Open GUI]
            C2[Syncthing<br/>Click: Open GUI]
            C3[n8n<br/>Click: Open GUI]
        end

        subgraph VPS Section
            C4[Oracle Cloud<br/>Click: Console<br/>Copy: CLI command<br/>Copy: Install CLI]
            C5[Google Cloud<br/>Click: Console<br/>Copy: CLI command<br/>Copy: Install CLI]
        end

        subgraph VMs Section
            C6[web-server-1<br/>Click: Proxy GUI<br/>Copy: SSH command<br/>Buttons: Proxy / Firewall]
            C7[services-server-1<br/>Click: Proxy GUI<br/>Copy: SSH command<br/>Buttons: Proxy / Firewall]
            C8[arch-1<br/>Status: Pending]
        end

        subgraph Under Development
            C9[Mail]
            C10[OS Terminal]
            C11[DevOps Dashboard]
        end
    end
```

---

## 5. Port Flow Diagram

```mermaid
flowchart LR
    subgraph External Ports
        E22[SSH :22]
        E80[HTTP :80]
        E443[HTTPS :443]
        E81[NPM :81]
        E22000[Sync :22000]
    end

    subgraph Internal Ports
        I8080[:8080 Matomo]
        I8384[:8384 Syncthing]
        I5678[:5678 n8n]
    end

    E22 -->|Direct| SSH[Host SSH]
    E80 -->|Redirect| E443
    E443 -->|Proxy| I8080 & I8384 & I5678
    E81 -->|Admin| NPM[Proxy Manager]
    E22000 -->|Direct| SYNC[Syncthing Protocol]
```

---

## 6. Access Methods

| Access Type | Method | Example |
|-------------|--------|---------|
| Service GUI | HTTPS via domain | `https://analytics.diegonmarcos.com` |
| Proxy Admin | HTTP via IP:81 | `http://130.110.251.193:81` |
| SSH Access | SSH via IP:22 | `ssh -i ~/.ssh/key ubuntu@IP` |
| Firewall | Cloud Console | Oracle Security Lists |
| CLI | Terminal command | `oci compute instance list` |

---

## Changelog

| Date | Change | By |
|------|--------|-----|
| 2025-11-27 | Initial handoff structure | Cloud Engineer |

