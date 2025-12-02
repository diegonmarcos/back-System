#!/usr/bin/env python3
"""
Cloud Infrastructure Dashboard
A Python TUI for monitoring and managing cloud VMs and services

Version: 5.0.0
Author: Diego Nepomuceno Marcos
Last Updated: 2025-12-02

Dependencies: paramiko (optional for SSH), requests (optional for HTTP checks)
Data Source: cloud-infrastructure.json
"""

import json
import os
import subprocess
import sys
import shutil
from pathlib import Path
from typing import Optional, Dict, Any, List

# =============================================================================
# CONFIGURATION
# =============================================================================

VERSION = "5.0.0"
SCRIPT_DIR = Path(__file__).parent.resolve()
CONFIG_FILE = SCRIPT_DIR / "cloud-infrastructure.json"

# Timeouts (seconds)
SSH_TIMEOUT = 5
PING_TIMEOUT = 2
CURL_TIMEOUT = 5

# ANSI Colors
class Colors:
    RED = '\033[0;31m'
    GREEN = '\033[0;32m'
    YELLOW = '\033[0;33m'
    BLUE = '\033[0;34m'
    MAGENTA = '\033[0;35m'
    CYAN = '\033[0;36m'
    BOLD = '\033[1m'
    DIM = '\033[2m'
    RESET = '\033[0m'

C = Colors()

# =============================================================================
# CONFIG LOADING
# =============================================================================

_config: Optional[Dict[str, Any]] = None

def load_config() -> Dict[str, Any]:
    """Load and cache the JSON configuration."""
    global _config
    if _config is None:
        if not CONFIG_FILE.exists():
            print(f"{C.RED}Error: Config not found: {CONFIG_FILE}{C.RESET}")
            sys.exit(1)
        with open(CONFIG_FILE, 'r') as f:
            _config = json.load(f)
    return _config

def get_vm_ids() -> List[str]:
    """Get all VM IDs."""
    return list(load_config().get('virtualMachines', {}).keys())

def get_vm_ids_by_category(category: str) -> List[str]:
    """Get VM IDs filtered by category."""
    vms = load_config().get('virtualMachines', {})
    return [k for k, v in vms.items() if v.get('category') == category]

def get_vm_categories() -> List[str]:
    """Get all VM category IDs."""
    return list(load_config().get('vmCategories', {}).keys())

def get_vm_category_name(category: str) -> str:
    """Get VM category display name."""
    return load_config().get('vmCategories', {}).get(category, {}).get('name', category)

def get_vm(vm_id: str, prop: str = None) -> Any:
    """Get VM data or specific property."""
    vm = load_config().get('virtualMachines', {}).get(vm_id, {})
    if prop is None:
        return vm

    # Navigate nested properties like ".network.publicIp"
    props = prop.strip('.').split('.')
    result = vm
    for p in props:
        if isinstance(result, dict):
            result = result.get(p)
        else:
            return None
    return result

def get_service_ids() -> List[str]:
    """Get all service IDs."""
    return list(load_config().get('services', {}).keys())

def get_service_ids_by_category(category: str) -> List[str]:
    """Get service IDs filtered by category."""
    svcs = load_config().get('services', {})
    return [k for k, v in svcs.items() if v.get('category') == category]

def get_service_categories() -> List[str]:
    """Get all service category IDs."""
    return list(load_config().get('serviceCategories', {}).keys())

def get_service_category_name(category: str) -> str:
    """Get service category display name."""
    return load_config().get('serviceCategories', {}).get(category, {}).get('name', category)

def get_svc(svc_id: str, prop: str = None) -> Any:
    """Get service data or specific property."""
    svc = load_config().get('services', {}).get(svc_id, {})
    if prop is None:
        return svc

    # Navigate nested properties
    props = prop.strip('.').split('.')
    result = svc
    for p in props:
        if isinstance(result, dict):
            result = result.get(p)
        else:
            return None
    return result

def expand_path(path: str) -> str:
    """Expand ~ in paths."""
    if path and path.startswith('~'):
        return os.path.expanduser(path)
    return path or ''

# =============================================================================
# HEALTH CHECK FUNCTIONS
# =============================================================================

def check_ping(host: str) -> bool:
    """Check if host responds to ping."""
    try:
        result = subprocess.run(
            ['ping', '-c', '1', '-W', str(PING_TIMEOUT), host],
            capture_output=True,
            timeout=PING_TIMEOUT + 1
        )
        return result.returncode == 0
    except (subprocess.TimeoutExpired, Exception):
        return False

