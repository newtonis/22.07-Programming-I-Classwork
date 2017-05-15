#ifndef GAME_H
#define GAME_H


void init_game(char init_matrix[][N],char game_mat[][N]);

void next_evolution(char mat[][N]);


/* next_cell_ev: recibe las coordenadas de una celda, y la matriz de juego, y devuelve
   el estado que tendra dicha celda en la siguiente iteracion. */
static int next_cell_ev(int i,int j,char mat[][M]); 

/* cnt_nbours: recibe las coordenadas de una celda, y la matriz de juego, y devuelve la
   cantidad de celulas vecinas vivas que posee en las 8 celdas de alrededor. */
static int cnt_nbours(int i, int j,char mat[][N]);




#endif //GAME_H