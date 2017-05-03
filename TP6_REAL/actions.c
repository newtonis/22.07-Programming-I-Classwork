#include <stdio.h>
#define ERR -1

float calc_res(float x, float y, char op);
float (∗actions[MAX_OPERATORS]) (float ,float) = {add,sub,mult};
int main(){

}

float calc_res(float x, float y, char op){
	float *p2x=&x;
	float *p2y=&y;
	

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


