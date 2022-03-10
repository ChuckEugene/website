import flask
import chuck
import sqlite3
from datetime import datetime


@chuck.app.route('/api/finance/', methods=['GET'])
def finance_api():

	args = flask.request.args

	#defaults
	t1 = '2000-01-01'
	t2 = '2023-01-01'
	dtype = 'p'
	dtype_dict = {'p':'price', 'd':'day', 
				  'w':'week', 'm':'month',
				  '3m':'three','6m':'six'
				 }

	#Company name
	if 'abbr' not in args:
		return 'Specify (abbr) in URL in all caps', 400
	else:
		sym = args['abbr']

	#Start time
	if 't1' in args:
		t1 = args['t1']
		
	#End time
	if 't2' in args:
		t2 = args['t2']
		
	#data returned
	if 'd_type' in args:
		dtype = args['d_type']

	epoch_1 = datetime.strptime(t1, '%Y-%m-%d').timestamp()
	epoch_2 = datetime.strptime(t2, '%Y-%m-%d').timestamp()
	dtype2 = dtype_dict[dtype]


	stmt1 = f"""SELECT date(day,'unixepoch') as date,{dtype2} as {dtype} FROM {sym}
				WHERE day >= {epoch_1} AND day <= {epoch_2};
			"""

	stmt2 = f'''SELECT name FROM companies 
				WHERE symbol = '{sym}';
			'''
	try:
		conn = chuck.model.get_db()
		c = conn.cursor()
		c2 = conn.cursor()
		res = c.execute(stmt1).fetchall()
		comp = c2.execute(stmt2).fetchone()
		chuck.model.close_db(0)
	except Exception as e:
		return f"DATABASE_ERROR: {e}", 400

	context = {	'company':comp["name"],
				'ticker':sym,
				'data':res[:]
			   }

	return flask.jsonify(**context)









	