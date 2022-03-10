
import flask

app = flask.Flask(__name__)

app.config.from_object('chuck.config')

app.config.from_envvar('CHUCK_SETTINGS', silent=True)

import chuck.api
import chuck.views
import chuck.model
