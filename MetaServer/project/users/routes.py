from flask import render_template

from . import users_blueprint
from .forms import RegisterForm, LoginForm, ForgottenPasswordForm


@users_blueprint.route('/register')
def register():
	return render_template('users/register.html', title='Register', form=RegisterForm())

@users_blueprint.route('/login')
def login():
	return render_template('users/login.html', title='Log in', form=LoginForm())

@users_blueprint.route('/forgotten_password')
def forgotten_password():
	return render_template('users/forgotten_password.html', title='Forgotten password', form=ForgottenPasswordForm())
