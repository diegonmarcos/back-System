#!/bin/bash
# Oracle ARM Instance Creator with Auto-Retry
# Keeps trying until capacity becomes available

set -e

# Configuration
COMPARTMENT_ID="ocid1.tenancy.oc1..aaaaaaaate22jsouuzgaw65ucwvufcj3lzjxw4ithwcz3cxw6iom6ys2ldsq"
AVAILABILITY_DOMAIN="bRpM:EU-MARSEILLE-1-AD-1"
SUBNET_ID="ocid1.subnet.oc1.eu-marseille-1.aaaaaaaapz6g4htlyisp45zplqi47t3mms4noceyqebb5huhccrlt432ugeq"
IMAGE_ID="ocid1.image.oc1.eu-marseille-1.aaaaaaaar3pm2xlih5tqkjwr7ykfgzixjytjivkacgmqrlxi66vzlf5a2wlq"
SSH_KEY_FILE="/home/diego/.ssh/id_rsa.pub"
INSTANCE_NAME="arm-server"
OCPUS=2
MEMORY_GB=12
BOOT_VOLUME_GB=50
RETRY_INTERVAL=60  # seconds between retries

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m'

export SUPPRESS_LABEL_WARNING=True

echo -e "${GREEN}=== Oracle ARM Instance Creator ===${NC}"
echo -e "Instance: ${INSTANCE_NAME}"
echo -e "Shape: VM.Standard.A1.Flex (${OCPUS} OCPU, ${MEMORY_GB}GB RAM)"
echo -e "Region: eu-marseille-1"
echo ""

attempt=1
while true; do
    echo -e "${YELLOW}[$(date '+%Y-%m-%d %H:%M:%S')] Attempt #${attempt}...${NC}"

    result=$(oci compute instance launch \
        --compartment-id "$COMPARTMENT_ID" \
        --availability-domain "$AVAILABILITY_DOMAIN" \
        --shape "VM.Standard.A1.Flex" \
        --shape-config "{\"ocpus\": $OCPUS, \"memoryInGBs\": $MEMORY_GB}" \
        --subnet-id "$SUBNET_ID" \
        --image-id "$IMAGE_ID" \
        --display-name "$INSTANCE_NAME" \
        --assign-public-ip true \
        --ssh-authorized-keys-file "$SSH_KEY_FILE" \
        --boot-volume-size-in-gbs "$BOOT_VOLUME_GB" 2>&1) || true

    if echo "$result" | grep -q "Out of host capacity"; then
        echo -e "${RED}Out of capacity. Retrying in ${RETRY_INTERVAL}s...${NC}"
        sleep $RETRY_INTERVAL
        ((attempt++))
    elif echo "$result" | grep -q '"lifecycle-state"'; then
        echo -e "${GREEN}=== Instance Created! ===${NC}"
        echo "$result" | python3 -c "import sys,json; d=json.load(sys.stdin)['data']; print(f\"Instance ID: {d['id']}\"); print(f\"State: {d['lifecycle-state']}\")"

        # Wait for running state
        instance_id=$(echo "$result" | python3 -c "import sys,json; print(json.load(sys.stdin)['data']['id'])")
        echo -e "${YELLOW}Waiting for instance to be RUNNING...${NC}"

        oci compute instance get --instance-id "$instance_id" --wait-for-state RUNNING --wait-interval-seconds 15

        # Get public IP
        echo -e "${YELLOW}Getting public IP...${NC}"
        sleep 10
        vnic_attachment=$(oci compute vnic-attachment list --compartment-id "$COMPARTMENT_ID" --instance-id "$instance_id" --query "data[0].\"vnic-id\"" --raw-output)
        public_ip=$(oci network vnic get --vnic-id "$vnic_attachment" --query "data.\"public-ip\"" --raw-output)

        echo ""
        echo -e "${GREEN}=== SUCCESS ===${NC}"
        echo -e "Instance ID: ${instance_id}"
        echo -e "Public IP: ${GREEN}${public_ip}${NC}"
        echo -e "SSH: ${GREEN}ssh ubuntu@${public_ip}${NC}"
        echo ""
        echo -e "Instance details saved to: ~/arm-instance-info.txt"

        cat > ~/arm-instance-info.txt << EOF
ARM Instance Info
=================
Instance ID: ${instance_id}
Public IP: ${public_ip}
SSH: ssh ubuntu@${public_ip}
Shape: VM.Standard.A1.Flex (${OCPUS} OCPU, ${MEMORY_GB}GB RAM)
Region: eu-marseille-1
Created: $(date)
EOF

        exit 0
    else
        echo -e "${RED}Unexpected error:${NC}"
        echo "$result"
        echo -e "${YELLOW}Retrying in ${RETRY_INTERVAL}s...${NC}"
        sleep $RETRY_INTERVAL
        ((attempt++))
    fi
done
