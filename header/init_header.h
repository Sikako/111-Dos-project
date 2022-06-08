#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include "packet_struct.h"


void init_header(struct iphdr *, struct tcphdr *,struct pseudohdr *, char *, int, char);
