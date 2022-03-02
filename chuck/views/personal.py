import flask
import chuck


@chuck.app.route('/personal/', methods=['GET'])
def get_personal():
	return flask.render_template("personal.html")