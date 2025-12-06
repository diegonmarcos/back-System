# Mail Server

Self-hosted email server for personal/professional use.

---

## 📋 Status

- **Status**: ⏳ Planned
- **Purpose**: Self-hosted email for @diegonmarcos.com domain
- **Target**: Personal and professional email

---

## 🎯 Planned Features

### Core Services

- **SMTP** (Send): Postfix
- **IMAP/POP3** (Receive): Dovecot
- **Webmail**: Roundcube or Rainloop
- **Spam Filter**: SpamAssassin or rspamd
- **Antivirus**: ClamAV
- **DKIM/SPF/DMARC**: Email authentication

### Domains

- `diego@diegonmarcos.com`
- `me@diegonmarcos.com`
- Catch-all: `*@diegonmarcos.com`

---

## 🛠️ Technology Stack (Proposed)

### Option 1: Docker Mailserver

**Image**: `docker-mailserver/docker-mailserver`

**Pros**:
- All-in-one container
- Well-maintained
- Good documentation
- Easy setup

**Cons**:
- Single container (less modular)
- Higher resource usage

### Option 2: Mailcow

**Image**: `mailcow/mailcow-dockerized`

**Pros**:
- Full-featured
- Modern UI
- Calendar/contacts (SOGo)
- Docker Compose based

**Cons**:
- Heavier (~1GB RAM)
- More complex

### Option 3: Manual Setup

**Components**: Postfix + Dovecot + Roundcube

**Pros**:
- Maximum control
- Lightweight
- Modular

**Cons**:
- Time-consuming setup
- More maintenance

---

## 📊 Resource Requirements (Estimated)

| Solution | RAM | CPU | Disk |
|----------|-----|-----|------|
| **Docker Mailserver** | ~400 MB | 0.2 vCPU | ~500 MB |
| **Mailcow** | ~1 GB | 0.4 vCPU | ~2 GB |
| **Manual** | ~300 MB | 0.2 vCPU | ~300 MB |

**⚠️ Note**: Current VPS has 1GB RAM. Mail server may require instance upgrade or external mail relay.

---

## 🔐 Security Requirements

### DNS Records Needed

```dns
# MX Record
@ MX 10 mail.diegonmarcos.com

# A Record for mail server
mail A 130.110.251.193

# SPF Record
@ TXT "v=spf1 mx ~all"

# DKIM Record (generated during setup)
mail._domainkey TXT "v=DKIM1; k=rsa; p=PUBLIC_KEY"

# DMARC Record
_dmarc TXT "v=DMARC1; p=quarantine; rua=mailto:dmarc@diegonmarcos.com"
```

### SSL/TLS

- Let's Encrypt certificates via Nginx Proxy Manager
- TLS 1.2+ only
- Valid certificate for mail.diegonmarcos.com

### Authentication

- Strong passwords (min 16 chars)
- Two-factor authentication (recommended)
- Rate limiting
- Fail2ban for brute-force protection

---

## 📝 Implementation Plan

### Phase 1: Research & Planning
- [ ] Choose mail server solution
- [ ] Test on local environment
- [ ] Plan resource allocation
- [ ] Estimate migration downtime

### Phase 2: DNS & Domain Setup
- [ ] Configure MX records
- [ ] Set up SPF/DKIM/DMARC
- [ ] Verify DNS propagation
- [ ] Test email deliverability

### Phase 3: Server Installation
- [ ] Deploy mail server containers
- [ ] Configure SSL certificates
- [ ] Set up user accounts
- [ ] Configure spam filtering

### Phase 4: Testing
- [ ] Send/receive test emails
- [ ] Test spam filtering
- [ ] Verify DKIM signatures
- [ ] Check blacklist status

### Phase 5: Production
- [ ] Migrate existing emails
- [ ] Configure email clients
- [ ] Enable monitoring
- [ ] Document procedures

---

## 🌐 Planned Endpoints

| Service | URL | Port |
|---------|-----|------|
| **SMTP (TLS)** | mail.diegonmarcos.com | 587 |
| **SMTP (SSL)** | mail.diegonmarcos.com | 465 |
| **IMAP (SSL)** | mail.diegonmarcos.com | 993 |
| **POP3 (SSL)** | mail.diegonmarcos.com | 995 |
| **Webmail** | https://mail.diegonmarcos.com | 443 |

---

## ⚠️ Important Considerations

### Deliverability Challenges

**Email hosting is complex**. Consider these challenges:

1. **IP Reputation**: New VPS IPs may be blacklisted
   - Check: https://mxtoolbox.com/blacklists.aspx
   - May need "warm-up" period

2. **Port 25 Blocking**: Some ISPs block outbound port 25
   - Oracle Cloud: Check if port 25 is open
   - Alternative: Use SMTP relay service

3. **Spam Filters**: Gmail/Outlook are strict
   - Requires proper SPF/DKIM/DMARC
   - Reverse DNS must match
   - Monitor deliverability closely

4. **Maintenance**: Email servers need constant monitoring
   - Security updates
   - Spam filter tuning
   - Backup verification

### Alternative: Hybrid Approach

**Option**: Use external SMTP relay for outbound, self-host for inbound:

- **Outbound**: SendGrid, Mailgun, or AWS SES
- **Inbound**: Self-hosted (Dovecot + webmail)

**Benefits**:
- Better deliverability
- Lower maintenance
- Still control incoming mail

---

## 📚 Related Documentation

- **Main VPS Spec**: [`../README.md`](../README.md)
- **Docker Mailserver**: https://docker-mailserver.github.io/
- **Mailcow**: https://mailcow.email/
- **Email Security Best Practices**: https://www.rfc-editor.org/rfc/rfc8314

---

## 🔍 Pre-requisites Checklist

Before deploying:

- [ ] VPS has sufficient RAM (may need upgrade)
- [ ] Port 25, 587, 465, 993, 995 available
- [ ] Domain DNS controlled
- [ ] Reverse DNS configured
- [ ] IP not blacklisted
- [ ] Backup strategy planned

---

**Status**: ⏳ Planning Stage
**Priority**: Medium (after sync service)
**Recommended**: Consider managed email (ProtonMail, Fastmail) for reliability
**Last Updated**: 2025-11-25
