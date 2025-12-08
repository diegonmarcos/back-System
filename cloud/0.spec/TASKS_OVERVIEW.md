# 0.spec Tasks Overview

**Project:** Cloud Infrastructure Architecture v2
**Location:** `/home/diego/Documents/Git/back-System/cloud/0.spec/`
**Last Updated:** 2025-12-07

---

## Task Organization

### Task0 - Architecture Design ✅ COMPLETE
**Created:** 2025-12-04
**Agent:** Sonnet (Claude Code)
**Status:** Archived

**Deliverables:**
- Architecture v2 design (90% cost reduction)
- Migration plan from old architecture
- Implementation checklist
- Task breakdown for deployment

**Files:**
- `ARCHITECTURE_V2_20251204.md`
- `MIGRATION_PLAN_V2_20251204.md`
- `IMPLEMENTATION_REPORT_V2.md`
- `TASKS_SONNET_V2_20251204.md`
- `CHECKLIST_V2_20251204.md`

**Outcome:** Complete architecture redesign achieving ~$44.50/month savings

---

### Task1 - NPM Deployment & Configuration ✅ COMPLETE (Technical)
**Created:** 2025-12-04
**Agent:** Sonnet (Claude Code)
**Status:** Awaiting user validation → Task1_validation/

**Deliverables:**
- gcp-f-micro_1 VM deployed with NPM
- oci-p-flex_1 created
- 6 strong passwords generated
- NPM proxy hosts configured (5 total)
- Old NPM migrated and cleaned up
- Complete documentation

**Files:**
- `DEPLOYMENT_COMPLETE.md`
- `NPM_MIGRATION.md`
- `NPM_MIGRATION_SUMMARY.md`
- `TASKS_DEPLOYMENT_CLI.md`
- `CHECKLIST_DEPLOYMENT.md`

**Outcome:** NPM infrastructure ready, awaiting DNS + SSL configuration by user

---

### Task1_validation - NPM Validation ⏳ PENDING
**Created:** 2025-12-05
**Status:** Awaiting user actions

**User Actions Required:**
1. Update DNS in Squarespace (n8n, analytics, git, cloud → 34.55.55.234)
2. Change NPM default password
3. Add SSL certificates via NPM web UI
4. Change service default passwords

**Files:**
- `SESSION_REPORT_NPM_CONFIGURATION.md` - Full report for Opus
- `NPM_PROXY_HOSTS_COMPLETE.md` - Configuration reference
- `NPM_MIGRATION_SUMMARY.md` - Migration details
- `VALIDATION_CHECKLIST.md` - Step-by-step validation

**Technical Status:** 100% complete
**User Actions:** 0% complete

---

### Task2 - sync-app.py Development 🚧 READY TO START
**Created:** 2025-12-04
**Agent:** Sonnet (Claude Code)
**Supervisor:** Opus (Architect)
**Approver:** Diego (CEO)
**Status:** Not started

**Objective:** Unified Git & Rclone sync manager

**Features:**
- TUI dashboard for all repos
- CLI for automation
- Flask API for remote control
- Background job management
- Real-time status tracking

**Files:**
- `SYNC_APP_ARCHITECTURE.md` - Full architecture spec
- `TASKS_SYNC_APP.md` - Implementation tasks
- `CHECKLIST_SYNC_APP.md` - Testing checklist

**Target Location:** `/home/diego/Documents/Git/ops-Tooling/1_GitDriveDb/sync-app/`

---

### Task3 - Mail Server (Stalwart + Cloudflare) 🚧 IN PROGRESS
**Created:** 2025-12-05
**Updated:** 2025-12-07
**Agent:** Opus (Claude Code)
**Status:** Cloudflare Email Routing configured, DNS propagating

**Objective:** Self-hosted mail server with Cloudflare Email Routing

**Architecture (Full Design):**

