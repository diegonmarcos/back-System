#!/usr/bin/env python3
"""
cloud_json_export.py - Export cloud JSON files to markdown

Usage:
    python cloud_json_export.py           # Export both arch and monitor
    python cloud_json_export.py arch      # Export architecture only
    python cloud_json_export.py monitor   # Export monitor only
    python cloud_json_export.py -h        # Show help
"""

import json
import sys
from pathlib import Path
from datetime import datetime

SCRIPT_DIR = Path(__file__).parent

# File paths
ARCH_JSON = SCRIPT_DIR / "cloud_architecture.json"
ARCH_MD = SCRIPT_DIR / "cloud_architecture.md"
MONITOR_JSON = SCRIPT_DIR / "cloud_monitor.json"
MONITOR_MD = SCRIPT_DIR / "cloud_monitor.md"
API_JSON = SCRIPT_DIR / "cloud_api.json"
API_MD = SCRIPT_DIR / "cloud_api.md"
OPENAPI_JSON = SCRIPT_DIR / "openapi.json"
OPENAPI_YAML = SCRIPT_DIR / "openapi.yaml"


def load_json(path: Path) -> dict:
    with open(path, "r") as f:
        return json.load(f)


def fmt(value) -> str:
    """Format value for display, handling None."""
    if value is None:
        return "-"
    if isinstance(value, bool):
        return "Yes" if value else "No"
    return str(value)


def table(headers: list[str], rows: list[list[str]]) -> str:
    """Generate a markdown table."""
    if not rows:
        return "*No data*\n"

    widths = [len(h) for h in headers]
    for row in rows:
        for i, cell in enumerate(row):
            if i < len(widths):
                widths[i] = max(widths[i], len(str(cell)))

    lines = []
    lines.append("| " + " | ".join(h.ljust(widths[i]) for i, h in enumerate(headers)) + " |")
    lines.append("| " + " | ".join("-" * widths[i] for i in range(len(headers))) + " |")
    for row in rows:
        lines.append("| " + " | ".join(str(cell).ljust(widths[i]) for i, cell in enumerate(row)) + " |")

    return "\n".join(lines) + "\n"


# =============================================================================
# ARCHITECTURE EXPORT
# =============================================================================

def arch_part1(data: dict) -> str:
    output = []
    output.append("## Part I: Overview\n")
    part1 = data.get("partI_overview", {})

    output.append("### Cloud Providers\n")
    providers = part1.get("providers", {})
    rows = []
    for pid, p in providers.items():
        cli = p.get("cli", {})
        rows.append([p.get("name", pid), p.get("tier", ""), p.get("region", ""),
                     f"[Console]({p.get('consoleUrl', '#')})", f"`{cli.get('name', '')}`"])
    output.append(table(["Provider", "Tier", "Region", "Console", "CLI"], rows))

    output.append("### Active Services Summary\n")
    services = part1.get("activeServicesSummary", [])
    rows = [[s.get("name", ""), s.get("url", ""), s.get("availability", "")] for s in services]
    output.append(table(["Service", "URL", "Availability"], rows))

    proxy = part1.get("proxyAdmin", {})
    if proxy:
        output.append("### Central Proxy\n")
        output.append(f"**Name**: {proxy.get('name', 'N/A')}\n")
        output.append(f"**URL**: {proxy.get('url', 'N/A')}\n")
        output.append(f"**VM**: {proxy.get('vmId', 'N/A')}\n")

    return "\n".join(output)


