#!/bin/sh
# Cloud Infrastructure Dashboard
# POSIX-compliant TUI for managing VMs and services
# Version: 1.0.0
# Last Updated: 2025-12-01

set -e

#=============================================================================
# CONFIGURATION
#=============================================================================

# Colors (ANSI escape codes)
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
BOLD='\033[1m'
DIM='\033[2m'
NC='\033[0m' # No Color

# VM Configuration
VM1_NAME="web-server-1"
VM1_IP="130.110.251.193"
VM1_USER="ubuntu"
VM1_KEY="$HOME/.ssh/matomo_key"
VM1_SERVICES="matomo-app matomo-db nginx-proxy syncthing"

VM2_NAME="services-server-1"
VM2_IP="129.151.228.66"
VM2_USER="ubuntu"
VM2_KEY="$HOME/.ssh/matomo_key"
VM2_SERVICES="n8n nginx-proxy"

# Service to domain mapping
MATOMO_URL="https://analytics.diegonmarcos.com"
SYNCTHING_URL="https://sync.diegonmarcos.com"
N8N_URL="https://n8n.diegonmarcos.com"

# Timeouts
SSH_TIMEOUT=10
PING_TIMEOUT=5
CURL_TIMEOUT=10

#=============================================================================
# UTILITY FUNCTIONS
#=============================================================================

# Clear screen and move cursor to top
clear_screen() {
    printf '\033[2J\033[H'
}

# Print colored text
print_color() {
    color="$1"
    shift
    printf "%b%s%b" "$color" "$*" "$NC"
}

# Print a horizontal line
print_line() {
    char="${1:-─}"
    width="${2:-80}"
    i=0
    while [ $i -lt "$width" ]; do
        printf "%s" "$char"
        i=$((i + 1))
    done
    printf "\n"
}

# Print centered text
print_centered() {
    text="$1"
    width="${2:-80}"
    text_len=${#text}
    padding=$(( (width - text_len) / 2 ))
    printf "%*s%s\n" "$padding" "" "$text"
}

# Print a box header
print_box_header() {
    title="$1"
    width="${2:-78}"
    printf "┌"
    print_line "─" "$width"
    printf "┐\n"
    printf "│ %b%-*s%b │\n" "$BOLD$CYAN" "$((width - 1))" "$title" "$NC"
    printf "├"
    print_line "─" "$width"
    printf "┤\n"
}

# Print a box footer
print_box_footer() {
    width="${1:-78}"
    printf "└"
    print_line "─" "$width"
    printf "┘\n"
}

# Print a box row
print_box_row() {
    content="$1"
    width="${2:-78}"
    # Strip ANSI codes for length calculation
    clean_content=$(printf "%s" "$content" | sed 's/\x1b\[[0-9;]*m//g')
    content_len=${#clean_content}
    padding=$((width - content_len - 1))
    if [ $padding -lt 0 ]; then
        padding=0
    fi
    printf "│ %b%*s │\n" "$content" "$padding" ""
}

# Show a spinner while waiting
show_spinner() {
    pid=$1
    message="${2:-Loading...}"
    spin='⠋⠙⠹⠸⠼⠴⠦⠧⠇⠏'
    i=0
    while kill -0 "$pid" 2>/dev/null; do
        i=$(( (i + 1) % 10 ))
        char=$(printf "%s" "$spin" | cut -c$((i + 1)))
        printf "\r%b %s %s" "$CYAN" "$char" "$message$NC"
        sleep 0.1
    done
    printf "\r%*s\r" 50 ""
}

# Press any key to continue
press_any_key() {
    printf "\n%bPress any key to continue...%b" "$DIM" "$NC"
    stty -echo -icanon
    dd bs=1 count=1 2>/dev/null
    stty echo icanon
    printf "\n"
}

# Confirm action
confirm_action() {
    message="$1"
    printf "%b%s [y/N]: %b" "$YELLOW" "$message" "$NC"
    read -r response
    case "$response" in
        [yY]|[yY][eE][sS]) return 0 ;;
        *) return 1 ;;
    esac
}

#=============================================================================
# STATUS CHECK FUNCTIONS
#=============================================================================

