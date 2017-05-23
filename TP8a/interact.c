#include <stdio.h>

#define INPUT_ERR -1
#define INPUT_BIT -2
enum {FALSE, TRUE};

char get_input(void); // gets user input, only one char, otherwise returns INPUT_ERR

int process_input(char bit_data);

int main(void)
{
	char aux, again = 1, exit;

	while(again){

		aux = get_input();

		exit = process_input(aux);

		if(exit)
			again = 0;
	}

	return 0;
}

char get_input(void){

	unsigned int i = 0;

	char c, in_char;

	while ( (c = getchar()) != '\n'){
		i++;
		in_char = c;
	}

	if(i != 1)	
		in_char = INPUT_ERR;
	
	return in_char;
}

int process_input(char bit_data){

	char change_bit, fun_choice = bit_data;
	int ans = FALSE;

	if(bit_data >= '0' && bit_data <= '7'){
		change_bit = bit_data;
		fun_choice = INPUT_BIT;
	}

	switch(fun_choice){
		case 's':
			printf("Switch ON\n");
		break;
		case 'c':
			printf("Switch OFF\n");
		break;
		case 'b':
			printf("Blink\n");
		break;
		case 'e':
			ans = TRUE;
		break;
		case INPUT_BIT:
			printf("Switch port bit %c\n", change_bit);
		break;
		case INPUT_ERR: default:
			printf("Invalid IN\n");
		break;
	}

	return ans;
}