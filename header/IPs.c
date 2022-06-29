#include <stdio.h>
#include <stdlib.h>
#include "IPs.h"



void getIP(char IP[]){

    int a = rand() % MaxIP;

    for(int i=0; i<16; i++){
        IP[i] = ip[a][i];
    }
}


int main(){
    time_t t;
    srand((unsigned) time(&t));
    int host = rand() % 253 + 2; // 2 ~ 254

    char IP[16]={0};
    getIP(IP);

    for(int i = 0; i<16; i++){
        printf("%c", IP[i]);
    }
    printf("\n");
    return 0;

}