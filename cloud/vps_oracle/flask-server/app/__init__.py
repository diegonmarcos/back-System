"""
Cloud Dashboard Flask Server
API backend for cloud infrastructure monitoring and management
"""
from flask import Flask
from flask_cors import CORS


def create_app():
    """Application factory."""
    app = Flask(__name__, template_folder='../templates')
    CORS(app)

    # Load config
    app.config.from_mapping(
        SECRET_KEY='dev-key-change-in-production',
        JSON_CONFIG_PATH='/opt/cloud-dashboard/cloud-infrastructure.json',
    )

    # Register blueprints
    from app.routes import api_bp
    from app.web import web_bp

    app.register_blueprint(api_bp, url_prefix='/api')
    app.register_blueprint(web_bp)  # Serves at / for HTML dashboard

    return app
