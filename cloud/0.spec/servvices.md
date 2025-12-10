## A) Services - Stack & Features Definition

```
Pattern: SERVICE → front (our GUI) + app (forked/custom) + db(s)

Container          | Purpose                         | Stack
───────────────────┼─────────────────────────────────┼──────────────────────────
```

### AI

```
ai                 | AI Assistants Hub               | -
  ↳ ai-front       | AI services landing page        | SvelteKit 5 + SCSS
  │
  ├─ ai-chat       | AI Web Chat Interface           | -
  │  ↳ chat-front  | Login + chat UI wrapper         | SvelteKit 5 + SCSS
  │  ↳ chat-app    | Chat backend                    | Open WebUI / LibreChat
  │  ↳ chat-api    | LLM API backend                 | Ollama / OpenAI API
  │  ↳ chat-db0    | Chat history, users             | SQL:PostgreSQL
  │
  └─ ai-cli        | AI CLI Assistant                | -
     ↳ cli-app     | Terminal AI assistant           | Claude Code / Aider

```

### DevUser Productivity

```
terminal           | Web Terminal & Shell            | -
  ↳ terminal-front | Login + command index           | SvelteKit 5 + SCSS
  ↳ shell-app      | Python TUI with command index   | Python3
  ↳ webterminal-app| Browser-based terminal          | wetty / ttyd

mail               | Email Suite                     | -
  ↳ mail-front     | Nginx reverse proxy             | Nginx
  ↳ mail-admin     | Admin web interface             | Mailu-Admin
  ↳ mail-imap      | IMAP server                     | Dovecot
  ↳ mail-smtp      | SMTP server                     | Postfix
  ↳ mail-webmail   | Webmail client                  | Roundcube
  ↳ mail-db_file0  | Mailboxes storage               | Maildir

sync               | File Synchronization Hub        | -
  ↳ sync-front     | File tree viewer (collapsible)  | SvelteKit 5 + SCSS
  ↳ sync-app       | Aggregates drive+git            | Python3
  │
  ├─ drive         | Cloud Drive (Filesystem Mount)  | -
  │  ↳ drive-front | File browser display            | SvelteKit 5 + SCSS
  │  ↳ drive-app   | Bisync / FUSE mount daemon      | Rclone
  │  ↳ drive-db0   | Mount configs + cache           | Filesystem
  │
  └─ git           | Git Hosting                     | -
     ↳ git-front   | Login + repo display            | SvelteKit 5 + SCSS
     ↳ git-app     | Git server + web UI             | Gitea
     ↳ git-db_file0| Users, issues, PRs              | SQL:SQLite
     ↳ git-db_obj0 | Git repositories (.git objects) | Filesystem

photos             | Photo Library Management        | -
  ↳ photo-front    | Login + gallery display         | SvelteKit 5 + SCSS
  ↳ photo-app      | Photo viewer + AI tagging       | Photoprism
  ↳ photo-db_file0 | Metadata (EXIF, location, AI)   | SQL:MariaDB
  ↳ photo-db_obj0  | Photo files storage             | Filesystem
```

### DevUser Security

```
vault              | Password Manager                | -
  ↳ vault-front    | Login (uses Vaultwarden UI)     | Vaultwarden (built-in)
  ↳ vault-app      | Bitwarden-compatible API        | Vaultwarden
  ↳ vault-db_file0 | Encrypted credentials           | SQL:SQLite

vpn                | VPN Server                      | -
  ↳ vpn-front      | Client config download page     | SvelteKit 5 + SCSS
  ↳ vpn-app        | VPN server + client generator   | Wireguard
  ↳ vpn-db_file0   | Client configs + certificates   | Filesystem
```

---

### Devs Cloud Dashboard

