from flask import Flask

from project.users import users_blueprint


app = Flask(__name__)
app.register_blueprint(users_blueprint)

@app.route('/')
def index():
	return "Hello World!"