```
                              ┌─────────────────────────────────────────────────┐
                              │              INCOMING EMAIL                      │
                              └─────────────────────────────────────────────────┘
                                                   │
                                                   ▼
                              ┌─────────────────────────────────────────────────┐
                              │         CLOUDFLARE (MX on port 25)              │
                              │  route1/2/3.mx.cloudflare.net                   │
                              └─────────────────────────────────────────────────┘
                                                   │
                                                   ▼
                              ┌─────────────────────────────────────────────────┐
                              │         CLOUDFLARE EMAIL WORKER                 │
                              │  (Processes + forwards to both destinations)    │
                              └─────────────────────────────────────────────────┘
                                         │                    │
                          ┌──────────────┘                    └──────────────┐
                          ▼                                                  ▼
        ┌─────────────────────────────────┐          ┌─────────────────────────────────┐
        │      GMAIL (PRIMARY)            │          │      STALWART (ARCHIVE)         │
        │  me@diegonmarcos.com            │          │      130.110.251.193:587        │
        │  - Daily use                    │          │      - Self-hosted backup       │
        │  - Mobile sync                  │          │      - Full control             │
        │  - Spam filtering               │          │      - IMAP: 993 / JMAP         │
        │  - 15GB storage                 │          │      - Unlimited storage        │
        └─────────────────────────────────┘          └─────────────────────────────────┘
                          │                                                  │
                          ▼                                                  ▼
        ┌─────────────────────────────────┐          ┌─────────────────────────────────┐
        │      OUTGOING via GMAIL         │          │      OUTGOING via STALWART      │
        │  smtp.gmail.com:587             │          │      (optional - via relay)     │
        │  - Good reputation              │          │      Gmail SMTP relay for       │
        │  - DKIM/SPF handled             │          │      deliverability             │
        └─────────────────────────────────┘          └─────────────────────────────────┘


                              ┌─────────────────────────────────────────────────┐
                              │              ACCESS METHODS                      │
                              └─────────────────────────────────────────────────┘

        ┌─────────────────────────────────┐          ┌─────────────────────────────────┐
        │      GMAIL CLIENTS              │          │      STALWART CLIENTS           │
        │  - Gmail Web                    │          │      - Thunderbird              │
        │  - Gmail App (iOS/Android)      │          │      - Any IMAP client          │
        │  - Any IMAP client              │          │      - JMAP clients             │
        └─────────────────────────────────┘          └─────────────────────────────────┘
```

**Phase 1 (Current):** Cloudflare → Gmail only
**Phase 2 (Next):** Cloudflare Worker → Gmail + Stalwart (parallel)
**Phase 3 (Optional):** Stalwart as primary, Gmail as backup

**What's Done:**
- [x] Stalwart mail server deployed on oci-f-micro_1
- [x] Domain `diegonmarcos.com` created in Stalwart
- [x] Admin credentials saved to LOCAL_KEYS/README.md
- [x] Spec files updated (Cloud-spec_.md, Cloud-spec_Tables.md)
- [x] Container running (~120MB RAM)
- [x] DNS migrated to Cloudflare (nameservers updated)
- [x] MX records configured (route1/2/3.mx.cloudflare.net)
- [x] SPF record updated (includes Cloudflare)
- [x] DKIM record added (cf2024-1._domainkey)
- [x] Email Routing enabled
- [x] Routing rule created (me@ → forward)
- [x] Destination address verified

**Pending (Phase 1 - Current):**
- [ ] DNS propagation (~24-48h from nameserver change)
- [ ] Test Gmail receiving (send test email)
- [ ] Verify SPF/DKIM/DMARC pass

**Pending (Phase 2 - Gmail + Stalwart):**
- [ ] Create Stalwart user account (me@diegonmarcos.com)
- [ ] Create Cloudflare Email Worker (forwards to both Gmail + Stalwart)
- [ ] Configure Stalwart SMTP relay (via Gmail for outgoing)
- [ ] Test Stalwart IMAP access
- [ ] Configure Thunderbird client

**Pending (Phase 3 - Optional):**
- [ ] Switch primary to Stalwart
- [ ] Gmail as backup only
- [ ] Full self-hosted email

