#include <stdio.h>

#include "config.h"
#include "io.h"
#include "game.h"
#include "front_end.h"


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
				finalize_evolution(game_matrix); 
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