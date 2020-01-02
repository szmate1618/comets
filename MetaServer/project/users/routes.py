from flask import render_template

from . import users_blueprint


@users_blueprint.route('/register')
def register():
	return render_template('users/register.html')
