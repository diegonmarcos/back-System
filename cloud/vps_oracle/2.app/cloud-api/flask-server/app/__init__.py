"""
Cloud Dashboard Flask Server
API backend for cloud infrastructure monitoring and management
"""
import os
from flask import Flask
from flask_cors import CORS


def create_app():
    """Application factory."""
    app = Flask(__name__, template_folder='../templates')
    CORS(app, supports_credentials=True)

    # Load config
    app.config.from_mapping(
        SECRET_KEY=os.environ.get('JWT_SECRET_KEY', 'dev-key-change-in-production'),
        JSON_CONFIG_PATH=os.environ.get('CLOUD_CONFIG_PATH', '/opt/cloud-dashboard/cloud-infrastructure.json'),
    )

    # Register blueprints
    from app.routes import api_bp
    from app.web import web_bp
    from app.auth import auth_bp
    from app.admin import admin_bp

    app.register_blueprint(api_bp, url_prefix='/api')
    app.register_blueprint(auth_bp, url_prefix='/api/auth')
    app.register_blueprint(admin_bp, url_prefix='/api/admin')
    app.register_blueprint(web_bp)  # Serves at / for HTML dashboard

    return app
