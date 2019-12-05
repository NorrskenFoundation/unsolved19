import os
from flask import Flask, request, send_from_directory, make_response, redirect, Response, url_for
from flask_cors import CORS


build_dir = 'build'
app = Flask(__name__, static_folder=build_dir+'/static')
CORS(app, origins='*')


@app.route('/', defaults={'path': ''})
@app.route('/<path:path>')
def index(path):

    # files only served if authenticated
    if path != "" and os.path.exists(build_dir + path):
        return send_from_directory(build_dir, path)
    else:
        return send_from_directory(build_dir+'/', 'index.html')

if __name__ == '__main__':
    app.run(debug=True)
