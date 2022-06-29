#include "IPs.h"



void getIPRange(char IP[]){

    int a = rand() % MaxIP;

    for(int i=0; i<16; i++){
        IP[i] = _IPRange[a][i];
    }
}

void printIP(char IP[]){
    for(int i=0; i<16; i++){
        printf("%c", IP[i]);
    }
}

int getSAddr(){
    time_t t;
    srand((unsigned) time(&t));
    int host = rand() % 253 + 2; // 2 ~ 254

    char IP[16]={0};
    uint32_t IP_b;  // binary
    getIPRange(IP);
    inet_pton(AF_INET, IP, &IP_b);
    IP_b = htonl(IP_b);
    IP_b = IP_b + host;
    IP_b = ntohl(IP_b);
    // inet_ntop(AF_INET, &IP_b, IP, sizeof(IP));
    return IP_b;
}