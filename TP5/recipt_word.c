#include <stdio.h>

#define WAIT_WORD -3
#define WORD_OK -2
#define ERR_CHAR -1 
#define START 0
#define WAIT 1
#define INFO_OK 2
#define IS_ENTER 3
#define WORD_LIMIT 20
#define C_LET (26*2)
#define C_ASCI 256

/* init_null_array: recives the reference of where an
   array is stored and his lenght, and sets all the
   elements in 0. */
void init_null_array(char array[], int arr_size);

/* recipt_word: receives the reference of the array where 
   the word will be stored, a reference to the array of
   the number of chars of the same type contained, and the 
   number of the word (1, 2, etc.). */
void recipt_word (char string_src[], char chars[C_ASCI], int num);

/* welcome_print: prints a message with initial instructions
   to the final user. It needs a define with the max. number
   of letters. */
void welcome_print(void);

/* validate_word: receives a reference to the array where
   the word is stored and checks if contains a symbol or 
   character not allowed. It returns a pointer with the 
   result of the check process: WORD_OK or ERR_CHAR. */
//void validate_word(char src_word[], int *w_state);

/* The array valid_let is global because its for read only
   purposes.*/
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

int main()
{
	enum{W1 = 1, W2};

	int h = 0, state = WAIT_WORD;

	char word_1[WORD_LIMIT], w1_chars[C_ASCI]; 
	//char word_2[WORD_LIMIT], w2_chars[C_ASCI];

	init_null_array(w1_chars, C_ASCI);

	welcome_print();

	while(state == WAIT_WORD){
		recipt_word(word_1, w1_chars, W1);
		//validate_word(word_1, &state);
		if(state == ERR_CHAR){
			printf("Word %d entered wrong. Try again: ", W1);
			state = WAIT_WORD;
		}
	}

	return 0;
}

void welcome_print(void){

	printf("Welcome to the Anagram Search Program\n");
	printf("-------------------------------------\n\n");
	printf("Enter words in spanish with a lenght of no more than %d letters.\n", WORD_LIMIT); 
	printf("DO NOT include numbers or strange symbols.\n");
}

void recipt_word (char string_src[], char chars[C_ASCI], int num){

	int i = START, aux_var = 0, control = WAIT;

	while(control == WAIT){
		printf("Enter the word number %d: ", num);
		while((aux_var = getchar()) != '\n'){ // While is not ENTER
			string_src[i] = aux_var;
			chars[aux_var]++;
			i++;
		}

		if(i != START){ // At least 1 character entered
			string_src[i] = '\n';
			control = INFO_OK;
		}
	}

	i = START;
}

void validate_word(char src_word[], int *w_state){

	
}

void init_null_array(char array[], int arr_size){

	int i;
	for(i = 0; i < arr_size; i++)
		array[i] = 0;
}