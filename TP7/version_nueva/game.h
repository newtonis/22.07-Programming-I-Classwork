#ifndef GAME_H
#define GAME_H


#define M 6 // Cantidad de filas
#define N 6 // Cantidad de columnas
#define MIN_NB 2 // Configuracion minima y maxima de la cantidad de vecinos para una celda ser viva o muerta
#define MAX_NB 3
#define ALIVE '*' // Simbologia adoptada para identificar celulas vivas y muertas
#define DEAD ' '

#define CNT_NBOURS 8 // Cantidad de vecinos de una celda (usada en una matriz para el funcionamiento del juego)

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

void next_evolution(char mat[][N]);


/* next_cell_ev: recibe las coordenadas de una celda, y la matriz de juego, y devuelve
   el estado que tendra dicha celda en la siguiente iteracion. */
static int next_cell_ev(int i,int j,char mat[][M]); 

/* cnt_nbours: recibe las coordenadas de una celda, y la matriz de juego, y devuelve la
   cantidad de celulas vecinas vivas que posee en las 8 celdas de alrededor. */
static int cnt_nbours(int i, int j,char mat[][N]);




#endif GAME_H