# Check if host is reachable via ping
check_ping() {
    host="$1"
    if ping -c 1 -W "$PING_TIMEOUT" "$host" >/dev/null 2>&1; then
        return 0
    else
        return 1
    fi
}

# Check if SSH is accessible
check_ssh() {
    host="$1"
    user="$2"
    key="$3"
    if ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$host" "echo ok" >/dev/null 2>&1; then
        return 0
    else
        return 1
    fi
}

# Check HTTP/HTTPS endpoint
check_http() {
    url="$1"
    if curl -s -o /dev/null -w "%{http_code}" --connect-timeout "$CURL_TIMEOUT" "$url" | grep -q "^[23]"; then
        return 0
    else
        return 1
    fi
}

# Get VM status
get_vm_status() {
    ip="$1"
    user="$2"
    key="$3"

    # Check ping first
    if ! check_ping "$ip"; then
        printf "OFFLINE"
        return
    fi

    # Check SSH
    if check_ssh "$ip" "$user" "$key"; then
        printf "ONLINE"
    else
        printf "UNREACHABLE"
    fi
}

# Get service status from Docker
get_docker_status() {
    ip="$1"
    user="$2"
    key="$3"
    container="$4"

    status=$(ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker inspect -f '{{.State.Status}}' $container 2>/dev/null" 2>/dev/null || echo "error")

    case "$status" in
        running) printf "RUNNING" ;;
        exited) printf "STOPPED" ;;
        paused) printf "PAUSED" ;;
        restarting) printf "RESTARTING" ;;
        *) printf "UNKNOWN" ;;
    esac
}

# Get all container statuses from a VM
get_all_containers() {
    ip="$1"
    user="$2"
    key="$3"

    ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker ps -a --format '{{.Names}}|{{.Status}}|{{.Ports}}'" 2>/dev/null
}

# Get system stats from VM
get_system_stats() {
    ip="$1"
    user="$2"
    key="$3"

    ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "echo \"CPU: \$(top -bn1 | grep 'Cpu(s)' | awk '{print \$2}')% | RAM: \$(free -h | awk '/^Mem:/{print \$3\"/\"\$2}') | Disk: \$(df -h / | awk 'NR==2{print \$3\"/\"\$2}')\"" 2>/dev/null
}

#=============================================================================
# SERVICE MANAGEMENT FUNCTIONS
#=============================================================================

