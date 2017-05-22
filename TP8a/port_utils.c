#include "port_struct.h"

int init_ports(microPorts* mp){ // initializate all port structure
	mp.A = (uint8_t *) malloc(sizeof(uint8_t));
	mp.B = (uint8_t *) malloc(sizeof(uint8_t));
	mp.D = (uint16_t*)mp.A;
	int err;
	if (mp.A == NULL || mp.B == NULL || mp.C == NULL){
		err = 1;
	}else{
		err = 0;
	}
	return err;
}
void end_ports(microPorts* mp){ // end ports system
	free(mp.A);
	free(mp.B);
}

void bitSet(port_t *port, int bit){
	(*(port.dir)) | (1<<bit);
}
void bitClr(port_t *port, int bit){
	(*port.dir)) & (~(1<<bit));
}
int bitGet(port_t *port, int bit){
	return (port.dir & (1<<bit))!=0;
}
void maskOn(port_t *port, int mask){

}
void maskOff(port_t *port, int mask){

}
void maskToggle(port_t *port, int mask){

}