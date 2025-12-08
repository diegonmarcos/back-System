-- PhotoView Auto-Login Module
-- Automatically injects PhotoView authentication after Authelia 2FA passes
-- This bypasses PhotoView's internal login since Authelia provides 2FA
--
-- Location on GCP VM: /home/diego/npm/data/photoview_autologin.lua
-- Used by: NPM proxy for photos.diegonmarcos.com

local _M = {}

local http = require "resty.http"
local cjson = require "cjson"

-- PhotoView configuration
local PHOTOVIEW_HOST = "10.0.0.2"
local PHOTOVIEW_PORT = 8080
local PHOTOVIEW_USER = "me@diegonmarcos.com"
local PHOTOVIEW_PASS = "ogeid1A!"

-- Token cache key
local CACHE_KEY = "photoview_token"
local TOKEN_TTL = 86400 -- 24 hours

local function get_cached_token()
    local tokens = ngx.shared.photoview_tokens
    if not tokens then
        ngx.log(ngx.WARN, "[PhotoView AutoLogin] Shared dict not available")
        return nil
    end
    return tokens:get(CACHE_KEY)
end

local function cache_token(token)
    local tokens = ngx.shared.photoview_tokens
    if tokens then
        local ok, err = tokens:set(CACHE_KEY, token, TOKEN_TTL)
        if not ok then
            ngx.log(ngx.WARN, "[PhotoView AutoLogin] Failed to cache token: ", err)
        else
            ngx.log(ngx.INFO, "[PhotoView AutoLogin] Token cached successfully")
        end
    end
end

local function fetch_new_token()
    local httpc = http.new()
    httpc:set_timeout(5000) -- 5 second timeout

    local graphql_query = string.format(
        '{"query": "mutation { authorizeUser(username: \\"%s\\", password: \\"%s\\") { success status token } }"}',
        PHOTOVIEW_USER, PHOTOVIEW_PASS
    )

    local res, err = httpc:request_uri(
        string.format("http://%s:%d/api/graphql", PHOTOVIEW_HOST, PHOTOVIEW_PORT),
        {
            method = "POST",
            body = graphql_query,
            headers = {
                ["Content-Type"] = "application/json",
            }
        }
    )

    if not res then
        ngx.log(ngx.ERR, "[PhotoView AutoLogin] HTTP request failed: ", err)
        return nil
    end

    if res.status ~= 200 then
        ngx.log(ngx.ERR, "[PhotoView AutoLogin] GraphQL returned status: ", res.status)
        return nil
    end

    local ok, data = pcall(cjson.decode, res.body)
    if not ok then
        ngx.log(ngx.ERR, "[PhotoView AutoLogin] JSON decode failed: ", data)
        return nil
    end

    if data.data and data.data.authorizeUser and data.data.authorizeUser.success then
        local token = data.data.authorizeUser.token
        ngx.log(ngx.INFO, "[PhotoView AutoLogin] Got new token")
        return token
    else
        ngx.log(ngx.ERR, "[PhotoView AutoLogin] Auth failed: ", res.body)
        return nil
    end
end

function _M.inject_auth()
    -- Only inject if Authelia passed (auth_request succeeded)
    -- This function is called in access_by_lua_block after auth_request

    -- Try to get cached token first
    local token = get_cached_token()

    if not token then
        ngx.log(ngx.INFO, "[PhotoView AutoLogin] No cached token, fetching new one")
        token = fetch_new_token()
        if token then
            cache_token(token)
        end
    end

    if token then
        -- Inject the token as a cookie that PhotoView expects
        local existing_cookie = ngx.var.http_cookie or ""
        if existing_cookie ~= "" then
            ngx.req.set_header("Cookie", existing_cookie .. "; auth-token=" .. token)
        else
            ngx.req.set_header("Cookie", "auth-token=" .. token)
        end
        ngx.log(ngx.DEBUG, "[PhotoView AutoLogin] Token injected into Cookie header")
    else
        ngx.log(ngx.WARN, "[PhotoView AutoLogin] No token available, proceeding without auto-login")
    end
end

return _M