# Restart a Docker container
restart_container() {
    ip="$1"
    user="$2"
    key="$3"
    container="$4"

    printf "%bRestarting %s...%b\n" "$YELLOW" "$container" "$NC"

    result=$(ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker restart $container" 2>&1)

    if [ $? -eq 0 ]; then
        printf "%b✓ Container %s restarted successfully%b\n" "$GREEN" "$container" "$NC"
        return 0
    else
        printf "%b✗ Failed to restart %s: %s%b\n" "$RED" "$container" "$result" "$NC"
        return 1
    fi
}

# Stop a Docker container
stop_container() {
    ip="$1"
    user="$2"
    key="$3"
    container="$4"

    printf "%bStopping %s...%b\n" "$YELLOW" "$container" "$NC"

    result=$(ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker stop $container" 2>&1)

    if [ $? -eq 0 ]; then
        printf "%b✓ Container %s stopped%b\n" "$GREEN" "$container" "$NC"
        return 0
    else
        printf "%b✗ Failed to stop %s: %s%b\n" "$RED" "$container" "$result" "$NC"
        return 1
    fi
}

# Start a Docker container
start_container() {
    ip="$1"
    user="$2"
    key="$3"
    container="$4"

    printf "%bStarting %s...%b\n" "$YELLOW" "$container" "$NC"

    result=$(ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker start $container" 2>&1)

    if [ $? -eq 0 ]; then
        printf "%b✓ Container %s started%b\n" "$GREEN" "$container" "$NC"
        return 0
    else
        printf "%b✗ Failed to start %s: %s%b\n" "$RED" "$container" "$result" "$NC"
        return 1
    fi
}

# View container logs
view_container_logs() {
    ip="$1"
    user="$2"
    key="$3"
    container="$4"
    lines="${5:-50}"

    printf "%b═══ Last %s lines of %s logs ═══%b\n\n" "$CYAN" "$lines" "$container" "$NC"

    ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        "sudo docker logs --tail $lines $container" 2>&1

    printf "\n%b═══ End of logs ═══%b\n" "$CYAN" "$NC"
}

# Reboot VM
reboot_vm() {
    ip="$1"
    user="$2"
    key="$3"
    name="$4"

    if confirm_action "Are you sure you want to reboot $name ($ip)?"; then
        printf "%bRebooting %s...%b\n" "$YELLOW" "$name" "$NC"

        ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
            "sudo reboot" 2>/dev/null

        printf "%b✓ Reboot command sent. VM will be back online in ~1 minute.%b\n" "$GREEN" "$NC"
        return 0
    else
        printf "%bReboot cancelled.%b\n" "$YELLOW" "$NC"
        return 1
    fi
}

#=============================================================================
# DISPLAY FUNCTIONS
#=============================================================================

# Display main dashboard
display_dashboard() {
    clear_screen

    printf "\n"
    print_color "$BOLD$CYAN" "  ╔══════════════════════════════════════════════════════════════════════════╗\n"
    print_color "$BOLD$CYAN" "  ║                    CLOUD INFRASTRUCTURE DASHBOARD                        ║\n"
    print_color "$BOLD$CYAN" "  ╚══════════════════════════════════════════════════════════════════════════╝\n"
    printf "\n"

    # VM Status Section
    print_color "$BOLD$WHITE" "  ┌─ VIRTUAL MACHINES ─────────────────────────────────────────────────────┐\n"
    printf "  │                                                                          │\n"

    # VM 1 Status
    printf "  │  "
    vm1_status=$(get_vm_status "$VM1_IP" "$VM1_USER" "$VM1_KEY")
    case "$vm1_status" in
        ONLINE) print_color "$GREEN" "● ONLINE  " ;;
        OFFLINE) print_color "$RED" "○ OFFLINE " ;;
        *) print_color "$YELLOW" "◐ UNKNOWN " ;;
    esac
    printf " %-20s  %-15s  " "$VM1_NAME" "$VM1_IP"
    if [ "$vm1_status" = "ONLINE" ]; then
        stats=$(get_system_stats "$VM1_IP" "$VM1_USER" "$VM1_KEY" 2>/dev/null || echo "N/A")
        print_color "$DIM" "$stats"
    fi
    printf "      │\n"

    # VM 2 Status
    printf "  │  "
    vm2_status=$(get_vm_status "$VM2_IP" "$VM2_USER" "$VM2_KEY")
    case "$vm2_status" in
        ONLINE) print_color "$GREEN" "● ONLINE  " ;;
        OFFLINE) print_color "$RED" "○ OFFLINE " ;;
        *) print_color "$YELLOW" "◐ UNKNOWN " ;;
    esac
    printf " %-20s  %-15s  " "$VM2_NAME" "$VM2_IP"
    if [ "$vm2_status" = "ONLINE" ]; then
        stats=$(get_system_stats "$VM2_IP" "$VM2_USER" "$VM2_KEY" 2>/dev/null || echo "N/A")
        print_color "$DIM" "$stats"
    fi
    printf "      │\n"

    printf "  │                                                                          │\n"
    print_color "$BOLD$WHITE" "  └──────────────────────────────────────────────────────────────────────────┘\n"
    printf "\n"

    # Services Section
    print_color "$BOLD$WHITE" "  ┌─ SERVICES ────────────────────────────────────────────────────────────────┐\n"
    printf "  │                                                                          │\n"

    # Check web services
    printf "  │  "
    if check_http "$MATOMO_URL" 2>/dev/null; then
        print_color "$GREEN" "● ONLINE  "
    else
        print_color "$RED" "○ OFFLINE "
    fi
    printf " %-20s  %s\n" "Matomo Analytics" "$MATOMO_URL"
    printf "                                                                            │\n"

    printf "  │  "
    if check_http "$SYNCTHING_URL" 2>/dev/null; then
        print_color "$GREEN" "● ONLINE  "
    else
        print_color "$RED" "○ OFFLINE "
    fi
    printf " %-20s  %s\n" "Syncthing" "$SYNCTHING_URL"
    printf "                                                                            │\n"

    printf "  │  "
    if check_http "$N8N_URL" 2>/dev/null; then
        print_color "$GREEN" "● ONLINE  "
    else
        print_color "$RED" "○ OFFLINE "
    fi
    printf " %-20s  %s\n" "n8n Automation" "$N8N_URL"
    printf "                                                                            │\n"

    printf "  │                                                                          │\n"
    print_color "$BOLD$WHITE" "  └──────────────────────────────────────────────────────────────────────────┘\n"
    printf "\n"

    # Menu
    print_color "$BOLD$WHITE" "  ┌─ COMMANDS ───────────────────────────────────────────────────────────────┐\n"
    printf "  │                                                                          │\n"
    printf "  │   [1] VM Details        [4] Restart Service      [7] SSH to VM          │\n"
    printf "  │   [2] Container Status  [5] View Logs            [8] Open Service URL   │\n"
    printf "  │   [3] Reboot VM         [6] Stop/Start Service   [R] Refresh            │\n"
    printf "  │                                                                          │\n"
    printf "  │   [Q] Quit                                                              │\n"
    printf "  │                                                                          │\n"
    print_color "$BOLD$WHITE" "  └──────────────────────────────────────────────────────────────────────────┘\n"
    printf "\n"
}

