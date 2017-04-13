#include <stdio.h>

#define C_LET (26*2)
#define C_ASCI 256

char valid_let[C_LET] = 
{'a','b','c','d','e',
'f','g','h','i','j',
'k','l','m','n','o',
'p','q','r','s','t',
'u','v','w','x','y',
'z',
'A','B','C','D','E',
'F','G','H','I','J',
'K','L','M','N','O',
'P','Q','R','S','T',
'U','V','W','X','Y',
'Z'};

void enough_letters(char A[C_ASCI] , B[C_ASCI] , valid_let[C_LET]);

int main(){

}


int enough_letters(char A[C_ASCI] , B[C_ASCI]){
	int i;
	int ans = 1;
	for (i = 0;(ans && i < C_LET);i++){
		if (A[ valid_let[i] ] < B[ valid_let[i] ]){ // not enough letters
			ans = 0;
		}
	}
	return ans;
}
