from flask import render_template, flash, redirect, url_for
from flask_login import current_user, login_user, logout_user

from . import users_blueprint
from .forms import RegisterForm, LoginForm, ForgottenPasswordForm
from project.models import User, LoginEvent
from project import db


@users_blueprint.route('/register', methods=['GET', 'POST'])
def register():
	form = RegisterForm()
	if form.validate_on_submit():
		new_user = User(Username=form.username.data, EmailAddress=form.email_address.data)
		new_user.set_password(form.password.data)
		db.session.add(new_user)
		db.session.commit()
		flash(f"Registration sent. Please check your email ({form.email_address.data}) to confirm your registration.")
		return redirect(url_for('index'))
	return render_template('users/register.html', title='Register', form=form)

@users_blueprint.route('/login', methods=['GET', 'POST'])
def login():
	if current_user.is_authenticated:
		return redirect(url_for('index'))
	form = LoginForm()
	if form.validate_on_submit():
		user = User.query.filter_by(EmailAddress=form.email_address.data).first()
		if user is None or not user.check_password(form.password.data):
			flash('Invalid username or password.')
			return redirect(url_for('login'))
		login_user(user, remember=form.remember_me.data)
		flash("Logged in successfully.")
		return redirect(url_for('index'))
	return render_template('users/login.html', title='Log in', form=form)

@users_blueprint.route('/logout')
def logout():
	logout_user()
	flash("Logged out successfully.")
	return redirect(url_for('index'))

@users_blueprint.route('/forgotten_password', methods=['GET', 'POST'])
def forgotten_password():
	form = ForgottenPasswordForm()
	if form.validate_on_submit():
		flash(f"New password sent to {form.email_address.data}. Please change it after first log in.")
		return redirect(url_for('index'))
	return render_template('users/forgotten_password.html', title='Forgotten password', form=form)
