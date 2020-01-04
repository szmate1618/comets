from flask import render_template

from . import users_blueprint


@users_blueprint.route('/register')
def register():
	return render_template('users/register.html')

@users_blueprint.route('/login')
def login():
	return render_template('users/login.html')

@users_blueprint.route('/forgotten_password')
def forgotten_password():
	return render_template('users/forgotten_password.html')