def arch_part2(data: dict) -> str:
    output = []
    output.append("## Part II: Infrastructure\n")
    part2 = data.get("partII_infrastructure", {})

    output.append("### VM Categories\n")
    cats = part2.get("vmCategories", {})
    rows = [[cid, c.get("name", ""), c.get("description", "")] for cid, c in cats.items()]
    output.append(table(["ID", "Name", "Description"], rows))

    output.append("### Virtual Machines\n")
    vms = part2.get("virtualMachines", {})
    rows = []
    for vmid, vm in vms.items():
        specs = vm.get("specs", {})
        network = vm.get("network", {})
        cost = vm.get("cost", {})
        monthly = cost.get("monthly", 0) if isinstance(cost, dict) else cost
        rows.append([vmid, vm.get("displayName", vm.get("name", "")), vm.get("provider", ""),
                     network.get("publicIp", ""), specs.get("ram", ""), specs.get("storage", ""),
                     vm.get("availability", "24/7"), f"${monthly}/mo"])
    output.append(table(["VM ID", "Name", "Provider", "Public IP", "RAM", "Storage", "Availability", "Cost"], rows))

    output.append("### Service Categories\n")
    scats = part2.get("serviceCategories", {})
    rows = [[cid, c.get("name", ""), c.get("description", "")] for cid, c in scats.items()]
    output.append(table(["ID", "Name", "Description"], rows))

    output.append("### Services Registry\n")
    services = part2.get("services", {})
    rows = []
    for sid, s in services.items():
        urls = s.get("urls", {})
        main_url = list(urls.values())[0] if urls else ""
        rows.append([sid, s.get("displayName", ""), s.get("category", ""), s.get("vmId", ""), main_url])
    output.append(table(["Service ID", "Name", "Category", "VM", "URL"], rows))

    output.append("### Docker Networks\n")
    networks = part2.get("dockerNetworks", {})
    rows = [[nid, n.get("vmId", ""), n.get("subnet", ""), n.get("purpose", "")] for nid, n in networks.items()]
    output.append(table(["Network", "VM", "Subnet", "Purpose"], rows))

    output.append("### VM Ports\n")
    rows = []
    for vmid, vm in vms.items():
        ports = vm.get("ports", {})
        external = ", ".join(map(str, ports.get("external", []))) or "-"
        internal = ", ".join(map(str, ports.get("internal", []))) or "-"
        rows.append([vmid, external, internal])
    output.append(table(["VM", "External Ports", "Internal Ports"], rows))

    return "\n".join(output)


def arch_part3(data: dict) -> str:
    output = []
    output.append("## Part III: Security\n")
    part3 = data.get("partIII_security", {})

    domains = part3.get("domains", {})
    output.append("### Domain Configuration\n")
    output.append(f"**Primary Domain**: {domains.get('primary', 'N/A')}\n")
    output.append(f"**Registrar**: {domains.get('registrar', 'N/A')}\n")
    ns = domains.get("nameservers", [])
    if ns:
        output.append(f"**Nameservers**: {', '.join(ns)}\n")

    output.append("\n### Subdomain Routing\n")
    subdomains = domains.get("subdomains", {})
    rows = []
    for subdomain, info in subdomains.items():
        rows.append([subdomain, info.get("service", ""), info.get("vmId", info.get("hosting", "")),
                     info.get("proxyVia", "direct"), info.get("auth", "none"),
                     "Yes" if info.get("ssl", False) else "No"])
    output.append(table(["Domain", "Service", "VM/Host", "Proxy Via", "Auth", "SSL"], rows))

    output.append("### Firewall Rules\n")
    rules = part3.get("firewallRules", {})
    rows = []
    for vmid, rule_list in rules.items():
        for r in rule_list:
            rows.append([vmid, r.get("port", ""), r.get("protocol", ""), r.get("service", "")])
    output.append(table(["VM", "Port", "Protocol", "Service"], rows))

    output.append("### Authentication Methods\n")
    auth = part3.get("authentication", {})
    methods = auth.get("methods", {})
    rows = []
    for method, info in methods.items():
        services = ", ".join(info.get("services", []))
        rows.append([method, info.get("description", ""), services])
    output.append(table(["Method", "Description", "Services"], rows))

    authelia = auth.get("authelia", {})
    if authelia:
        output.append("\n### Authelia OIDC Endpoints\n")
        output.append(f"**Issuer**: {authelia.get('issuer', 'N/A')}\n")
        for name, url in authelia.get("endpoints", {}).items():
            output.append(f"- **{name}**: `{url}`\n")

    return "\n".join(output)


