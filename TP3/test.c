#include <stdio.h>

int dias_entre_anios(int anio1,int anio2);

enum {FAIL , SUCCESS};
enum {POS , NEG};
enum {INTEGER, DECIMAL};

int main(){
	int c;
	int result = SUCCESS;
	double number = 0;
	int sign = POS;
	int decimal_mode = 0;
	double unit;

	while ( (c = getchar()) != '\n'){
		if (c == '-'){
			sign = NEG;
		}else if(c == '.'){
			mode = DECIMAL;
			unit = 1;
		}else{
			if (mode == INTEGER){
				number *= 10;
				number += c-'0';
			}else if(mode == DECIMAL){
				number += (double)(c-'0') * unit;
				unit = unit / 10.0;
			}
		}
	}
	if (sign == NEG){
		number = - number;
	}
	number 
}