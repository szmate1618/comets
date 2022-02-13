from flask_wtf import FlaskForm
from wtforms import StringField, PasswordField, BooleanField, SubmitField
from wtforms.fields.html5 import EmailField
from wtforms.validators import DataRequired, Email, EqualTo, ValidationError
from project.models import User


class RegisterForm(FlaskForm):
	email_address = EmailField('Email', validators=[DataRequired(), Email()])
	username = StringField('Username', validators=[DataRequired()])
	password = PasswordField('Password', validators=[DataRequired()])
	confirm_password = PasswordField('Confirm password', validators=[EqualTo('password', message='Passwords must match.')])
	submit = SubmitField('Register')

	def validate_username(self, username):
		user = User.query.filter_by(Username=username.data).first()
		if user is not None:
			raise ValidationError('Username already taken.')

	def validate_email_address(self, email):
		user = User.query.filter_by(EmailAddress=email.data).first()
		if user is not None:
			raise ValidationError('Email address already registered for an other user.')

class LoginForm(FlaskForm):
	email_address = EmailField('Email', validators=[DataRequired()])
	password = PasswordField('Password', validators=[DataRequired()])
	remember_me = BooleanField('Remember me')
	submit = SubmitField('Log In')

class ForgottenPasswordForm(FlaskForm):
	email_address = EmailField('Email', validators=[DataRequired()])
	submit = SubmitField('Register')
