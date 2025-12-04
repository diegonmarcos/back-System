#!/usr/bin/env python3
"""
Cloud Dashboard Flask Server - Entry point

This simply calls the unified cloud_dash.py with 'serve' mode.
The main source of truth is in /home/diego/Documents/Git/back-System/cloud/0.spec/cloud_dash.py
"""
import os
import sys

# Add the script directory to path
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))

# Import and run from unified script
from cloud_dash import run_server

if __name__ == '__main__':
    debug = os.environ.get('FLASK_DEBUG', 'false').lower() == 'true'
    host = os.environ.get('FLASK_HOST', '0.0.0.0')
    port = int(os.environ.get('FLASK_PORT', 5000))

    run_server(host=host, port=port, debug=debug)
