///////////////////
// UTILS LIBRARY //
// ============= /////////////////////////////////////////
// Funciones y declaraciones de 'back-end' de uso comun //
// => Uso: se debe definir las dimensiones de la matriz //
//         M - Filas								    //
// 		   N - Columnas								    //
//////////////////////////////////////////////////////////
#ifndef UTILS_H
#define UTILS_H

#define BASE_NUM 10
#define IS_ENTER 1
#define NOT_ENTER 0

// Error codes //
// ----------- //
#define INPUT_ERR -1
#define INPUT_ENTER -2
// ----------- //

// leer_numero: obtener un numero de la entrada de usuario.
// 	Input: (teclado)
//  Output: numero entero en base 10 o codigo de error
int leer_numero();

// show_matrix: imprime el contenido de una matriz en pantalla.
// 	Input: matriz de MxN
//  Output: (none)
void show_matrix(char mat[][N]);

// copy_matrix: copia el contenido de una matriz en otra.
//	Input: matriz de MxN de origen
//  Output: matriz de MxN de destino
void copy_matrix (char src[][N], char dst[][N]);

#endif //UTILS_H