def arch_part4(data: dict) -> str:
    output = []
    output.append("## Part IV: Data\n")
    part4 = data.get("partIV_data", {})

    output.append("### Databases\n")
    dbs = part4.get("databases", {})
    rows = [[dbid, db.get("technology", ""), db.get("service", ""), db.get("vmId", ""), db.get("storage", "")]
            for dbid, db in dbs.items()]
    output.append(table(["Database", "Technology", "Service", "VM", "Storage"], rows))

    output.append("### Object Storage\n")
    storage = part4.get("objectStorage", {})
    rows = []
    for sid, s in storage.items():
        for bid, b in s.get("buckets", {}).items():
            rows.append([bid, s.get("provider", ""), b.get("size", ""), b.get("contents", "")])
    output.append(table(["Bucket", "Provider", "Size", "Contents"], rows))

    output.append("### Rclone Remotes\n")
    remotes = part4.get("rcloneRemotes", {})
    rows = [[rid, r.get("type", ""), r.get("purpose", "")] for rid, r in remotes.items()]
    output.append(table(["Remote", "Type", "Purpose"], rows))

    return "\n".join(output)


def arch_part5(data: dict) -> str:
    output = []
    output.append("## Part V: Operations\n")
    part5 = data.get("partV_operations", {})

    output.append("### SSH Commands\n")
    ssh = part5.get("sshCommands", {})
    rows = [[vmid, f"`{cmd}`"] for vmid, cmd in ssh.items()]
    output.append(table(["VM", "SSH Command"], rows))

    output.append("### Docker Commands\n")
    docker = part5.get("dockerCommands", {})
    rows = [[name, f"`{cmd}`"] for name, cmd in docker.items()]
    output.append(table(["Action", "Command"], rows))

    output.append("### Monitoring Commands\n")
    monitoring = part5.get("monitoringCommands", {})
    rows = [[name, f"`{cmd}`"] for name, cmd in monitoring.items()]
    output.append(table(["Action", "Command"], rows))

    output.append("### Status Legend\n")
    legend = part5.get("statusLegend", {})
    rows = [[status, info.get("color", ""), info.get("description", "")] for status, info in legend.items()]
    output.append(table(["Status", "Color", "Description"], rows))

    return "\n".join(output)


def arch_part6(data: dict) -> str:
    output = []
    output.append("## Part VI: Reference\n")
    part6 = data.get("partVI_reference", {})

    output.append("### Monthly Costs Summary\n")
    costs = part6.get("costs", {})
    total = costs.get("total", {})
    output.append(f"**Infrastructure**: ${total.get('infra', 0)}/mo\n")
    output.append(f"**AI Services**: ${total.get('ai', 0)}/mo\n")
    output.append(f"**Total**: ${total.get('total', 0)}/mo {total.get('currency', 'USD')}\n")

    output.append("\n### Infrastructure Costs\n")
    infra = costs.get("infra", {})
    rows = []
    for provider, info in infra.items():
        tier = info.get("tier", "")
        monthly = info.get("monthly", 0)
        paid = info.get("paidVms", {})
        if paid:
            for vm, cost in paid.items():
                rows.append([provider, vm, tier, f"${cost}/mo"])
        else:
            rows.append([provider, "-", tier, f"${monthly}/mo"])
    output.append(table(["Provider", "VM", "Tier", "Cost"], rows))

    output.append("### Wake-on-Demand Configuration\n")
    wod = part6.get("wakeOnDemand", {})
    output.append(f"**Enabled**: {'Yes' if wod.get('enabled', False) else 'No'}\n")
    output.append(f"**Target VM**: {wod.get('targetVm', 'N/A')}\n")
    output.append(f"**Health Check**: {wod.get('healthCheckUrl', 'N/A')}\n")
    output.append(f"**Idle Timeout**: {wod.get('idleTimeoutSeconds', 0)} seconds\n")
    services = wod.get("services", [])
    if services:
        output.append(f"**Services**: {', '.join(services)}\n")

    output.append("\n### Port Mapping\n")
    ports = part6.get("portMapping", [])
    rows = [[p.get("service", ""), str(p.get("internal", "")), str(p.get("external", "")), p.get("notes", "")]
            for p in ports]
    output.append(table(["Service", "Internal Port", "External Port", "Notes"], rows))

    output.append("### Docker Images\n")
    images = part6.get("dockerImages", [])
    rows = [[img.get("service", ""), img.get("image", ""), img.get("version", "")] for img in images]
    output.append(table(["Service", "Image", "Version"], rows))

    return "\n".join(output)


