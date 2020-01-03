from project import create_app


app = create_app('flask.cfg')

@app.route('/')
def index():
	return "Hello World!"
