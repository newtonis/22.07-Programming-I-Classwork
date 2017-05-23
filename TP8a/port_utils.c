#include <stdio.h>
#include <stdlib.h>
#include "port_utils.h"

int initPorts(microPorts_t* mp){ // initializate all port structure
	void * d = malloc(sizeof(uint16_t));
	void * a = d; // a and d points to the same place
	void * b = malloc(sizeof(uint16_t ));

	int err;
	if (a == NULL || b == NULL || d == NULL){
		err = 1;
	}else{
		// init ports
		mp->A.name = 'A';
		mp->A.dir = a;
		mp->B.name = 'B';
		mp->B.dir = b;
		mp->D.name = 'A';
		mp->D.dir = d;
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