#include <stdio.h>

#define SEPARADOR '/'
#define ESPERAR 0
#define INFO_OK 1

void print_instructions(void);	         // Imprime las instrucciones de uso
void proc_char1(char cont1, char dato1); // Procesa los caracteres fecha 1 salvo ENTER
void proc_char2(char cont2, char dato2); // Procesa los caracteres fecha 2 salvo ENTER
void check_in(char numero);			     // Chequea si el caracter recibido esta dentro de los esperados
void check_sep(char space);			     // Chequea si el caracter separador es el que corresponde
void clear_data(void);				     // Si hay error resetea los datos almacenados y avisa

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

}

void print_instructions(void){
	printf("Calcular el diferencial entre 2 fechas\n");
	printf("--------------------------------------\n");
	printf("Ingrese la fecha 1: ");
}

void proc_char1(char cont1, char dato1){ 
	switch(cont1){
		case(1): // Decenas del dia
			in_dia1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case(2): // Unidades del dia
			in_dia1 += (dato1 - 48);
			check_in(dato1);
		break;
		case(3): // Barra separadora
			check_sep(dato1);
		break;
		case(4): // Decenas mes
			in_mes1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case(5): // Unidades mes
			in_mes1 += (dato1 - 48);
			check_in(dato1);
		break;
		case(6): // Barra separadora
			check_sep(dato1);
		break;
		case(7): // Unidad de mil anios
			in_anio1 += ((dato1 - 48) * 1000);
			check_in(dato1);
		break;
		case(8): // Centena anios
			in_anio1 += ((dato1 - 48) * 100);
			check_in(dato1);
		break;
		case(9): // Decena anios
			in_anio1 += ((dato1 - 48) * 10);
			check_in(dato1);
		break;
		case(10): // Unidades anios
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
		case(1): // Decenas del dia
			in_dia2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case(2): // Unidades del dia
			in_dia2 += (dato2 - 48);
			check_in(dato2);
		break;
		case(3): // Barra separadora
			check_sep(dato2);
		break;
		case(4): // Decenas mes
			in_mes2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case(5): // Unidades mes
			in_mes2 += (dato2 - 48);
			check_in(dato2);
		break;
		case(6): // Barra separadora
			check_sep(dato2);
		break;
		case(7): // Unidad de mil anios
			in_anio2 += ((dato2 - 48) * 1000);
			check_in(dato2);
		break;
		case(8): // Centena anios
			in_anio2 += ((dato2 - 48) * 100);
			check_in(dato2);
		break;
		case(9): // Decena anios
			in_anio2 += ((dato2 - 48) * 10);
			check_in(dato2);
		break;
		case(10): // Unidades anios
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
	while((getchar()) != '\n');
}