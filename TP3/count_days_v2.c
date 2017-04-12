#include <stdio.h>

// Codigos de errores.
enum {OUT_OF_RANGE=-100,WRONG_ORDER};
enum {INVALID , VALID};

enum {ENE=1,FEB,MAR,ABR,MAY,JUN,JUL,AGO,SET,OCT,NOV,DEC};

#define ENE_DIAS 31
#define FEB_DIAS 28
#define FEB_DIAS_B 29
#define MAR_DIAS 31
#define ABR_DIAS 30
#define MAY_DIAS 31
#define JUN_DIAS 30
#define JUL_DIAS 31
#define AGO_DIAS 31
#define SET_DIAS 30
#define OCT_DIAS 31
#define NOV_DIAS 30
#define DEC_DIAS 31
#define MESES 12

#define DIAS_BICIESTO 366
#define DIAS_NO_BICIESTO 365

// calcular cuantos dias hay desde hoy hasta fin de anio [hoy,ultimo dia]
// Es importante el parametro anio para distinguir anios biciestos
int inc_anio(int dia , int mes , int anio);
// Calcular cuantos dias hay desde que inicio el anio [inicio , hoy]
int dec_anio(int dia,int mes,int anio);

int cantidad_dias(int mes,int anio); // calcular dias en un mes de un anio
int biciesto(int anio);
int dias_etr_anios(int anio1,int anio2); // total de dias entre dos anios inclusive [anio1,anio2]. Si anio1>anio2 retorna 0
int cant_dias_anio(int anio);

int process_days(int dia1 ,int mes1 ,int anio1 , int dia2, int mes2, int anio2); /// procesar la cantidad de dias entre ambos
int valid_range(int dia,int mes,int anio);



int main(){
	int v = process_days(3,11,1990,6,12,1992);
	printf("%d \n",v);
}

int process_days(int dia1 ,int mes1 ,int anio1 , int dia2, int mes2, int anio2){
	int ans;
	if (!valid_range(dia1,mes1,anio1)){
		ans = OUT_OF_RANGE;
	}else if(!valid_range(dia2,mes2,anio2)){
		ans = OUT_OF_RANGE;
	}else if (anio1 > anio2){ /// no se respeta el orden de las fechas
		ans = WRONG_ORDER;
	}else if (anio1 == anio2){ /// Este caso lo podemos calcular con inclusion/exclusion de conjuntos
		int a_to_ini = dec_anio(dia1,mes1,anio1);
		int b_to_end = inc_anio(dia2,mes2,anio2);
		ans = cant_dias_anio( anio1 ) - a_to_ini - b_to_end + 2; 
		if (ans <= 0){
			ans = WRONG_ORDER; // no se respeta el orden de las fechas
		}
	}else{
		ans = dias_etr_anios(anio1+1,anio2-1); /// nota: la funcion devuelve 0 si se le da un rango invalido
		ans += inc_anio(dia1,mes1,anio1);
		ans += dec_anio(dia2,mes2,anio2);
	}
	return ans;
}
int valid_range(int dia,int mes,int anio){
	int ans = INVALID;
	if (mes >= 1 && mes <= MESES){
		if (dia >= 1 && dia <= cantidad_dias(mes,anio)){
			ans = VALID;
		}
	}
	return ans;
}
int dias_etr_anios(int anio1,int anio2){ //etr = entre
	int ans;
	if (anio1 > anio2){
		ans = 0;
	}else{
		ans = 0;
		for (int anio_act = anio1;anio_act <= anio2;anio_act++){
			ans += biciesto(anio_act) ? DIAS_BICIESTO : DIAS_NO_BICIESTO;
		}
	}
	return ans;
}
int inc_anio(int dia , int mes , int anio){
	int tot_dias = 0;

	while (mes <= MESES){ /// realizamos todos los incrementos posibles mientras estemos dentro del anio
		while (dia <= cantidad_dias(mes , anio)){
			tot_dias ++;
			dia ++;
		}
		dia = 1;
		mes ++;
	}

	return tot_dias;
}
int dec_anio(int dia,int mes,int anio){
	int tot_dias = 0;

	while (mes >= 1){ /// realizamos todos los decrementos posibles mientras estemos dentro del anio
		while (dia >= 1){
			tot_dias ++;
			dia --;
		}
		mes --;
		if (mes >= 1){
			dia = cantidad_dias(mes,anio);
		}
	}
	return tot_dias;
}

int cantidad_dias(int mes,int anio){
	int ans = -1;
	switch (mes){
		case ENE: ans = ENE_DIAS;
		break;
		case FEB: ans = biciesto(anio) ? FEB_DIAS_B : FEB_DIAS;
		break;
		case MAR: ans = MAR_DIAS;
		break;
		case ABR: ans = ABR_DIAS;
		break;
		case MAY: ans = MAY_DIAS;
		break; 
		case JUN: ans = JUN_DIAS;
		break;
		case JUL: ans = JUL_DIAS;
		break;
		case AGO: ans = AGO_DIAS;
		break;
		case SET: ans = SET_DIAS;
		break;
		case OCT: ans = OCT_DIAS;
		break;
		case NOV: ans = NOV_DIAS;
		break;
		case DEC: ans = DEC_DIAS;
		break;
		default: printf("Fatal Error En Cant dias \n");
		break;
	}	
	return ans;
}

int biciesto(int anio){
	int ans;
	if (anio % 100 == 0){
		ans = (anio % 400) == 0;
	}else{
		ans = (anio % 4) == 0;
	}
	return ans;
}

int cant_dias_anio(int anio){
	return biciesto(anio) ? DIAS_BICIESTO : DIAS_NO_BICIESTO;
}