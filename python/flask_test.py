# use env in ./flask_app 
# flask run
# kill $(pidof a.out)

from flask import Flask,request
import os

app = Flask(__name__)
@app.route("/start", methods=["GET"])
def start_pid():
    cmd = "sudo ../tools/udp_attack 172.24.19.216 80"
    r = os.system(cmd)
    return str(r)

@app.route("/stop")
def close_pid():
    app = "udp_attack"
    pid = os.system(f"pidof {app}")
    cmd = f"sudo kill -9 {pid}"
    r = os.system(cmd)
    return str(r)




if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port="9999")