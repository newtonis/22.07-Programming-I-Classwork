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

#define ANIO_INCIAL 1900
#define ANIO_FINAL 2500



 /// Funcion para uso externo
int procesar_dias(int dia1 ,int mes1 ,int anio1 , int dia2, int mes2, int anio2); /// procesar la cantidad de dias entre dos dias. Objetivo princial


//// Funciones Auxiliares ////

// calcular cuantos dias hay desde hoy hasta fin de anio [hoy,ultimo dia]
// Es importante el parametro anio para distinguir anios biciestos
int inc_anio(int dia , int mes , int anio);
// Calcular cuantos dias hay desde que inicio el anio [inicio , hoy]
int dec_anio(int dia,int mes,int anio);
int cantidad_dias(int mes,int anio); // calcular dias en un mes de un anio
int biciesto(int anio);
int dias_entre_anios(int anio1,int anio2); // total de dias entre dos anios inclusive [anio1,anio2]. Si anio1>anio2 retorna 0
int dias_entre_meses(int mes1 ,int mes2,int anio); // total de dias entre dos meses de un mismo anio [mes1,mes2] Si mes1>mes2 retorna 0
int cant_dias_anio(int anio);
int valid_range(int dia,int mes,int anio); // retorna si una fecha es consistente, es decir, existe en el calendario.


int main(){
	int v = procesar_dias(6,12,2000,6,12,1992);
	
	if(v == OUT_OF_RANGE){
		printf("Las fechas no tienen fechas que existan \n");
	}else if (v == WRONG_ORDER){
		printf("Las fechas se encuentran en orden incorrecto\n");
	}else{
		printf("Cantidad de dias entre las fechas: %d\n",v);
	}

}

int procesar_dias(int dia1 ,int mes1 ,int anio1 , int dia2, int mes2, int anio2){
	int ans;
	if (!valid_range(dia1,mes1,anio1)){
		ans = OUT_OF_RANGE;
	}else if(!valid_range(dia2,mes2,anio2)){
		ans = OUT_OF_RANGE;
	}else if (anio1 > anio2){ /// no se respeta el orden de las fechas (f1 > f2)
		ans = WRONG_ORDER;
	}else if (anio1 < anio2){  // caso de dos anios distintos
		/// sumamos:
	    /// - dias entre anios sin incluir los anios de inicio y fin (pueden ser 0 anios, corresponden 0 dias)
	    /// - dias desde el primer dia hasta el fin de su anio
	    /// - dias desde el ultimo dia hasta el inicio de su anio

		ans = 0; //[a+1,b-1]
		ans += dias_entre_anios(anio1+1,anio2-1); ///si anio2=anio1+1 entonces la funcion retornara 0, pues no hay anios intermedios entre las fechas.
		ans += inc_anio(dia1,mes1,anio1);
		ans += dec_anio(dia2,mes2,anio2);
	}else if (anio1 == anio2){ /// Aprovechamos las funciones ya hechas para calcular el caso de dos anios iguales
		int a_to_ini = dec_anio(dia1,mes1,anio1); // simplemente restamos los dias que no debemos contar a la cantidad de dias del anio
		int b_to_end = inc_anio(dia2,mes2,anio2);
		ans = cant_dias_anio( anio1 ) - a_to_ini - b_to_end + 2; 
		if (ans <= 0){
			ans = WRONG_ORDER; // no se respeta el orden ya que no hay dias entre las dos fechas (dias negativos => no hay dias)
		}
	}
	return ans;
}
int valid_range(int dia,int mes,int anio){
	int ans = INVALID;
	if (anio >= ANIO_INCIAL && anio <= ANIO_FINAL){
		if (mes >= 1 && mes <= MESES){
			if (dia >= 1 && dia <= cantidad_dias(mes,anio)){
				ans = VALID;
			}
		}
	}
	return ans;
}
int dias_entre_anios(int anio1,int anio2){ 
	int ans;
	if (anio1 > anio2){ // rango invalido, retornamos 0 dias
		ans = 0;
	}else{
		ans = 0;
		int anio_act;
		for (anio_act = anio1;anio_act <= anio2;anio_act++){
			ans += biciesto(anio_act) ? DIAS_BICIESTO : DIAS_NO_BICIESTO;
		}
	}
	return ans;
}
int inc_anio(int dia , int mes , int anio){
	int dias_fin_mes  = cantidad_dias(mes,anio) - dia + 1; // dias hasta fin de mes
	int dias_fin_anio = dias_entre_meses(mes + 1 , MESES,anio); // dias entre el mes proximo y fin de anio.
	//Si no hay dias, el rango sera invalido => se retorna 0 dias

	return dias_fin_mes + dias_fin_anio;
}
int dec_anio(int dia,int mes,int anio){
	int dias_inicio_mes = dia;
	int dias_incio_anio = dias_entre_meses(1, mes - 1,anio); // dias entre incio de anio y el mes anterior

	return dias_inicio_mes + dias_incio_anio;
}
int dias_entre_meses(int mes1 ,int mes2,int anio){ // cuantos dias hay entre [mes1,mes2], dentro de un mismo anio.
	int ans;
	if (mes1 > mes2){
		ans = 0; // el rango no es valido. Retornamos 0 dias
	}else{
		ans = 0;
		int mes_i;
		for (mes_i = mes1;mes_i <= mes2;mes_i++){
			ans += cantidad_dias(mes_i,anio);
		}
	}
	return ans;
}

int cantidad_dias(int mes,int anio){ /// retornamos la cantidad de dias en un mes del anio
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

int biciesto(int anio){ /// revisar de ser biciesto un anio
	int ans;
	if (anio % 100 == 0){
		ans = (anio % 400) == 0;
	}else{
		ans = (anio % 4) == 0;
	}
	return ans;
}

int cant_dias_anio(int anio){ /// revisar cuatnos dias tiene un anio
	return biciesto(anio) ? DIAS_BICIESTO : DIAS_NO_BICIESTO;
}