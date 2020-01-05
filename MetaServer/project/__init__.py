from flask import Flask
from flask_sqlalchemy import SQLAlchemy

from project.users import users_blueprint


db = SQLAlchemy()

def create_app(config_filename=None):
	app = Flask(__name__, instance_relative_config=True)
	app.config.from_pyfile(config_filename)

	db.init_app(app)

	app.register_blueprint(users_blueprint)

	return app


from . import models
