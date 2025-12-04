#!/usr/bin/env python3
"""
Cloud Infrastructure Dashboard
A unified Python tool for monitoring and managing cloud VMs and services

Modes:
  - TUI Mode: Interactive terminal dashboard
  - Server Mode: Flask API for web dashboard
  - CLI Mode: Quick status output

Version: 6.0.0
Author: Diego Nepomuceno Marcos
Last Updated: 2025-12-03

Usage:
  python cloud_dash.py          # Interactive TUI
  python cloud_dash.py serve    # Start Flask API server
  python cloud_dash.py status   # Quick CLI status
  python cloud_dash.py help     # Show help

Data Source: cloud_dash.json
"""

import json
import os
import subprocess
import sys
import shutil
from datetime import datetime
from pathlib import Path
from typing import Optional, Dict, Any, List
from functools import lru_cache

# =============================================================================
# CONFIGURATION
# =============================================================================

VERSION = "6.0.0"
SCRIPT_DIR = Path(__file__).parent.resolve()
CONFIG_FILE = SCRIPT_DIR / "cloud_dash.json"
FRONTEND_URL = "https://cloud.diegonmarcos.com/cloud_dash.html"

# Server config
SERVER_HOST = '0.0.0.0'
SERVER_PORT = 5000

# GitHub OAuth config
# Create an OAuth App at: https://github.com/settings/developers
# Set callback URL to: https://cloud.diegonmarcos.com/cloud_dash.html
GITHUB_CLIENT_ID = os.environ.get('GITHUB_CLIENT_ID', 'Ov23liOg9JhezyYUCHmS')
GITHUB_CLIENT_SECRET = os.environ.get('GITHUB_CLIENT_SECRET', '66b4c7574336946f42b1b8645010e467c003ec98')
# Allowed GitHub usernames that can perform admin actions (reboot, etc.)
GITHUB_ALLOWED_USERS = os.environ.get('GITHUB_ALLOWED_USERS', 'diegonmarcos').split(',')

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

def load_config(force_reload: bool = False) -> Dict[str, Any]:
    """Load and cache the JSON configuration."""
    global _config
    if _config is None or force_reload:
        if not CONFIG_FILE.exists():
            raise FileNotFoundError(f"Config not found: {CONFIG_FILE}")
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
# HELPER FUNCTIONS FOR METRICS & COSTS
# =============================================================================

def run_ccusage(args: List[str], timeout: int = 30) -> Dict[str, Any]:
    """Run ccusage CLI and return JSON output."""
    try:
        result = subprocess.run(
            ['ccusage'] + args + ['--json'],
            capture_output=True, text=True, timeout=timeout
        )
        if result.returncode == 0 and result.stdout.strip():
            return json.loads(result.stdout)
        return {"error": result.stderr or "Empty response"}
    except subprocess.TimeoutExpired:
        return {"error": f"Timeout after {timeout}s"}
    except FileNotFoundError:
        return {"error": "ccusage not found. Install: npm i -g ccusage"}
    except Exception as e:
        return {"error": str(e)}

def run_ssh_command(vm_id: str, command: str, timeout: int = 10) -> Dict[str, Any]:
    """Run SSH command on VM and return output."""
    vm = get_vm(vm_id)
    if not vm:
        return {"error": f"VM {vm_id} not found"}

    ssh_user = vm.get("ssh", {}).get("user", "ubuntu")
    ssh_host = vm.get("network", {}).get("publicIp")

    if not ssh_host or ssh_host == "pending":
        return {"error": f"VM {vm_id} has no IP"}

    key_path = expand_path(vm.get("ssh", {}).get("keyPath", ""))

    try:
        result = subprocess.run(
            ["ssh", "-i", key_path, "-o", "ConnectTimeout=5", "-o", "StrictHostKeyChecking=no",
             f"{ssh_user}@{ssh_host}", command],
            capture_output=True, text=True, timeout=timeout
        )
        return {"output": result.stdout, "error": result.stderr if result.returncode != 0 else None}
    except subprocess.TimeoutExpired:
        return {"error": "SSH timeout"}
    except Exception as e:
        return {"error": str(e)}

def parse_free_output(output: str) -> Optional[Dict[str, Any]]:
    """Parse 'free -m' output to get memory stats."""
    try:
        lines = output.strip().split('\n')
        mem_line = [l for l in lines if l.startswith('Mem:')][0]
        parts = mem_line.split()
        return {
            "total_mb": int(parts[1]),
            "used_mb": int(parts[2]),
            "free_mb": int(parts[3]),
            "available_mb": int(parts[6]) if len(parts) > 6 else int(parts[3]),
            "percent_used": round(int(parts[2]) / int(parts[1]) * 100, 1)
        }
    except:
        return None

