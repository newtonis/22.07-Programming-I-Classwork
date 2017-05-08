#include <stdio.h>
#include <math.h> // See overview

/////////////////////////////////
//// TP6 - ADVANCED POINTERS ////
//// ----------------------- ////
//// ==> MESTANZA, Joaquin   ////
//// ==> NOWIK, Ariel        ////
//// ==> REGUEIRA, Marcelo   ////////////////////////////////////////////
//// --------------------------------------------------------------- ////
//// The following code is a calculator that allows the user to      ////
//// make four (4) basic operations (Add, Substract, Multiply,       ////
//// Divide) and three (3) logic operations (AND, OR, XOR).          ////
//// To call de operations, the user can make use of the first       ////
//// letter of the operation (both uppercase and lowercase letters   ////
//// are valid) or the corresponding symbol. 						 ////
//// The user also can change the mode of calling operations, there  ////
//// are three (3) cases: Only Symbols, Only Letters, Both letters   ////
//// and symbols. 													 ////
//// The instructions are displayed at the beigining of the program. ////
//// NOTE: math.h was only used for Not-A-Number case, because if    ////
//// the result = NAN, the condition (result != result) its true,    ////
//// and its is necessary for a simple code flow; if not, the        ////
//// general operation of the program needs to be changed.           ////
//// --------------------------------------------------------------- ////
/////////////////////////////////////////////////////////////////////////

//// DEFINE SECTION ////
//// -------------- ////
#define MAX_OP 20
#define ASCII 256
#define ERR -1
#define MAX_STR_SZ 100

#define CODE_SUCCESS "@"
#define CHAR_CODE_SUCCESS '@'

#define letters_sz 52

enum {SYMBOL_MODE , LETTER_MODE , ALL_ENABLED};
//// -------------- ////

//// MAIN FUNCTIONS ////
//// -------------- ////
void welcome_print(void);
//// welcome_print: displays the instruction menu.
////	Input/Output: (none)
void set_operations_symbol(int mode);
//// set_operations_symbol: sets the array of valid chars.
//// to use at calling operations.
//// 	Input: mode (defines SYMBOL_MODE / LETTER_MODE / ALL_ENABLED)
////	Output: (none)
void add_operation(char o, float (*a)(float, float));
//// add_operation: sets a pointers to functions with the
//// corresponding address. 
////	Input: char of the operation, pointer to function
////	Output: (none)
void config_operations(void);
//// config_operations: sets an array of pointers to functions, 
//// calling add_operation.
////	Input/Output: (none)
//// -------------- ////

//// INPUT FUNCTIONS ////
//// --------------- ////
int  validate(char *input);
//// validate: validates a string of a real number.
////	Input: pointer to array with real number
////	Output: 1 (valid), 0 (not valid)
void str_2_float( char *input , double *v_ans , int *err);
//// str_2_float: converts a string of a number into a double,
//// and returns it through a pointer to double.
////	Input: pointer to string with a real number
////	Output: (none)
void read_line(char *str , int *sz);
//// read_line: scans a word from the keyboard, and returns the word
//// and its size through pointers.
////	Input: pointer to string, pointer to size
////	Output: (none)
void process_command(char *input,int sz,char **ans,double *n_ans);
//// process_command: calls read_command_operation for changing actual 
//// valid operators, or calls read_number_operation for doing operations.
////	Input: pointer to string with keyboard entry word, size of the word, double
////           pointer to answer char, pointer to double number (in case of doing an operation)
////	Output: (none)
void read_command_operation(char *input,int sz,char **ans);
//// read_command_operation: modifies the actual valid operators (symbols,
//// letters or both). Returns through a pointer, a message with the modification. 
////	Input: pointer to string with word, size of the word, double pointer to string
////	Output: (none)
void read_number_operation(char *input,int sz,char **ans,double *n_ans);
//// read_number_operation: processes the entered word, if its valid, separates
//// the numbers entered and the operator, makes the operation and returns the result 
//// through a pointer. If the word, the operation or the operator are not valid,  
//// displays the corresponding messages.
////	Input: pointer to string with numbers and operation, size of the word, double 
////	       pointer to message, pointer to the result of the operation   
////	Output: (none)
void remove_spaces(char *str ,int *sz);
//// remove_spaces: modifies a string, removing space chars.
////	Input: pointer to string, pointer to size
////	Output: (none)
//// --------------- ////

//// BASIC SET FUNCTIONS ////
//// ------------------- ////
void set(int arr[] , int n,int v); 
//// set: set all array values to input v.
////	Input: pointer to array, size of array, value to set
////	Output: (none)
void set_custom(int arr[], int indexes[],int ind_sz, int value);
//// set_custom: sets indexes[i] elements of arr with value, i >=0.
////	Input: array to set elements, array whose elements are the index of the
////		   elements of arr to modify, size of indexes array, value to set 
////		   in arr elements.
////	Output: (none) 
//// ------------------- ////

