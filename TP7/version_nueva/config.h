////////////////////
// CONFIG LIBRARY //
// ============== ///////////////////////
// Todas las definiciones relacionadas //
// con el funcionamiento del juego     //
/////////////////////////////////////////
#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>

#define M 6 // Cantidad de filas
#define N 6 // Cantidad de columnas
#define MIN_NB 2 // Configuracion minima y maxima de la cantidad de vecinos para una celda ser viva o muerta
#define MAX_NB 3
#define ALIVE '*' // Simbologia adoptada para identificar celulas vivas y muertas
#define DEAD ' '

#define CNT_NBOURS 8 // Cantidad de vecinos de una celda (usada en una matriz para el funcionamiento del juego)

enum {FALSE, TRUE};

#endif //CONFIG_H