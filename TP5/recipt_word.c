#include <stdio.h>

#define WORD_LIMIT 20

#define CNT_LET (52)
#define CNT_ASCI (256)

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

// ask user word until it gives a valid one
void loop_read_word(char str[],char msg[], int *sz , int is_valid[]);

int main(){
	// compute valid letters table
	int is_valid[CNT_ASCI];
	process_valid(is_valid , valid_let , CNT_ASCI);

	char str1[WORD_LIMIT] , str2[WORD_LIMIT];
	int sz1, sz2;

	welcome_print();
	
	loop_read_word(str1,"Insert first word: " ,&sz1 , is_valid);
	loop_read_word(str2,"Insert second word: ",&sz2 , is_valid);

	printf("%s %s \n",str1,str2);
	return 0;
}

void loop_read_word(char str[],char msg[], int *sz , int is_valid[]){
	int end = 0;
	while (!end){
		printf("%s", msg);
		recipt_word(str,sz);
		int valid = valid_word(str,*sz,is_valid);
		switch (valid){
			case ERR_CHAR_VALID:
				printf("Invalid character inserted\n");
			break;
			case ERR_SZ:
				printf("Max size exceeded: %d>%d\n",*sz,WORD_LIMIT);
			break;
			case VALID:
				end = 1;
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

void recipt_word (char str[],int *sz){
	int i = 0;
	char aux_var;
	*sz = 0;
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
		ans = VALID;
		for(i = 0;(ans==VALID) && i < word_sz;i++){
			if (!is_valid[ (int)word[i] ]){
				ans = ERR_CHAR_VALID;
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