#include "game.h"
#include "config.h"
#include "utils.h"

void next_evolution(char mat[][N]){ // Actualizamos cada casillero por separado
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

void init_game(char init_matrix[][N],char game_mat[][N]){
	copy_matrix(init_matrix , game_mat);
}
