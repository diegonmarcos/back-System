# Photos Project - Deployment Plan

> **Project**: Self-hosted Google Photos alternative
> **Phases**: 3 (Light → Multi-viewer → AI-enhanced)
> **VM**: oci-p-flex_1 (8GB RAM, Wake-on-Demand)
> **Storage**: Oracle S3 (300GB, $7.14/mo)
> **Version**: 1.0.0 | **Updated**: 2025-12-06

---

## Architecture Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    PHOTOS PROJECT PHASES                     │
└─────────────────────────────────────────────────────────────┘

PHASE 1: Light Deploy (Week 1-2)
├─ S3 Storage: 300GB raw photos
├─ PostgreSQL: Metadata DB (EXIF, location, hashes)
├─ Python Script: S3 webhook processor (EXIF, geocoding)
└─ Frontend: PhotoView (lightweight, timeline + map)

PHASE 2: Multi-Viewer (Week 3)
├─ Same S3 + PostgreSQL + script
├─ Add Photoprism (full-featured)
├─ Add Immich (no-ML fork)
└─ User chooses viewer

PHASE 3: AI-Enhanced (Week 4+)
├─ Deploy ml-Agentic (oci-f-arm_1)
├─ Face detection → Albums by Face
├─ Auto-tagging → Smart search
├─ All viewers display new features
└─ Same PostgreSQL (shared data)
```

---

## Phase 1: Light Deploy

### 1.1 Storage Setup

**Oracle S3 Bucket**
```bash
Name: photos
Region: eu-marseille-1
Size: 300GB
Cost: $7.14/month (after 20GB free tier)
Access: Via S3 credentials (IAM policy)
```

**Upload Methods**
```
Desktop:  rclone sync ~/Pictures/ s3://photos/
Mobile:   FolderSync (Android) → S3
iOS:      Syncthing → S3 (via rclone on desktop)
```

### 1.2 Database Setup

**PostgreSQL Schema**
```sql
-- Photos metadata table
CREATE TABLE photos (
    id BIGSERIAL PRIMARY KEY,
    filename VARCHAR(500) UNIQUE,
    s3_path TEXT,
    size_bytes BIGINT,

    -- EXIF data
    taken_date TIMESTAMP,
    camera_model VARCHAR(255),
    iso INT,
    shutter_speed VARCHAR(50),
    aperture VARCHAR(50),
    focal_length VARCHAR(50),

    -- Geolocation
    latitude DECIMAL(9,6),
    longitude DECIMAL(9,6),
    location_name VARCHAR(500),

    -- Deduplication
    perceptual_hash VARCHAR(64),

    -- Timestamps
    created_at TIMESTAMP DEFAULT NOW(),
    indexed_at TIMESTAMP
);

-- AI results table (created in Phase 3)
CREATE TABLE photo_ai_results (
    photo_id BIGINT PRIMARY KEY REFERENCES photos(id),
    faces JSONB,
    objects JSONB,
    tags TEXT[],
    processing_status VARCHAR(50),
    processing_timestamp TIMESTAMP
);

-- Indexes for fast queries
CREATE INDEX idx_taken_date ON photos(taken_date);
CREATE INDEX idx_location ON photos USING GIST(
    ll_to_earth(latitude, longitude)
);
CREATE INDEX idx_camera ON photos(camera_model);
```

**Host**: oci-p-flex_1 (local)
**RAM**: 50-200 MB
**Storage**: 100-300 MB (300k photos × 1.5KB metadata)

### 1.3 Webhook Processor (Python)

**File**: `/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photos-webhook/webhook.py`

```python
import piexif
import geopy.geocoders
import psycopg2
from PIL import Image
import imagehash
import boto3
import os
from datetime import datetime

