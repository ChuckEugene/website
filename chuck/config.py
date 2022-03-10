
import pathlib

APPLICATION_ROOT = '/'

# Secret key for encrypting cookies
# SECRET_KEY = b'n\xfe\xf14\x98\r\x85W\x9d\x02\x9c\xf4\xddf '\
#             b'\xc8\x83\xca\xac\x03~\x91\xef_'
# SESSION_COOKIE_NAME = 'login'

# File Upload to var/uploads/
CHUCK_ROOT = pathlib.Path(__file__).resolve().parent.parent
UPLOAD_FOLDER = CHUCK_ROOT/'var'
TSP_INPUT = UPLOAD_FOLDER/'coords.txt'
TSP_OUTPUT = UPLOAD_FOLDER/'out.txt'
TSP_EXE = UPLOAD_FOLDER/'tsp'
ALLOWED_EXTENSIONS = set(['txt','png', 'jpg', 'jpeg', 'gif'])
MAX_CONTENT_LENGTH = 16 * 1024 * 1024

# Database file is var/insta485.sqlite3
DATABASE_FILENAME = CHUCK_ROOT/'var'/'stocks'

