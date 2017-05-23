#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"

void initReg(port_t* port , char name , uint16_t *dir,int sz){
	port.name = name;
	port.dir = dir;
	port.sz = sz;
	// make it zero by default
	(*port.dir) = 0;
}

int initPorts(microPorts_t* mp){ // initializate all port structure
	uint16_t * d = malloc(sizeof(uint16_t));
	uint16_t * a = d; // a and d points to the same place
	uint16_t * b = malloc(sizeof(uint16_t ));

	int err;
	if (a == NULL || b == NULL || d == NULL){
		err = 1;
	}else{
		// init ports
		initReg(&mp->A,'A',8);
		initReg(&mp->B,'B',8);
		initReg(&mp->D,'D',16);
		err = 0;
	}
	return err;
}
void end_ports(microPorts_t* mp){ // end ports system
	free(mp->A.dir);
	free(mp->B.dir);
}

void bitSet(port_t *port, uint16_t bit){
	if (bit < port->sz){
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
	if (port->sz == 8){
		mask &= 0xFF; // we make sure invalid bits are disabled
	}
	(*port->dir) |= mask;
}
void maskOff(port_t *port, uint16_t mask){
	if (port->sz == 8){
		mask &= 0xFF; // we make sure invalid bits are disabled
	}
	(*port->dir) &= ~mask;
}
void maskToggle(port_t *port, uint16_t mask){
	if (port->sz == 8){
		mask &= 0xFF; // we make sure invalid bits are disabled
	}
	(*port->dir) ^= mask;
}