///////////////////
// LIBRERIA GAME //
// ============= ///////////////////////////////////////////////////
// Funciones para el funcionamiento interno del juego             //
// => Uso: se utilizan los siguientes parametros de configuracion //
// 		   M - Filas de matriz                                    //
//         N - Colmnas de matriz					              //
////////////////////////////////////////////////////////////////////
#ifndef GAME_H
#define GAME_H

// init_game: inicializa las matrices del juego.
//	Input: matriz de dato
// 	Output: matriz de destino, a modificar durante el juego
void init_game(char init_matrix[][N],char game_mat[][N]);

// next_evolution: actualiza en una iteracion todo el juego.
//	Input: matriz de juego
// 	Output: (none)
void next_evolution(char mat[][N]);

#endif //GAME_H