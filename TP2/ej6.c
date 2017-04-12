#include <stdio.h>

/// Cantidad de terminos en taylor

#define CNT_TERM 100

int main(){
	double expnt = 1.0; // exponente de e^x
	double acc_expnt = 1; /// exponnte actual, neutro de la multiplicacion es 1
	double sol = 0;

	double crt_val = 1; // variable auxiliar con la constante a dividir en cada termino
	int i;
	for (i = 0;i < CNT_TERM;i++){
		sol += acc_expnt / crt_val;
		//transicion a la proxima potencia de n necesiada
		acc_expnt *= expnt; // x^n = (x^n-1)*n
		//transicion al proximo factorial necesario 
		crt_val *= (i+1); /// f^n+1 = f^n * (n+1)
	}
	printf("%.10f\n",sol);
}