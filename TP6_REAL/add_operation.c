#include <stdio.h>

#define MAX_OPERATORS 10
#define ASCI 256
#define SYMBOL_MODE 2
#define LETTER_MODE 3

//// MAIN FUNCTIONS ////
void set_operations_symbol(int mode); 

void add_operation(char o, float (*a)(float, float));

//// OPERATION FUNCTIONS ////
float add(float a, float b);
float sub(float a, float b);
float mul(float a, float b);
//// ------------------- ////

//// GLOBAL VARIABLES ////
int op_asign; // Only used by set_operations_symbol
int operators[ASCI];
float (* actions [MAX_OPERATORS])(float, float);
//// ---------------- ////


int main(void)
{
	int op_mode = SYMBOL_MODE;
	set_operations_symbol(op_mode);
	

	return 0;
}

void set_operations_symbol(int mode){

	op_asign = 0;

	switch(mode){
		case SYMBOL_MODE:
			add_operation('+', add); // add function
			add_operation('-', sub); // sub function 
			add_operation('*', mul); // mul function
		break;
		case LETTER_MODE:
			add_operation('a', add); // add function
			add_operation('s', sub); // sub function 
			add_operation('m', mul); // mul function
		break;
	}

}

void add_operation(char o, float (*a)(float, float)){

	operators[(int)o] = op_asign;
	actions[op_asign] = a;

	op_asign++;
}

float add(float a, float b){

	return (a+b);
}

float sub(float a, float b){

	return (a-b);
}

float mul(float a, float b){

	return (a*b);
}