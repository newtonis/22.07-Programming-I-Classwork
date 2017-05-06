#include <stdio.h>


int validate(char *input){ // is an input a decimal number?
	int valid = 1;
	if (!input[0]){
		valid = 0;
	}else{
		int i = 0;
		int dot = 0;
		while (input[i]){
			if (input[i] >= '0' && input[i] <= '9'){
				// nice!
			}else if (input[i] == '.'){
				dot ++;
			}else{
				valid = 0;
			}
			i ++ ;
		}
		if (dot >= 2){
			valid = 0;
		}
		printf("%d %d \n",dot , valid);
	} 
	return valid;
}
void str_2_float( char *input , double *v_ans , int *err){
	/// convert input string to float. Err = 1 in case of invalid string
	int valid = validate( input );
	if (!valid){
		*err = 1;
	}else{
		enum {READ_INT , READ_DEC};
		*err = 0;

		int i = 0;
		int st = READ_INT; // state
		double ans = 0;
		double mul = 0.1;
		while (input[i]){
			switch (st){
				case READ_INT:
					if (input[i] != '.'){
						ans = ans * 10.0 + (double)(input[i] - '0');
					}else{
						st = READ_DEC;
					}
				break;
				case READ_DEC:
					ans = ans + mul * (double)(input[i] - '0');
					mul = mul / 10.0;
				break;
			}
			i ++;
		}
		*v_ans = ans;
	}
}

/// scan a word from keyboard.
void receive_word (char str[],int *sz,int max_sz){ 
	int i = 0;
	char aux_var;
	*sz = 0;
	while((aux_var = getchar()) != '\n'){
		if (i < max_sz){ // we can't store them, there is not enough memory
			str[i] = aux_var;
		}
		i++;
	}
	str[i] = '\0';
	
	*sz = i; // we return total characters inserted no matter we did't add extra ones
}


int main(){
	char test[200];
	int sz, err;
	receive_word(test , &sz , 200);

	double ans;
	str_2_float( test , &ans , &err);

	printf("%f \n", ans);
}