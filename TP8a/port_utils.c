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

int bit_setup(port_t *port, char c){

	int ans = TRUE, result;
	char aux_var = INPUT_ERR;

	switch(c){
		case '1': // bitSet
			printf("Enter bit to set: \n");
			aux_var = get_input();
			while((aux_var == INPUT_ERR)||(aux_var < '0')||(aux_var > '7')){ // bit validation
				printf("Invalid input option. Type again:\n");
				aux_var = get_input();
			}
			bitSet(port, (aux_var - '0'));
			showPort(port);
		break;
		case '2': // clear bit
			printf("Enter bit to clear: \n");
			aux_var = get_input();
			while((aux_var == INPUT_ERR)||(aux_var < '0')||(aux_var > '7')){ // bit validation
				printf("Invalid input option. Type again:\n");
				aux_var = get_input();
			}
			bitClr(port, (aux_var - '0'));
			showPort(port);
		break;
		case '3': // get bit status
			printf("Enter bit to get status: \n");
			aux_var = get_input();
			while((aux_var == INPUT_ERR)||(aux_var < '0')||(aux_var > '7')){ // bit validation
				printf("Invalid input option. Type again:\n");
				aux_var = get_input();
			}
			result = bitGet(port, (aux_var - '0'));
			printf("Bit %c status: %d\n", aux_var, result);
		break;
		case '4': // mask on 
		break;
		case '5': // mask off
		break;
		case '6': // mask toogle
		break;
		default:
			ans = FALSE;
		break;
	}

	return ans;
}

int portConfig(port_t *port, char c){

	int operation_ok = TRUE;

	if(('0' <= c ) && ( c <= '7')){ // Bit set to port
		bitSet(port,(int)(c-'0'));
		printf("Status port ");
		showPort(port);
	}else if(c == 'b'){ // Blink bit
		int i = 0;
		int mask_aux = 0;
		for( int i ; i < sizeof(uint8_t) ; i++ ){
			if( bitGet (port,i) == 1 ){
				mask_aux |= 1<<i ;
			}						   
		}
		printf("Status port ");
		printf("%d",mask_aux);
		maskToggle(port,mask_aux);
		showPort(port);
	}else if(c == 'c'){ // Turn off bits
		maskOff(port,ALL_BITS_MASK);
		printf("Status port ");
		showPort(port);
	}else if(c == 's'){ // Set all bits 
		maskOn(port,ALL_BITS_MASK);
		printf("Status port ");
		showPort(port);
	}else{
		operation_ok = FALSE;
	}

	return operation_ok;
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

int maskvalid(port_t *port, int random_mask){
	int ans;
	if((port->sz)>(sizeof(uint16_t))){
		ans=NOT_VALID;
	}else{

	if((port->sz) == sizeof(uint8_t)){
		if((0<=random_mask)&& (random_mask<=0xFF)){
			ans=VALID;
		}else{
			ans=NOT_VALID;
		}
	}

	if((port->sz) == sizeof(uint16_t)){
		if((0<=random_mask)&& (random_mask<=0xFFFF)){
			ans=VALID;
		}else{
			ans=NOT_VALID;
			}
		}
	}
	return ans;
}