def check_ssh(host: str, user: str, key_path: str) -> bool:
    """Check if SSH connection is possible."""
    try:
        result = subprocess.run(
            [
                'ssh', '-i', key_path,
                '-o', 'BatchMode=yes',
                '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                '-o', 'StrictHostKeyChecking=no',
                f'{user}@{host}', 'true'
            ],
            capture_output=True,
            timeout=SSH_TIMEOUT + 2
        )
        return result.returncode == 0
    except (subprocess.TimeoutExpired, Exception):
        return False

def check_http(url: str) -> bool:
    """Check if HTTP endpoint returns success status."""
    if not url or url == 'null':
        return False

    try:
        result = subprocess.run(
            [
                'curl', '-s', '-o', '/dev/null', '-w', '%{http_code}',
                '--connect-timeout', str(CURL_TIMEOUT),
                '--max-time', str(CURL_TIMEOUT + 2),
                url
            ],
            capture_output=True,
            text=True,
            timeout=CURL_TIMEOUT + 5
        )
        code = result.stdout.strip()
        return code.startswith('2') or code.startswith('3')
    except (subprocess.TimeoutExpired, Exception):
        return False

def get_vm_status(vm_id: str) -> str:
    """Get formatted VM status string."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return f"{C.YELLOW}◐ PENDING{C.RESET}"

    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    if check_ssh(ip, user, key_path):
        return f"{C.GREEN}● ONLINE{C.RESET}"
    elif check_ping(ip):
        return f"{C.YELLOW}◐ NO SSH{C.RESET}"
    else:
        return f"{C.RED}○ OFFLINE{C.RESET}"

def get_vm_ram_percent(vm_id: str) -> str:
    """Get RAM usage percentage via SSH."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return '-'

    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    try:
        result = subprocess.run(
            [
                'ssh', '-i', key_path,
                '-o', 'BatchMode=yes',
                '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                '-o', 'StrictHostKeyChecking=no',
                f'{user}@{ip}',
                "free | awk '/^Mem:/{printf \"%.0f\", $3/$2*100}'"
            ],
            capture_output=True,
            text=True,
            timeout=SSH_TIMEOUT + 2
        )
        if result.returncode == 0:
            return result.stdout.strip() or '-'
    except (subprocess.TimeoutExpired, Exception):
        pass
    return '-'

def get_svc_status(svc_id: str) -> str:
    """Get formatted service status string."""
    status = get_svc(svc_id, 'status')

    if status in ('planned', 'development'):
        return f"{C.BLUE}◑ DEV{C.RESET}"

    url = get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')

    if not url or url == 'null':
        return f"{C.DIM}- N/A{C.RESET}"

    if check_http(url):
        return f"{C.GREEN}● HEALTHY{C.RESET}"
    else:
        return f"{C.RED}✖ ERROR{C.RESET}"

# =============================================================================
# TUI HELPERS
# =============================================================================

def cls():
    """Clear screen."""
    print('\033[2J\033[H', end='')

def hline(width: int = 78, char: str = '-') -> str:
    """Create horizontal line."""
    return char * width

def wait_key():
    """Wait for user input."""
    input(f"\n{C.DIM}Press Enter to continue...{C.RESET}")

def confirm(message: str) -> bool:
    """Ask for confirmation."""
    response = input(f"{C.YELLOW}{message} [y/N]: {C.RESET}").strip().lower()
    return response in ('y', 'yes')

# =============================================================================
# DISPLAY FUNCTIONS
# =============================================================================

def print_header():
    """Print dashboard header."""
    print()
    print(f"  {C.BOLD}{C.CYAN}+{hline(76, '=')}+{C.RESET}")
    print(f"  {C.BOLD}{C.CYAN}|{C.RESET}           CLOUD INFRASTRUCTURE DASHBOARD v{VERSION}                   {C.BOLD}{C.CYAN}|{C.RESET}")
    print(f"  {C.BOLD}{C.CYAN}+{hline(76, '=')}+{C.RESET}")
    print()

