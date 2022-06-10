#!/usr/bin/env python

from http import client
from logging import exception
from pydoc import cli
from unittest import result
import paramiko

username = "sikako"
password = "Ji3g4tp6xj4p!"
hostname = "192.168.200.62"
port = 22

cmd = "cd /home/sikako/Desktop/111-Dos-project/;pwd;ls -al"

def run_remote_command(username, password, cmd):
    try:
        client = paramiko.SSHClient()
        client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        client.connect(hostname, port, username, password)
        # client.exec_command('cd /')
        stdin, stdout, stderr = client.exec_command(cmd)
        result = stdout.read().decode().strip()
        print(result)
    except exception:
        print('Exeption!!')
        raise

run_remote_command(username,password, cmd)
    