#include <stdio.h>

#include "config.h"
#include "utils.h"
#include "game.h"
#include "front_end.h"

///////////////////////////////////////
//// TP7 - MULTIARCHIVOS - GRUPO 3 ////
//// ----------------------------- ////
//// ==> MESTANZA, Joaquin         ////
//// ==> NOWIK, Ariel              ////
//// ==> REGUEIRA, Marcelo   	   //////////////////////////////////////
//// --------------------------------------------------------------- ////
//// El codigo consta de una reesctructuracion del TP4 - Juego de la ////
//// vida, en formato de multiarchivos. Los conjuntos armados fueron ////
//// los siguientes:												 ////
//// ==> config.h: es un header con las definiciones comunes usadas  ////
////     en los diferentes archivos .c.								 ////
//// ==> game.h/game.c: contienen funciones utilizadas para la       ////
////     actualizacion del estado de las celulas a lo largo de todo  ////
////     el juego.													 ////
//// ==> front_end.h/front_end.c: contienen funciones de interaccion ////
////	 con el usuario a lo largo del juego (como instrucciones de  ////
////     uso).														 //// 
//// ==> utils.h/utils.c: poseen un conjunto de funciones de uso     ////
////     generico que pueden implementarse en cualquier otro progra- ////
////	 ma si asi fuera necesario.									 ////
//// --------------------------------------------------------------- ////
/////////////////////////////////////////////////////////////////////////

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

int main(){
	char game_matrix[M][N];
	
	init_game(seed_matrix , game_matrix);

	welcome_msg();

	int i = 0;
	int cont = TRUE;
	int it = INPUT_ERR;

	while (cont){
		show_game_status(i);
		show_matrix(game_matrix);
		int input = get_turn_user_input();
		if (input != INPUT_ENTER){ // si oprimimos enter, repetimos la opcion elegida antes
			it = input;
		}
		if(it == INPUT_ERR){
			show_error();
		}else if (it != 0){
			int j;
			for (j = 0;j < it;j++){ // iteramos "it" veces el mundo
				i ++ ;
				next_evolution(game_matrix); 
				if (j != it-1){ // no queremos ver la misma matriz dos veces!
					show_game_status(i);
					show_matrix(game_matrix);
				}
			}
		}else if (it == 0){
			cont = FALSE;
		}
	}
}