#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"
#include "output.h"

void initReg(port_t* port , uint16_t *dir, char name , int sz){
	port->name = name;
	port->dir = dir;
	port->sz = sz;
	// make it zero by default
	(*port->dir) = 0;
}

int initPorts(microPorts_t* mp){ // initializate all port structure
	uint16_t * d = malloc(sizeof(uint16_t));
	uint16_t * a = d; // a and d points to the same place
	uint16_t * b = (uint16_t*)( (uint8_t*)a+1); // b points to the half of d

	int err;
	if (a == NULL || b == NULL || d == NULL){
		err = 1;
	}else{
		// init ports
		initReg(&mp->A,a,'A',8);
		initReg(&mp->B,b,'B',8);
		initReg(&mp->D,d,'D',16);
		err = 0;
	}
	return err;
}
void endPorts(microPorts_t* mp){ // end ports system
	free(mp->D.dir);
}

void bitSet(port_t *port, uint16_t bit){
	if (bit < port->sz){ // check if bit is valid
		(*port->dir) |= (1<<bit);
	}
}
void bitClr(port_t *port, uint16_t bit){
	if (bit < port->sz){
		(*port->dir) &= (~(1<<bit));
	}
}
int bitGet(port_t *port, uint16_t bit){
	int ans;
	if (bit < port->sz){
		ans = ((*port->dir) & (1<<bit))!=0;
	}else{
		ans = -1;
	}
	return ans;
}
void maskOn(port_t *port, uint16_t mask){
	mask &= (1<<(port->sz+1) )-1; // disable mask invalid bits
	(*port->dir) |= mask;
}
void maskOff(port_t *port, uint16_t mask){
	mask &= (1<<(port->sz+1) )-1;
	(*port->dir) &= ~mask;
}
void maskToggle(port_t *port, uint16_t mask){
	mask &= (1<<(port->sz+1) )-1;
	(*port->dir) ^= mask;
}

int bit_setup(port_t *port, char c, char port_letter){

	int ans = TRUE, result, mask;
	int aux_var = INPUT_ERR;

	switch(c){
		case '1': // bitSet
			printf("Enter bit to set: ");
			aux_var = get_number();
			if(port_letter == 'D'){
				while(aux_var == INPUT_ERR){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to set: ");
					aux_var = get_number();
				}	
			}else{
				while((aux_var == INPUT_ERR)||(aux_var > 7)){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to set: ");
					aux_var = get_number();
				}
			}
			
			bitSet(port, aux_var);
			showPort(port);
		break;
		case '2': // clear bit
			printf("Enter bit to clear: ");
			aux_var = get_number();
			if(port_letter == 'D'){
				while(aux_var == INPUT_ERR){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to clear: ");
					aux_var = get_number();
				}	
			}else{
				while((aux_var == INPUT_ERR)||(aux_var > 7)){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to clear: ");
					aux_var = get_number();
				}
			}

			bitClr(port, aux_var);
			showPort(port);
		break;
		case '3': // get bit status
			printf("Enter bit to get status: ");
			aux_var = get_number();
			if(port_letter == 'D'){
				while(aux_var == INPUT_ERR){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to get status: ");
					aux_var = get_number();
				}	
			}else{
				while((aux_var == INPUT_ERR)||(aux_var > 7)){ // bit validation
					system("clear");
					bitConfig_print(port_letter);
					printf("Invalid input option. Type again bit to get status: ");
					aux_var = get_number();
				}
			}
			result = bitGet(port, aux_var);
			printf("Bit %d status: %d\n", aux_var, result);
		break;
		case '4': // mask on 
			mask = MASK_ON;
			maskOn(port, mask);
			showPort(port);
		break;
		case '5': // mask off
			mask = MASK_OFF;
			maskOff(port, mask);
			showPort(port);
		break;
		case '6': // mask toogle
			mask = MASK_TOGGLE;
			maskToggle(port, mask);
			showPort(port);
		break;
		default:
			ans = FALSE;
		break;
		}


	return ans;
}

char get_input(void){

	unsigned int i = 0;

	char c, in_char;

	while ( (c = getchar()) != '\n'){
		i++;
		in_char = c;
	}

	if(i != 1)	
		in_char = INPUT_ERR;
	
	return in_char;
}

int get_number(void){

	unsigned int i = 0, in_num = 0;

	char c; 

	while ( (c = getchar()) != '\n'){
		i++;
		if(i >= 3){ // exceded format
			in_num = INPUT_ERR;
		}else if((c >= '0')&&(c <= '9')){
			if(i == 1){
				in_num += (c - '0');
			}
			if(i == 2){
				in_num = (in_num * 10) + (c - '0'); 
			}
		}else{ // invalid input
			in_num = INPUT_ERR;		
		}
	}

	if(i == 0){
		in_num = INPUT_ERR; // input only enter
	}
	return in_num;
}	
