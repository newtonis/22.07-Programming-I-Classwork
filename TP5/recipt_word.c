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


enum {FALSE , TRUE};

// sets all array elements to 0
void init_null_arr(char arr[], int sz);

// reads from input one word. sz=0 if no word entered
void recipt_word (char str[], int *sz);

void welcome_print(void);

// checks a word to be valid, if all chars are valid letters
void valid_word(char word[],int word_sz);

// The array valid_let is global because its for read only purposes
char valid_let[C_LET] = 
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

int main()
{
	enum{W1 = 1, W2};

	int state = WAIT_WORD;

	char word_1[WORD_LIMIT], w1_chars[C_ASCI]; 
	//char word_2[WORD_LIMIT], w2_chars[C_ASCI];

	init_null_arr(w1_chars, C_ASCI);

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
	printf("Enter words in spanish with a length of no more than %d letters.\n", WORD_LIMIT); 
	printf("DO NOT include numbers or strange symbols.\n");
}

void recipt_word (char str[],int *sz){
	int i = 0;
	while((aux_var = getchar()) != '\n'){
		str[i] = aux_var;
		i++;
	}
	*sz = i;
}

void process_valid(int is_valid[]){
	init_null_arr(is_valid , str);
	int i = 0;
	for (i = 0;i < C_LET;i++){
		is_valid[ valid_let[i] ] = TRUE;
	}
}

int valid_word(char word[], int word_sz , int is_valid[]){
	int i;
	ans = FALSE;
	for(i = 0;!ans && i < word_sz;i++){
		if (is_valid[word[i]]){
			ans = TRUE;
		}
	}
	return ans;	
}

void init_null_arr(char arr[], int sz){
	int i;
	for(i = 0; i < sz; i++){
		arr[i] = 0;
	}
}