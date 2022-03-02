import flask
import chuck


@chuck.app.route('/', methods=['GET'])
def get_homepage():
	return flask.render_template("home.html")