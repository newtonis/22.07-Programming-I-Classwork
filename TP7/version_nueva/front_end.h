#ifndef FRONT_END_H
#define FRONT_END_H

// Funciones relacionadas con la interaccion con el usuario


// mensaje de bienvenida
void welcome_msg(); 

// mensaje de turno de juego
void game_msg();

/* recibe la referncia a la matriz del juego, y muestra en pantalla
   el ultimo estado modificado. */
void output_world(char mat[][N]);




#endif // FRONT_END_H