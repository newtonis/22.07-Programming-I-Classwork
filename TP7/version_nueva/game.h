#ifndef GAME_H
#define GAME_H


#define M 6 // Cantidad de filas
#define N 6 // Cantidad de columnas
#define MIN_NB 2 // Configuracion minima y maxima de la cantidad de vecinos para una celda ser viva o muerta
#define MAX_NB 3
#define ALIVE '*' // Simbologia adoptada para identificar celulas vivas y muertas
#define DEAD ' '

#define CNT_NBOURS 8 // Cantidad de vecinos de una celda (usada en una matriz para el funcionamiento del juego)


void init_game(char mat[][N]);

void get_world_matrix(char mat[][N]);

void finalize_evolution(char mat[][N]);


/* next_cell_ev: recibe las coordenadas de una celda, y la matriz de juego, y devuelve
   el estado que tendra dicha celda en la siguiente iteracion. */
static int next_cell_ev(int i,int j,char mat[][M]); 



#endif GAME_H