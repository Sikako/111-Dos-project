#!/bin/bash

gcc -o attck flood_attack.c init_header.c CRC16_check.c -lpthread
if [ "$?" = "1" ]
then   
    echo "error"
else
    echo "Compile Succeses at ./attack"
fi