# Display VM selection menu
select_vm() {
    printf "\n%bSelect VM:%b\n" "$BOLD" "$NC"
    printf "  [1] %s (%s)\n" "$VM1_NAME" "$VM1_IP"
    printf "  [2] %s (%s)\n" "$VM2_NAME" "$VM2_IP"
    printf "  [0] Cancel\n"
    printf "\nChoice: "
    read -r choice

    case "$choice" in
        1) echo "1" ;;
        2) echo "2" ;;
        *) echo "0" ;;
    esac
}

# Display container selection menu for a VM
select_container() {
    vm_num="$1"

    case "$vm_num" in
        1)
            ip="$VM1_IP"
            user="$VM1_USER"
            key="$VM1_KEY"
            ;;
        2)
            ip="$VM2_IP"
            user="$VM2_USER"
            key="$VM2_KEY"
            ;;
    esac

    printf "\n%bFetching containers...%b\n" "$DIM" "$NC"
    containers=$(get_all_containers "$ip" "$user" "$key")

    if [ -z "$containers" ]; then
        printf "%bNo containers found or VM unreachable%b\n" "$RED" "$NC"
        return 1
    fi

    printf "\n%bSelect Container:%b\n" "$BOLD" "$NC"
    i=1
    echo "$containers" | while IFS='|' read -r name status ports; do
        printf "  [%d] %-20s %s\n" "$i" "$name" "$status"
        i=$((i + 1))
    done
    printf "  [0] Cancel\n"
    printf "\nChoice: "
    read -r choice

    if [ "$choice" = "0" ] || [ -z "$choice" ]; then
        return 1
    fi

    container=$(echo "$containers" | sed -n "${choice}p" | cut -d'|' -f1)
    echo "$container"
}

# Display VM details
display_vm_details() {
    vm_num="$1"

    case "$vm_num" in
        1)
            name="$VM1_NAME"
            ip="$VM1_IP"
            user="$VM1_USER"
            key="$VM1_KEY"
            ;;
        2)
            name="$VM2_NAME"
            ip="$VM2_IP"
            user="$VM2_USER"
            key="$VM2_KEY"
            ;;
    esac

    clear_screen
    printf "\n"
    print_color "$BOLD$CYAN" "  ═══ VM DETAILS: $name ═══\n"
    printf "\n"

    printf "  %bBasic Info:%b\n" "$BOLD" "$NC"
    printf "  ├─ Name: %s\n" "$name"
    printf "  ├─ IP: %s\n" "$ip"
    printf "  └─ User: %s\n" "$user"
    printf "\n"

    printf "  %bFetching live data...%b\n" "$DIM" "$NC"

    # Get detailed system info
    ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" '
        echo "  System Info:"
        echo "  ├─ Hostname: $(hostname)"
        echo "  ├─ Uptime: $(uptime -p)"
        echo "  ├─ Kernel: $(uname -r)"
        echo "  └─ Arch: $(uname -m)"
        echo ""
        echo "  Resources:"
        echo "  ├─ CPU: $(nproc) cores, $(top -bn1 | grep "Cpu(s)" | awk "{print \$2}")% used"
        echo "  ├─ RAM: $(free -h | awk "/^Mem:/{print \$3\"/\"\$2\" used\"}")"
        echo "  └─ Disk: $(df -h / | awk "NR==2{print \$3\"/\"\$2\" used (\"100-\$5\"%% free)\"}")"
        echo ""
        echo "  Docker Containers:"
        sudo docker ps -a --format "  ├─ {{.Names}}: {{.Status}}" | head -10
        echo "  └─ ($(sudo docker ps -q | wc -l) running)"
    ' 2>/dev/null || printf "  %bFailed to connect to VM%b\n" "$RED" "$NC"

    printf "\n"
}

