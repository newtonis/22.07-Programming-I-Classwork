#include <stdio.h>
#include <stdlib.h>

//// TP5 - POINTERS ////
//// -------------- ////
// MESTANZA, Joaquin  //
// NOWIK, Ariel       // 
// REGUEIRA, Marcelo  //
//
// a) We reused the method of word reception, changing the validation conditions, and
// now the complete word is stored into an array, insted of being processed char-by-char.
// b) ARI COMPLETE HERE PLEASE! 
//// -------------- ////

//// GLOBAL CONSTANTS ////
//// ---------------- ////
#define WORD_LIMIT 20
#define SMALL_SZ 1
#define TERMINATOR 1
#define TERM_CHAR '\0'
#define NO_WORD 0
#define ANS_EXCEEDED 2

#define CNT_LET 52
#define CNT_ASCI 256

enum {ERR_SZ, ERR_CHAR_VALID, ERR_EMPTY, VALID};
enum {FALSE, TRUE};
//// ---------------- ////

//// GLOBAL VARIABLES ////
//// ---------------- ////
// The array valid_let is global because its for read only purposes
char valid_let[CNT_LET] = 
{'a','b','c','d','e',
'f','g','h','i','j',
'k','l','m','n','o',
'p','q','r','s','t',
'u','v','w','x','y','z',
'A','B','C','D','E',
'F','G','H','I','J',
'K','L','M','N','O',
'P','Q','R','S','T',
'U','V','W','X','Y','Z'};
//// ---------------- ////

//// FUNCTIONS (CALLED BY THE MAIN) ////
//// ------------------------------ ////
//// process_valid: converts letter list array to the equivalent in
//   the asci table (valid letters value is 1)
void process_valid(int is_valid[] ,char let_list[] , int let_list_sz);

//// welcome_print: prints a short description of the program
void welcome_print();

//// loop_input: the general function of the program. It receives the
//   valid asci letter array, and determinates (calling other functions)
//   if the second word can be formed with the letters of the first word
void loop_input(int is_valid[]);

//// loop_continue: asks the user for end the program or start it again
//   to use other words
void loop_continue(int *end); 
//// ------------------------------ ////

//// SUB-FUNCTIONS ////
//// ------------- ////
//// init_null_arr: receives an array and its size, and sets 
//   all array elements to 0
void init_null_arr(int arr[], int sz);

//// valid_word: receives the word, his size and the list in asci 
//   of valid letters, then checks a word to be valid, if all chars 
//   are valid letters
int valid_word(char word[], int word_sz , int is_valid[]);

//// loop_read_word: receives the array where the word will be stored, 
//   its size, a message indicating the user wich word will be typed 
//   (first or second), and the asci array of valid letters, then the
//   user is asked for a word until it gives a valid one
void loop_read_word(char str[],char msg[], int *sz , int is_valid[]);

//// receive_word: reads from input one word. sz = 0 if no word entered
void receive_word (char str[], int *sz, int max_sz);

//// get_let_freq: gets how many times each character appears in a word
void get_let_freq(int char_freq[],char word[],int word_sz);

//// check_make_word: receives the two entered words, and checks if the
//   the second one can be formed with the letters of the first one
int check_make_word(char str1[],int sz1,char str2[],int sz2);
//// ------------- ////

//// MAIN FUNCTION ////
//// ------------- ////
int main(){

	int is_valid[CNT_ASCI];
	process_valid(is_valid , valid_let , CNT_ASCI); // compute valid letters table (is_valid)

	welcome_print();

	int end = FALSE;
	do{
		loop_input(is_valid);
		loop_continue(&end);
	}while (!end);
	
	return 0;
}
//// ------------- ////
void loop_input(int is_valid[]){
	char str1[WORD_LIMIT+TERMINATOR] , str2[WORD_LIMIT+TERMINATOR]; 
	int sz1,sz2;
	
	loop_read_word(str1,"Insert first word: " ,&sz1 , is_valid);
	loop_read_word(str2,"Insert second word: ",&sz2 , is_valid);

	int ans = check_make_word(str1,sz1,str2,sz2);
	printf("Can '%s' be formed with '%s' letters: %s\n",str1, str2, ans?"YES":"NO");

}

