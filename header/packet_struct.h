struct ip{
	unsigned char       hl;
	unsigned char       tos;
	unsigned short      total_len;
	unsigned short      id;
	unsigned short      frag_and_flags;
	unsigned char       ttl;
	unsigned char       proto;
	unsigned short      checksum;
	unsigned int        sourceIP;
	unsigned int        destIP;
};
	
struct tcphdr{
	unsigned short      sport;
	unsigned short      dport;
	unsigned int        seq;
	unsigned int        ack;
	unsigned char       lenres;
	unsigned char       flag;
	unsigned short      win;
	unsigned short      sum;
	unsigned short      urp;
};

struct pseudohdr{
	unsigned int	    saddr;
	unsigned int 	    daddr;
	char                zero;
	char                protocol;
	unsigned short      length;
};