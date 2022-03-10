import flask
import chuck
import os
import subprocess
import sys


@chuck.app.route('/api/tsp/', methods=['GET'])
def get_TSP():
	file = flask.request.files['text']
	file.save(os.path.join(chuck.config.UPLOAD_FOLDER, 'coords.txt'))

	run()

	opt = open(chuck.config.TSP_OUTPUT, 'r')
	dst = opt.readline()
	route = opt.read()

	dst = float(dst.replace('\n',''))
	verts = [int(i) for i in route if i != ' ' and i != '\n']

	context = {'distance':dst,
			   'route': verts
	}

	return flask.jsonify(**context)

def run():
	myInput = open(chuck.config.TSP_INPUT, 'r')
	myOutput = open(chuck.config.TSP_OUTPUT, 'w')
	s = subprocess.run([chuck.config.TSP_EXE],stdin = myInput, stdout=myOutput)


    