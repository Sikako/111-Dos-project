#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(){
	int i, LEN = 5 + 1;
	srandom(time(NULL));
	unsigned char text[LEN];
	memset(text, 1, LEN);
	for(i = 0; i< LEN - 1; i++){
		text[i] = (unsigned char) (rand() % 255 + 1);
		printf("%c", text[i]);
	}
	text[LEN-1] = 0;
	printf("\nplain-text:");
	printf("strlen(text)=%zd\n", strlen(text));
}