def process_photo(s3_key, s3_bucket):
    """Process photo from S3 event"""

    # 1. Download from S3
    s3 = boto3.client('s3')
    photo_path = f"/tmp/{os.path.basename(s3_key)}"
    s3.download_file(s3_bucket, s3_key, photo_path)

    # 2. Extract EXIF
    try:
        exif_data = piexif.load(photo_path)
        taken_date = extract_exif_date(exif_data)
        camera = extract_exif_camera(exif_data)
        iso = extract_exif_iso(exif_data)
        lat, lon = extract_gps(exif_data)
    except:
        taken_date = None
        camera = None
        iso = None
        lat, lon = None, None

    # 3. Reverse geocode
    location_name = None
    if lat and lon:
        try:
            geolocator = geopy.geocoders.Nominatim(user_agent="photos-app")
            location = geolocator.reverse(f"{lat}, {lon}")
            location_name = location.address
        except:
            pass

    # 4. Compute hash
    try:
        image = Image.open(photo_path)
        p_hash = str(imagehash.phash(image))
    except:
        p_hash = None

    # 5. Save to PostgreSQL
    conn = psycopg2.connect("dbname=photos user=photos password=SECURE_PASSWORD host=localhost")
    cur = conn.cursor()

    cur.execute("""
        INSERT INTO photos
        (filename, s3_path, taken_date, camera_model, iso,
         latitude, longitude, location_name, perceptual_hash, indexed_at)
        VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, NOW())
    """, (os.path.basename(s3_key), f"s3://{s3_bucket}/{s3_key}",
          taken_date, camera, iso, lat, lon, location_name, p_hash))

    conn.commit()
    cur.close()
    conn.close()

    # 6. Cleanup
    os.remove(photo_path)

    return {"status": "indexed", "s3_key": s3_key}

# Flask endpoint for S3 webhook
from flask import Flask, request, jsonify

app = Flask(__name__)

@app.post("/webhook/s3-photo-upload")
def handle_s3_upload():
    event = request.json
    s3_key = event['Records'][0]['s3']['object']['key']
    s3_bucket = event['Records'][0]['s3']['bucket']['name']

    try:
        result = process_photo(s3_key, s3_bucket)
        return jsonify(result), 200
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500

if __name__ == "__main__":
    app.run(port=5001)  # Separate from cloud-app
```

### 1.4 PhotoView Deployment

**Docker Compose**: `/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photoview/docker-compose.yml`

```yaml
version: '3.8'

services:
  photoview:
    image: viktorstrate/photoview:latest
    container_name: photoview-app
    ports:
      - "3000:3000"
    environment:
      - DATABASE_URL=postgresql://photos:SECURE_PASSWORD@localhost:5432/photos
      - PHOTOVIEW_LISTEN_IP=0.0.0.0
      - PHOTOVIEW_LISTEN_PORT=3000
    volumes:
      - /mnt/photos:/photos:ro  # Mount S3 bucket locally (via s3fs)
    networks:
      - photos_net
    restart: unless-stopped

networks:
  photos_net:
    driver: bridge
```

**Installation Steps**
```bash
# 1. Install PostgreSQL
sudo apt install postgresql postgresql-contrib

# 2. Create photos database
psql -U postgres -c "CREATE DATABASE photos;"
psql -U postgres -c "CREATE USER photos WITH PASSWORD 'SECURE_PASSWORD';"
psql -U postgres -c "GRANT ALL PRIVILEGES ON DATABASE photos TO photos;"

# 3. Load schema
psql -U photos -d photos -f /path/to/schema.sql

# 4. Install s3fs for local mounting
sudo apt install s3fs
echo "S3_ACCESS_KEY:S3_SECRET_KEY" > ~/.s3fs-credentials
chmod 600 ~/.s3fs-credentials

# 5. Mount S3 bucket
mkdir -p /mnt/photos
s3fs photos /mnt/photos -o passwd_file=~/.s3fs-credentials

# 6. Deploy PhotoView
cd /home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/photoview
docker-compose up -d
```

**Access**: https://photos.diegonmarcos.com (via NPM)

### 1.5 Estimated Resources (Phase 1)

| Component | RAM | Storage | Status |
|-----------|-----|---------|--------|
| PostgreSQL | 50-100 MB | 100-300 MB | Running |
| PhotoView | 100-150 MB | 50-100 MB | Running |
| Webhook processor | - | <5 MB | Triggered only |
| **Total** | **150-250 MB** | **~500 MB** | **Dev** |

**Available on oci-p-flex_1**: 8GB RAM (plenty headroom)

---

## Phase 2: Add More Viewers (Week 3)

### 2.1 Deploy Photoprism

**Same PostgreSQL, same S3 bucket**

```yaml
# docker-compose additions
photoprism:
  image: photoprism/photoprism:latest
  container_name: photoprism-app
  ports:
    - "2342:2342"
  environment:
    - PHOTOPRISM_DATABASE_DSN=postgresql://photos:PASSWORD@localhost:5432/photos?sslmode=disable
    - PHOTOPRISM_STORAGE_PATH=/photos
  volumes:
    - /mnt/photos:/photos:ro
  networks:
    - photos_net
