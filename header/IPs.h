#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#define MaxIP 76

extern char _IPRange[MaxIP][16];

void getIPRange(char[]);

void printIP(char[]);

int getSAddr();
    