def parse_df_output(output: str) -> Optional[Dict[str, Any]]:
    """Parse 'df -h /' output to get disk stats."""
    try:
        lines = output.strip().split('\n')
        data_line = lines[1]
        parts = data_line.split()
        return {
            "total": parts[1],
            "used": parts[2],
            "available": parts[3],
            "percent_used": int(parts[4].replace('%', ''))
        }
    except:
        return None

def parse_uptime_output(output: str) -> Optional[Dict[str, Any]]:
    """Parse 'uptime' output to get load average."""
    try:
        # Format: "16:30:01 up 5 days, 4:23, 1 user, load average: 0.08, 0.03, 0.01"
        load_part = output.split('load average:')[1].strip()
        loads = [float(x.strip().replace(',', '')) for x in load_part.split(',')[:3]]
        return {
            "load_1m": loads[0],
            "load_5m": loads[1],
            "load_15m": loads[2]
        }
    except:
        return None

def parse_docker_stats(output: str) -> List[Dict[str, str]]:
    """Parse docker stats output."""
    if not output:
        return []
    results = []
    for line in output.strip().split('\n'):
        if not line:
            continue
        parts = line.split('\t')
        if len(parts) >= 3:
            results.append({
                "name": parts[0],
                "cpu": parts[1],
                "memory": parts[2]
            })
    return results

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

def get_vm_status_dict(vm_id: str) -> Dict:
    """Get VM status as dictionary (for API)."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return {'status': 'pending', 'label': 'PENDING', 'ping': False, 'ssh': False}

    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    ssh_ok = check_ssh(ip, user, key_path)
    ping_ok = check_ping(ip) if not ssh_ok else True

    if ssh_ok:
        return {'status': 'online', 'label': 'ONLINE', 'ping': True, 'ssh': True}
    elif ping_ok:
        return {'status': 'no_ssh', 'label': 'NO SSH', 'ping': True, 'ssh': False}
    else:
        return {'status': 'offline', 'label': 'OFFLINE', 'ping': False, 'ssh': False}

def get_vm_status(vm_id: str) -> str:
    """Get formatted VM status string (for TUI)."""
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

def get_vm_ram_percent(vm_id: str) -> Optional[int]:
    """Get RAM usage percentage via SSH."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return None

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
        if result.returncode == 0 and result.stdout.strip():
            return int(result.stdout.strip())
    except (subprocess.TimeoutExpired, ValueError, Exception):
        pass
    return None

