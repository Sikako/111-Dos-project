# use flask_app venv
# flask run

from flask import Flask,request
import os

app = Flask(__name__)
@app.route("/", methods=["GET"])
def hello():
    name = request.args.get('name')
    return "Hello World!!"+name

if __name__ == '__main__':
    app.run()