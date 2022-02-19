from flask_wtf import FlaskForm
from flask_wtf.file import FileField, FileRequired
from wtforms import StringField, SubmitField
from wtforms.validators import DataRequired


class CreateForm(FlaskForm):
	texture = FileField(validators=[FileRequired()])
	shipname = StringField('Shipname', validators=[DataRequired()])
	submit = SubmitField('Save')
