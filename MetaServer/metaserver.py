from flask import render_template

from project import create_app


app = create_app('flask.cfg')

@app.route('/')
@app.route('/index')
def index():
	return render_template('index.html')