# Display container status for a VM
display_container_status() {
    vm_num="$1"

    case "$vm_num" in
        1)
            name="$VM1_NAME"
            ip="$VM1_IP"
            user="$VM1_USER"
            key="$VM1_KEY"
            ;;
        2)
            name="$VM2_NAME"
            ip="$VM2_IP"
            user="$VM2_USER"
            key="$VM2_KEY"
            ;;
    esac

    clear_screen
    printf "\n"
    print_color "$BOLD$CYAN" "  ═══ CONTAINERS: $name ═══\n"
    printf "\n"

    printf "  %b%-25s %-15s %-30s%b\n" "$BOLD" "CONTAINER" "STATUS" "PORTS" "$NC"
    print_line "─" 75
    printf "\n"

    ssh -i "$key" -o ConnectTimeout="$SSH_TIMEOUT" -o BatchMode=yes -o StrictHostKeyChecking=no "$user@$ip" \
        'sudo docker ps -a --format "{{.Names}}|{{.Status}}|{{.Ports}}"' 2>/dev/null | \
    while IFS='|' read -r cname cstatus cports; do
        # Color based on status
        if echo "$cstatus" | grep -q "^Up"; then
            status_color="$GREEN"
        else
            status_color="$RED"
        fi

        # Truncate long values
        cstatus=$(echo "$cstatus" | cut -c1-15)
        cports=$(echo "$cports" | cut -c1-30)

        printf "  %-25s %b%-15s%b %-30s\n" "$cname" "$status_color" "$cstatus" "$NC" "$cports"
    done

    printf "\n"
}

#=============================================================================
# MAIN MENU HANDLERS
#=============================================================================

handle_vm_details() {
    vm=$(select_vm)
    if [ "$vm" != "0" ]; then
        display_vm_details "$vm"
        press_any_key
    fi
}

handle_container_status() {
    vm=$(select_vm)
    if [ "$vm" != "0" ]; then
        display_container_status "$vm"
        press_any_key
    fi
}

handle_reboot_vm() {
    vm=$(select_vm)
    case "$vm" in
        1) reboot_vm "$VM1_IP" "$VM1_USER" "$VM1_KEY" "$VM1_NAME" ;;
        2) reboot_vm "$VM2_IP" "$VM2_USER" "$VM2_KEY" "$VM2_NAME" ;;
    esac
    [ "$vm" != "0" ] && press_any_key
}

handle_restart_service() {
    vm=$(select_vm)
    if [ "$vm" != "0" ]; then
        container=$(select_container "$vm")
        if [ -n "$container" ]; then
            case "$vm" in
                1) restart_container "$VM1_IP" "$VM1_USER" "$VM1_KEY" "$container" ;;
                2) restart_container "$VM2_IP" "$VM2_USER" "$VM2_KEY" "$container" ;;
            esac
            press_any_key
        fi
    fi
}

handle_view_logs() {
    vm=$(select_vm)
    if [ "$vm" != "0" ]; then
        container=$(select_container "$vm")
        if [ -n "$container" ]; then
            printf "\nLines to show [50]: "
            read -r lines
            lines=${lines:-50}
            clear_screen
            case "$vm" in
                1) view_container_logs "$VM1_IP" "$VM1_USER" "$VM1_KEY" "$container" "$lines" ;;
                2) view_container_logs "$VM2_IP" "$VM2_USER" "$VM2_KEY" "$container" "$lines" ;;
            esac
            press_any_key
        fi
    fi
}

