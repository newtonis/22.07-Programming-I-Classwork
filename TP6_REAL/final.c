#include <stdio.h>

#define MAX_OP 20
#define ASCI 256

enum {SYMBOL_MODE , LETTER_MODE , ALL_ENABLED};

//// MAIN FUNCTIONS ////
void set_operations_symbol(int mode); 
void add_operation(char o, float (*a)(float, float));

//// Input functions ////
int validate(char *input);
void str_2_float( char *input , double *v_ans , int *err);
void receive_word (char str[],int *sz,int max_sz);


//// operations ////
float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);

//// GLOBAL VARIABLES ////
int cnt_op; // which mode is enabled
int operators[ASCI]; // asci -> index
float (*actions[MAX_OP])(float, float);

int enabled_chars[ASCI]; // enabled characters codes

#define letters_sz 52
int letters[letters_sz] = 
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

void set(int arr[] , int n,int v){// set all arr values to v 
	int i;
	for (i = 0;i < n;i++) arr[i] = v;
}
void set_custom(int arr[], int indexes[],int ind_sz, int value){
	int i;
	for (i = 0;i < ind_sz;i++){
		arr [ indexes[i] ] = value;
	}
}

void set_operations_symbol(int mode){
	if (mode == SYMBOL_MODE){
		set ( enabled_chars , ASCI , 0);
		set_custom ( enabled_chars , letters  , letters_sz , 0); // disable letters
	}else if(mode == LETTER_MODE){
		set( enabled_chars , ASCI , 1);
		set_custom( enabled_chars , letters , letters_sz, 1); // enable letters
	}else if (mode == ALL_ENABLED){
		set( enabled_chars , ASCI , 1); // enable all symbols
	}
}

void add_operation(char o, float (*a)(float, float)){
	operators[(int)o] = cnt_op;
	actions[cnt_op] = a;

	cnt_op++;
}




/// Functions to read user input ///

int validate(char *input){ // is an input a decimal number?
	int valid = 1;
	if (!input[0]){
		valid = 0;
	}else{
		int i = 0;

		if (input[0] == '-' || input[0] == '+') i++;

		int dot = 0;
		while (input[i]){
			if (input[i] >= '0' && input[i] <= '9'){
				// nice!
			}else if (input[i] == '.'){
				dot ++;
			}else{
				valid = 0;
			}
			i ++ ;
		}
		if (dot >= 2){
			valid = 0;
		}
	} 
	return valid;
}
void str_2_float( char *input , double *v_ans , int *err){
	/// convert input string to float. Err = 1 in case of invalid string
	int valid = validate( input );
	if (!valid){
		*err = 1;
	}else{
		enum {READ_INT , READ_DEC};
		*err = 0;

		int i = 0;
		int sg = 1;
		if (input[i] == '+'){
			i++;
		}else if (input[i] == '-'){
			i++;
			sg = -1;
		}

		int st = READ_INT; // state
		double ans = 0;
		double mul = 0.1;
		while (input[i]){
			switch (st){
				case READ_INT:
					if (input[i] != '.'){
						ans = ans * 10.0 + (double)(input[i] - '0');
					}else{
						st = READ_DEC;
					}
				break;
				case READ_DEC:
					ans = ans + mul * (double)(input[i] - '0');
					mul = mul / 10.0;
				break;
			}
			i ++;
		}
		ans *= sg;
		*v_ans = ans;
	}
}

/// scan a word from keyboard.
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
	str[i] = '\0';
	
	*sz = i; // we return total characters inserted no matter we did't add extra ones
}


int main(){
	cnt_op = 0;

	/// Add normal functions
	add_operation('+', add); 
	add_operation('-', sub);
	add_operation('*', mul); 
	
	/// Add their letter clones
	add_operation('a', add); 
	add_operation('s', sub);
	add_operation('m', mul);


	
}