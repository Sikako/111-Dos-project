import logging
import paramiko



class Computer():
    def __init__(self, host, name, password):
        self.host = host
        self.name = name
        self.password = password

def ssh_run_remote_command(self, cmd):
    client = paramiko.SSHClient()
    client.set_missing_host_key_policy(paramiko.AutoAddPolicy())
    client.connect(hostname=self.host,
                    username=self.name,
                    password=self.password)

    stdin, stdout, stderr = client.exec_command(cmd)

    out = stdout.read().decode().strip()
    error = stderr.read().decode().strip()
    

    if error:
        raise Exception('There was an error pulling the runtime: {}'.format(error))
    else:
        logging.info(out)
    client.close()

    return out