def export_architecture() -> int:
    """Export architecture JSON to markdown."""
    print(f"Loading: {ARCH_JSON}")
    data = load_json(ARCH_JSON)

    version = data.get("version", "0.0.0")
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M")

    header = f"""# Cloud Infrastructure Tables

> **Version**: {version}
> **Generated**: {timestamp}
> **Source**: `cloud_architecture.json`

This document is auto-generated from `cloud_architecture.json` using `cloud_json_export.py`.
Do not edit manually - changes will be overwritten.

---

"""

    sections = [header, arch_part1(data), arch_part2(data), arch_part3(data),
                arch_part4(data), arch_part5(data), arch_part6(data)]
    markdown = "\n".join(sections)

    print(f"Writing: {ARCH_MD}")
    with open(ARCH_MD, "w") as f:
        f.write(markdown)

    print(f"  -> {len(markdown)} chars, 21 tables")
    return len(markdown)


# =============================================================================
# MONITOR EXPORT
# =============================================================================

def monitor_summary(data: dict) -> str:
    output = []
    output.append("## Summary\n")

    summary = data.get("summary", {})
    rows = [
        ["Total VMs", fmt(summary.get("totalVMs"))],
        ["VMs Online", fmt(summary.get("vmsOnline"))],
        ["Total Endpoints", fmt(summary.get("totalEndpoints"))],
        ["Endpoints Healthy", fmt(summary.get("endpointsHealthy"))],
        ["Total Containers", fmt(summary.get("totalContainers"))],
        ["Containers Running", fmt(summary.get("containersRunning"))],
        ["Last Full Check", fmt(summary.get("lastFullCheck"))],
    ]
    output.append(table(["Metric", "Value"], rows))

    ssl_expiring = summary.get("sslExpiringWithin30Days", [])
    output.append("### SSL Certificates Expiring Soon\n")
    if ssl_expiring:
        rows = [[domain] for domain in ssl_expiring]
        output.append(table(["Domain"], rows))
    else:
        output.append("*None*\n")

    return "\n".join(output)


def monitor_vm_status(data: dict) -> str:
    output = []
    output.append("## VM Status\n")

    vms = data.get("vmStatus", {})
    rows = []
    for vmid, vm in vms.items():
        rows.append([vmid, fmt(vm.get("ip")), fmt(vm.get("pingable")), fmt(vm.get("sshable")),
                     fmt(vm.get("latencyMs")), fmt(vm.get("uptime")), fmt(vm.get("lastCheck"))])
    output.append(table(["VM", "IP", "Pingable", "SSH", "Latency (ms)", "Uptime", "Last Check"], rows))

    output.append("### VM Resources\n")
    rows = []
    for vmid, vm in vms.items():
        rows.append([vmid, fmt(vm.get("loadAvg")), fmt(vm.get("memoryUsedPercent")), fmt(vm.get("diskUsedPercent"))])
    output.append(table(["VM", "Load Avg", "Memory %", "Disk %"], rows))

    output.append("### Wake-on-Demand Status\n")
    rows = []
    for vmid, vm in vms.items():
        wod = vm.get("wakeOnDemand")
        if wod:
            rows.append([vmid, fmt(wod.get("isAwake")), fmt(wod.get("lastWakeTime")),
                         fmt(wod.get("lastSleepTime")), fmt(wod.get("wakeReason"))])
    if rows:
        output.append(table(["VM", "Awake", "Last Wake", "Last Sleep", "Wake Reason"], rows))
    else:
        output.append("*No wake-on-demand VMs*\n")

    return "\n".join(output)