def print_vm_table():
    """Print VM status table."""
    print(f"  {C.BOLD}+{hline(76, '-')}+{C.RESET}")
    print(f"  {C.BOLD}| VIRTUAL MACHINES                                                         |{C.RESET}")

    for cat in get_vm_categories():
        cat_name = get_vm_category_name(cat)
        vms = get_vm_ids_by_category(cat)

        if not vms:
            continue

        print(f"  +{hline(74, '-')}+")
        print(f"  {C.BOLD}{C.MAGENTA}| {cat_name:<72} |{C.RESET}")
        print(f"  +{'-'*22}+{'-'*15}+{'-'*10}+{'-'*6}+{'-'*16}+")
        print(f"  | {'NAME':<20} | {'IP':<13} | {'STATUS':<8} | {'RAM%':<4} | {'TYPE':<14} |")
        print(f"  +{'-'*22}+{'-'*15}+{'-'*10}+{'-'*6}+{'-'*16}+")

        for vm_id in vms:
            name = (get_vm(vm_id, 'name') or '')[:20]
            ip = (get_vm(vm_id, 'network.publicIp') or '')[:13]
            vm_type = (get_vm(vm_id, 'instanceType') or '')[:14]
            status = get_vm_status(vm_id)
            ram = get_vm_ram_percent(vm_id)
            ram_display = f"{ram}%" if ram != '-' else '-'

            # Status contains ANSI codes, need special handling
            print(f"  | {name:<20} | {ip:<13} | {status} | {ram_display:>4} | {vm_type:<14} |")

    print(f"  +{'-'*22}+{'-'*15}+{'-'*10}+{'-'*6}+{'-'*16}+")
    print()

def print_svc_table():
    """Print service status table."""
    print(f"  {C.BOLD}+{hline(76, '-')}+{C.RESET}")
    print(f"  {C.BOLD}| SERVICES                                                                  |{C.RESET}")

    for cat in get_service_categories():
        cat_name = get_service_category_name(cat)
        svcs = get_service_ids_by_category(cat)

        if not svcs:
            continue

        print(f"  +{hline(74, '-')}+")
        print(f"  {C.BOLD}{C.MAGENTA}| {cat_name:<72} |{C.RESET}")
        print(f"  +{'-'*22}+{'-'*38}+{'-'*10}+")
        print(f"  | {'NAME':<20} | {'URL':<36} | {'STATUS':<8} |")
        print(f"  +{'-'*22}+{'-'*38}+{'-'*10}+")

        for svc_id in svcs:
            name = (get_svc(svc_id, 'name') or '')[:20]
            url = get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin') or ''

            if url and url != 'null':
                short_url = url.replace('https://', '').replace('http://', '')[:36]
            else:
                short_url = '-'

            status = get_svc_status(svc_id)

            print(f"  | {name:<20} | {short_url:<36} | {status} |")

    print(f"  +{'-'*22}+{'-'*38}+{'-'*10}+")
    print()

def print_menu():
    """Print command menu."""
    print(f"  {C.BOLD}+{hline(76, '-')}+{C.RESET}")
    print(f"  {C.BOLD}| COMMANDS                                                                  |{C.RESET}")
    print(f"  +{hline(74, '-')}+")
    print(f"  |                                                                          |")
    print(f"  |   {C.CYAN}[1]{C.RESET} VM Details        {C.CYAN}[4]{C.RESET} Restart Container   {C.CYAN}[7]{C.RESET} SSH to VM           |")
    print(f"  |   {C.CYAN}[2]{C.RESET} Container Status  {C.CYAN}[5]{C.RESET} View Logs           {C.CYAN}[8]{C.RESET} Open URL            |")
    print(f"  |   {C.CYAN}[3]{C.RESET} Reboot VM         {C.CYAN}[6]{C.RESET} Stop/Start          {C.CYAN}[R]{C.RESET} Refresh             |")
    print(f"  |                                                                          |")
    print(f"  |   {C.CYAN}[S]{C.RESET} Quick Status      {C.CYAN}[Q]{C.RESET} Quit                                        |")
    print(f"  |                                                                          |")
    print(f"  +{hline(74, '-')}+")
    print()

def display_dashboard():
    """Display full dashboard."""
    cls()
    print_header()
    print_vm_table()
    print_svc_table()
    print_menu()

# =============================================================================
# SELECTION HELPERS
# =============================================================================

