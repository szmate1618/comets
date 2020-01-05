from flask import render_template, flash, redirect, url_for

from . import users_blueprint
from .forms import RegisterForm, LoginForm, ForgottenPasswordForm
from project.models import User, LoginEvent
from project import db


@users_blueprint.route('/register', methods=['GET', 'POST'])
def register():
	form = RegisterForm()
	if form.validate_on_submit():
		new_user = User(Username=form.username.data, EmailAddress=form.email_address.data, PasswordHash='asdasd')
		db.session.add(new_user)
		db.session.commit()
		flash(f"Registration sent. Please check your email ({form.email_address.data}) to confirm your registration.")
		return redirect(url_for('index'))
	return render_template('users/register.html', title='Register', form=form)

@users_blueprint.route('/login', methods=['GET', 'POST'])
def login():
	form = LoginForm()
	if form.validate_on_submit():
		flash(f"Successfully logged in.")
		return redirect(url_for('index'))
	return render_template('users/login.html', title='Log in', form=form)

@users_blueprint.route('/forgotten_password', methods=['GET', 'POST'])
def forgotten_password():
	form = ForgottenPasswordForm()
	if form.validate_on_submit():
		flash(f"New password sent to {form.email_address.data}. Please change it after first log in.")
		return redirect(url_for('index'))
	return render_template('users/forgotten_password.html', title='Forgotten password', form=form)