def monitor_endpoint_status(data: dict) -> str:
    output = []
    output.append("## Endpoint Status\n")

    endpoints = data.get("endpointStatus", {})
    rows = []
    for domain, ep in endpoints.items():
        wod = "Yes" if ep.get("wakeOnDemand") else "No"
        rows.append([domain, fmt(ep.get("httpCode")), fmt(ep.get("latencyMs")), fmt(ep.get("sslValid")),
                     fmt(ep.get("sslExpiry")), wod, fmt(ep.get("lastCheck"))])
    output.append(table(["Domain", "HTTP", "Latency (ms)", "SSL Valid", "SSL Expiry", "WoD", "Last Check"], rows))

    return "\n".join(output)


def monitor_container_status(data: dict) -> str:
    output = []
    output.append("## Container Status\n")

    containers = data.get("containerStatus", {})

    output.append("### All Containers\n")
    rows = []
    for vmid, vm_containers in containers.items():
        for container, status in vm_containers.items():
            rows.append([vmid, container, fmt(status.get("running")), fmt(status.get("restarts")),
                         fmt(status.get("memoryMb")), fmt(status.get("cpuPercent"))])
    output.append(table(["VM", "Container", "Running", "Restarts", "Memory (MB)", "CPU %"], rows))

    for vmid, vm_containers in containers.items():
        output.append(f"### {vmid} Containers\n")
        rows = []
        for container, status in vm_containers.items():
            rows.append([container, fmt(status.get("running")), fmt(status.get("restarts")),
                         fmt(status.get("memoryMb")), fmt(status.get("cpuPercent"))])
        output.append(table(["Container", "Running", "Restarts", "Memory (MB)", "CPU %"], rows))

    return "\n".join(output)


def monitor_alerts(data: dict) -> str:
    output = []
    output.append("## Alerts\n")

    alerts = data.get("alerts", [])
    if alerts:
        rows = [[fmt(a.get("timestamp")), fmt(a.get("severity")), fmt(a.get("source")), fmt(a.get("message"))]
                for a in alerts]
        output.append(table(["Timestamp", "Severity", "Source", "Message"], rows))
    else:
        output.append("*No active alerts*\n")

    return "\n".join(output)


def export_monitor() -> int:
    """Export monitor JSON to markdown."""
    print(f"Loading: {MONITOR_JSON}")
    data = load_json(MONITOR_JSON)

    version = data.get("version", "0.0.0")
    last_updated = data.get("lastUpdated") or "Never"
    updated_by = data.get("updatedBy") or "N/A"
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M")

    header = f"""# Cloud Infrastructure Monitor

> **Version**: {version}
> **Generated**: {timestamp}
> **Last Data Update**: {last_updated}
> **Updated By**: {updated_by}
> **Source**: `cloud_monitor.json`

This document is auto-generated from `cloud_monitor.json` using `cloud_json_export.py`.
Do not edit manually - changes will be overwritten.

---

"""

    sections = [header, monitor_summary(data), monitor_vm_status(data),
                monitor_endpoint_status(data), monitor_container_status(data), monitor_alerts(data)]
    markdown = "\n".join(sections)

    print(f"Writing: {MONITOR_MD}")
    with open(MONITOR_MD, "w") as f:
        f.write(markdown)

    print(f"  -> {len(markdown)} chars, 10 tables")
    return len(markdown)


# =============================================================================
# API EXPORT
# =============================================================================

