from RemoteCommand import Computer, ssh_run_remote_command


host1 = Computer('192.168.200.62', 'root', 'root')

cmd = 'cd /home/sikako/Desktop/111-Dos-project;./tools/tcp_attack 192.168.200.55 80 S'

out = ssh_run_remote_command(host1, cmd)

print(out)