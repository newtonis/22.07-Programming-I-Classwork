#include "front_end.h"
#include "io.h"
#include "config.h"

void welcome_msg(){
	printf("Bienvenido al juego de la vida \n");
	printf("Configuracion: %dx%d \n",M,N);
	printf("-------------------- \n");
	printf("\n");
}
void show_game_status(int i){
	printf("Estado del juego: (iteracion %d) \n",i);
}
void show_error(){
	printf("Entrada invalida \n");
}
int get_turn_user_input(){
	printf("Escriba la cantidad de iteraciones a realizar en formato decimal\n");
	printf("(Escribir 0 para terminar el programa) \n");
	printf("\n");
	printf("Iteraciones: ");
	int it = leer_numero();
	return it;
}
