# Mail App Status

**Status:** DEPLOYED
**Date:** 2025-12-08
**VM:** oci-f-micro_1 (130.110.251.193)

---

## Deployment Status

| Component | Status | Version |
|-----------|--------|---------|
| Stalwart Mail Server | DEPLOYED | latest |
| Snappymail Webmail | DEPLOYED | latest |
| Cloudflare Email Routing | CONFIGURED | - |
| OCI Security List | CONFIGURED | - |
| **OCI Email Delivery Relay** | **CONFIGURED** | - |

## Services Running

```
CONTAINER       IMAGE                             STATUS          PORTS
stalwart-mail   stalwartlabs/mail-server:latest   Up              25,587,993,8080
snappymail      djmaze/snappymail:latest          Up              8888
```

## Endpoints

| Service | URL | Status |
|---------|-----|--------|
| Stalwart Admin | http://130.110.251.193:8080 | OK |
| Snappymail | http://130.110.251.193:8888 | OK |
| IMAP | 130.110.251.193:993 | OK |
| SMTP | 130.110.251.193:587 | OK |

---

## What's Done

- [x] Stalwart container deployed
- [x] Snappymail container deployed
- [x] Admin account created (diego + 2FA)
- [x] Email account created (me@diegonmarcos.com)
- [x] Cloudflare MX records configured
- [x] Cloudflare Email Routing enabled (Gmail as primary)
- [x] OCI security list updated (ports 587, 993, 8080, 8888)
- [x] Thunderbird client configured
- [x] Docker Compose updated
- [x] Documentation updated
- [x] Let's Encrypt TLS certificates (ACME) - DONE 2025-12-07
- [x] **OCI Email Delivery Relay configured** - DONE 2025-12-08

## Pending

- [ ] Cloudflare Worker for archive forwarding to Stalwart
- [ ] DKIM configuration
- [ ] Additional alias addresses

---

## Architecture

### Inbound Mail Flow
```
Internet → Cloudflare (port 25) → Email Routing → Gmail (PRIMARY)
                                                → Stalwart (ARCHIVE via Worker - planned)
```

### Outbound Mail Flow (NEW)
```
Thunderbird/Client → Stalwart (port 587/STARTTLS) → OCI Email Delivery Relay → Internet
                                                    (smtp.email.eu-marseille-1.oci.oraclecloud.com:587)
```

**Note:** Oracle Cloud blocks outbound port 25, so all outbound mail is routed through OCI Email Delivery service.

See [OCI-RELAY.md](./OCI-RELAY.md) for detailed relay configuration.

## Quick Access

```bash
# SSH to server
ssh -i ~/.ssh/id_rsa ubuntu@130.110.251.193

# Stalwart Admin
http://130.110.251.193:8080  (admin / 8HkSfq6mCW)

# Snappymail Webmail
http://130.110.251.193:8888  (me@diegonmarcos.com / diego123)

# Check services
sudo docker ps | grep -E 'stalwart|snappymail'
```
