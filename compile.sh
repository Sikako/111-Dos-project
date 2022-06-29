#!/bin/bash

    gcc -o tools/tcp_attack tcp_attack.c header/init_header.c header/CRC16_check.c header/IPs.c -lpthread >&2
    gcc -o tools/udp_attack udp_attack.c header/init_header.c header/CRC16_check.c header/IPs.c -lpthread >&2
    gcc -o tools/smurf_attack smurf.c  header/CRC16_check.c header/init_header.c header/pause.c -lpthread >&2
if [ "$?" = "0" ]
then
    echo "Compile Succeses at ./tools"   
fi
