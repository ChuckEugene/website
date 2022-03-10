import flask
import chuck
import os
import subprocess
import sys
from subprocess import PIPE
import signal

@chuck.app.route('/api/tsp/', methods=['GET'])
def get_TSP():
	data = flask.request.get_data()

	file = open(chuck.config.TSP_INPUT, 'wb')
	file.write(data)

	temp = run()
	# os.system(f"{chuck.config.TSP_EXE}")
	
	return "done"

def run():
	myInput = open(chuck.config.TSP_INPUT, 'r')
	myOutput = open(chuck.config.TSP_OUTPUT, 'w')
	s = subprocess.run([chuck.config.TSP_EXE],stdin = myInput, stdout=myOutput, stderr=PIPE)
	print(s)


    