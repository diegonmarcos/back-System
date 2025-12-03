"""
API Routes for Cloud Dashboard
"""
from flask import Blueprint, jsonify, request

from app.config import (
    load_config,
    get_vm_ids, get_vm_ids_by_category, get_vm_categories, get_vm_category_name, get_vm,
    get_service_ids, get_service_ids_by_category, get_service_categories, get_service_category_name, get_svc
)
from app.health import (
    get_vm_status, get_vm_ram_percent, get_vm_details,
    get_svc_status, get_container_status
)

api_bp = Blueprint('api', __name__)


# =============================================================================
# Health Check
# =============================================================================

@api_bp.route('/health', methods=['GET'])
def health_check():
    """API health check endpoint."""
    return jsonify({
        'status': 'ok',
        'service': 'cloud-dashboard-api',
        'version': '1.0.0'
    })


# =============================================================================
# Configuration Endpoints
# =============================================================================

@api_bp.route('/config', methods=['GET'])
def get_full_config():
    """Get full infrastructure configuration."""
    try:
        config = load_config()
        return jsonify(config)
    except FileNotFoundError as e:
        return jsonify({'error': str(e)}), 404


@api_bp.route('/config/reload', methods=['POST'])
def reload_config():
    """Force reload configuration from disk."""
    try:
        config = load_config(force_reload=True)
        return jsonify({'status': 'ok', 'message': 'Configuration reloaded'})
    except FileNotFoundError as e:
        return jsonify({'error': str(e)}), 404


# =============================================================================
# VM Endpoints
# =============================================================================

@api_bp.route('/vms', methods=['GET'])
def list_vms():
    """List all VMs with basic info."""
    category = request.args.get('category')

    if category:
        vm_ids = get_vm_ids_by_category(category)
    else:
        vm_ids = get_vm_ids()

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


@api_bp.route('/vms/categories', methods=['GET'])
def list_vm_categories():
    """List all VM categories."""
    categories = []
    for cat_id in get_vm_categories():
        categories.append({
            'id': cat_id,
            'name': get_vm_category_name(cat_id)
        })
    return jsonify({'categories': categories})


@api_bp.route('/vms/<vm_id>', methods=['GET'])
def get_vm_info(vm_id: str):
    """Get detailed VM information."""
    vm_data = get_vm(vm_id)
    if not vm_data:
        return jsonify({'error': f'VM not found: {vm_id}'}), 404

    return jsonify({
        'id': vm_id,
        **vm_data
    })


@api_bp.route('/vms/<vm_id>/status', methods=['GET'])
def get_vm_health(vm_id: str):
    """Get VM health status (ping, SSH)."""
    vm_data = get_vm(vm_id)
    if not vm_data:
        return jsonify({'error': f'VM not found: {vm_id}'}), 404

    status = get_vm_status(vm_id)
    ram = get_vm_ram_percent(vm_id)

    return jsonify({
        'id': vm_id,
        'name': vm_data.get('name'),
        'ip': vm_data.get('network', {}).get('publicIp'),
        **status,
        'ram_percent': ram
    })


@api_bp.route('/vms/<vm_id>/details', methods=['GET'])
def get_vm_remote_details(vm_id: str):
    """Get detailed system info from VM via SSH."""
    vm_data = get_vm(vm_id)
    if not vm_data:
        return jsonify({'error': f'VM not found: {vm_id}'}), 404

    details = get_vm_details(vm_id)
    if details is None:
        return jsonify({'error': 'Failed to connect to VM'}), 503

    return jsonify({
        'id': vm_id,
        'name': vm_data.get('name'),
        'details': details
    })


@api_bp.route('/vms/<vm_id>/containers', methods=['GET'])
def get_vm_containers(vm_id: str):
    """Get Docker container status on VM."""
    vm_data = get_vm(vm_id)
    if not vm_data:
        return jsonify({'error': f'VM not found: {vm_id}'}), 404

    containers = get_container_status(vm_id)
    if containers is None:
        return jsonify({'error': 'Failed to get container status'}), 503

    return jsonify({
        'id': vm_id,
        'name': vm_data.get('name'),
        'containers': containers
    })