def select_vm(filter_type: str = 'all') -> Optional[str]:
    """Interactive VM selection. Returns VM ID or None."""
    print(f"\n{C.BOLD}Select VM:{C.RESET}")

    options = []
    for vm_id in get_vm_ids():
        ip = get_vm(vm_id, 'network.publicIp')
        name = get_vm(vm_id, 'name')

        if filter_type == 'online' and ip == 'pending':
            continue
        elif filter_type == 'pending' and ip != 'pending':
            continue

        options.append((vm_id, name, ip))

    for i, (vm_id, name, ip) in enumerate(options, 1):
        print(f"  [{i}] {name} ({ip})")

    print("  [0] Cancel")

    try:
        choice = input("Choice: ").strip()
        if not choice or choice == '0':
            return None
        idx = int(choice) - 1
        if 0 <= idx < len(options):
            return options[idx][0]
    except (ValueError, IndexError):
        pass

    return None

def select_service(filter_type: str = 'all') -> Optional[str]:
    """Interactive service selection. Returns service ID or None."""
    print(f"\n{C.BOLD}Select Service:{C.RESET}")

    options = []
    for svc_id in get_service_ids():
        name = get_svc(svc_id, 'name')
        container = get_svc(svc_id, 'docker.containerName')
        status = get_svc(svc_id, 'status')

        if filter_type == 'docker':
            if not container or container == 'null':
                continue
        elif filter_type == 'active':
            if status in ('planned', 'development'):
                continue

        options.append((svc_id, name, container))

    for i, (svc_id, name, container) in enumerate(options, 1):
        if container and container != 'null':
            print(f"  [{i}] {name} (container: {container})")
        else:
            print(f"  [{i}] {name}")

    print("  [0] Cancel")

    try:
        choice = input("Choice: ").strip()
        if not choice or choice == '0':
            return None
        idx = int(choice) - 1
        if 0 <= idx < len(options):
            return options[idx][0]
    except (ValueError, IndexError):
        pass

    return None

# =============================================================================
# ACTIONS
# =============================================================================

def action_vm_details():
    """Show detailed VM information."""
    vm_id = select_vm('online')
    if not vm_id:
        return

    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')
    name = get_vm(vm_id, 'name')

    cls()
    print(f"\n{C.BOLD}{C.CYAN}=== VM Details: {name} ==={C.RESET}\n")

    print(f"{C.BOLD}Local Config:{C.RESET}")
    print(f"  ID:       {vm_id}")
    print(f"  IP:       {ip}")
    print(f"  User:     {user}")
    print(f"  Provider: {get_vm(vm_id, 'provider')}")
    print(f"  Category: {get_vm(vm_id, 'category')}")
    print(f"  Type:     {get_vm(vm_id, 'instanceType')}\n")

    print(f"{C.BOLD}Remote System Info:{C.RESET}")

    remote_cmd = '''
echo "  Hostname: $(hostname)"
echo "  Uptime:   $(uptime -p 2>/dev/null || uptime)"
echo "  Kernel:   $(uname -r)"
echo ""
echo "Resources:"
echo "  CPU:      $(nproc) cores"
echo "  RAM:      $(free -h | awk '/^Mem:/{print $3 "/" $2}')"
echo "  RAM %:    $(free | awk '/^Mem:/{printf "%.1f%%", $3/$2*100}')"
echo "  Disk:     $(df -h / | awk 'NR==2{print $3 "/" $2}')"
echo ""
echo "Docker:"
echo "  Running:  $(sudo docker ps -q 2>/dev/null | wc -l) containers"
'''

    try:
        result = subprocess.run(
            ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
             '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}', remote_cmd],
            capture_output=True, text=True, timeout=SSH_TIMEOUT + 5
        )
        print(result.stdout)
    except Exception:
        print(f"  {C.RED}Failed to connect{C.RESET}")

    wait_key()

def action_container_status():
    """Show container status on a VM."""
    vm_id = select_vm('online')
    if not vm_id:
        return

    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')
    name = get_vm(vm_id, 'name')

    cls()
    print(f"\n{C.BOLD}{C.CYAN}=== Containers on {name} ==={C.RESET}\n")

    try:
        result = subprocess.run(
            ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
             '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}',
             'sudo docker ps -a --format "table {{.Names}}\t{{.Status}}\t{{.Ports}}"'],
            capture_output=True, text=True, timeout=SSH_TIMEOUT + 5
        )
        print(result.stdout)
    except Exception:
        print(f"{C.RED}Failed to connect{C.RESET}")

    wait_key()

