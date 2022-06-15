# use env in ./flask_app 
# flask run
# kill $(pidof a.out)
# use sudo without password -----------------!!
# sudo visudo
# <USER> <FROM>=<ACTAS> NOPASSWD: <CMDS>
# sikako ALL=(ALL) NOPASSWD: ALL
# -------------------------------------------

from flask import Flask,request
import subprocess

attack = ""
p = ""

app = Flask(__name__)

@app.route("/start")
def start_pid():
    global p
    p = subprocess.Popen("./a.out")
    print('process id: ', p.pid)
    return "start attack"


@app.route("/stop")
def close_pid():
    global p
    p.kill()

    return "stop attack"




if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port="9999")