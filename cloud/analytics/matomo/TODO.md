# Analytics Implementation TODO

## Pending Tasks

### 1. Run GTM Setup Script
- [ ] Navigate to `.gtm` folder
- [ ] Add IP configuration if needed
- [ ] Run: `python setup_gtm.py`
- [ ] Verify new triggers and tags are created
- [ ] Check for any API errors

### 2. Test in GTM Dashboard
- [ ] Open [Google Tag Manager](https://tagmanager.google.com)
- [ ] Review container **GTM-TN9SV57D**
- [ ] Verify 4 new triggers:
  - UI Controls Click
  - Collapsible Toggle Click
  - vCard Download
  - Navigation Menu Click
- [ ] Verify 4 new tags:
  - GA4 Event - UI Control Click
  - GA4 Event - Collapsible Toggle
  - GA4 Event - vCard Download
  - GA4 Event - Navigation Click

### 3. Test Cookie Consent Banner
- [ ] Visit each page and verify banner appears:
  - [ ] `/index.html` (root/landpage)
  - [ ] `/linktree/index.html`
  - [ ] `/cv_web/index.html`
  - [ ] `/cv_pdf/index.html`
  - [ ] `/myprofile/` (SvelteKit app)
- [ ] Test "OK" button → All tracking enabled
- [ ] Test "Options" → Granular controls work
- [ ] Verify consent persists (refresh page, banner should not reappear)

### 4. Test GTM Preview Mode
- [ ] Enable GTM Preview Mode
- [ ] Test UI controls (theme toggles, font size, etc.)
- [ ] Test collapsible buttons
- [ ] Test vCard download
- [ ] Test navigation clicks
- [ ] Verify events fire in GA4 DebugView

### 5. Publish GTM Container
- [ ] Review all changes in GTM
- [ ] Click **Submit**
- [ ] Version name: `"Universal Event Tracking v2.0 - UI Controls + Cookie Consent"`
- [ ] Description: `"Added 4 new triggers (UI controls, collapsible, vCard, navigation) and 4 new tags. Integrated cookie consent banner."`
- [ ] Click **Publish**

### 6. Commit and Push Changes
- [ ] Stage all changes
- [ ] Commit with message: `"feat: complete analytics implementation with GTM tracking and cookie consent"`
- [ ] Push to branch: `claude/review-analytics-matomo-01AfDPW6dLDgTW5qRkCDh5Mj`

### 7. Monitor GA4 Events
- [ ] Wait 24-48 hours for data collection
- [ ] Check GA4 for new events:
  - `ui_control_click`
  - `collapsible_toggle`
  - `vcard_download`
  - `navigation_click`
- [ ] Review user journey insights

---

## Notes

- Cookie consent files are in `/5.analytics/` for all HTML pages
- MyProfile uses static files in `/myprofile/1.3.svelte/static/`
- GTM Container ID: **GTM-TN9SV57D**
- GA4 Measurement ID: **G-VB9ENP6DZ0**
- All pages except `/others/` folder have tracking

---

**Last Updated**: 2025-11-18
