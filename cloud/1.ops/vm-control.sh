#!/bin/bash
# vm-control.sh - Check status or wake oci-p-flex_1 without false triggers
#
# Usage:
#   ./vm-control.sh status   # Check if running (NO WAKE)
#   ./vm-control.sh wake     # Start the VM
#   ./vm-control.sh stop     # Stop the VM (graceful)
#   ./vm-control.sh ssh      # SSH if running, otherwise offer to wake
#
# The status check uses OCI API - it queries Oracle Cloud, NOT the VM itself.
# This means checking status will NEVER accidentally wake the VM.

set -euo pipefail

# === Configuration ===
OCI_INSTANCE_ID="ocid1.instance.oc1.eu-marseille-1.anwxeljruadvczachwpa3qrh7n25vfez3smidz4o7gpmtj4ga4d7zqlja5yq"
VM_IP="84.235.234.87"
VM_USER="ubuntu"
SSH_KEY="/home/diego/Documents/Git/LOCAL_KEYS/00_terminal/ssh/id_rsa"

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# === Functions ===

get_status() {
    # Query OCI API for instance lifecycle state
    # This does NOT wake the VM - it's just an API call to Oracle Cloud
    local state
    state=$(oci compute instance get \
        --instance-id "$OCI_INSTANCE_ID" \
        --query 'data."lifecycle-state"' \
        --raw-output 2>/dev/null) || {
        echo -e "${RED}ERROR: Failed to query OCI API${NC}"
        echo "Make sure 'oci' CLI is configured: oci session validate"
        return 1
    }
    echo "$state"
}

cmd_status() {
    echo -e "${CYAN}Checking oci-p-flex_1 status via OCI API...${NC}"
    echo "(This does NOT wake the VM)"
    echo ""

    local state
    state=$(get_status) || return 1

    case "$state" in
        RUNNING)
            echo -e "Status: ${GREEN}RUNNING${NC}"
            echo -e "IP: ${VM_IP}"
            echo -e "SSH: ssh -i $SSH_KEY ${VM_USER}@${VM_IP}"
            ;;
        STOPPED)
            echo -e "Status: ${YELLOW}STOPPED (dormant)${NC}"
            echo "Run './vm-control.sh wake' to start"
            ;;
        STOPPING)
            echo -e "Status: ${YELLOW}STOPPING...${NC}"
            ;;
        STARTING)
            echo -e "Status: ${CYAN}STARTING...${NC}"
            echo "Wait ~60 seconds, then SSH"
            ;;
        *)
            echo -e "Status: ${RED}$state${NC}"
            ;;
    esac
}

cmd_wake() {
    echo -e "${CYAN}Checking current status...${NC}"
    local state
    state=$(get_status) || return 1

    if [[ "$state" == "RUNNING" ]]; then
        echo -e "${GREEN}VM is already running!${NC}"
        echo -e "SSH: ssh -i $SSH_KEY ${VM_USER}@${VM_IP}"
        return 0
    fi

    if [[ "$state" != "STOPPED" ]]; then
        echo -e "${YELLOW}VM is in state: $state${NC}"
        echo "Cannot start - wait for current operation to complete"
        return 1
    fi

    echo -e "${CYAN}Starting oci-p-flex_1...${NC}"
    oci compute instance action \
        --instance-id "$OCI_INSTANCE_ID" \
        --action START \
        --wait-for-state RUNNING \
        --max-wait-seconds 120 >/dev/null 2>&1 &

    local pid=$!
    echo -n "Waiting for VM to start "

    local count=0
    while kill -0 $pid 2>/dev/null; do
        echo -n "."
        sleep 2
        ((count++))
        if [[ $count -gt 60 ]]; then
            echo ""
            echo -e "${YELLOW}Taking longer than expected. Check OCI console.${NC}"
            break
        fi
    done
    wait $pid || true
    echo ""

    # Verify
    state=$(get_status)
    if [[ "$state" == "RUNNING" ]]; then
        echo -e "${GREEN}VM is now RUNNING!${NC}"
        echo ""
        echo "Waiting for SSH to become available..."
        sleep 10

        local ssh_ready=false
        for i in {1..12}; do
            if timeout 3 nc -z "$VM_IP" 22 2>/dev/null; then
                ssh_ready=true
                break
            fi
            echo -n "."
            sleep 5
        done
        echo ""

        if $ssh_ready; then
            echo -e "${GREEN}SSH is ready!${NC}"
            echo -e "SSH: ssh -i $SSH_KEY ${VM_USER}@${VM_IP}"
        else
            echo -e "${YELLOW}SSH not yet available. Try again in a minute.${NC}"
        fi
    else
        echo -e "${YELLOW}VM state: $state${NC}"
    fi
}

cmd_stop() {
    echo -e "${CYAN}Checking current status...${NC}"
    local state
    state=$(get_status) || return 1

    if [[ "$state" == "STOPPED" ]]; then
        echo -e "${YELLOW}VM is already stopped${NC}"
        return 0
    fi

    if [[ "$state" != "RUNNING" ]]; then
        echo -e "${YELLOW}VM is in state: $state${NC}"
        echo "Cannot stop - wait for current operation to complete"
        return 1
    fi

    echo -e "${CYAN}Stopping oci-p-flex_1 (graceful)...${NC}"
    oci compute instance action \
        --instance-id "$OCI_INSTANCE_ID" \
        --action SOFTSTOP \
        --wait-for-state STOPPED \
        --max-wait-seconds 180 >/dev/null 2>&1 &

    local pid=$!
    echo -n "Waiting for VM to stop "

    while kill -0 $pid 2>/dev/null; do
        echo -n "."
        sleep 2
    done
    wait $pid || true
    echo ""

    state=$(get_status)
    if [[ "$state" == "STOPPED" ]]; then
        echo -e "${GREEN}VM is now STOPPED${NC}"
    else
        echo -e "${YELLOW}VM state: $state${NC}"
    fi
}

cmd_ssh() {
    local state
    state=$(get_status) || return 1

    if [[ "$state" == "RUNNING" ]]; then
        echo -e "${GREEN}VM is running. Connecting...${NC}"
        exec ssh -i "$SSH_KEY" "${VM_USER}@${VM_IP}"
    else
        echo -e "${YELLOW}VM is $state${NC}"
        read -p "Wake the VM? [y/N] " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            cmd_wake
            echo ""
            echo -e "${CYAN}Connecting...${NC}"
            exec ssh -i "$SSH_KEY" "${VM_USER}@${VM_IP}"
        fi
    fi
}

# === Main ===

case "${1:-}" in
    status|s)
        cmd_status
        ;;
    wake|start|w)
        cmd_wake
        ;;
    stop)
        cmd_stop
        ;;
    ssh)
        cmd_ssh
        ;;
    *)
        echo "vm-control.sh - Manage oci-p-flex_1 wake-on-demand VM"
        echo ""
        echo "Usage:"
        echo "  $0 status   Check if VM is running (NO WAKE)"
        echo "  $0 wake     Start the VM"
        echo "  $0 stop     Stop the VM (graceful)"
        echo "  $0 ssh      SSH (will offer to wake if stopped)"
        echo ""
        echo "The 'status' command queries OCI API, not the VM."
        echo "This means checking status will NEVER accidentally wake the VM."
        ;;
esac
