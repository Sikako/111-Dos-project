# this is a file to test running remote command using 
# RemoteComman.py.


from RemoteCommand import Computer, ssh_run_remote_command


host1 = Computer('192.168.200.62', 'root', 'root')

cmd = 'cd /home/sikako/Desktop/;gedit'

out = ssh_run_remote_command(host1, cmd)

print(out)