def action_reboot_vm():
    """Reboot a VM."""
    vm_id = select_vm('online')
    if not vm_id:
        return

    name = get_vm(vm_id, 'name')
    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    print()
    if confirm(f"REBOOT {name} ({ip})?"):
        print(f"{C.YELLOW}Sending reboot command...{C.RESET}")
        try:
            subprocess.run(
                ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                 '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}', 'sudo reboot'],
                capture_output=True, timeout=SSH_TIMEOUT + 2
            )
        except Exception:
            pass
        print(f"{C.GREEN}Reboot signal sent.{C.RESET}")
        wait_key()

def action_restart_container():
    """Restart a Docker container."""
    svc_id = select_service('docker')
    if not svc_id:
        return

    name = get_svc(svc_id, 'name')
    container = get_svc(svc_id, 'docker.containerName')
    vm_id = get_svc(svc_id, 'vmId')
    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    print()
    if confirm(f"Restart container '{container}' ({name})?"):
        print(f"{C.YELLOW}Restarting...{C.RESET}")
        try:
            subprocess.run(
                ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                 '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}',
                 f'sudo docker restart {container}'],
                capture_output=True, timeout=60
            )
            print(f"{C.GREEN}Done.{C.RESET}")
        except Exception:
            print(f"{C.RED}Failed{C.RESET}")
        wait_key()

def action_view_logs():
    """View container logs."""
    svc_id = select_service('docker')
    if not svc_id:
        return

    container = get_svc(svc_id, 'docker.containerName')
    vm_id = get_svc(svc_id, 'vmId')
    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    lines = input("Lines to show [50]: ").strip() or '50'

    cls()
    print(f"\n{C.BOLD}{C.CYAN}=== Logs: {container} (last {lines} lines) ==={C.RESET}\n")

    try:
        result = subprocess.run(
            ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
             '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}',
             f'sudo docker logs --tail {lines} {container}'],
            capture_output=True, text=True, timeout=30
        )
        print(result.stdout)
        print(result.stderr)
    except Exception as e:
        print(f"{C.RED}Failed to get logs: {e}{C.RESET}")

    wait_key()

def action_stop_start():
    """Stop or start a container."""
    svc_id = select_service('docker')
    if not svc_id:
        return

    container = get_svc(svc_id, 'docker.containerName')
    vm_id = get_svc(svc_id, 'vmId')
    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    print("\n  [1] Start\n  [2] Stop")
    action = input("Action: ").strip()

    cmd = 'start' if action == '1' else 'stop' if action == '2' else None
    if not cmd:
        return

    if confirm(f"{cmd} container '{container}'?"):
        print(f"{C.YELLOW}Executing docker {cmd}...{C.RESET}")
        try:
            subprocess.run(
                ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                 '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}',
                 f'sudo docker {cmd} {container}'],
                capture_output=True, timeout=60
            )
            print(f"{C.GREEN}Done.{C.RESET}")
        except Exception:
            print(f"{C.RED}Failed{C.RESET}")
        wait_key()

def action_ssh():
    """Open interactive SSH session."""
    vm_id = select_vm('online')
    if not vm_id:
        return

    ip = get_vm(vm_id, 'network.publicIp')
    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')
    name = get_vm(vm_id, 'name')

    print(f"\n{C.CYAN}Connecting to {name}...{C.RESET}")
    print(f"{C.DIM}Type 'exit' to return{C.RESET}\n")

    # Run SSH interactively
    os.system(f'ssh -i {key_path} -o StrictHostKeyChecking=no {user}@{ip}')

