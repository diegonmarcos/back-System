// Cloudflare Email Worker - Stalwart Primary via HTTP Proxy, Gmail Backup
// Flow: Internet -> Cloudflare -> Try Stalwart (via SMTP proxy) -> If fail, forward to Gmail

export default {
  async email(message, env, ctx) {
    const from = message.from;
    const to = message.to;
    console.log(`Email received: ${from} -> ${to}`);
    console.log(`SMTP_PROXY_URL: ${env.SMTP_PROXY_URL}`);

    let stalwartSuccess = false;
    let stalwartError = "";

    // 1. Try Stalwart FIRST (Primary) via HTTP-to-SMTP proxy
    try {
      const rawEmail = await new Response(message.raw).text();
      console.log(`Raw email size: ${rawEmail.length} bytes`);

      // Send to SMTP proxy (runs on VPS behind Cloudflare Tunnel)
      const proxyResponse = await fetch(env.SMTP_PROXY_URL, {
        method: "POST",
        headers: {
          "X-API-Key": env.SMTP_PROXY_KEY,
          "Content-Type": "message/rfc822"
        },
        body: rawEmail
      });

      const responseText = await proxyResponse.text();
      console.log(`Proxy response: ${proxyResponse.status} - ${responseText}`);

      if (proxyResponse.ok) {
        try {
          const result = JSON.parse(responseText);
          if (result.status === "delivered") {
            stalwartSuccess = true;
            console.log(`Stalwart: SUCCESS - Email delivered`);
          } else {
            stalwartError = result.error || "Unknown proxy error";
            console.error(`Stalwart proxy error: ${stalwartError}`);
          }
        } catch (parseErr) {
          stalwartError = `JSON parse error: ${responseText}`;
          console.error(stalwartError);
        }
      } else {
        stalwartError = `HTTP ${proxyResponse.status}: ${responseText}`;
        console.error(`Stalwart proxy HTTP error: ${stalwartError}`);
      }
    } catch (e) {
      stalwartError = e.message;
      console.error(`Stalwart fetch error: ${e.message}`);
    }

    // 2. If Stalwart failed, forward to Gmail (Backup)
    if (!stalwartSuccess) {
      console.log(`Stalwart failed, trying Gmail backup: ${env.GMAIL_BACKUP}`);
      try {
        await message.forward(env.GMAIL_BACKUP);
        console.log(`Gmail BACKUP: Email forwarded successfully`);
      } catch (e) {
        console.error(`Gmail backup failed: ${e.message}`);
        // Last resort: reject so sender knows delivery failed
        message.setReject(`Delivery failed: ${stalwartError || e.message}`);
      }
    }
  }
};
