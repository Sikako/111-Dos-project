# use env in ./flask_app 
# flask run
# kill $(pidof a.out)
# use sudo without password -----------------
# sudo visudo
# <USER> <FROM>=<ACTAS> NOPASSWD: <CMDS>
# sikako ALL=(ALL) NOPASSWD: ALL
# !!!!!must run server by root
# -------------------------------------------

from flask import Flask,request
import subprocess, os

# subprocess
p = ""

# start attack ------------------------------------------------
# request http://<IP>:9999/start with POST cantaining
# 'attack', 'IP', 'port', [mode], [BcstIP]
# -------------------------------------------------------------
app = Flask(__name__)
@app.route("/start", methods=["POST"])
def start_pid():
    global p
    cmd = []
    attack = str(request.form["attack"])
    tool = "../tools/"+attack
    IP = str(request.form["IP"])

    cmd.extend([tool, IP])  # sudo ../tools/<attack> <IP>

    if attack == 'tcp_attack':
        port = str(request.form["port"])
        mode = str(request.form["mode"])
        cmd.extend([port, mode])

    elif attack == 'udp_attack':
        port = str(request.form["port"])
        cmd.append(port)

    elif attack == 'smurf.attack':
        BcstIP = str(request.form["BdstIP"])
        cmd.append(BcstIP)

    p = subprocess.Popen(cmd)
    print("pid=", p.pid)
    print("cmd:", cmd)

    return "start attack"

@app.route("/stop")
def close_pid():
    global p
    # cmd = f"sudo kill -9 {p.pid}"
    # os.system(cmd)
    p.kill()

    return "stop attack"




if __name__ == '__main__':
    app.run(debug=True,host="0.0.0.0",port="9999")