def get_vm_details(vm_id: str) -> Optional[Dict]:
    """Get detailed VM information via SSH."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return None

    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    remote_cmd = '''
echo "hostname:$(hostname)"
echo "uptime:$(uptime -p 2>/dev/null || uptime)"
echo "kernel:$(uname -r)"
echo "cpu:$(nproc)"
echo "ram_used:$(free -h | awk '/^Mem:/{print $3}')"
echo "ram_total:$(free -h | awk '/^Mem:/{print $2}')"
echo "ram_percent:$(free | awk '/^Mem:/{printf "%.1f", $3/$2*100}')"
echo "disk_used:$(df -h / | awk 'NR==2{print $3}')"
echo "disk_total:$(df -h / | awk 'NR==2{print $2}')"
echo "containers:$(sudo docker ps -q 2>/dev/null | wc -l)"
'''

    try:
        result = subprocess.run(
            ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
             '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}', remote_cmd],
            capture_output=True, text=True, timeout=SSH_TIMEOUT + 5
        )
        if result.returncode == 0:
            details = {}
            for line in result.stdout.strip().split('\n'):
                if ':' in line:
                    key, value = line.split(':', 1)
                    details[key.strip()] = value.strip()
            return details
    except Exception:
        pass
    return None

def get_svc_status_dict(svc_id: str) -> Dict:
    """Get service status as dictionary (for API)."""
    status = get_svc(svc_id, 'status')

    # Status: on, dev, hold, tbd
    if status in ('dev', 'development', 'planned'):
        return {'status': 'development', 'label': 'DEV', 'healthy': None}
    if status == 'hold':
        return {'status': 'hold', 'label': 'HOLD', 'healthy': None}
    if status == 'tbd':
        return {'status': 'tbd', 'label': 'TBD', 'healthy': None}

    url = get_svc(svc_id, 'urls.health') or get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')

    if not url or url == 'null':
        return {'status': 'no_url', 'label': 'N/A', 'healthy': None}

    healthy = check_http(url)
    return {
        'status': 'healthy' if healthy else 'error',
        'label': 'HEALTHY' if healthy else 'ERROR',
        'healthy': healthy
    }

def get_svc_status(svc_id: str) -> str:
    """Get formatted service status string (for TUI)."""
    status = get_svc(svc_id, 'status')

    # Status: on, dev, hold, tbd
    if status in ('dev', 'development', 'planned'):
        return f"{C.BLUE}◑ DEV{C.RESET}"
    if status in ('hold',):
        return f"{C.YELLOW}◐ HOLD{C.RESET}"
    if status in ('tbd',):
        return f"{C.DIM}○ TBD{C.RESET}"

    url = get_svc(svc_id, 'urls.health') or get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')

    if not url or url == 'null':
        return f"{C.DIM}- N/A{C.RESET}"

    if check_http(url):
        return f"{C.GREEN}● HEALTHY{C.RESET}"
    else:
        return f"{C.RED}✖ ERROR{C.RESET}"

def get_container_status(vm_id: str) -> Optional[list]:
    """Get Docker container status on a VM."""
    ip = get_vm(vm_id, 'network.publicIp')

    if ip == 'pending':
        return None

    user = get_vm(vm_id, 'ssh.user')
    key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

    try:
        result = subprocess.run(
            ['ssh', '-i', key_path, '-o', f'ConnectTimeout={SSH_TIMEOUT}',
             '-o', 'StrictHostKeyChecking=no', f'{user}@{ip}',
             'sudo docker ps -a --format "{{.Names}}|{{.Status}}|{{.Ports}}"'],
            capture_output=True, text=True, timeout=SSH_TIMEOUT + 5
        )
        if result.returncode == 0:
            containers = []
            for line in result.stdout.strip().split('\n'):
                if '|' in line:
                    parts = line.split('|')
                    containers.append({
                        'name': parts[0] if len(parts) > 0 else '',
                        'status': parts[1] if len(parts) > 1 else '',
                        'ports': parts[2] if len(parts) > 2 else ''
                    })
            return containers
    except Exception:
        pass
    return None

# =============================================================================
# FLASK API SERVER
# =============================================================================

def run_server(host: str = SERVER_HOST, port: int = SERVER_PORT, debug: bool = False):
    """Run Flask API server."""
    try:
        from flask import Flask, jsonify, request, send_from_directory
    except ImportError:
        print(f"{C.RED}Error: Flask not installed. Run: pip install flask{C.RESET}")
        sys.exit(1)

    app = Flask(__name__)

    # Enable CORS for API endpoints
    @app.after_request
    def add_cors_headers(response):
        # Allow requests from any origin for the dashboard
        origin = request.headers.get('Origin', '*')
        response.headers['Access-Control-Allow-Origin'] = origin
        response.headers['Access-Control-Allow-Methods'] = 'GET, POST, OPTIONS'
        response.headers['Access-Control-Allow-Headers'] = 'Content-Type, Authorization'
        response.headers['Access-Control-Allow-Credentials'] = 'true'
        return response

    @app.route('/api/<path:path>', methods=['OPTIONS'])
    def handle_options(path):
        """Handle CORS preflight requests."""
        return '', 204

    # -------------------------------------------------------------------------
    # Health & Config
    # -------------------------------------------------------------------------

    @app.route('/api/health')
    def api_health():
        return jsonify({'status': 'ok', 'service': 'cloud-dashboard', 'version': VERSION})

    @app.route('/api/config')
    def api_config():
        try:
            return jsonify(load_config())
        except FileNotFoundError as e:
            return jsonify({'error': str(e)}), 404

    @app.route('/api/config/reload', methods=['POST'])
    def api_config_reload():
        try:
            load_config(force_reload=True)
            return jsonify({'status': 'ok', 'message': 'Configuration reloaded'})
        except FileNotFoundError as e:
            return jsonify({'error': str(e)}), 404

    # -------------------------------------------------------------------------
    # VMs
    # -------------------------------------------------------------------------

    @app.route('/api/vms')
    def api_list_vms():
        category = request.args.get('category')
        vm_ids = get_vm_ids_by_category(category) if category else get_vm_ids()

        vms = []
        for vm_id in vm_ids:
            vm_data = get_vm(vm_id)
            vms.append({
                'id': vm_id,
                'name': vm_data.get('name'),
                'provider': vm_data.get('provider'),
                'category': vm_data.get('category'),
                'ip': vm_data.get('network', {}).get('publicIp'),
                'instanceType': vm_data.get('instanceType'),
                'configStatus': vm_data.get('status')
            })
        return jsonify({'vms': vms})

    @app.route('/api/vms/categories')
    def api_vm_categories():
        categories = [{'id': c, 'name': get_vm_category_name(c)} for c in get_vm_categories()]
        return jsonify({'categories': categories})

    @app.route('/api/vms/<vm_id>')
    def api_get_vm(vm_id: str):
        vm_data = get_vm(vm_id)
        if not vm_data:
            return jsonify({'error': f'VM not found: {vm_id}'}), 404
        return jsonify({'id': vm_id, **vm_data})

    @app.route('/api/vms/<vm_id>/status')
    def api_vm_status(vm_id: str):
        vm_data = get_vm(vm_id)
        if not vm_data:
            return jsonify({'error': f'VM not found: {vm_id}'}), 404

        status = get_vm_status_dict(vm_id)
        ram = get_vm_ram_percent(vm_id)

        return jsonify({
            'id': vm_id,
            'name': vm_data.get('name'),
            'ip': vm_data.get('network', {}).get('publicIp'),
            **status,
            'ram_percent': ram
        })

    @app.route('/api/vms/<vm_id>/details')
    def api_vm_details(vm_id: str):
        vm_data = get_vm(vm_id)
        if not vm_data:
            return jsonify({'error': f'VM not found: {vm_id}'}), 404

        details = get_vm_details(vm_id)
        if details is None:
            return jsonify({'error': 'Failed to connect to VM'}), 503

        return jsonify({'id': vm_id, 'name': vm_data.get('name'), 'details': details})

    @app.route('/api/vms/<vm_id>/containers')
    def api_vm_containers(vm_id: str):
        vm_data = get_vm(vm_id)
        if not vm_data:
            return jsonify({'error': f'VM not found: {vm_id}'}), 404

        containers = get_container_status(vm_id)
        if containers is None:
            return jsonify({'error': 'Failed to get container status'}), 503

        return jsonify({'id': vm_id, 'name': vm_data.get('name'), 'containers': containers})

    # -------------------------------------------------------------------------
    # Services
    # -------------------------------------------------------------------------

    @app.route('/api/services')
    def api_list_services():
        category = request.args.get('category')
        svc_ids = get_service_ids_by_category(category) if category else get_service_ids()

        services = []
        for svc_id in svc_ids:
            svc_data = get_svc(svc_id)
            url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
            services.append({
                'id': svc_id,
                'name': svc_data.get('name'),
                'displayName': svc_data.get('displayName'),
                'category': svc_data.get('category'),
                'vmId': svc_data.get('vmId'),
                'url': url,
                'configStatus': svc_data.get('status')
            })
        return jsonify({'services': services})

    @app.route('/api/services/categories')
    def api_service_categories():
        categories = [{'id': c, 'name': get_service_category_name(c)} for c in get_service_categories()]
        return jsonify({'categories': categories})

    @app.route('/api/services/<svc_id>')
    def api_get_service(svc_id: str):
        svc_data = get_svc(svc_id)
        if not svc_data:
            return jsonify({'error': f'Service not found: {svc_id}'}), 404
        return jsonify({'id': svc_id, **svc_data})

    @app.route('/api/services/<svc_id>/status')
    def api_service_status(svc_id: str):
        svc_data = get_svc(svc_id)
        if not svc_data:
            return jsonify({'error': f'Service not found: {svc_id}'}), 404

        status = get_svc_status_dict(svc_id)
        url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')

        return jsonify({
            'id': svc_id,
            'name': svc_data.get('name'),
            'displayName': svc_data.get('displayName'),
            'url': url,
            **status
        })

    # -------------------------------------------------------------------------
    # Dashboard Summary
    # -------------------------------------------------------------------------

    @app.route('/api/dashboard/summary')
    def api_dashboard_summary():
        """Full summary with health checks."""
        vm_summary = []
        for cat_id in get_vm_categories():
            cat_vms = []
            for vm_id in get_vm_ids_by_category(cat_id):
                vm_data = get_vm(vm_id)
                status = get_vm_status_dict(vm_id)
                ram = get_vm_ram_percent(vm_id)
                cat_vms.append({
                    'id': vm_id,
                    'name': vm_data.get('name'),
                    'ip': vm_data.get('network', {}).get('publicIp'),
                    'instanceType': vm_data.get('instanceType'),
                    **status,
                    'ram_percent': ram
                })
            if cat_vms:
                vm_summary.append({
                    'category': cat_id,
                    'categoryName': get_vm_category_name(cat_id),
                    'vms': cat_vms
                })

        svc_summary = []
        for cat_id in get_service_categories():
            cat_svcs = []
            for svc_id in get_service_ids_by_category(cat_id):
                svc_data = get_svc(svc_id)
                status = get_svc_status_dict(svc_id)
                url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
                cat_svcs.append({
                    'id': svc_id,
                    'name': svc_data.get('name'),
                    'displayName': svc_data.get('displayName'),
                    'url': url,
                    **status
                })
            if cat_svcs:
                svc_summary.append({
                    'category': cat_id,
                    'categoryName': get_service_category_name(cat_id),
                    'services': cat_svcs
                })

        return jsonify({'vms': vm_summary, 'services': svc_summary})

    @app.route('/api/dashboard/quick-status')
    def api_quick_status():
        """Quick status from config only (no health checks)."""
        vms = []
        for vm_id in get_vm_ids():
            vm_data = get_vm(vm_id)
            vms.append({
                'id': vm_id,
                'name': vm_data.get('name'),
                'ip': vm_data.get('network', {}).get('publicIp'),
                'provider': vm_data.get('provider'),
                'category': vm_data.get('category'),
                'configStatus': vm_data.get('status')
            })

        services = []
        for svc_id in get_service_ids():
            svc_data = get_svc(svc_id)
            url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
            services.append({
                'id': svc_id,
                'name': svc_data.get('name'),
                'displayName': svc_data.get('displayName'),
                'category': svc_data.get('category'),
                'vmId': svc_data.get('vmId'),
                'url': url,
                'configStatus': svc_data.get('status')
            })

        return jsonify({'vms': vms, 'services': services})

    @app.route('/api/providers')
    def api_providers():
        return jsonify({'providers': load_config().get('providers', {})})

    @app.route('/api/domains')
    def api_domains():
        return jsonify(load_config().get('domains', {}))

    # -------------------------------------------------------------------------
    # Cost API Endpoints
    # -------------------------------------------------------------------------

    @app.route('/api/costs/infra')
    def api_costs_infra():
        """Get infrastructure costs from config."""
        config = load_config()
        return jsonify(config.get("costs", {}).get("infra", {}))

    @app.route('/api/costs/ai/now')
    def api_costs_ai_now():
        """Current 5h block with projections."""
        return jsonify(run_ccusage(['blocks', '-a']))

    @app.route('/api/costs/ai/daily')
    def api_costs_ai_daily():
        """Daily breakdown with model costs."""
        return jsonify(run_ccusage(['daily', '-b']))

    @app.route('/api/costs/ai/weekly')
    def api_costs_ai_weekly():
        """Weekly aggregation."""
        return jsonify(run_ccusage(['weekly', '-b']))

    @app.route('/api/costs/ai/monthly')
    def api_costs_ai_monthly():
        """Monthly totals."""
        return jsonify(run_ccusage(['monthly', '-b']))

    # -------------------------------------------------------------------------
    # Metrics API Endpoints
    # -------------------------------------------------------------------------

    @app.route('/api/metrics/vms')
    def api_metrics_vms():
        """Get metrics for all active VMs."""
        config = load_config()
        vms = config.get("virtualMachines", {})
        results = {}

        for vm_id, vm in vms.items():
            if vm.get("status") not in ["active", "on"]:
                continue

            ip = vm.get("network", {}).get("publicIp")
            if not ip or ip == "pending":
                continue

            # Collect metrics via SSH
            memory = run_ssh_command(vm_id, "free -m")
            disk = run_ssh_command(vm_id, "df -h /")
            load = run_ssh_command(vm_id, "uptime")
            docker = run_ssh_command(vm_id, "sudo docker stats --no-stream --format '{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}'")

            results[vm_id] = {
                "name": vm.get("name"),
                "ip": ip,
                "memory": parse_free_output(memory.get("output", "")) if not memory.get("error") else None,
                "disk": parse_df_output(disk.get("output", "")) if not disk.get("error") else None,
                "load": parse_uptime_output(load.get("output", "")) if not load.get("error") else None,
                "containers": parse_docker_stats(docker.get("output", "")) if not docker.get("error") else [],
                "error": memory.get("error") or disk.get("error") or load.get("error")
            }

        return jsonify(results)

    @app.route('/api/metrics/vms/<vm_id>')
    def api_metrics_vm(vm_id: str):
        """Get metrics for single VM."""
        config = load_config()
        vm = config.get("virtualMachines", {}).get(vm_id)

        if not vm:
            return jsonify({"error": f"VM {vm_id} not found"}), 404

        memory = run_ssh_command(vm_id, "free -m")
        disk = run_ssh_command(vm_id, "df -h /")
        load = run_ssh_command(vm_id, "uptime")
        docker = run_ssh_command(vm_id, "sudo docker stats --no-stream --format '{{.Name}}\t{{.CPUPerc}}\t{{.MemUsage}}'")

        return jsonify({
            "vm_id": vm_id,
            "name": vm.get("name"),
            "memory": parse_free_output(memory.get("output", "")) if not memory.get("error") else {"error": memory.get("error")},
            "disk": parse_df_output(disk.get("output", "")) if not disk.get("error") else {"error": disk.get("error")},
            "load": parse_uptime_output(load.get("output", "")) if not load.get("error") else {"error": load.get("error")},
            "containers": parse_docker_stats(docker.get("output", "")) if not docker.get("error") else {"error": docker.get("error")}
        })

    @app.route('/api/metrics/services/<service_id>')
    def api_metrics_service(service_id: str):
        """Get metrics for a specific Docker container."""
        config = load_config()
        service = config.get("services", {}).get(service_id)

        if not service:
            return jsonify({"error": f"Service {service_id} not found"}), 404

        # Find which VM runs this service
        for vm_id, vm in config.get("virtualMachines", {}).items():
            if service_id in vm.get("services", []):
                container_name = service.get("deployment", {}).get("containerName", service_id)
                stats = run_ssh_command(vm_id, f"sudo docker stats --no-stream --format 'json' {container_name}")

                if stats.get("error"):
                    return jsonify({"error": stats.get("error")}), 500

                try:
                    return jsonify(json.loads(stats.get("output", "{}")))
                except:
                    return jsonify({"raw": stats.get("output")})

        return jsonify({"error": "Service VM not found"}), 404

    @app.route('/api/capacity')
    def api_capacity():
        """Get infrastructure capacity assessment."""
        config = load_config()
        estimates = config.get("resourceEstimates", {})

        return jsonify({
            "vms": {
                "oracle-web-server-1": {
                    "total_ram_mb": 1024,
                    "estimated_used": estimates.get("vmAllocations", {}).get("oracle-web-server-1", {}).get("ram", {}),
                    "services": config.get("virtualMachines", {}).get("oracle-web-server-1", {}).get("services", []),
                    "status": "AT_LIMIT"
                },
                "oracle-services-server-1": {
                    "total_ram_mb": 1024,
                    "estimated_used": estimates.get("vmAllocations", {}).get("oracle-services-server-1", {}).get("ram", {}),
                    "services": config.get("virtualMachines", {}).get("oracle-services-server-1", {}).get("services", []),
                    "status": "CLOSE"
                },
                "gcloud-arch-1": {
                    "total_ram_mb": 1024,
                    "estimated_used": estimates.get("vmAllocations", {}).get("gcloud-arch-1", {}).get("ram", {}),
                    "services": config.get("virtualMachines", {}).get("gcloud-arch-1", {}).get("services", []),
                    "status": "DEV"
                },
                "oracle-arm-server": {
                    "total_ram_mb": 24576,
                    "estimated_used": estimates.get("vmAllocations", {}).get("oracle-arm-server", {}).get("ram", {}),
                    "services": config.get("virtualMachines", {}).get("oracle-arm-server", {}).get("services", []),
                    "status": "HOLD"
                }
            },
            "summary": {
                "nonAi": estimates.get("nonAi", {}),
                "ai": estimates.get("ai", {})
            },
            "recommendations": [
                "oracle-web-server-1 is at RAM limit - consider moving services",
                "gcloud-arch-1 needs deployment (mail, terminal)",
                "oracle-arm-server waiting for Oracle approval (AI workloads)"
            ]
        })

    # -------------------------------------------------------------------------
    # GitHub OAuth & Authentication
    # -------------------------------------------------------------------------

    @app.route('/api/auth/callback')
    def api_github_callback():
        """Exchange GitHub OAuth code for access token and redirect back to frontend."""
        import requests as req
        from urllib.parse import urlencode

        code = request.args.get('code')
        frontend_url = FRONTEND_URL

        if not code:
            return f'<script>window.location.href="{frontend_url}?error=no_code";</script>'

        if not GITHUB_CLIENT_ID or not GITHUB_CLIENT_SECRET:
            return f'<script>window.location.href="{frontend_url}?error=not_configured";</script>'

        # Exchange code for access token
        try:
            token_response = req.post(
                'https://github.com/login/oauth/access_token',
                headers={'Accept': 'application/json'},
                data={
                    'client_id': GITHUB_CLIENT_ID,
                    'client_secret': GITHUB_CLIENT_SECRET,
                    'code': code
                },
                timeout=10
            )
            token_data = token_response.json()

            if 'error' in token_data:
                return f'<script>window.location.href="{frontend_url}?error=oauth_failed";</script>'

            access_token = token_data.get('access_token')
            if not access_token:
                return f'<script>window.location.href="{frontend_url}?error=no_token";</script>'

            # Get user info
            user_response = req.get(
                'https://api.github.com/user',
                headers={
                    'Authorization': f'Bearer {access_token}',
                    'Accept': 'application/json'
                },
                timeout=10
            )
            user_data = user_response.json()

            # Check if user is allowed
            username = user_data.get('login', '')
            is_admin = username in GITHUB_ALLOWED_USERS

            # Redirect back to frontend with token in URL fragment (not query param for security)
            import json
            user_json = json.dumps({
                'login': username,
                'avatar_url': user_data.get('avatar_url', ''),
                'name': user_data.get('name', ''),
                'is_admin': is_admin
            })

            # Use JavaScript to store in localStorage and redirect
            return f'''
            <script>
                localStorage.setItem('github_token', '{access_token}');
                localStorage.setItem('github_user', '{user_json}');
                window.location.href = '{frontend_url}';
            </script>
            '''

        except Exception as e:
            return f'<script>window.location.href="{frontend_url}?error=exception";</script>'

    def verify_github_token(token: str) -> Optional[Dict]:
        """Verify GitHub token and return user info if valid and authorized."""
        import requests as req

        if not token:
            return None

        try:
            response = req.get(
                'https://api.github.com/user',
                headers={
                    'Authorization': f'Bearer {token}',
                    'Accept': 'application/json'
                },
                timeout=10
            )
            if response.status_code != 200:
                return None

            user_data = response.json()
            username = user_data.get('login', '')

            if username not in GITHUB_ALLOWED_USERS:
                return None

            return user_data
        except Exception:
            return None

    # -------------------------------------------------------------------------
    # VM Actions (Authenticated)
    # -------------------------------------------------------------------------

    @app.route('/api/vm/<vm_id>/reboot', methods=['POST'])
    def api_vm_reboot(vm_id: str):
        """Reboot a VM (requires GitHub authentication)."""
        # Check authorization
        auth_header = request.headers.get('Authorization', '')
        if not auth_header.startswith('Bearer '):
            return jsonify({'error': 'Authorization required'}), 401

        token = auth_header[7:]  # Remove 'Bearer ' prefix
        user = verify_github_token(token)
        if not user:
            return jsonify({'error': 'Invalid token or unauthorized user'}), 403

        # Get VM info
        vm_data = get_vm(vm_id)
        if not vm_data:
            return jsonify({'error': f'VM not found: {vm_id}'}), 404

        ip = get_vm(vm_id, 'network.publicIp')
        if ip == 'pending':
            return jsonify({'error': 'VM IP is pending'}), 400

        user_ssh = get_vm(vm_id, 'ssh.user')
        key_path = expand_path(get_vm(vm_id, 'ssh.keyPath') or '')

        # Execute reboot
        try:
            subprocess.run(
                ['ssh', '-i', key_path,
                 '-o', 'BatchMode=yes',
                 '-o', f'ConnectTimeout={SSH_TIMEOUT}',
                 '-o', 'StrictHostKeyChecking=no',
                 f'{user_ssh}@{ip}', 'sudo reboot'],
                capture_output=True,
                timeout=SSH_TIMEOUT + 5
            )
            return jsonify({
                'status': 'ok',
                'message': f'Reboot signal sent to {vm_id}',
                'vm': vm_id,
                'initiated_by': user.get('login')
            })
        except subprocess.TimeoutExpired:
            # Timeout is expected as connection drops during reboot
            return jsonify({
                'status': 'ok',
                'message': f'Reboot signal sent to {vm_id}',
                'vm': vm_id,
                'initiated_by': user.get('login')
            })
        except Exception as e:
            return jsonify({'error': f'Failed to reboot: {str(e)}'}), 500

    # -------------------------------------------------------------------------
    # Root redirect to frontend
    # -------------------------------------------------------------------------

    @app.route('/')
    def root_redirect():
        """Redirect to the frontend dashboard."""
        return f'<script>window.location.href="{FRONTEND_URL}";</script>'

    # -------------------------------------------------------------------------
    # Run Server
    # -------------------------------------------------------------------------

    print(f"{C.CYAN}Starting Cloud Dashboard Server v{VERSION}{C.RESET}")
    print(f"{C.GREEN}  API:       http://{host}:{port}/api/health{C.RESET}")
    print(f"{C.GREEN}  Dashboard: http://{host}:{port}/dashboard{C.RESET}")
    print(f"{C.DIM}  Config:    {CONFIG_FILE}{C.RESET}")
    print()

    app.run(host=host, port=port, debug=debug)

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
# TUI DISPLAY FUNCTIONS
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
            ram_display = f"{ram}%" if ram else '-'

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
            display_name = get_svc(svc_id, 'displayName') or get_svc(svc_id, 'name') or svc_id
            name = display_name[:20]
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
# TUI SELECTION HELPERS
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
            if status in ('dev', 'development', 'planned', 'hold', 'tbd'):
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
# TUI ACTIONS
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

    details = get_vm_details(vm_id)
    if details:
        print(f"  Hostname: {details.get('hostname', '-')}")
        print(f"  Uptime:   {details.get('uptime', '-')}")
        print(f"  Kernel:   {details.get('kernel', '-')}")
        print(f"\nResources:")
        print(f"  CPU:      {details.get('cpu', '-')} cores")
        print(f"  RAM:      {details.get('ram_used', '-')}/{details.get('ram_total', '-')} ({details.get('ram_percent', '-')}%)")
        print(f"  Disk:     {details.get('disk_used', '-')}/{details.get('disk_total', '-')}")
        print(f"\nDocker:")
        print(f"  Running:  {details.get('containers', '-')} containers")
    else:
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

            if not ram:
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
            display_name = get_svc(svc_id, 'displayName') or get_svc(svc_id, 'name') or svc_id
            status = get_svc_status(svc_id)
            print(f"  {display_name:<25} {status}")
        print()

    wait_key()

# =============================================================================
# CLI MODE
# =============================================================================

def cli_status():
    """Print status for CLI mode (no colors)."""
    print(f"Cloud Infrastructure Status v{VERSION}")
    print("=" * 40)
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
            display_name = get_svc(svc_id, 'displayName') or get_svc(svc_id, 'name') or svc_id
            url = get_svc(svc_id, 'urls.gui') or get_svc(svc_id, 'urls.admin')
            status = get_svc(svc_id, 'status')

            if status in ('dev', 'development', 'planned'):
                print(f"  {display_name}: DEV")
            elif status == 'hold':
                print(f"  {display_name}: HOLD")
            elif status == 'tbd':
                print(f"  {display_name}: TBD")
            elif not url or url == 'null':
                print(f"  {display_name}: NO URL")
            elif check_http(url):
                print(f"  {display_name}: HEALTHY")
            else:
                print(f"  {display_name}: ERROR")
        print()

def cli_help():
    """Print help message."""
    print(f"""Cloud Infrastructure Dashboard v{VERSION}

