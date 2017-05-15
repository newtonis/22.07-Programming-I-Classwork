#include "config.h"

void copy_matrix (char src[][N], char dst[][N]){
	int i, j;
	for(i = 0; i < M; i++){
		for(j = 0; j < N; j++){
			dst[i][j] = src[i][j];
		}
	}
}

