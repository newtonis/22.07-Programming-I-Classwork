/// Marcelo Regueira
/// Joaquin Mestanza
/// Ariel Nowik

/// Nota sobre el funcionamiento: 
/// Se calcula la cantidad de dias incluyendo ambas fechas. (es decir, si ambas fechas son iguales, se retornara 1 dia)
/// El programa verifica primero el formato y luego que la fecha exista antes de calcular el resultado

#include <stdio.h>

// Codigos de errores.
enum {OUT_OF_RANGE=-100,WRONG_ORDER};
enum {INVALID , VALID};
 
enum {ENE=1,FEB,MAR,ABR,MAY,JUN,JUL,AGO,SET,OCT,NOV,DEC};
 
// Costantes para el procesamiento de la entrada
#define SEPARADOR '/'
enum {ESPERAR , INFO_OK};


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


//// Funciones de procesamiento de entrada ////

void print_instructions(void);	         // Imprime las instrucciones de uso
void proc_char1(char cont1, char dato1); // Procesa los caracteres fecha 1 salvo ENTER
void proc_char2(char cont2, char dato2); // Procesa los caracteres fecha 2 salvo ENTER
void check_in(char numero);			     // Chequea si el caracter recibido esta dentro de los esperados
void check_sep(char space);			     // Chequea si el caracter separador es el que corresponde
void clear_data(void);				     // Si hay error resetea los datos almacenados y avisa

 /// procesar la cantidad de dias entre las dos fechas. En Objetivo princial
int procesar_dias(int dia1 ,int mes1 ,int anio1 , int dia2, int mes2, int anio2);

//// Funciones Auxiliares ////


// calcular cuantos dias hay desde hoy hasta fin de anio [hoy,ultimo dia]
// Es importante el parametro anio para distinguir anios biciestos
int inc_anio(int dia , int mes , int anio); 
int dec_anio(int dia,int mes,int anio);     // Calcular cuantos dias hay desde que inicio el anio [inicio , hoy]
int cantidad_dias(int mes,int anio);        // calcular dias en un mes de un anio
int biciesto(int anio);
int dias_entre_anios(int anio1,int anio2);  // total de dias entre dos anios inclusive [anio1,anio2]. Si anio1>anio2 retorna 0
int dias_entre_meses(int mes1 ,int mes2,int anio); // total de dias entre dos meses de un mismo anio [mes1,mes2] Si mes1>mes2 retorna 0
int cant_dias_anio(int anio);
int valid_range(int dia,int mes,int anio);  // retorna si una fecha es consistente, es decir, existe en el calendario.
 

unsigned char in_dia1 = 0, in_dia2 = 0, in_mes1 = 0, in_mes2 = 0, i = 0, fecha = 1; 
int in_anio1 = 0, in_anio2 = 0;

int main(void){

	unsigned char control = ESPERAR;
	int aux = 0;

	print_instructions();

	while(control == ESPERAR){ // Procesamiento de datos para fecha 1
		while((aux = getchar()) != '\n'){ // Mientras recibe datos
			i++;
			proc_char1(i,aux);
		}
		if((i == 10)||(i == 8)){ // Cuando la info esta OK
			if(i == 8){ // Indica anio en formato 1900
				in_anio1 /= 100;
				in_anio1 += 1900;
			}
			i = 0;
			control = INFO_OK;
			fecha = 2;
		}else{
			i = 0;
			in_dia1 = 0;
			in_mes1 = 0;
			in_anio1 = 0;
			printf("\nFecha mal ingresada. Trate nuevamente: ");
		}
	}

	printf("	-Fecha 1 Ingresada: %d/%d/%d\n\n", in_dia1, in_mes1, in_anio1);
	printf("Ingrese la fecha 2: ");
	
	control = ESPERAR;

	while(control == ESPERAR){ // Procesamiento de datos para fecha 2
		while((aux = getchar()) != '\n'){ // Mientras recibe datos
			i++;
			proc_char2(i,aux);
		}
		if((i == 10)||(i == 8)){ // Cuando la info esta OK
			control = INFO_OK;
			if(i == 8){ // Indica anio en formato 1900
				in_anio2 /= 100;
				in_anio2 += 1900;
			}
		}else{
			i = 0;
			in_dia2 = 0;
			in_mes2 = 0;
			in_anio2 = 0;
			printf("\nFecha mal ingresada. Trate nuevamente: ");
		}
	}

	printf("Las fechas elegidas fueron:\n");
	printf("	-Fecha 1 Ingresada: %d/%d/%d\n", in_dia1, in_mes1, in_anio1);
	printf("	-Fecha 2 Ingresada: %d/%d/%d\n", in_dia2, in_mes2, in_anio2);

	/* En este punto las variables de salida si corresponden al formato 
	   se encuentran con la informacion correspondiente: dia, mes, anio,
	   con subindice 1 para los de la primer fecha y subindice 2 para los
	   de la segunda fecha. */

	int v = procesar_dias(in_dia1,in_mes1,in_anio1,in_dia2,in_mes2,in_anio2);
     
    if(v == OUT_OF_RANGE){
        printf("Alguna fecha no existe \n");
    }else if (v == WRONG_ORDER){
        printf("Las fechas se encuentran en orden incorrecto\n");
    }else{
        printf("Cantidad de dias entre las fechas: %d\n",v);
    }

}

