/* TP4 - GRUPO 3 */
/* El Juego de la Vida*/

/// 	Ariel Nowik
/// 	Marcelo Regueira
/// 	Joaquin Mestanza

#include <stdio.h>

#define M 6 // Cantidad de filas
#define N 6 // Cantidad de columnas
#define MIN_NB 2 // Configuracion minima y maxima de la cantidad de vecinos para una celda ser viva o muerta
#define MAX_NB 3
#define ALIVE '*' // Simbologia adoptada para identificar celulas vivas y muertas
#define DEAD ' '

#define CNT_NBOURS 8 // Cantidad de vecinos de una celda (usada en una matriz para el funcionamiento del juego)


#define INPUT_ERR -1 // Codigos de error input
#define INPUT_ENTER -2

// Criterio: la matrix hardcodeada se declara global. De esta forma
// esta cerca del principio del programa y es facil modificarla rapido

char seed_matrix[M][N] = {
	{' ',' ',' ',' ',' ',' '},
	{' ','*','*','*','*',' '},
	{' ','*','*','*',' ',' '},
	{' ','*','*','*','*',' '},
	{' ','*',' ',' ',' ',' '},
	{' ',' ','*','*',' ',' '}
};

void init_game(char mat[][N]);

void finalize_evolution(char mat[][N]); // pasar al siguiente estado

void output_world(char mat[][N]);


//// funciones mas auxiliares 
void copy_matrix (char src[][M], char dst[][M]); // copia de src(source) a dst(destination)

int next_cell_ev(int i,int j,char mat[][M]); // si estamos en la iteracion i, nos retornara el estado de la celda en la iteracion i+1

int cnt_nbours(int i, int j,char mat[][N]); // cotar la cantidad de vecinos vivos de una celda

int leer_numero(); // leer un entero de la entrada estandar

int main(){
	char game_matrix[M][N];
	init_game(game_matrix);


	printf("Bienvenido al juego de la vida \n");
	printf("Configuracion: %dx%d \n",M,N);
	printf("-------------------- \n");
	printf("\n");

	int i = 0;
	int cont = 1;

	while (cont){
		printf("Estado del juego: (iteracion %d) \n",i);
		output_world(game_matrix);
		printf("Escriba la cantidad de iteraciones a realizar\n");
		printf("(Escribir 0 para terminar el programa) \n");
		printf("\n");
		printf("Iteraciones: ");
		int it = leer_numero();
		if(it == INPUT_ERR){
			printf("Entrada invalida \n");
		}else if (it != 0){
			int j;
			for (j = 0;j < it;j++){ // iteramos it veces el mundo
				i ++ ;
				finalize_evolution(game_matrix); 
				if (j != it-1){ // no queremos ver la misma matriz dos veces!
					printf("Estado del juego: (iteracion %d) \n",i);
					output_world(game_matrix);
				}
			}
		}else if (it == 0){
			cont = 0;
		}
	}
}

void finalize_evolution(char mat[][N]){ // actualizamos cada casillero por separado
	int i , j; 
	char aux_next[N][M]; // matriz auxiliar con el futuro estado del juego.

	for (i = 0;i < M;i++){
		for (j = 0;j < N;j++){
			aux_next[i][j] = next_cell_ev(i,j,mat); // estudiamos el estado de la celda segun las reglas
		}
	}
	copy_matrix(aux_next , mat); // ahora si se actualiza la matriz del juego
}

int next_cell_ev (int i,int j,char mat[][M]){

	int cant_vecinos, cell_status, new_state;

	cell_status = mat[i][j]; // Averiguo primero el estado de la celda

	cant_vecinos = cnt_nbours(i, j, mat);

	switch(cell_status){
		case ALIVE: // If the cell is ALIVE
			if((cant_vecinos < MIN_NB) || (cant_vecinos > MAX_NB)){
				new_state = DEAD;
			}else if((cant_vecinos == MIN_NB) || (cant_vecinos == MAX_NB)){
				new_state = ALIVE;
			}
		break;
		case DEAD: // If the cell is DEAD
			if(cant_vecinos == MAX_NB){
				new_state = ALIVE;
			}else{
				new_state = DEAD;
			}
		break;
	}
	return new_state;
}

int cnt_nbours(int i, int j,char mat[][N]){
    int k;
    int ans = 0;

	int mv_i[CNT_NBOURS] = {1, 1, 0,-1,-1,-1,0,1};
	int mv_j[CNT_NBOURS] = {0,-1,-1,-1 ,0, 1,1,1}; // OJO

    for(k = 0 ;k < CNT_NBOURS;k++){
		int n_i = i + mv_i[k];
		int n_j = j + mv_j[k];
		if (n_i >= 0 && n_i <= M && n_j >= 0 && n_j <= N){        
        	ans += (mat[ i + mv_i[k] ][ j + mv_j[k] ]) == ALIVE;
    	}
    }

    return ans;
}

void output_world(char mat[][N]){
	int i, j;
	printf("\n");
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			printf("|%c",mat[i][j]);
		}
		printf("|\n");
	}
	printf ("\n");
}

void init_game(char mat[][N]){
	copy_matrix(seed_matrix , mat);
}

int leer_numero(){
	int ans = 0; // en el caso de que el usuario solo presione enter
	int abort = 0;
	int f_enter = 1; // flag para controlar si el usuario solo escribe enter

	char c;
	while ( (c = getchar()) != '\n'){
		if (c >= '0' && c <= '9'){
			ans *= 10;
			ans += (c - '0');
		}else{
			abort = 1; // seguiremos iterando para vaciar el buffer
		}
		f_enter = 0;
	} 
	if (abort){
		ans = INPUT_ERR;
	}
	if (f_enter){
		ans = INPUT_ENTER;
	}
	return ans;
}

void copy_matrix (char src[][N], char dst[][N]){
	int i, j;
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			dst[i][j] = src[i][j];
		}
	}
}