**Email Worker Code (Phase 2):**
```javascript
// Cloudflare Email Worker - forwards to Gmail + Stalwart
export default {
  async email(message, env, ctx) {
    // Forward to Gmail (primary)
    await message.forward("me@diegonmarcos.com");

    // Forward to Stalwart (archive) via SMTP on port 587
    // Note: Requires Cloudflare Email Workers paid plan for custom SMTP
    // Alternative: Use Gmail auto-forward to Stalwart
  }
}
```

**Alternative (Simpler - Gmail Auto-Forward):**
1. Gmail Settings → Forwarding → Add forwarding address
2. Enter: stalwart@diegonmarcos.com (Stalwart user)
3. Gmail forwards copy to Stalwart automatically

**Cloudflare Configuration:**
- **Zone ID:** ff4335cc9c7de42e580d0dff9a0d70eb
- **Account ID:** e5cb0a0c6f448e54f217de484259f0ae
- **Nameservers:** burt.ns.cloudflare.com, phoenix.ns.cloudflare.com
- **MX Records:** route1/2/3.mx.cloudflare.net (priorities 22/85/97)

**Stalwart Access:**
- **Admin URL:** http://130.110.251.193:8080
- **Username:** admin
- **Password:** KTrgIHpg2y
- **Ports:** 587 (SMTP), 993 (IMAPS), 8080 (Admin)

**Why Cloudflare:**
- Oracle Cloud blocks port 25 inbound
- Cloudflare Email Routing receives on port 25 (free)
- Can forward to any port via Email Workers
- Full DNS control + DNSSEC support

**Files:**
- `vps_oracle/vm-oci-f-micro_1/2.app/mail-app/docker-compose.yml` - Stalwart config
- `LOCAL_KEYS/README.md` - All credentials (Cloudflare, Stalwart, Gmail SMTP)

**Target VM:** oci-f-micro_1 (130.110.251.193)

---

## Project Structure

```
/home/diego/Documents/Git/back-System/cloud/
│
├── 0.spec/                                # SOURCE OF TRUTH (Specifications)
│   ├── Cloud-spec_.md                     # Main specification
│   ├── Cloud-spec_Tables.md               # Architecture reference tables
│   ├── cloud_dash.json                    # Cloud infrastructure config (v4.1.0)
│   ├── cloud_dash.py                      # Cloud dashboard (Python TUI)
│   ├── front-cloud/                       # Dashboard frontend
│   │   └── dist_vanilla/
│   │       └── cloud_dash.html
│   ├── TASKS_OVERVIEW.md                  # This file
│   │
│   ├── Task_archive/                      # ✅ COMPLETED TASKS (Archived)
│   │   ├── Task0/                         # Architecture Design (2025-12-04)
│   │   └── Task1/                         # NPM Deployment & Config (2025-12-05)
│   │
│   ├── Task1_validation/                  # ⏳ AWAITING USER ACTION
│   │
│   └── Task2/                             # 🚧 READY TO START (Sync App)
│       ├── SYNC_APP_ARCHITECTURE.md
│       ├── TASKS_SYNC_APP.md
│       └── CHECKLIST_SYNC_APP.md
│
├── vps_oracle/                            # ORACLE CLOUD VMs
│   │
│   ├── vm-oci-f-micro_1/                  # 24/7 FREE E2.Micro (Mail)
│   │   ├── 1.os/oci-f-micro_1.md
│   │   ├── 2.app/mail-app/
│   │   └── 3.db/mail-db/
│   │
│   ├── vm-oci-f-micro_2/                  # 24/7 FREE E2.Micro (Analytics)
│   │   ├── 1.os/oci-f-micro_2.md
│   │   ├── 2.app/analytics-app/, npm-app/
│   │   └── 3.db/analytics-db/
│   │
│   ├── vm-oci-f-arm_1/                    # HOLD FREE A1.Flex ARM (AI)
│   │   ├── 1.os/oci-f-arm_1.md
│   │   ├── 2.app/n8n-ai-app/
│   │   └── 3.db/n8n-ai-db/
│   │
│   └── vm-oci-p-flex_1/                   # Wake-on-Demand PAID E4.Flex (Dev)
│       ├── 1.os/oci-p-flex_1.md
│       ├── 2.app/n8n-infra-app/, sync-app/, flask-app/, git-app/, vpn-app/, terminal-app/, cache-app/
│       └── 3.db/cloud-db/, git-db/
│
└── vps_gcloud/                            # GOOGLE CLOUD VMs
    │
    └── vm-gcp-f-micro_1/                  # 24/7 FREE e2-micro (NPM Proxy)
        ├── 1.os/gcp-f-micro_1.md
        ├── 2.app/npm-app/, mail-app/, terminal-app/, billing-disabler/
        └── 3.db/mail-db/
```

