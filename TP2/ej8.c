#include <stdio.h>

/// Ejericicio 8:
// Ariel Nowik
// Joaquin Mestanza
// Marcelo Regueira


#define FORM_CASILLERO(i,j) ((i)+(j)) /// que valor tendra un casillero en funcion de fila (i) y columna (j)
#define FILAS 10
#define COLUMNAS 10

/// Notar que, al asignarle a un casillero i+j, luego todas las secuencias horizontales y vertciales seran crecientes

int main(){
	int n = FILAS , m = COLUMNAS; 
	int fil,col; 
	for (fil = 0;fil < n;fil++){ // por cada fila 
		for (col = 0;col < m;col++){ // por cada columna 
			printf("%3d ", FORM_CASILLERO(fil,col) );
		}
		printf("\n"); // ha terminado la columna
	}
	printf("%d",h);
}
