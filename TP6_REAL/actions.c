#include <stdio.h>
#define ERR -1
#define NO_ERR 0
#define MAX_OPERATORS 10
#define ASCI 256
#define SYMBOL_MODE 2
#define LETTER_MODE 3

float calc_res(float x, float y, char op);
float add(float a,float b);
float sub(float a,float b);
float mult(float a,float b);
float div(float a,float b);

void set_operations_symbol(int mode); 

void add_operation(char o, float (*a)(float, float));

//// GLOBAL VARIABLES ////
int op_asign; // Only used by set_operations_symbol
int operators[ASCI];
float (* actions [MAX_OPERATORS])(float, float);
//// ---------------- ////
int err_op=NO_ERR;
int *p2err=&err_op;
	

int main(){
	int op_mode = SYMBOL_MODE;
	set_operations_symbol(op_mode);
	
	float x =0.2;
	float y =0.0;
	char op = '/';
	printf("%lf\n",calc_res(x,y,op) );	

}

float calc_res(float x, float y, char op){

	float ans;

		if( ( operators[(int)op] != ERR )){	
			ans=(actions[operators[(int)op]])(x,y);
		
	}else{
		*p2err=ERR;
	}
	return ans;
}

float add(float a,float b){
	float ans;
	ans= a+b;
	return ans;
}
float sub(float a,float b){
	float ans;
	ans= a-b;
	return ans;
}
float mul(float a,float b){
	float ans;
	ans= a*b;
	return ans;
}

float div(float a,float b){
	float ans;

	if(b!=0){
	ans= a/b;
	}else{
		ans=ERR;
		*p2err=ERR;
	}
	return ans;	
}



void set_operations_symbol(int mode){

	op_asign = 0;

	switch(mode){
		case SYMBOL_MODE:
			add_operation('+', add); // add function
			add_operation('-', sub); // sub function 
			add_operation('*', mul); // mul function
			add_operation('/', div);
		break;
		case LETTER_MODE:
			add_operation('a', add); // add function
			add_operation('s', sub); // sub function 
			add_operation('m', mul); // mul function
			add_operation('d', div);
		break;
	}
}

void add_operation(char o, float (*a)(float, float)){

	operators[(int)o] = op_asign;
	actions[op_asign] = a;

	op_asign++;
}

