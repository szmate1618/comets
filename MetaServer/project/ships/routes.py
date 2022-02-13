from flask import render_template, flash, redirect, url_for
from flask_login import current_user, login_user, logout_user, login_required

from . import ships_blueprint
from .forms import CreateForm
#from project.models import User, LoginEvent
#from project import db


@ships_blueprint.route('/create', methods=['GET', 'POST'])
@login_required
def create():
	form = CreateForm()
	if form.validate_on_submit():
		pass
	return render_template('ships/create.html', title='Create', form=form)
