#!/bin/bash

gcc -o flood_attck flood_attack.c init_header.c CRC16_check.c -lpthread
if [ "$?" = "1" ]
then   
    echo "error"
else
    echo "Compile Succeses at ./flood_attack"
fi
