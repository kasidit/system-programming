#include <stdio.h>

char A[5] = { 1, 2, 3, 4, 5 };
char B[5] = { 0, 0, 0, 0, 0 }; 
char C[5] = { 0, 0, 0, 0, 0 }; 

void send1(register char *to, register char *from, register int count); 
void send2(register char *to, register char *from, register int count); 

int main(int argc, char *argv[]){ 
	
	int i; 
	printf("A = "); 
        for(i=0; i < 5; i++) printf("%d ", (int)A[i]); 	
	printf("\n"); 
	send1(B, A, 5); 
	printf("B = "); 
        for(i=0; i < 5; i++) printf("%d ", (int)B[i]); 	
	printf("\n"); 
	send2(C, A, 5); 
	printf("C = "); 
        for(i=0; i < 5; i++) printf("%d ", (int)C[i]); 	
	printf("\n"); 

}

void send1(register char *to, register char *from, register int count){
	do
		*to++ = *from++;
	while(--count>0);
}	

void send2(register char *to, register char *from, register int count){
	register int n=(count+7)/8;

	switch(count%8){
	case 0:	do{	*to++ = *from++;
	case 7:		*to++ = *from++;
	case 6:		*to++ = *from++;
	case 5:		*to++ = *from++;
	case 4:		*to++ = *from++;
	case 3:		*to++ = *from++;
	case 2:		*to++ = *from++;
	case 1:		*to++ = *from++;
		}while(--n>0);
	}
}
