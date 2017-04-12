#include <stdio.h>

#define PORTA 0x53 /// valor defecto PORTA

int main(){
	unsigned char porta = PORTA;

	unsigned char itr_mask = 1<<(sizeof(porta)*8-1); /// marcara de iteracion (itr)

	while (itr_mask){
		printf("%d",(porta&itr_mask)!=0);
		itr_mask >>= 1;
	}
	
}