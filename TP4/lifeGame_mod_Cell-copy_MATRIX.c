#include <stdio.h>

#define ALIVE '*'
#define DEAD '@'
#define MIN_vecinos 2
#define MAX_vecinos 3
#define N 6 // Cantidad de filas
#define M 6 // Cantidad de columnas

/* mod_Cell: Recibe las coordenadas de una celda y la matriz de
   juego, y devuelve el nuevo estado a colocar en dicha celda. */
int mod_Cell (int X,int Y,int MATRIX[][M]); 
/* copy_MATRIX: Recibe la matriz de juego y la matriz auxiliar,
   y copia la informacion de la auxiliar a la de juego. */
void copy_MATRIX (int source_MAT[][M], int destiny_MAT[][M]);

int main(void)
{
	return 0;
}

int mod_Cell (int X,int Y,int MATRIX[][M]){

	int cant_vecinos, cell_status, new_state;

	cell_status = get_cell_state(X, Y); // Averiguo primero el estado de la celda

	cant_vecinos = count_vecinos(X, Y, MATRIX);

	switch(cell_status){
		case ALIVE: // If the cell is ALIVE
			if((cant_vecinos < MIN_vecinos)||(cant_vecinos > MAX_vecinos)){
				new_state = DEAD;
			}
			else{
				new_state = ALIVE;
			}
		break;
		case DEAD: // If the cell is DEAD
			if(cant_vecinos == MAX_vecinos){
				new_state = ALIVE;
			}
			else{
				new_state = DEAD;
			}
		break;
	}
	return new_state;
}

void copy_MATRIX (int source_MAT[][M], int destiny_MAT[][M]){

	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < M; j++){
			destiny_MAT[i][j] = source_MAT[i][j];
		}
	}
	
	return 0;
}