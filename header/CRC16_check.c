#include "CRC16_check.h"


/* CRC16校驗 */
unsigned short check_sum (unsigned short *buffer, unsigned short size){  

	unsigned long cksum = 0;
	
	while(size>1){
		cksum += *buffer++;
		size  -= sizeof(unsigned short);
	}
	
	if(size){
		cksum += *(unsigned char *)buffer;
	}
	
	cksum = (cksum >> 16) + (cksum & 0xffff);
	cksum += (cksum >> 16);
	
	return((unsigned short )(~cksum));
}