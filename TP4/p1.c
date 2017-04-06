#define M 5// FILS //ROWS
#define N 5// COLS
#define NEIGHBOURS 8// cantidad de vecinos

int count_vecinos(int x, int y, int master_matrix[][N]);


int mvx[NEIGHBOURS]={1,1,0,-1,-1,-1,0,1};
int mvy[NEIGHBOURS]={0,-1,-1,-1,0,1,-1,1};



/*
Count vecinos recibe la posicion de una celda (x,y)
y revisa el estado de los 8 vecinos de esa celda; Además
recibe la direccion inicial de la matriz. En base a eso,
genero un dezplazamiento y me fijo si esa celda (vecina)
esta viva para poder contar cuantas vivas hay.
*/
int count_vecinos(int x, int y,int master_matrix[][N]){

        int i;
        int vecinos = 0;

        for(i=0; i < NEIGHBOURS;i++){
                vecinos+=( (master_matrix[ y+mvy[i] ][ x+mvx[i] ]) == '*');
        }
        return vecinos;
}