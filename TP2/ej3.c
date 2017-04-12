#include <stdio.h>

#define TEMPER 28.0

int main(){
	double temp = TEMPER;
	if (temp >= 30.0 && temp <= 90.0){
		printf("Alta\n");
	}else if(temp >= 15.0 && temp < 30.0){
		printf("Media\n");
	}else if(temp >= 0 && temp < 15){
		printf("Baja\n");
	}else if (temp > 90.0 && temp < 0){ /// nota: mucho mas claro que poner un else! 
		printf("Alarma");
	}

}