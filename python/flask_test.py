# use env in ./flask_app 
# flask run
# kill $(pidof a.out)

from flask import Flask,request
import os

app = Flask(__name__)
@app.route("/", methods=["GET"])
def hello():
    name = request.args.get('name')
    return "Hello World!!"+name

if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port="9999")