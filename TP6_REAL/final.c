#include <stdio.h>
#include <math.h>

#define MAX_OP 20
#define ASCI 256
#define ERR -1
#define MAX_STR_SZ 100
#define CODE_SUCCESS '&'

enum {SYMBOL_MODE , LETTER_MODE , ALL_ENABLED};

//// MAIN FUNCTIONS ////
void set_operations_symbol(int mode); 
void add_operation(char o, float (*a)(float, float));

//// Input functions ////
int validate(char *input);
void str_2_float( char *input , double *v_ans , int *err);
void receive_word (char str[],int *sz,int max_sz);

void read_line(char *str , int *sz);

void process_command(char *input,int sz,char **ans,double *n_ans);

void read_command_operation(char *input,int sz,char **ans);
void read_number_operation(char *input,int sz,char **ans,double *n_ans);

void remove_spaces(char *str ,int *sz);


//// operations ////
float add (float a,float b);
float sub (float a,float b);
float mul (float a,float b);
float div (float a,float b);

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





int main(){
	cnt_op = 0;

	/// Add normal functions
	add_operation('+', add); 
	add_operation('-', sub);
	add_operation('*', mul); 
	add_operation('/', div);
	
	/// Add their letter clones
	add_operation('a', add); 
	add_operation('s', sub);
	add_operation('m', mul);
	add_operation('d', div);

	printf("Welcome to calculator \n");
	printf("Type [number][op][number] \n");

	printf("c2 => enable letter operators \n");
	printf("c1 => enable number operators \n");
	printf("c0 => enable all operators \n");
	printf("e => Exit \n");

	printf("Default commands : ,Add(+),Substract(-),Multiply(*),Divide(-) \n"); 

	int end = 0;
	
	while (!end){
		char input_line[MAX_STR_SZ];
		int sz;
		printf("==>");
		read_line(input_line,&sz); 
		
		char *ans;
		double n_ans;
		process_command(input_line,sz,&ans,&n_ans);
		if (ans[0] == 'e'){
			end = 1;
		}else{
			if (ans[0] == CODE_SUCCESS){
				printf("%f \n",n_ans);
			}
			printf("%s \n",ans);
		}
	}
}


float add(float a,float b){
	return a+b;
}
float sub(float a,float b){
	return a-b;
}
float mul(float a,float b){
	return a*b;
}

float div(float a,float b){
	float ans;
	if(b != 0){
		ans = a / b;
	}else{
		ans = NAN; // not a number
	}
	return ans;	
}






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


float calc_res(float x, float y, char op,int *p2err){
	float ans;

	if( enabled_chars[(int)op] && ( operators[(int)op] != ERR) ){	
		ans = (actions[operators[(int)op]])(x,y);
		*p2err = 0;
	}else{
		*p2err = ERR;
	}
	return ans;
}




/// Functions to read user input ///

void process_command(char *input,int sz,char **ans,double *n_ans){
	remove_spaces(input , &sz);
	if (input[0] == 'c'){
		read_command_operation(input,sz,ans);
	}else{
		read_number_operation(input,sz,ans,n_ans);
	}
}

void read_command_operation(char *input,int sz, char **ans){
	
	if (sz != 2){
		*ans = "Error, no mode specified ";
	}else if (input[1] == '0'){
		set_operations_symbol(ALL_ENABLED);
		*ans = "Both symbols and letters are now valid";
	}else if(input[1] == '1'){
		set_operations_symbol(SYMBOL_MODE);
		*ans = "Symbol mode enabled";
	}else if(input[1] == '2'){
		set_operations_symbol(LETTER_MODE);
		*ans = "Letters mode enabled";
	}
}
int is_number_type(char a){
	return a == '.' || (a >= '0' && a <= '9');
}
void read_number_operation(char *input,int sz,char **ans,double *n_ans){
	char number_a[MAX_STR_SZ] , number_b[MAX_STR_SZ];
	int pnt_a = 0, pnt_b = 0;
	char op;
	int pnt = 0;
	if (input[pnt] == '+' || input[pnt] == '-') pnt ++; // it may be a starting + or -

	while (pnt < sz && (is_number_type(input[pnt])) ){ // number characters
		number_a[pnt_a++] = input[pnt++];
	}
	number_a[pnt_a] = '\0';
	
	if (pnt == sz){ // invalid!, nothing more than one number
		*ans = "Invalid input a";
	}else{ 
		op = input[pnt++];	
		if (pnt == sz){ // invalid, no second number
			*ans = "Invalid input b";
		}else{
			while (pnt < sz){
				number_b[pnt_b++] = input[pnt++];
			}
			number_b[pnt_b] = '\0';

			// process input numbers
			double num_a , num_b ;
			int err_a, err_b;

			str_2_float( number_a , &num_a , &err_a);
			str_2_float( number_b , &num_b , &err_b);

			if (err_a == ERR || err_b == ERR){
				*ans = "Invalid input (numbers are not readable)"; // invalid numbers1
			}else{
				int err;

				float num_ans = calc_res(num_a, num_b , op , &err);

				if (err == ERR){
					*ans = "Invalid input (invalid operation) ";
				}
				if (num_ans != num_ans){ // ans is Nan
					*ans = "Math error";
				}else{
					*ans[0] = CODE_SUCCESS;
					*n_ans = num_ans;
				}
			}
		}
	}


}

void remove_spaces(char *str ,int *sz){
	char ans[MAX_STR_SZ];
	int i = 0 , j = 0;
	for (i = 0;i < *sz;i++){
		if (str[i] != ' '){
			ans[j++] = str[i];
		}
	}
	*sz = j;
	for (i = 0;i < *sz;i++){
		str[i] = ans[i];
		//printf("%d ",i);
	} 
	str[*sz] = '\0'; 
}


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
		*err = ERR;
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
void read_line (char *str,int *sz){ 
	int i = 0;
	char aux_var;
	*sz = 0;
	while((aux_var = getchar()) != '\n'){
		if (i < MAX_STR_SZ){ // we can't store them, there is not enough memory
			str[i] = aux_var;
		}
		i++;
	}
	str[i] = '\0';
	
	*sz = i; // we return total characters inserted no matter we did't add extra ones
}


