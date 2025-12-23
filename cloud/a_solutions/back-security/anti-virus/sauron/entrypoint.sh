#!/bin/bash
set -e

RULES_DIR="${RULES_DIR:-/etc/sauron/yara-rules}"
WATCH_DIR="${WATCH_DIR:-/watch}"
OUTPUT_FILE="${OUTPUT_FILE:-/var/log/sauron/alerts.jsonl}"
LOG_FILE="${LOG_FILE:-/var/log/sauron/sauron.log}"

echo "[$(date -Iseconds)] Sauron starting..." | tee -a "$LOG_FILE"
echo "[$(date -Iseconds)] Watching: $WATCH_DIR" | tee -a "$LOG_FILE"
echo "[$(date -Iseconds)] Rules: $RULES_DIR" | tee -a "$LOG_FILE"

# Ensure output directory exists
mkdir -p "$(dirname "$OUTPUT_FILE")"

# Change to watch directory (sauron watches current dir in realtime mode)
cd "$WATCH_DIR"

# Run sauron in realtime monitoring mode with JSON output
# It will monitor the current directory for file changes
exec /usr/local/bin/sauron \
    --rules "$RULES_DIR" \
    --report-json \
    --report-output "$OUTPUT_FILE" \
    --report-errors \
    2>&1 | tee -a "$LOG_FILE"
