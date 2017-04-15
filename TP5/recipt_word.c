#include <stdio.h>

#define WAIT_WORD -3
#define WORD_OK -2
#define START 0
#define WAIT 1
#define INFO_OK 2
#define IS_ENTER 3
#define WORD_LIMIT 20

#define CNT_LET (26*2)
#define CNT_ASCI 256

enum {ERR_SZ,ERR_CHAR_VALID,VALID};
enum {FALSE , TRUE};

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


// sets all array elements to 0
void init_null_arr(int arr[], int sz);
// reads from input one word. sz=0 if no word entered
void recipt_word (char str[], int *sz);
void welcome_print();
// checks a word to be valid, if all chars are valid letters
int valid_word(char word[], int word_sz , int is_valid[]);

// convert letter list to asci table (valid letters value is 1)
void process_valid(int is_valid[] ,char let_list[] , int let_list_sz);

int main(){
	// compute valid letters table
	int is_valid[CNT_ASCI];
	process_valid(is_valid , valid_let , CNT_ASCI);

	char str1[WORD_LIMIT] , str2[WORD_LIMIT];
	int sz1, sz2;

	welcome_print();
	printf("Insert first word: ");
	recipt_word(str1,&sz1);
	printf("Insert second word: ");
	recipt_word(str2,&sz2);
	
	int valid1 = valid_word(str1 , sz1 , is_valid);
	int valid2 = valid_word(str2 , sz2 , is_valid);

	printf("%d %d",valid1,valid2);
	return 0;
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

void recipt_word (char str[],int *sz){
	int i = 0;
	char aux_var;
	while((aux_var = getchar()) != '\n'){
		str[i] = aux_var;
		i++;
	}
	*sz = i;
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
	}else{
		int i;
		ans = ERR_CHAR_VALID;
		for(i = 0;(ans!=VALID) && i < word_sz;i++){
			if (is_valid[ (int)word[i] ]){
				ans = VALID;
			}
		}
	}
	return ans;	
}

void init_null_arr(int arr[], int sz){
	int i;
	for(i = 0; i < sz; i++){
		arr[i] = 0;
	}
}