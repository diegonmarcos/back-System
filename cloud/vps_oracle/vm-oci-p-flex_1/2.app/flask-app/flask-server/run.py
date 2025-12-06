#!/usr/bin/env python3
"""
Cloud Dashboard Flask Server - Entry point

Exposes Flask app for gunicorn: gunicorn --bind 0.0.0.0:5000 run:app
"""
import os
import sys
import json

# Add the script directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

from flask import Flask, jsonify

# Config file path
CONFIG_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cloud_dash.json')

def load_config():
    """Load config from JSON file."""
    try:
        with open(CONFIG_FILE, 'r') as f:
            return json.load(f)
    except Exception as e:
        print(f"Error loading config: {e}")
        return None

def get_dashboard_summary(config):
    """Generate dashboard summary from config."""
    vms = config.get('virtualMachines', {})
    services = config.get('services', {})

    # Count VMs by status
    vm_online = sum(1 for vm in vms.values() if vm.get('runtimeStatus', {}).get('online', False))
    vm_total = len(vms)

    # Count services by status
    svc_active = sum(1 for svc in services.values() if svc.get('status') == 'active')
    svc_total = len(services)

    return {
        'vms': {
            'online': vm_online,
            'offline': vm_total - vm_online,
            'total': vm_total,
            'list': [
                {
                    'id': vm_id,
                    'name': vm.get('name', vm_id),
                    'provider': vm.get('provider', 'unknown'),
                    'status': vm.get('status', 'unknown'),
                    'online': vm.get('runtimeStatus', {}).get('online', False),
                    'ip': vm.get('publicIP', 'N/A'),
                    'lastCheck': vm.get('runtimeStatus', {}).get('lastCheck', 'never')
                }
                for vm_id, vm in vms.items()
            ]
        },
        'services': {
            'active': svc_active,
            'inactive': svc_total - svc_active,
            'total': svc_total,
            'list': [
                {
                    'id': svc_id,
                    'name': svc.get('name', svc_id),
                    'status': svc.get('status', 'unknown'),
                    'vmId': svc.get('vmId', 'N/A'),
                    'port': svc.get('port', 'N/A')
                }
                for svc_id, svc in services.items()
            ]
        },
        'lastUpdated': config.get('metadata', {}).get('lastUpdated', 'unknown')
    }

# Create Flask app for gunicorn
app = Flask(__name__)

# Enable CORS for API endpoints
@app.after_request
def after_request(response):
    response.headers.add('Access-Control-Allow-Origin', '*')
    response.headers.add('Access-Control-Allow-Headers', 'Content-Type')
    response.headers.add('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
    return response

@app.route('/api/health')
def health():
    return jsonify({'status': 'healthy'})

@app.route('/api/dashboard/summary')
def dashboard_summary():
    config = load_config()
    if not config:
        return jsonify({'error': 'Failed to load configuration'}), 500
    summary = get_dashboard_summary(config)
    return jsonify(summary)

@app.route('/api/config')
def get_config():
    config = load_config()
    if not config:
        return jsonify({'error': 'Failed to load configuration'}), 500
    return jsonify(config)

if __name__ == '__main__':
    debug = os.environ.get('FLASK_DEBUG', 'false').lower() == 'true'
    host = os.environ.get('FLASK_HOST', '0.0.0.0')
    port = int(os.environ.get('FLASK_PORT', 5000))
    app.run(host=host, port=port, debug=debug)