def api_overview(data: dict) -> str:
    output = []
    output.append("## API Overview\n")

    output.append(f"**Title**: {data.get('title', 'N/A')}\n")
    output.append(f"**Version**: {data.get('version', 'N/A')}\n")
    output.append(f"**Description**: {data.get('description', 'N/A')}\n")

    output.append("\n### Servers\n")
    servers = data.get("server", {})
    rows = [[name, s.get("baseUrl", ""), s.get("description", "")] for name, s in servers.items()]
    output.append(table(["Environment", "Base URL", "Description"], rows))

    output.append("### Authentication\n")
    auth = data.get("auth", {})
    output.append(f"**Type**: {auth.get('type', 'N/A')}\n")
    output.append(f"**Provider**: {auth.get('provider', 'N/A')}\n")
    output.append(f"**Token Endpoint**: `{auth.get('tokenEndpoint', 'N/A')}`\n")

    output.append("\n### Auth Scopes\n")
    scopes = auth.get("scopes", {})
    rows = [[scope, desc] for scope, desc in scopes.items()]
    output.append(table(["Scope", "Description"], rows))

    return "\n".join(output)


def api_endpoints_summary(data: dict) -> str:
    output = []
    output.append("## Endpoints Summary\n")

    endpoints = data.get("endpoints", {})
    rows = []
    for category, category_endpoints in endpoints.items():
        desc = category_endpoints.get("_description", "")
        count = len([k for k in category_endpoints.keys() if not k.startswith("_")])
        rows.append([category, desc, str(count)])
    output.append(table(["Category", "Description", "Endpoints"], rows))

    # Index summary
    index = data.get("_index", {})
    output.append(f"\n**Total Endpoints**: {index.get('endpointCount', 'N/A')}\n")

    return "\n".join(output)


def api_endpoints_detail(data: dict) -> str:
    output = []
    output.append("## Endpoints Detail\n")

    endpoints = data.get("endpoints", {})

    for category, category_endpoints in endpoints.items():
        desc = category_endpoints.get("_description", "")
        source = category_endpoints.get("_source", "")

        output.append(f"### {category.upper()}\n")
        if desc:
            output.append(f"*{desc}*\n")
        if source:
            output.append(f"**Source**: `{source}`\n")
        output.append("")

        rows = []
        for ep_name, ep in category_endpoints.items():
            if ep_name.startswith("_"):
                continue
            method = ep.get("method", "GET")
            path = ep.get("path", "")
            auth = ep.get("auth", "read")
            ep_desc = ep.get("description", "")
            rows.append([f"`{method}`", f"`{path}`", auth, ep_desc])

        if rows:
            output.append(table(["Method", "Path", "Auth", "Description"], rows))

    return "\n".join(output)


def api_endpoints_curl(data: dict) -> str:
    output = []
    output.append("## Curl Examples\n")

    endpoints = data.get("endpoints", {})

    for category, category_endpoints in endpoints.items():
        has_curl = False
        curl_rows = []

        for ep_name, ep in category_endpoints.items():
            if ep_name.startswith("_"):
                continue
            curl = ep.get("curl")
            if curl:
                has_curl = True
                curl_rows.append([ep_name, f"`{curl}`"])

        if has_curl:
            output.append(f"### {category}\n")
            output.append(table(["Endpoint", "Curl Command"], curl_rows))

    return "\n".join(output)


def api_schemas(data: dict) -> str:
    output = []
    output.append("## Schemas\n")

    schemas = data.get("schemas", {})

    for schema_name, schema in schemas.items():
        output.append(f"### {schema_name}\n")

        props = schema.get("properties", {})
        required = schema.get("required", [])

        rows = []
        for prop_name, prop in props.items():
            prop_type = prop.get("type", "any")
            if "enum" in prop:
                prop_type = f"enum: {', '.join(prop['enum'])}"
            elif "$ref" in prop:
                prop_type = f"ref: {prop['$ref']}"
            is_required = "Yes" if prop_name in required else "No"
            prop_desc = prop.get("description", "")
            rows.append([prop_name, prop_type, is_required, prop_desc])

        output.append(table(["Property", "Type", "Required", "Description"], rows))

    return "\n".join(output)


