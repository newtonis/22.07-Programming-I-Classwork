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
#define IS_ENTER 1
#define NOT_ENTER 0
#define TRUE 1
#define FALSE 0
#define BASE_NUM 10 

#define CNT_NBOURS 8 // Cantidad de vecinos de una celda (usada en una matriz para el funcionamiento del juego)


#define INPUT_ERR -1 // Codigos de error de input de teclado
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

/* init_game: inicializa el juego, recibe la matriz local a utilizar, y el contenido
   de la matriz semilla (seed_matrix) es copiado a la matriz pasada de referencia. */
void init_game(char mat[][N]);

/* finalize_evolution: recibe la referncia a la matriz del juego, y modifica una 
   matriz local con los nuevos estados. Al finalizar copia la matriz resultante 
   a la del juego. */
void finalize_evolution(char mat[][N]);

/* output_world: recibe la referncia a la matriz del juego, y muestra en pantalla
   el ultimo estado modificado. */
void output_world(char mat[][N]);

/* copy_matrix: recibe una referencia a una matriz origen (src) y a una matriz 
   destino (dst), y copia el contenido de la matriz origen en la matriz de destino*/
void copy_matrix (char src[][M], char dst[][M]); 

/* next_cell_ev: recibe las coordenadas de una celda, y la matriz de juego, y devuelve
   el estado que tendra dicha celda en la siguiente iteracion. */
int next_cell_ev(int i,int j,char mat[][M]); 

/* cnt_nbours: recibe las coordenadas de una celda, y la matriz de juego, y devuelve la
   cantidad de celulas vecinas vivas que posee en las 8 celdas de alrededor. */
int cnt_nbours(int i, int j,char mat[][N]);

/* leer_numero: lee un entero de la entrada estandar (teclado), devuelve el numero 
   ingresado en formato decimal. */
int leer_numero(); 


int main(){
	char game_matrix[M][N];
	
	init_game(game_matrix);

	printf("Bienvenido al juego de la vida \n");
	printf("Configuracion: %dx%d \n",M,N);
	printf("-------------------- \n");
	printf("\n");

	int i = 0;
	int cont = TRUE;

	while (cont){
		printf("Estado del juego: (iteracion %d) \n",i);
		output_world(game_matrix);
		printf("Escriba la cantidad de iteraciones a realizar en formato decimal\n");
		printf("(Escribir 0 para terminar el programa) \n");
		printf("\n");
		printf("Iteraciones: ");
		int it = leer_numero();
		if(it == INPUT_ERR){
			printf("Entrada invalida \n");
		}else if (it != 0){
			int j;
			for (j = 0;j < it;j++){ // iteramos "it" veces el mundo
				i ++ ;
				finalize_evolution(game_matrix); 
				if (j != it-1){ // no queremos ver la misma matriz dos veces!
					printf("Estado del juego: (iteracion %d) \n",i);
					output_world(game_matrix);
				}
			}
		}else if (it == 0){
			cont = FALSE;
		}
	}
}

void finalize_evolution(char mat[][N]){ // Actualizamos cada casillero por separado
	int i , j; 
	char aux_next[N][M]; // Matriz auxiliar con el futuro estado del juego.

	for (i = 0;i < M;i++){
		for (j = 0;j < N;j++){
			aux_next[i][j] = next_cell_ev(i,j,mat); // Estudiamos el estado de la celda segun las reglas
		}
	}
	copy_matrix(aux_next , mat); // Ahora si se actualiza la matriz del juego
}

int next_cell_ev (int i,int j,char mat[][M]){

	int cant_vecinos, cell_status, new_state;

	cell_status = mat[i][j]; // Averiguo primero el estado de la celda

	cant_vecinos = cnt_nbours(i, j, mat);

	switch(cell_status){
		case ALIVE: // Si la celula esta "ALIVE"
			if((cant_vecinos < MIN_NB) || (cant_vecinos > MAX_NB)){
				new_state = DEAD;
			}else if((cant_vecinos == MIN_NB) || (cant_vecinos == MAX_NB)){
				new_state = ALIVE;
			}
		break;
		case DEAD: // Si la celula esta "DEAD"
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

	int mv_i[CNT_NBOURS] = {1, 1, 0,-1,-1,-1,0,1}; // Desplazamiento horizontal
	int mv_j[CNT_NBOURS] = {0,-1,-1,-1 ,0, 1,1,1}; // Desplazamiento vertical

    for(k = 0 ;k < CNT_NBOURS;k++){
	int n_i = i + mv_i[k];
	int n_j = j + mv_j[k];
	if (n_i >= 0 && n_i <= M-1 && n_j >= 0 && n_j <= N-1){        
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
	int ans = 0; // En el caso de que el usuario solo presione enter
	int abort = FALSE;
	int f_enter = IS_ENTER; // Flag para controlar si el usuario solo escribe enter

	char c;
	while ( (c = getchar()) != '\n'){
		if (c >= '0' && c <= '9'){
			ans *= BASE_NUM; // En este caso la base numerica es 10
			ans += (c - '0');
		}else{
			abort = TRUE; // Seguiremos iterando para vaciar el buffer
		}
		f_enter = NOT_ENTER;
	} 
	if (abort == TRUE){
		ans = INPUT_ERR;
	}
	if (f_enter == IS_ENTER){
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
