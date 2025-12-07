# Photos Project - Complete Index

> **Status**: Planning Complete ✓
> **VM**: oci-p-flex_1 (8GB, wake-on-demand)
> **Storage**: Oracle S3 (300GB, $7.14/mo)
> **Total Project Cost**: ~$12.64/mo
> **Timeline**: 3 phases (2-4 weeks each)

---

## Quick Navigation

### Master Documents
- **Deployment Plan**: `/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/photos-deployment.md`
  - Full architecture, setup steps, Docker configs

- **Frontend Spec**: `/home/diego/Documents/Git/front-Github_io/myphotos/spec.md`
  - PhotoView or custom React viewer options

- **Infrastructure Tables**: `/home/diego/Documents/Git/back-System/cloud/0.spec/Cloud-spec_Tables.md`
  - Updated with photos resource estimates

---

## What Was Decided

### Architecture
```
S3 (300GB raw)
  ↓
S3 Events → Python webhook
  ↓
Extract EXIF + geocoding
  ↓
PostgreSQL (metadata)
  ↓
PhotoView/Photoprism/Immich (viewers)
  ↓
ml-Agentic (Phase 3, faces/tags)
```

### Authentication
- **Upload control**: S3 credentials (rclone/FolderSync)
- **S3 access**: IAM policy (photos bucket only)
- **Webhook signature**: S3 signs each request
- **Viewer auth**: Future OAuth2 (optional)

### Storage
- **Photos**: Oracle S3 ($7.14/mo)
- **Metadata**: PostgreSQL on oci-p-flex_1
- **Cache**: Redis (optional, future)
- **Total**: ~$12.64/mo (photos + VM)

---

## Three Phases

### Phase 1: Light Deploy (Weeks 1-2)
**Goal**: Organized photo library with one lightweight viewer

**Deploy**:
1. PostgreSQL database
2. S3 webhook processor (Python)
3. PhotoView (timeline + map)
4. Upload 300GB photos

**Resources**: 150-250 MB RAM
**Result**: Fully functional photo library

### Phase 2: Multi-Viewer (Week 3)
**Goal**: Choose from 3 different viewer apps

**Deploy**:
1. Photoprism (full-featured)
2. Immich (no-ML fork)
3. Keep PhotoView (lightweight)

**Resources**: +550-1000 MB RAM (all 3 viewers)
**Result**: Same photos, different interfaces

### Phase 3: AI-Enhanced (Weeks 4+, parallel)
**Goal**: Smart organization via ml-Agentic

**Deploy**:
1. ml-Agentic on oci-f-arm_1 (24GB ARM VM)
2. Face detection workflows
3. Auto-tagging workflows
4. Album generation

**Resources**: 6+ GB on oci-f-arm_1 (separate VM)
**Result**: Albums by face, smart search, auto-tags

---

## Key Files Created/Updated

### Infrastructure Spec
- ✓ `/home/diego/Documents/Git/back-System/cloud/0.spec/Cloud-spec_Tables.md`
  - Added photos service table
  - Updated oci-p-flex_1 resources
  - Phase 1-3 breakdown

### Deployment Plan
- ✓ `/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/photos-deployment.md`
  - PostgreSQL schema
  - Python webhook code
  - Docker-compose for all 3 viewers
  - Installation steps
  - Resource estimates

### Frontend Spec
- ✓ `/home/diego/Documents/Git/front-Github_io/myphotos/spec.md`
  - PhotoView (recommended, ready-to-use)
  - Custom React option (for future)
  - API endpoints needed
  - Features by phase

### Directory Structure
```
Created:
├── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/photos-deployment.md
├── /home/diego/Documents/Git/front-Github_io/myphotos/spec.md
└── /home/diego/Documents/Git/back-System/PHOTOS-PROJECT-INDEX.md (this file)

Will Create:
├── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photos-webhook/webhook.py
├── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photoview/docker-compose.yml
├── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photoprism/docker-compose.yml
├── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/immich/docker-compose.yml
└── /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photos-webhook/requirements.txt
```

---

## Tech Stack Summary