```

### 2.2 Deploy Immich (No ML Fork)

**Fork from main repo, disable ML service**

```yaml
immich:
  image: ghcr.io/immich-app/immich-server:latest
  container_name: immich-app
  ports:
    - "3001:3001"
  environment:
    - DB_HOSTNAME=localhost
    - DB_DATABASE=photos
    - DB_USERNAME=photos
    - DB_PASSWORD=SECURE_PASSWORD
    - IMMICH_MACHINE_LEARNING_ENABLED=false
    - IMMICH_SKIP_ML_INIT=true
  volumes:
    - /mnt/photos:/photos:ro
  networks:
    - photos_net
```

### 2.3 Resource Update (Phase 2)

| Component | RAM | Storage |
|-----------|-----|---------|
| PhotoView | 100-150 MB | 100-200 MB |
| Photoprism | 150-250 MB | 200-300 MB |
| Immich (no ML) | 200-400 MB | 300-500 MB |
| PostgreSQL | 100-200 MB | 100-300 MB |
| **Total** | **550-1000 MB** | **700-1300 MB** |

**Still within oci-p-flex_1 capacity** ✓

---

## Phase 3: AI-Enhanced Features (Week 4+)

### 3.1 Deploy ml-Agentic (oci-f-arm_1)

Runs in parallel on separate VM with 24GB RAM.

**Creates workflows for:**
- Face detection
- Object recognition
- Auto-tagging
- Album generation

**Writes to**: Same `photo_ai_results` table in PostgreSQL

### 3.2 New Features in Viewers

All three viewers automatically display:
- Faces detected in photos
- Auto-generated tags
- Albums by face, object, tag
- Enhanced search

**No migration needed** - same database, new table.

---

## Configuration Files

### Directory Structure
```
/home/diego/Documents/Git/back-System/cloud/vps_oracle/vm-oci-p-flex_1/2.app/
├── photos-webhook/
│   ├── webhook.py
│   ├── requirements.txt
│   └── Dockerfile
├── photoview/
│   └── docker-compose.yml
├── photoprism/
│   └── docker-compose.yml
└── immich/
    └── docker-compose.yml

/home/diego/Documents/Git/front-Github_io/myphotos/
├── spec.md (Light viewer HTML spec)
├── index.html (Timeline + map view)
├── css/
│   └── styles.css
└── js/
    └── app.js
```

### Critical Files to Create
1. PostgreSQL schema: `schema.sql`
2. Webhook processor: `webhook.py`
3. Docker compositions: `docker-compose.yml` files
4. Frontend HTML: `index.html` (PhotoView custom or use existing)

---

## Timeline

### Phase 1: Light Deploy (2 weeks)
- Week 1: Database + webhook setup, upload 100GB test
- Week 2: PhotoView deployment, upload remaining 200GB

### Phase 2: Add Viewers (1 week)
- Week 3: Deploy Photoprism + Immich, test all 3 views

### Phase 3: AI Features (2+ weeks, parallel)
- Week 4+: ml-Agentic deployment (on oci-f-arm_1)
- Ongoing: Workflow integration, feature development

---

## Cost Summary

| Component | Cost | Notes |
|-----------|------|-------|
| Oracle S3 (300GB) | $7.14/mo | After 20GB free tier |
| oci-p-flex_1 (photos) | Included | Part of $5.50/mo wake-on-demand |
| oci-f-arm_1 (Phase 3) | $0/mo | Free tier ARM VM |
| **Total** | **~$12.64/mo** | |

---

## Security Notes

- S3 credentials stored in environment variables (not in code)
- PostgreSQL password in `.env` file (not in repo)
- S3 IAM policy restricts to photos bucket only
- Webhook endpoint requires S3 signature verification
- Photos not accessible without authentication (future: add OAuth2)

---

## Next Steps

1. ✓ Plan created
2. ⏳ Create PostgreSQL schema
3. ⏳ Write webhook processor
4. ⏳ Deploy PhotoView
5. ⏳ Upload 300GB photos
6. ⏳ Verify metadata extraction
7. ⏳ Deploy Photoprism + Immich (Phase 2)
8. ⏳ Deploy ml-Agentic (Phase 3)