# =============================================================================
# Service Endpoints
# =============================================================================

@api_bp.route('/services', methods=['GET'])
def list_services():
    """List all services with basic info."""
    category = request.args.get('category')

    if category:
        svc_ids = get_service_ids_by_category(category)
    else:
        svc_ids = get_service_ids()

    services = []
    for svc_id in svc_ids:
        svc_data = get_svc(svc_id)
        url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
        services.append({
            'id': svc_id,
            'name': svc_data.get('name'),
            'category': svc_data.get('category'),
            'vmId': svc_data.get('vmId'),
            'url': url,
            'configStatus': svc_data.get('status')
        })

    return jsonify({'services': services})


@api_bp.route('/services/categories', methods=['GET'])
def list_service_categories():
    """List all service categories."""
    categories = []
    for cat_id in get_service_categories():
        categories.append({
            'id': cat_id,
            'name': get_service_category_name(cat_id)
        })
    return jsonify({'categories': categories})


@api_bp.route('/services/<svc_id>', methods=['GET'])
def get_service_info(svc_id: str):
    """Get detailed service information."""
    svc_data = get_svc(svc_id)
    if not svc_data:
        return jsonify({'error': f'Service not found: {svc_id}'}), 404

    return jsonify({
        'id': svc_id,
        **svc_data
    })


@api_bp.route('/services/<svc_id>/status', methods=['GET'])
def get_service_health(svc_id: str):
    """Get service health status (HTTP check)."""
    svc_data = get_svc(svc_id)
    if not svc_data:
        return jsonify({'error': f'Service not found: {svc_id}'}), 404

    status = get_svc_status(svc_id)
    url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')

    return jsonify({
        'id': svc_id,
        'name': svc_data.get('name'),
        'url': url,
        **status
    })


# =============================================================================
# Dashboard Summary Endpoints
# =============================================================================

@api_bp.route('/dashboard/summary', methods=['GET'])
def get_dashboard_summary():
    """Get summary of all VMs and services with status."""
    # VMs
    vm_summary = []
    for cat_id in get_vm_categories():
        cat_vms = []
        for vm_id in get_vm_ids_by_category(cat_id):
            vm_data = get_vm(vm_id)
            status = get_vm_status(vm_id)
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

    # Services
    svc_summary = []
    for cat_id in get_service_categories():
        cat_svcs = []
        for svc_id in get_service_ids_by_category(cat_id):
            svc_data = get_svc(svc_id)
            status = get_svc_status(svc_id)
            url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
            cat_svcs.append({
                'id': svc_id,
                'name': svc_data.get('name'),
                'url': url,
                **status
            })
        if cat_svcs:
            svc_summary.append({
                'category': cat_id,
                'categoryName': get_service_category_name(cat_id),
                'services': cat_svcs
            })

    return jsonify({
        'vms': vm_summary,
        'services': svc_summary
    })


@api_bp.route('/dashboard/quick-status', methods=['GET'])
def get_quick_status():
    """Get quick status without health checks (from config only)."""
    # VMs
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

    # Services
    services = []
    for svc_id in get_service_ids():
        svc_data = get_svc(svc_id)
        url = svc_data.get('urls', {}).get('gui') or svc_data.get('urls', {}).get('admin')
        services.append({
            'id': svc_id,
            'name': svc_data.get('name'),
            'category': svc_data.get('category'),
            'vmId': svc_data.get('vmId'),
            'url': url,
            'configStatus': svc_data.get('status')
        })

    return jsonify({
        'vms': vms,
        'services': services
    })


# =============================================================================
# Providers & Domains
# =============================================================================

@api_bp.route('/providers', methods=['GET'])
def list_providers():
    """List all cloud providers."""
    config = load_config()
    return jsonify({'providers': config.get('providers', {})})


@api_bp.route('/domains', methods=['GET'])
def list_domains():
    """List all domains and subdomains."""
    config = load_config()
    return jsonify(config.get('domains', {}))
