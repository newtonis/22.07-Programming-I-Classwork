#include "game.h"
void copy_matrix (char src[][N], char dst[][N]){
	int i, j;
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			dst[i][j] = src[i][j];
		}
	}
}

void output_world(char mat[][N]){
	int i, j;
	printf("\n");
	for (i = 0;i < N;i++){
		for (j = 0;j < M;j++){
			printf("|%c",mat[i][j]);
		}
		printf("|\n");
	}
	printf ("\n");
}