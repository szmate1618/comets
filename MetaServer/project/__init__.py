from flask import Flask
from flask_sqlalchemy import SQLAlchemy


db = SQLAlchemy()

def create_app(config_filename=None):
	app = Flask(__name__, instance_relative_config=True)
	app.config.from_pyfile(config_filename)

	db.init_app(app)

	#This import must not precede the instantiation of `db`.
	#That would cause 'cannot import' erros, because of the cyclic references.
	#TODO: Eliminate cyclic references.
	from project.users import users_blueprint
	app.register_blueprint(users_blueprint)

	return app
