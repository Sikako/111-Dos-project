// Test file to get broadcast IP


#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <pthread.h>
#include <iostream>
#include "header/CRC16_check.h"
#include "header/init_header.h"


int main(){
    char ip[16] = {"192.168.200.64"};
    uint32_t ip_b;
    // to binary 
    inet_pton(AF_INET, ip, &ip_b);

    printf("inet_pthon: 0x%x\n", ip_b);

    std::cout << ip_b << "\n";

    // ip_b = ip_b & 0xFFFFFF00;
    // AND to find broadcast address
    ip_b = ip_b & 0x00FFFFFF;
    printf("&: 0x%x\n", ip_b);
    std::cout << ip_b << "\n";
    ip_b = htonl(ip_b);
    printf("htonl: 0x%x\n", ip_b);
    std::cout << ip_b << "\n";
    ip_b = ip_b + 0x000000FF;
    printf("+: 0x%x\n", ip_b);
    std::cout << ip_b << "\n";
    ip_b = ntohl(ip_b);
    inet_ntop(AF_INET, &ip_b, ip, sizeof(ip));

    std::cout << ip << "\n";

    return 0;



}
