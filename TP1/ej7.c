#include <stdio.h>

// GRUPO 3 - TP1 - EJERCICIO 7 //
// Regueira, Nowik, Mestanza

#define MASC_A 0x21 // 0010 0001
#define MASC_B 0x18 // 0001 1000

int main(){
	unsigned char porta = 0x2F;
	int cnd1 = (porta & MASC_A) == MASC_A; // bits 5 y 0 en 1?
	int cnd2 = ((~porta) & MASC_B) == MASC_B; // bits 3 y 4 en 0?
	
	printf("%d \n", (cnd1 || cnd2)); //es alguna condicion verdadera? (!=0)
}