//////////////////
// GAME LIBRARY //
// ============ ////////////////////////////////////////////////////
// Funciones para el funcionamiento interno del juego             //
// => Uso: se utilizan los siguientes parametros de configuracion //
// 		   M - Filas de matriz                                    //
//         N - Colmnas de matriz					              //
////////////////////////////////////////////////////////////////////
#ifndef GAME_H
#define GAME_H

void init_game(char init_matrix[][N],char game_mat[][N]);

void next_evolution(char mat[][N]);

#endif //GAME_H