---

## Infrastructure Status

### Deployed Infrastructure ✅

**gcp-f-micro_1 (NPM Reverse Proxy) - FREE TIER**
- IP: 34.55.55.234
- VM Type: e2-micro (1 vCPU, 1GB RAM, 30GB)
- OS: Fedora Cloud 42
- Services: NPM (ports 80, 443, 81)
- Cost: $0/month
- Availability: 24/7

**oci-p-flex_1 (Wake-on-Demand) - PAID**
- IP: 84.235.234.87
- Shape: VM.Standard.E3.Flex (1 OCPU, 8GB RAM, 100GB)
- OS: Ubuntu 22.04 Minimal
- Services: n8n, Syncthing, Gitea, Redis, Cloud Dashboard, OpenVPN, ttyd
- Cost: $5.50/month
- Availability: Wake-on-demand

**oci-f-micro_1 (Stalwart Mail) - FREE TIER**
- IP: 130.110.251.193
- Services: Stalwart Mail Server (~120MB RAM), RocksDB
- Admin: http://130.110.251.193:8080 (admin/KTrgIHpg2y)
- Ports: 587 (SMTP), 993 (IMAPS), 8080 (Admin)
- Cost: $0/month
- Availability: 24/7
- **Note:** Port 25 blocked by Oracle, requires Cloudflare Email Routing

**oci-f-micro_2 (Analytics) - FREE TIER**
- IP: 129.151.228.66
- Services: Matomo Analytics
- Cost: $0/month
- Availability: 24/7

**Total Monthly Cost:** $5.50 (90% reduction from $50+)

---

### NPM Proxy Configuration ✅

All configured and verified:

1. **n8n.diegonmarcos.com** → 84.235.234.87:5678
2. **sync.diegonmarcos.com** → 84.235.234.87:8384
3. **git.diegonmarcos.com** → 84.235.234.87:3000
4. **analytics.diegonmarcos.com** → 129.151.228.66:8080
5. **cloud.diegonmarcos.com** → 84.235.234.87:5000

**Status:**
- NPM configuration: ✅ Complete
- DNS propagation: ❌ Pending (2/5 domains wrong)
- SSL certificates: ❌ Pending (after DNS)

---

## Quick Reference

### NPM Admin
```bash
# Access NPM
open http://34.55.55.234:81

# Default credentials (CHANGE IMMEDIATELY)
Username: admin@example.com
Password: changeme

# New password (in LOCAL_KEYS/README.md)
Password: Cu$sB^mFIAIIMhNBOGE%z6xH
```

### VM Access
```bash
# gcp-f-micro_1
gcloud compute ssh arch-1 --zone=us-central1-a

# oci-p-flex_1
ssh -i ~/.ssh/id_rsa ubuntu@84.235.234.87

# oci-f-micro_1
ssh -i ~/.ssh/id_rsa ubuntu@130.110.251.193

# oci-f-micro_2
ssh -i ~/.ssh/id_rsa ubuntu@129.151.228.66
```

### Wake Dev Server
```bash
oci compute instance action \
  --instance-id ocid1.instance.oc1.eu-marseille-1.anwxeljruadvczachwpa3qrh7n25vfez3smidz4o7gpmtj4ga4d7zqlja5yq \
  --action START
```

---

## Next Steps

### Immediate - Mail Server (Task3)
1. ~~**Migrate DNS to Cloudflare**~~ ✅ DONE
   - ~~Create Cloudflare account (free)~~
   - ~~Add diegonmarcos.com zone~~
   - ~~Update nameservers at Squarespace~~
   - DNS propagation in progress (~24-48h)

