from flask import Blueprint


ships_blueprint = Blueprint('ships', __name__, template_folder='templates')


from . import routes
