#include "config.h"
#include "io.h"

int leer_numero(){
	int ans = 0; // En el caso de que el usuario solo presione enter
	int abort = FALSE;
	int f_enter = IS_ENTER; // Flag para controlar si el usuario solo escribe enter

	char c;
	while ( (c = getchar()) != '\n'){
		if (c >= '0' && c <= '9'){
			ans *= BASE_NUM; // En este caso la base numerica es 10
			ans += (c - '0');
		}else{
			abort = TRUE; // Seguiremos iterando para vaciar el buffer
		}
		f_enter = NOT_ENTER;
	} 
	if (abort == TRUE){
		ans = INPUT_ERR;
	}
	if (f_enter == IS_ENTER){
		ans = INPUT_ENTER;
	}
	return ans;
}
