#!/bin/bash
# Matomo Anti-Blocker Proxy Setup
# Creates disguised endpoints to avoid browser ad-blockers

set -e

echo "======================================"
echo "Matomo Anti-Blocker Proxy Setup"
echo "======================================"

# Create multiple disguised endpoints
echo ""
echo "[1/5] Creating disguised tracking endpoints..."

ssh ubuntu@130.110.251.193 'docker exec matomo-app bash -c "
# Create collect.php (main tracking endpoint)
cat > /var/www/html/collect.php << '"'"'EOFCOLLECT'"'"'
<?php
// Analytics data collector
define(\"MATOMO_INCLUDE_PATH\", __DIR__);
\$_SERVER[\"SCRIPT_NAME\"] = \"/matomo.php\";
\$_SERVER[\"PHP_SELF\"] = \"/matomo.php\";
require __DIR__ . \"/matomo.php\";
EOFCOLLECT

# Create api.php (looks like a regular API)
cat > /var/www/html/api.php << '"'"'EOFAPI'"'"'
<?php
// API endpoint handler
define(\"MATOMO_INCLUDE_PATH\", __DIR__);
\$_SERVER[\"SCRIPT_NAME\"] = \"/matomo.php\";
\$_SERVER[\"PHP_SELF\"] = \"/matomo.php\";
require __DIR__ . \"/matomo.php\";
EOFAPI

# Create track.php (simple name)
cat > /var/www/html/track.php << '"'"'EOFTRACK'"'"'
<?php
// Tracking endpoint
define(\"MATOMO_INCLUDE_PATH\", __DIR__);
\$_SERVER[\"SCRIPT_NAME\"] = \"/matomo.php\";
\$_SERVER[\"PHP_SELF\"] = \"/matomo.php\";
require __DIR__ . \"/matomo.php\";
EOFTRACK

echo 'Created disguised tracking endpoints'
ls -lh /var/www/html/*.php | grep -E 'collect|api|track'
"'

echo "✓ Tracking endpoints created"

echo ""
echo "[2/5] Creating disguised JavaScript tracker..."

ssh ubuntu@130.110.251.193 'docker exec matomo-app bash -c "
# Create stats.js (looks like analytics lib)
cat > /var/www/html/stats.js << '"'"'EOFSTATS'"'"'
/* Analytics Library */
(function(){
  var s = document.createElement('"'"'script'"'"');
  s.src = '"'"'/matomo.js'"'"';
  s.async = true;
  s.onload = function() {
    if (typeof Matomo !== '"'"'undefined'"'"') {
      console.log('"'"'Analytics initialized'"'"');
    }
  };
  document.head.appendChild(s);
})();
EOFSTATS

echo 'Created disguised JS tracker'
ls -lh /var/www/html/stats.js
"'

echo "✓ JavaScript tracker created"

echo ""
echo "[3/5] Testing endpoints..."

for endpoint in collect.php api.php track.php; do
  STATUS=$(curl -s -o /dev/null -w "%{http_code}" "https://analytics.diegonmarcos.com/$endpoint")
  if [ "$STATUS" = "400" ] || [ "$STATUS" = "200" ]; then
    echo "  ✓ $endpoint is accessible (HTTP $STATUS)"
  else
    echo "  ✗ $endpoint returned HTTP $STATUS"
  fi
done

echo "✓ All endpoints tested"

echo ""
echo "[4/5] Endpoint summary..."
echo ""
echo "Available disguised endpoints:"
echo "  • https://analytics.diegonmarcos.com/collect.php (main)"
echo "  • https://analytics.diegonmarcos.com/api.php"
echo "  • https://analytics.diegonmarcos.com/track.php"
echo "  • https://analytics.diegonmarcos.com/stats.js"
echo ""
echo "Original endpoints (still work):"
echo "  • https://analytics.diegonmarcos.com/matomo.php"
echo "  • https://analytics.diegonmarcos.com/matomo.js"
echo ""

echo "[5/5] Configuration notes..."
echo ""
echo "To use in Matomo Tag Manager:"
echo "  1. Go to Tag Manager → Variables"
echo "  2. Edit 'Matomo Configuration'"
echo "  3. Set 'Custom Tracking Endpoint': collect.php"
echo "  4. Set 'Custom JS Endpoint': stats.js"
echo "  5. Publish container"
echo ""

echo "======================================"
echo "Setup Complete!"
echo "======================================"
echo ""
echo "Next: Publish container v7 with these endpoints"
