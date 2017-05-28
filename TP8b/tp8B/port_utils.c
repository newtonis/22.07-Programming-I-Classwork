#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"

static void initReg(port_t* port , uint16_t *dir, char name , int sz);

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

