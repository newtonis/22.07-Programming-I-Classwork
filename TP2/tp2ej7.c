#include <stdio.h>

// Ejercicio 7
//Marcelo Regueira
//Mestanza Joaquin
//Nowik Ariel

/* 
Se evalua si el valor de la constante NUMBER es primo.

Nota 1: Los numeros menores o iguales a 1 no se consideraran ni primos,
ni compuestos.
Nota 2: Existe una propiedad que dice que solo es necesario revisar (desde 2)
hasta la raiz del numero para revisar si es primo. Por lo tanto solo revisamos hasta 
ese valor. En caso de no ser entero, lo truncamos para abajo.
Esto implica que la demora del programa es proporcional a la raiz cuadrada del numero.	
*/

#define NUMBER  15

int main(){
	int i , num = NUMBER;

	char es_primo = 1;

	if(num <= 1){
		printf("El numero no es ni primo ni compuesto\n"); 
	}else{
		for(i = 2;i*i<=num;i++){ /// el (=) es importante. En el caso de un cuadrado perfecto la raiz debe ser revisada
			if(num % i == 0){
				es_primo = 0;  //encontramos un divisor => es compuesto
			}
		}
		if(es_primo == 1){	/// no hay divisores => es primo				   
			printf("el numero %d es primo\n",num);   
		}else{
			printf("el numero %d es compuesto\n",num);
		}
	}

	return 0;
}