def api_errors(data: dict) -> str:
    output = []
    output.append("## Error Codes\n")

    errors = data.get("errors", {})
    rows = [[code, e.get("code", ""), e.get("message", "")] for code, e in errors.items()]
    output.append(table(["HTTP Code", "Error Code", "Message"], rows))

    output.append("### Rate Limits\n")
    limits = data.get("rateLimits", {})
    rows = [[name, str(l.get("requests", "")), l.get("window", "")] for name, l in limits.items()]
    output.append(table(["Category", "Requests", "Window"], rows))

    return "\n".join(output)


def api_data_sources(data: dict) -> str:
    output = []
    output.append("## Data Sources Mapping\n")

    index = data.get("_index", {})
    sources = index.get("dataSources", {})

    for source, endpoints in sources.items():
        output.append(f"### {source}\n")
        if isinstance(endpoints, list):
            for ep in endpoints:
                output.append(f"- `{ep}`\n")
        output.append("")

    return "\n".join(output)


def export_api() -> int:
    """Export API JSON to markdown."""
    print(f"Loading: {API_JSON}")
    data = load_json(API_JSON)

    version = data.get("version", "0.0.0")
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M")

    header = f"""# Cloud Infrastructure API Reference

> **Version**: {version}
> **Generated**: {timestamp}
> **Source**: `cloud_api.json`

This document is auto-generated from `cloud_api.json` using `cloud_json_md.py`.
Do not edit manually - changes will be overwritten.

---

"""

    sections = [header, api_overview(data), api_endpoints_summary(data),
                api_endpoints_detail(data), api_endpoints_curl(data),
                api_schemas(data), api_errors(data), api_data_sources(data)]
    markdown = "\n".join(sections)

    print(f"Writing: {API_MD}")
    with open(API_MD, "w") as f:
        f.write(markdown)

    endpoint_count = data.get("_index", {}).get("endpointCount", 0)
    print(f"  -> {len(markdown)} chars, {endpoint_count} endpoints documented")
    return len(markdown)


# =============================================================================
# MAIN
# =============================================================================

def show_help():
    help_text = """
cloud_json_export.py - Export cloud JSON files to markdown

USAGE:
    python cloud_json_export.py              Export all (architecture, monitor, api)
    python cloud_json_export.py arch         Export architecture only
    python cloud_json_export.py monitor      Export monitor only
    python cloud_json_export.py api          Export API reference only
    python cloud_json_export.py -h, --help   Show this help

FILES:
    Input:
        cloud_architecture.json    Static infrastructure configuration
        cloud_monitor.json         Dynamic runtime monitoring data
        cloud_api.json             API endpoint definitions

    Output:
        cloud_architecture.md      21 tables (Part I-VI)
        cloud_monitor.md           10 tables (Summary, VMs, Endpoints, Containers, Alerts)
        cloud_api.md               API reference (endpoints, schemas, errors)

EXAMPLES:
    python cloud_json_export.py              # Export all
    python cloud_json_export.py arch         # Only architecture
    python cloud_json_export.py monitor      # Only monitor
    python cloud_json_export.py api          # Only API reference
"""
    print(help_text)


def main():
    args = sys.argv[1:]

    if not args:
        # No args: export all
        print("Exporting all...\n")
        export_architecture()
        print()
        export_monitor()
        print()
        export_api()
        print("\nDone!")
        return

    cmd = args[0].lower()

    if cmd in ["-h", "--help", "help"]:
        show_help()
    elif cmd == "arch":
        export_architecture()
        print("\nDone!")
    elif cmd == "monitor":
        export_monitor()
        print("\nDone!")
    elif cmd == "api":
        export_api()
        print("\nDone!")
    else:
        print(f"Unknown command: {cmd}")
        print("Use -h for help")
        sys.exit(1)


if __name__ == "__main__":
    main()
