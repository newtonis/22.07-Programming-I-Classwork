#include <stdio.h>

enum {INTEGER , DECIMAL};

enum {POS , NEG};

int main(){
	char c; 
	int mode = INTEGER;
	double number = 0;
	double dv = 1;
	int sign = POS;
	int it = 0; // iteraciones
	int err = 0;

	while ( !err && (c = getchar()) != '\n'){
		if (c >= '0' && c <= '9'){
			if (c == '.'){
				if (mode == INTEGER){
					mode = DECIMAL;
				}else{
					err = 1; // error, two points
				}
			}else if (c == '-'){
				if (it != 0){
					err = 1; /// error, no first iteration
				}else{
					sign = NEG;
				}
			}else{
				err = 1; ///error invalid character
			}	
		}else{
			switch (mode){
				case INTEGER:
					number += c - '0';
					number *= 10;
				break;
				case DECIMAL:
					dv /= 10.0;
					number += dv * (double)(c - '0');
				break;
			}
		}
		it ++;
	}

	if (sign == NEG){
		number = -number;
	}
	number *= 3.0;
	if (err){
		printf("err \n");
	}else{
		printf("%f \n",number);
	}
}
