#include <stdio.h>
#define ERR -1
#define NO_ERR 0

float calc_res(float x, float y, char op);
float (∗actions[MAX_OPERATORS]) (float ,float) = {add,sub,mult};
int main(){



}

float calc_res(float x, float y, char op,int *p2err){

	int err_op=NO_ERR;
	int *p2err=&err_op;

		if( ( *(operators[op]) ) != ERR ){	
			ans=(actions[operators[op]])(x,y);
		
	}else{
		*(p2err)=ERR;
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
float mult(float a,float b){
	float ans;
	ans= a*b;
	return ans;
}

float div(float a,float b){
	float ans;
	if(b!=0)
	ans= a/b;
	else{
		ans=ERR;
	}
	return ans;
}