//// OPERATION FUNCTIONS ////
//// ------------------- ////
float add (float a,float b); // Output: a + b
float sub (float a,float b); // Output: a - b
float mul (float a,float b); // Output: a * b
float div (float a,float b); // Output: a / b (b != 0)

float and(float a, float b); // Output: a & b
float or(float a,float b);   // Output: a | b
float xor(float a,float b);  // Output: a ^ b
//// ------------------- ////

//// GLOBAL VARIABLES ////
//// ---------------- ////
int cnt_op; // which mode is enabled
int operators[ASCII]; // ASCII -> index
float (*actions[MAX_OP])(float, float);

int enabled_chars[ASCII]; // enabled characters codes

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
//// ---------------- ////

int main(){
	set(operators,ASCII,ERR); // fill operators table with default ERR
	set_operations_symbol(ALL_ENABLED);

	cnt_op = 0;

	config_operations();

	welcome_print();

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
			if (ans[0] == CHAR_CODE_SUCCESS){
				printf("%f \n",n_ans);
			}else{
				printf("%s \n",ans);
			}
		}
	}
}

void welcome_print(void){

	printf("Welcome to Calculator \n");
	printf("---------------------\n");
	printf("Type [number][op][number] (without the brackets)\n");
	printf("General commands:\n");
	printf("c2 => enable only letter operators \n");
	printf("c1 => enable only symbol operators \n");
	printf("c0 => enable all operators \n");
	printf("e  => terminate the program \n");

	printf("Basic commands : Add(+),Substract(-),Multiply(*),Divide(/) \n"); 
	printf("Logic commands : AND(&),OR(|),XOR(^)\n");				
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


float and(float a, float b){
	return (float) ( (int)a & (int)b );
}

float or(float a,float b){
	return (float) ( (int)a | (int)b ); 
}

float xor(float a,float b){
	return (float) ( (int)a ^ (int)b );
}

void set(int arr[] , int n,int v){ 
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
		set ( enabled_chars , ASCII , 1);
		set_custom ( enabled_chars , letters  , letters_sz , 0); // disable letters
	}else if(mode == LETTER_MODE){
		set( enabled_chars , ASCII , 0);
		set_custom( enabled_chars , letters , letters_sz, 1); // enable letters
	}else if (mode == ALL_ENABLED){
		set( enabled_chars , ASCII , 1); // enable all symbols
	}
}

void add_operation(char o, float (*a)(float, float)){
	operators[(int)o] = cnt_op;
	actions[cnt_op] = a;

	cnt_op++;
}

void config_operations(void){

	//// Add symbol functions
	add_operation('+', add); 
	add_operation('-', sub);
	add_operation('*', mul); 
	add_operation('/', div);
	add_operation('&', and);
	add_operation('|', or);
	add_operation('^', xor);
			
	//// Add their letter clones
	add_operation('a', add); 
	add_operation('s', sub);
	add_operation('m', mul);
	add_operation('d', div);
	add_operation('n', and);
	add_operation('o', or);
	add_operation('x', xor);
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

//// Functions to read user input ////

void process_command(char *input,int sz,char **ans,double *n_ans){
	remove_spaces(input , &sz);
	if ((input[0] == 'c') || (input[0] == 'e')){
		read_command_operation(input,sz,ans);
	}else{
		read_number_operation(input,sz,ans,n_ans);
	}
}

void read_command_operation(char *input,int sz, char **ans){
	
	if((input[0] == 'c')){
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

	if(input[0] == 'e'){
		if(sz != 1){
			*ans = "Error, no command specified";
		}else{
			*ans = "e";
		}
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

	if (input[pnt] == '+' || input[pnt] == '-'){ // it may be a starting + or -
		number_a[pnt_a++] = input[pnt++];
	}
	while (pnt < sz && (is_number_type(input[pnt])) ){ // number characters
		number_a[pnt_a++] = input[pnt++];
	}
	number_a[pnt_a] = '\0';

	if (pnt == sz){ // invalid!, nothing more than one number
		*ans = "Invalid input a";
	}else{ 
		op = input[pnt++];	
		if (pnt == sz){ // invalid!, no second number
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
				*ans = "Invalid input (numbers are not readable)"; // invalid numbers
			}else{
				int err;
				float num_ans = calc_res(num_a, num_b , op , &err);
				
				if (err == ERR){
					*ans = "Invalid input (invalid operation) ";
				}
				else if (num_ans != num_ans){ // ans is Nan
					*ans = "Math error";
				}else{
					*ans = CODE_SUCCESS;
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

	int valid = validate( input );
	if (!valid){
		*err = ERR;
	}else{
		enum {READ_INT , READ_DEC};
		*err = 0;

		int i = 0;
		int sg = 1; // Sign variable
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