```
cloud              | Cloud Dashboard & Monitoring    | -
  ↳ cloud-front    | Dashboard UI                    | SvelteKit 5 + SCSS
  ↳ cloud-app      | Backend logic + collectors      | Python3
  ↳ cloud-db_file0 | Config + metrics storage        | Hybrid:JSON/SQLite

analytics          | Web Analytics Platform          | -
  ↳ analytics-front| Login + stats display           | SvelteKit 5 + SCSS
  ↳ analytics-app  | Analytics engine                | Matomo (PHP-FPM)
  ↳ analytics-db0  | Visits, events, reports         | SQL:MariaDB

n8n                | Workflow Automation Hub         | -
  ↳ n8n-front      | Workflows landing page          | SvelteKit 5 + SCSS
  │
  ├─ n8n-infra     | Infrastructure Workflows        | -
  │  ↳ infra-front | Login + workflow display        | n8n (built-in)
  │  ↳ infra-app   | Workflow engine + web editor    | n8n
  │  ↳ infra-db0   | Workflows, credentials, logs    | SQL:SQLite
  │
  └─ n8n-ai        | AI Agentic Workflows            | -
     ↳ ai-front    | Login + AI workflow display     | n8n (built-in)
     ↳ ai-app      | n8n + AI/LLM integrations       | n8n + LangChain
     ↳ ai-db0      | Vector embeddings, chat history | SQL:PostgreSQL + pgvector
     ↳ ai-gpu      | GPU compute runtime             | Vast.ai / Lambda
```

### Devs Security

```
webserver          | Central Proxy & Web Serving     | -
  ↳ proxy-front    | NPM admin UI                    | NPM (built-in)
  ↳ proxy-app      | Reverse proxy + SSL termination | NPM (Nginx Proxy Manager)
  ↳ proxy-db_file0 | Proxy configs + certs           | SQL:SQLite

oauth2             | GitHub OAuth2 Authentication    | -
  ↳ oauth2-front   | Login redirect page             | OAuth2-Proxy (built-in)
  ↳ oauth2-app     | OAuth2 proxy server             | OAuth2-Proxy
  ↳ oauth2-db_file0| Session tokens                  | Redis / Memory

authelia           | 2FA / SSO Gateway               | -
  ↳ authelia-front | Login + 2FA prompt              | Authelia (built-in)
  ↳ authelia-app   | Auth server + session mgmt      | Authelia
  ↳ authelia-db0   | Users, sessions, TOTP seeds     | SQL:PostgreSQL
```

### Devs Infrastructure

```
api                | Central API Gateway             | -
  ↳ api-front      | API docs / Swagger UI           | SvelteKit 5 + SCSS
  ↳ api-app        | Flask API server                | Python:Flask
  ↳ api-db_file0   | Aggregated JSONs from all apps  | Hybrid:JSON/SQLite

cache              | In-Memory Cache                 | -
  ↳ cache-app      | Session/cache data store        | Redis
```




### Service URLs

```
Service        | Public URL                   | Container Name     | Port
───────────────┼──────────────────────────────┼────────────────────┼───────
Proxy Admin    | (internal)                   | proxy-app          | :81
Auth           | auth.diegonmarcos.com        | authelia-app       | :9091
OAuth2         | (internal redirect)          | oauth2-app         | :4180
Mail           | mail.diegonmarcos.com        | mail-front         | :8080
Sync           | sync.diegonmarcos.com        | sync-front         | :8384
Drive          | drive.diegonmarcos.com       | drive-front        | :5572
Vault          | vault.diegonmarcos.com       | vault-app          | :8081
Photos         | photos.diegonmarcos.com      | photo-front        | :2342
Git            | git.diegonmarcos.com         | git-app            | :3000
Analytics      | analytics.diegonmarcos.com   | analytics-front    | :8080
Terminal       | terminal.diegonmarcos.com    | terminal-front     | :3000
Cloud          | cloud.diegonmarcos.com       | cloud-front        | :5000
Cloud API      | api.diegonmarcos.com         | api-app            | :5001
n8n Infra      | n8n.diegonmarcos.com         | infra-app          | :5678
n8n AI         | n8n-ai.diegonmarcos.com      | ai-app             | :5679
AI Chat        | chat.diegonmarcos.com        | chat-app           | :3000
VPN            | vpn.diegonmarcos.com         | vpn-front          | :51821
```

---