handle_stop_start_service() {
    vm=$(select_vm)
    if [ "$vm" != "0" ]; then
        container=$(select_container "$vm")
        if [ -n "$container" ]; then
            printf "\n[1] Start  [2] Stop  [0] Cancel: "
            read -r action
            case "$action" in
                1)
                    case "$vm" in
                        1) start_container "$VM1_IP" "$VM1_USER" "$VM1_KEY" "$container" ;;
                        2) start_container "$VM2_IP" "$VM2_USER" "$VM2_KEY" "$container" ;;
                    esac
                    ;;
                2)
                    case "$vm" in
                        1) stop_container "$VM1_IP" "$VM1_USER" "$VM1_KEY" "$container" ;;
                        2) stop_container "$VM2_IP" "$VM2_USER" "$VM2_KEY" "$container" ;;
                    esac
                    ;;
            esac
            [ "$action" != "0" ] && press_any_key
        fi
    fi
}

handle_ssh_to_vm() {
    vm=$(select_vm)
    case "$vm" in
        1)
            printf "\n%bConnecting to %s...%b\n" "$CYAN" "$VM1_NAME" "$NC"
            printf "%bType 'exit' to return to dashboard%b\n\n" "$DIM" "$NC"
            ssh -i "$VM1_KEY" -o StrictHostKeyChecking=no "$VM1_USER@$VM1_IP"
            ;;
        2)
            printf "\n%bConnecting to %s...%b\n" "$CYAN" "$VM2_NAME" "$NC"
            printf "%bType 'exit' to return to dashboard%b\n\n" "$DIM" "$NC"
            ssh -i "$VM2_KEY" -o StrictHostKeyChecking=no "$VM2_USER@$VM2_IP"
            ;;
    esac
}

handle_open_service_url() {
    printf "\n%bSelect Service:%b\n" "$BOLD" "$NC"
    printf "  [1] Matomo Analytics (%s)\n" "$MATOMO_URL"
    printf "  [2] Syncthing (%s)\n" "$SYNCTHING_URL"
    printf "  [3] n8n Automation (%s)\n" "$N8N_URL"
    printf "  [4] NPM Admin - web-server-1 (http://%s:81)\n" "$VM1_IP"
    printf "  [5] NPM Admin - services-server-1 (http://%s:81)\n" "$VM2_IP"
    printf "  [0] Cancel\n"
    printf "\nChoice: "
    read -r choice

    url=""
    case "$choice" in
        1) url="$MATOMO_URL" ;;
        2) url="$SYNCTHING_URL" ;;
        3) url="$N8N_URL" ;;
        4) url="http://$VM1_IP:81" ;;
        5) url="http://$VM2_IP:81" ;;
    esac

    if [ -n "$url" ]; then
        printf "%bOpening %s...%b\n" "$CYAN" "$url" "$NC"
        # Try different browsers
        if command -v xdg-open >/dev/null 2>&1; then
            xdg-open "$url" 2>/dev/null &
        elif command -v open >/dev/null 2>&1; then
            open "$url" 2>/dev/null &
        else
            printf "%bCouldn't open browser. URL: %s%b\n" "$YELLOW" "$url" "$NC"
        fi
        sleep 1
    fi
}

#=============================================================================
# MAIN LOOP
#=============================================================================

main() {
    # Check dependencies
    for cmd in ssh curl ping; do
        if ! command -v "$cmd" >/dev/null 2>&1; then
            printf "%bError: Required command '%s' not found%b\n" "$RED" "$cmd" "$NC"
            exit 1
        fi
    done

    while true; do
        display_dashboard

        printf "  Enter command: "
        read -r cmd

        case "$cmd" in
            1) handle_vm_details ;;
            2) handle_container_status ;;
            3) handle_reboot_vm ;;
            4) handle_restart_service ;;
            5) handle_view_logs ;;
            6) handle_stop_start_service ;;
            7) handle_ssh_to_vm ;;
            8) handle_open_service_url ;;
            [rR]) ;; # Refresh - just loop again
            [qQ])
                clear_screen
                printf "%bGoodbye!%b\n" "$CYAN" "$NC"
                exit 0
                ;;
            *)
                printf "%bInvalid command%b\n" "$RED" "$NC"
                sleep 1
                ;;
        esac
    done
}

# Run main function
main "$@"
