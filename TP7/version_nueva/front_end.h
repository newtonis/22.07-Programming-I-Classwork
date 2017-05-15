///////////////////////
// FRONT END LIBRARY //
// ================= ///////////////////////////////////////////
// Funciones de uso en el programa principal del juego        //
// => Uso: utiliza los siguientes parametros de configuracion //
// 		   M - Filas de matriz                                //
//         N - Colmnas de matriz					          //
////////////////////////////////////////////////////////////////
#ifndef FRONT_END_H
#define FRONT_END_H

// welcome_msg: imprime en pantalla la configuracion inicial
// del juego. Utiliza las dimensiones de la matriz (definidas).
// 	Input/Output: (none)
void welcome_msg();

// show_game_status: imprime en pantalla el estado actual de 
// iteracion del juego.
//	Input: numero entero de iteracion
//  Output: (none)
void show_game_status(int i);

// show_error: imprime un mensaje de error de entrada en pantalla.
// 	Input/Output: (none) 
void show_error();

// get_turn_user_input: muestra en pantalla las instrucciones de 
// uso y utiliza una funcion auxiliar de lectura de entrada 
// de teclado (leer_numero)
// 	Input/Output: (none)
int get_turn_user_input();

#endif //FRONT_END_H 