void print_instructions(void){
	printf("Calcular el diferencial entre 2 fechas\n");
	printf("--------------------------------------\n");
	printf("Ingrese las 2 fechas de las cuales desea calcular\n");
	printf("la diferencia de dias. Tenga en cuenta que debe\n");
	printf("ingresarlas de menor a mayor en el sentido temporal.\n\n");
	printf("Ingrese la fecha 1: ");
}

void proc_char1(char cont1, char dato1){ 
	switch(cont1){
		case 1: // Decenas del dia
			in_dia1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case 2: // Unidades del dia
			in_dia1 += (dato1 - 48);
			check_in(dato1);
		break;
		case 3: // Barra separadora
			check_sep(dato1);
		break;
		case 4: // Decenas mes
			in_mes1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case 5: // Unidades mes
			in_mes1 += (dato1 - 48);
			check_in(dato1);
		break;
		case 6: // Barra separadora
			check_sep(dato1);
		break;
		case 7: // Unidad de mil anios
			in_anio1 += ((dato1 - 48) * 1000);
			check_in(dato1);
		break;
		case 8: // Centena anios
			in_anio1 += ((dato1 - 48) * 100);
			check_in(dato1);
		break;
		case 9: // Decena anios
			in_anio1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case 10: // Unidades anios
			in_anio1 += (dato1 - 48);
			check_in(dato1);
		break;
		default: // Error - informacion de mas
			clear_data();
		break;
	}
}

void proc_char2(char cont2, char dato2){ 
	switch(cont2){
		case 1: // Decenas del dia
			in_dia2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case 2: // Unidades del dia
			in_dia2 += (dato2 - 48);
			check_in(dato2);
		break;
		case 3: // Barra separadora
			check_sep(dato2);
		break;
		case 4: // Decenas mes
			in_mes2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case 5: // Unidades mes
			in_mes2 += (dato2 - 48);
			check_in(dato2);
		break;
		case 6: // Barra separadora
			check_sep(dato2);
		break;
		case 7: // Unidad de mil anios
			in_anio2 += ((dato2 - 48) * 1000);
			check_in(dato2);
		break;
		case 8: // Centena anios
			in_anio2 += ((dato2 - 48) * 100);
			check_in(dato2);
		break;
		case 9: // Decena anios
			in_anio2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case 10: // Unidades anios
			in_anio2 += (dato2 - 48);
			check_in(dato2);
		break;
		default: // Error - informacion de mas
			clear_data();
		break;
	}
}

void check_in(char numero){ 
	if((numero < '0')||(numero > '9')){
		clear_data();
	}
}

void check_sep(char space){ 
	if(space != SEPARADOR){
		clear_data();
	}
}

void clear_data(void){ 
	printf("\nFecha mal ingresada. Trate nuevamente: ");
	i = 0;
	if(fecha == 1){
		in_dia1 = 0;
		in_mes1 = 0;
		in_anio1 = 0;
	}else{
		in_dia2 = 0;
		in_mes2 = 0;
		in_anio2 = 0;
	}	
	while((getchar()) != '\n'); // Se vacia la cola de caracteres
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