2. ~~**Enable Cloudflare Email Routing**~~ ✅ DONE
   - ~~Enable Email Routing in Cloudflare~~
   - ~~Configure MX records (route1/2/3.mx.cloudflare.net)~~
   - ~~Add routing rule for me@diegonmarcos.com~~
   - ~~Verify destination address~~

3. **Create Stalwart user account** ← NEXT
   - Login: http://130.110.251.193:8080
   - Create user: me@diegonmarcos.com
   - Configure email client (Thunderbird/etc)

4. **Phase 2: Email Worker** (Optional)
   - Create Cloudflare Worker to forward to Stalwart:587
   - Full self-hosted email (no Gmail dependency)

### Pending - NPM (Task1_validation)
1. ~~Update DNS in Squarespace~~ → DNS now on Cloudflare
2. **Change NPM password** ← HIGH PRIORITY (Security)
   - Login: http://34.55.55.234:81
   - Change from "changeme"
3. **Add SSL certificates** ← After DNS propagation
   - Via NPM web UI for each domain
   - Use Let's Encrypt

### Future Development
1. **Complete Task2** - sync-app.py implementation
   - Unified Git & Rclone manager
   - TUI dashboard
   - Flask API

2. **Service Configuration**
   - Change all service passwords
   - Configure OpenVPN (if needed)
   - Configure ttyd terminal (if needed)

---

## Documentation

### Main Documents
- **Architecture:** Task0/ARCHITECTURE_V2_20251204.md
- **Deployment:** Task1/DEPLOYMENT_COMPLETE.md
- **NPM Config:** Task1_validation/NPM_PROXY_HOSTS_COMPLETE.md
- **Validation:** Task1_validation/VALIDATION_CHECKLIST.md
- **Session Report:** Task1_validation/SESSION_REPORT_NPM_CONFIGURATION.md

### Credentials
- **Location:** `/home/diego/Documents/Git/LOCAL_KEYS/README.md`
- **Passwords:** NPM, n8n, Gitea, Syncthing, Redis, OpenVPN
- **Backup:** Synced via Syncthing (encrypted)

---

## Project Timeline

```
2025-12-03: Architecture v2 design started
2025-12-04: Task0 completed - Architecture finalized
2025-12-04: Task1 started - Infrastructure deployment
2025-12-04: gcp-f-micro_1 deployed
2025-12-04: oci-p-flex_1 deployed
2025-12-04: Task2 created (not started yet)
2025-12-05: NPM configuration completed
2025-12-05: Task1_validation created
2025-12-07: Task3 - Stalwart mail server deployed
2025-12-07: DNS migrated to Cloudflare (nameservers updated)
2025-12-07: MX/SPF/DKIM records configured via Cloudflare API
2025-12-07: Email Routing enabled + routing rule created
2025-12-07: Spec files updated (Cloud-spec_.md, TASKS_OVERVIEW.md)
```

**Total Time:** ~4 days (technical work)
**Agent Sessions:** 5 (Sonnet x3, Opus x2)
**User Actions Pending:** DNS propagation (~24-48h), SSL certificates

---

## Success Metrics

### Architecture v2
- ✅ 90% cost reduction ($50 → $5.50/month)
- ✅ Free tier NPM proxy (GCloud)
- ✅ Wake-on-demand dev server
- ✅ Centralized reverse proxy

### Deployment
- ✅ 2 VMs deployed successfully
- ✅ NPM running (port 81 accessible)
- ✅ 5 proxy hosts configured
- ✅ Old NPM cleaned up
- ✅ All passwords generated

### Email (Task3)
- ✅ Stalwart mail server deployed
- ✅ DNS migrated to Cloudflare
- ✅ MX records configured (Cloudflare)
- ✅ Email Routing enabled
- ✅ Routing rule created (me@)
- ⏳ DNS propagation in progress
- ⏳ Stalwart user account (pending)

### Pending
- ⏳ DNS propagation (Cloudflare nameservers)
- ⏳ SSL certificates (after DNS)
- ⏳ NPM password change

---

**Last Updated:** 2025-12-07
**Status:** Task3 (Mail) - Cloudflare Email Routing configured, DNS propagating
