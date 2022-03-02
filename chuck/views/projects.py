import flask
import chuck


@chuck.app.route('/projects/', methods=['GET'])
def get_projects():
	return flask.render_template("projects.html")