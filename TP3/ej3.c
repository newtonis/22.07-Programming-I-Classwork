#include <stdio.h>

/// Cantidad de iteraciones => Define la precision
#define ITER 30


/// Calcular la i-esina derivada del seno en 0
double sen_der_0(int);
double sine(double x);

int main(){
	double v = sine(0.5);
	printf("%f \n",v);
}

double sine(double x){
	double ans = 0;
	double power = 1; // El neutro de la multiplicacion es 1
	int    fact = 1;
	for (int i = 0;i < ITER;i++){
		ans += sen_der_0(i) / (double)fact * power;

		printf("ans = %f \n",sen_der_0(i) / (double)fact * power);

		fact *= (i+1);
		power *= x;
	}
	return ans;
}
double sen_der_0(int i){
	i = i % 4;
	double ans; 
	if (i == 0){
		ans = 0;
	}
	if (i == 1){
		ans = 1;
	}
	if (i == 2){
		ans = 0;
	}
	if (i == 3){
		ans = -1;
	}
	return ans;
}