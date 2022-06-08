#include "header/init_header.h"


void init_header(struct iphdr *ip_hdr, struct tcphdr *tcp_hdr, struct pseudohdr *pseudoheader, char *dst_ip, int dst_port, char mode){
	int len = sizeof(struct iphdr) + sizeof(struct tcphdr);
	// IP頭部初始化
	ip_hdr->version = 4;
	ip_hdr->ihl = 5;
	ip_hdr->tos = 0;
	ip_hdr->tot_len = htons(len);
	ip_hdr->id = random() && 0x00ffff;
	ip_hdr->frag_off = htons(0);
	ip_hdr->ttl = 255;
	ip_hdr->protocol = IPPROTO_TCP;
	ip_hdr->check = 0;
	ip_hdr->saddr = 0;
	ip_hdr->daddr = inet_addr(dst_ip);

	// TCP頭部初始化
	tcp_hdr->th_sport = htons( rand()%16383 + 49152 );
	tcp_hdr->th_dport = htons(dst_port);
	tcp_hdr->th_seq = htonl( rand()%90000000 + 2345 ); 
	tcp_hdr->th_ack = 0; 
	tcp_hdr->th_win = htons (2048);  
	tcp_hdr->th_sum = 0;
	tcp_hdr->th_urp = 0;

	// mode----------------------------------------------
	if(mode == 'A')	tcp_hdr->th_flags = TH_ACK;
	else if(mode == 'S')	tcp_hdr->th_flags = TH_SYN;
	// --------------------------------------------------

	//TCP偽頭部初始化
	pseudoheader->zero = 0;
	pseudoheader->protocol = IPPROTO_TCP;
	pseudoheader->length = htons(sizeof(struct tcphdr));
	pseudoheader->daddr = inet_addr(dst_ip);
	srand((unsigned) time(NULL));

}