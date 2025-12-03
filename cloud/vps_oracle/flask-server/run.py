#!/usr/bin/env python3
"""
Cloud Dashboard Flask Server - Entry point
"""
import os
from app import create_app

app = create_app()

if __name__ == '__main__':
    debug = os.environ.get('FLASK_DEBUG', 'false').lower() == 'true'
    host = os.environ.get('FLASK_HOST', '0.0.0.0')
    port = int(os.environ.get('FLASK_PORT', 5000))

    app.run(host=host, port=port, debug=debug)