Usage: {sys.argv[0]} [command]

Commands:
  (no args)     Launch interactive TUI dashboard
  serve         Start Flask API server (for web dashboard)
  serve --debug Start Flask in debug mode
  status        Show quick status of all VMs and services
  help          Show this help message

TUI Commands:
  1 - VM Details          4 - Restart Container    7 - SSH to VM
  2 - Container Status    5 - View Logs            8 - Open URL
  3 - Reboot VM           6 - Stop/Start           R - Refresh
  S - Quick Status        Q - Quit

API Endpoints (when running serve):
  GET /api/health              - API health check
  GET /api/vms                 - List all VMs
  GET /api/vms/<id>/status     - VM health status
  GET /api/services            - List all services
  GET /api/services/<id>/status - Service health status
  GET /api/dashboard/summary   - Full dashboard with health checks
  GET /api/dashboard/quick-status - Quick status (no health checks)

Config: {CONFIG_FILE}
Static: {STATIC_DIR}
""")

# =============================================================================
# MAIN
# =============================================================================

def main_loop():
    """Main interactive TUI loop."""
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
            'r': lambda: None,
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
    # Check basic dependencies
    for cmd in ['ssh', 'curl', 'ping']:
        if not shutil.which(cmd):
            print(f"{C.RED}Error: Missing dependency: {cmd}{C.RESET}")
            sys.exit(1)

    # Validate config
    try:
        load_config()
    except FileNotFoundError as e:
        print(f"{C.RED}Error: {e}{C.RESET}")
        sys.exit(1)

    # Parse command
    if len(sys.argv) > 1:
        cmd = sys.argv[1]
        if cmd == 'serve':
            debug = '--debug' in sys.argv
            run_server(debug=debug)
        elif cmd == 'status':
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