| Layer | Technology | Purpose |
|-------|-----------|---------|
| **Storage** | Oracle S3 | Photo storage (300GB) |
| **Metadata** | PostgreSQL | EXIF, location, AI results |
| **Events** | S3 webhooks | Trigger processing |
| **Processing** | Python (piexif, geopy) | Extract metadata |
| **Web Framework** | Flask | API + webhook endpoint |
| **Viewers (Phase 1)** | PhotoView | Lightweight viewer |
| **Viewers (Phase 2)** | Photoprism, Immich | Full-featured viewers |
| **AI (Phase 3)** | ml-Agentic (n8n) | Face/object detection |
| **Frontend** | React/HTML | Photo display |

---

## Resource Estimates

### Phase 1: Light
- **RAM**: 150-250 MB
- **Storage**: ~500 MB (app only, photos on S3)
- **Cost**: +$7.14/mo (S3 only)

### Phase 2: Multi-Viewer
- **RAM**: 550-1000 MB
- **Storage**: ~700-1300 MB
- **Cost**: +$0 (same S3)

### Phase 3: AI-Enhanced
- **RAM**: +6-24 GB (on oci-f-arm_1, separate)
- **Storage**: +5-20 GB (models, workflows)
- **Cost**: +$0 (free tier ARM VM)

### Total Monthly Cost
- Oracle S3: $7.14/mo
- oci-p-flex_1 (photos): Included in $5.50/mo wake-on-demand
- oci-f-arm_1 (Phase 3): $0/mo (free tier)
- **Total**: ~$12.64/mo

---

## Implementation Order

### Immediate (Phase 1 - Weeks 1-2)
1. Read: `photos-deployment.md` (understand architecture)
2. Create: PostgreSQL schema
3. Create: Python webhook processor
4. Deploy: PostgreSQL + schema
5. Deploy: PhotoView (via docker-compose)
6. Upload: 100GB test photos
7. Verify: Metadata extraction works
8. Upload: Remaining 200GB

### Short-term (Phase 2 - Week 3)
1. Deploy: Photoprism (docker-compose)
2. Deploy: Immich no-ML fork (docker-compose)
3. Test: All 3 viewers show same photos
4. Configure: NPM routing to all 3

### Medium-term (Phase 3 - Weeks 4+)
1. Plan: ml-Agentic integration
2. Deploy: ml-Agentic workflows
3. Implement: Face detection
4. Implement: Auto-tagging
5. Update: Viewers to show AI results

---

## Key Decisions Made

✓ **Light viewer first** (PhotoView, not custom build initially)
✓ **PostgreSQL for metadata** (standard, reliable)
✓ **S3 for storage** (cheap at $7.14/mo, Oracle free tier)
✓ **Event-driven processing** (S3 webhook, not polling)
✓ **S3 credentials for auth** (rclone/FolderSync handles it)
✓ **Phased approach** (MVP first, viewers second, AI third)
✓ **Same PostgreSQL for all viewers** (no duplication)
✓ **oci-p-flex_1 for Phase 1-2** (8GB enough, wake-on-demand)
✓ **oci-f-arm_1 for Phase 3 AI** (24GB free tier ARM)

---

## Next Immediate Action

**Read and understand**:
1. `/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/photos-deployment.md`
2. `/home/diego/Documents/Git/front-Github_io/myphotos/spec.md`

**Then choose**:
- Start Phase 1 now? (Create PostgreSQL schema)
- Need clarification on anything?
- Want to adjust any decisions?

---

## Questions to Consider

1. **Custom HTML for frontend?**
   - Option A: Use PhotoView as-is (fastest)
   - Option B: Fork PhotoView + customize (medium effort)
   - Option C: Build custom React from scratch (full control, more work)

2. **When to start uploading?**
   - After Phase 1 setup (safest)
   - Incrementally during Phase 1 (faster feedback)
   - Batch at end (less risk)

3. **Which viewer for daily use?**
   - PhotoView (light, fast)
   - Photoprism (traditional, mature)
   - Immich (modern, full-featured)

4. **Phase 3 timeline?**
   - Immediately after Phase 2 (weeks 4+)
   - Wait for feedback from Phase 1-2
   - Defer until later

---

## Success Criteria

✓ Phase 1 complete when:
- 300GB photos in S3
- All metadata extracted to PostgreSQL
- PhotoView displays all photos with timeline + map
- Metadata queries fast (<1s)

✓ Phase 2 complete when:
- All 3 viewers show same photos
- User can choose preferred interface
- Each viewer accessible via domain (NPM routing)

✓ Phase 3 complete when:
- Face detection working
- Auto-tags generated
- Albums by face created
- All viewers display AI results

---

**Ready to proceed?** Start with Phase 1 deployment plan.
