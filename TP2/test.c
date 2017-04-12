#include <stdio.h>

#define TERM 100

enum {IN,OUT};

int main(){
	
	int ln = 0;
	char c;
	
	int state = OUT;

	while ( (c = getchar()) != EOF){
		int letter_type = c == '\n' || c == '\t' || c == ' ';
		if (state == IN){
			if (letter_type){
				state = OUT;
				ln ++;
			}
		}else if(state == OUT){
			if (!letter_type){
				state = IN;
			}
		}
	}
	printf("Palabras %d: ",ln);
}