def action_open_url():
    """Open service URL in browser."""
    svc_id = select_service('active')
    if not svc_id:
        return

    url = get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')

    if not url or url == 'null':
        print(f"{C.YELLOW}No URL available.{C.RESET}")
        wait_key()
        return

    print(f"{C.CYAN}Opening {url}...{C.RESET}")

    # Try to open URL
    if shutil.which('xdg-open'):
        subprocess.Popen(['xdg-open', url], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    elif shutil.which('open'):
        subprocess.Popen(['open', url], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    else:
        print(f"{C.YELLOW}No browser opener. URL: {url}{C.RESET}")
        wait_key()
        return

    import time
    time.sleep(1)

def action_quick_status():
    """Show quick status summary."""
    print(f"\n{C.BOLD}{C.CYAN}=== Quick Status ==={C.RESET}\n")

    for cat in get_vm_categories():
        cat_name = get_vm_category_name(cat)
        vms = get_vm_ids_by_category(cat)
        if not vms:
            continue

        print(f"{C.BOLD}{C.MAGENTA}{cat_name} VMs:{C.RESET}")
        for vm_id in vms:
            name = get_vm(vm_id, 'name')
            ip = get_vm(vm_id, 'network.publicIp')
            status = get_vm_status(vm_id)
            ram = get_vm_ram_percent(vm_id)

            if ram == '-':
                print(f"  {name:<25} {ip:<16} {status}")
            else:
                print(f"  {name:<25} {ip:<16} {status} RAM: {ram}%")
        print()

    for cat in get_service_categories():
        cat_name = get_service_category_name(cat)
        svcs = get_service_ids_by_category(cat)
        if not svcs:
            continue

        print(f"{C.BOLD}{C.MAGENTA}{cat_name} Services:{C.RESET}")
        for svc_id in svcs:
            name = get_svc(svc_id, 'name')
            status = get_svc_status(svc_id)
            print(f"  {name:<25} {status}")
        print()

    wait_key()

# =============================================================================
# CLI MODE
# =============================================================================

def cli_status():
    """Print status for CLI mode (no colors)."""
    print("Cloud Infrastructure Status")
    print("=" * 28)
    print()

    for cat in get_vm_categories():
        cat_name = get_vm_category_name(cat)
        vms = get_vm_ids_by_category(cat)
        if not vms:
            continue

        print(f"{cat_name} VMs:")
        for vm_id in vms:
            name = get_vm(vm_id, 'name')
            ip = get_vm(vm_id, 'network.publicIp')

            if ip == 'pending':
                print(f"  {name}: PENDING")
            else:
                user = get_vm(vm_id, 'ssh.user')
                key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')
                if check_ssh(ip, user, key_path):
                    print(f"  {name} ({ip}): ONLINE")
                else:
                    print(f"  {name} ({ip}): OFFLINE")
        print()

    for cat in get_service_categories():
        cat_name = get_service_category_name(cat)
        svcs = get_service_ids_by_category(cat)
        if not svcs:
            continue

        print(f"{cat_name} Services:")
        for svc_id in svcs:
            name = get_svc(svc_id, 'name')
            url = get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')
            status = get_svc(svc_id, 'status')

            if status in ('planned', 'development'):
                print(f"  {name}: DEV/PLANNED")
            elif not url or url == 'null':
                print(f"  {name}: NO URL")
            elif check_http(url):
                print(f"  {name}: HEALTHY")
            else:
                print(f"  {name}: ERROR")
        print()

def cli_help():
    """Print help message."""
    print(f"""Cloud Infrastructure Dashboard v{VERSION}

Usage: {sys.argv[0]} [command]

Commands:
  (no args)     Launch interactive TUI dashboard
  status        Show quick status of all VMs and services
  help          Show this help message

Interactive Commands:
  1 - VM Details          4 - Restart Container    7 - SSH to VM
  2 - Container Status    5 - View Logs            8 - Open URL
  3 - Reboot VM           6 - Stop/Start           R - Refresh
  S - Quick Status        Q - Quit

Config: {CONFIG_FILE}
""")

# =============================================================================
# MAIN
# =============================================================================

def main_loop():
    """Main interactive loop."""
    while True:
        display_dashboard()
        cmd = input("  Command: ").strip().lower()

        actions = {
            '1': action_vm_details,
            '2': action_container_status,
            '3': action_reboot_vm,
            '4': action_restart_container,
            '5': action_view_logs,
            '6': action_stop_start,
            '7': action_ssh,
            '8': action_open_url,
            's': action_quick_status,
            'r': lambda: None,  # Refresh (just redraw)
        }

        if cmd == 'q':
            cls()
            print(f"{C.CYAN}Goodbye!{C.RESET}")
            break
        elif cmd in actions:
            actions[cmd]()
        else:
            print(f"{C.RED}Invalid command{C.RESET}")
            import time
            time.sleep(1)

def main():
    """Entry point."""
    # Check dependencies
    for cmd in ['ssh', 'curl', 'ping']:
        if not shutil.which(cmd):
            print(f"{C.RED}Error: Missing dependency: {cmd}{C.RESET}")
            sys.exit(1)

    # Load config to validate
    load_config()

    # Parse command
    if len(sys.argv) > 1:
        cmd = sys.argv[1]
        if cmd == 'status':
            cli_status()
        elif cmd in ('help', '--help', '-h'):
            cli_help()
        else:
            print(f"Unknown command: {cmd}")
            cli_help()
            sys.exit(1)
    else:
        main_loop()

if __name__ == '__main__':
    main()