void loop_continue(int *end){
	int ask = 1;
	while (ask){
		printf("Continue(y/n)?:");
		char str[SMALL_SZ+TERMINATOR];
		int sz;
		receive_word(str,&sz,SMALL_SZ);
		if (sz == NO_WORD || sz >= ANS_EXCEEDED){
			printf("Invalid answer\n");
		}else{
			char c = str[0];
			switch (c){
				case 'n':
				case 'N':					
					*end = TRUE;
					ask = 0;
				break;
				case 'Y':
				case 'y':
					*end = FALSE;
					ask = 0;
				break;
				default:
					printf("Invalid answer\n");
				break;
			}
		}
	}
}

void loop_read_word(char str[],char msg[], int *sz , int is_valid[]){
	int end = FALSE;
	while (!end){
		printf("%s", msg);
		receive_word(str,sz,WORD_LIMIT);
		int valid = valid_word(str,*sz,is_valid);
		switch (valid){
			case ERR_CHAR_VALID:
				printf("Invalid character inserted\n");
			break;
			case ERR_SZ:
				printf("Max size exceeded: %d>%d\n",*sz,WORD_LIMIT);
			break;
			case ERR_EMPTY:
				printf("No word inserted\n");
			break;
			case VALID:
				end = TRUE;
			break;
		}
	}
}

void welcome_print(){
	printf("Welcome to the Anagram Search Program\n");
	printf("-------------------------------------\n\n");
	printf("Max word length: %d\n", WORD_LIMIT); 
	printf("Valid characters: ");
	int i;
	for (i = 0;i < CNT_LET;i++){
		printf("%c ",valid_let[i]);
	}
	printf("\n");
	printf("-------------------------------------\n\n");
}

void receive_word (char str[],int *sz,int max_sz){ 
	int i = 0;
	char aux_var;
	*sz = 0;
	while((aux_var = getchar()) != '\n'){
		if (i < max_sz){ // we can't store them, there is not enough memory
			str[i] = aux_var;
		}
		i++;
	}
	if (i <= max_sz){ // there is enough space for terminator
		str[i] = TERM_CHAR;
	}
	*sz = i; // we return total characters inserted no matter we did't add extra ones
}

int check_make_word(char str1[],int sz1,char str2[],int sz2){
	int freq1[CNT_ASCI] , freq2[CNT_ASCI];
	get_let_freq(freq1 , str1 , sz1 );
	get_let_freq(freq2 , str2 , sz2 );
	int i;
	int ans = TRUE;
	for (i = 0;ans && i < CNT_LET;i++){
		if (freq1[ (int)valid_let[i] ] < freq2[ (int)valid_let[i] ]){ 
			ans = FALSE; // there are not enough letters of that type
		}
	}
	return ans;
}
void process_valid(int is_valid[] ,char let_list[] , int let_list_sz){
	init_null_arr(is_valid , let_list_sz);
	int i = 0;
	for (i = 0;i < let_list_sz;i++){
		is_valid[ (int)let_list[i] ] = TRUE;
	}
}

int valid_word(char word[], int word_sz , int is_valid[]){
	int ans;
	if (word_sz > WORD_LIMIT){
		ans = ERR_SZ;
	}else if(word_sz == 0){
		ans = ERR_EMPTY;
	}else{
		int i;
		ans = VALID;
		for(i = 0;(ans==VALID) && i < word_sz;i++){
			if (!is_valid[ (int)word[i] ]){
				ans = ERR_CHAR_VALID;
			}
		}
	}
	return ans;	
}

void get_let_freq(int char_freq[],char word[], int word_sz){          
	init_null_arr(char_freq , CNT_ASCI);
	int i;							
	for(i = 0;i < word_sz;i++){    								      
		char_freq[(int)(word[i])]++;		           		
	}									
}		

void init_null_arr(int arr[], int sz){
	int i;
	for(i = 0; i < sz; i++){
		arr[i] = 0;
	}
}
