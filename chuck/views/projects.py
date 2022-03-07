import flask
import chuck

@chuck.app.route('/projects/', methods=['GET'])
def get_projects():
	return flask.render_template("projects.html")

@chuck.app.route('/projects/api/', methods=['GET'])
def get_api():
	return flask.render_template("api.html")

@chuck.app.route('/projects/mr/', methods=['GET'])
def get_mr():
	return flask.render_template("mapreduce.html")

@chuck.app.route('/projects/nn/', methods=['GET'])
def get_nn():
	return flask.render_template("nn.html")

@chuck.app.route('/projects/piano/', methods=['GET'])
def get_piano():
	return flask.render_template("piano.html")

@chuck.app.route('/projects/v2p/', methods=['GET'])
def get_v2p():
	return flask.render_template("V2P.html")

@chuck.app.route('/projects/tsp/', methods=['GET'])
def get_tsp():
	return flask.render_template("tsp.html")