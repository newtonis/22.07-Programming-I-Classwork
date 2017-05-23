#include "port_utils.h"
#include "testing.h"

void testBitSet( microPorts_t * mp){
	bitSet(&mp->A,0);
	bitSet(&mp->B,3);

	bitSet(&mp->D,7);
	bitSet(&mp->D,8);
	bitSet(&mp->D,15);
}

void testBitClear( microPorts_t * mp){
	//bitSet(&mp->A,0);
	//bitSet(&mp->B,3);

	bitSet(&mp->D,7);
	bitSet(&mp->D,8);
	//bitSet(&mp->D,15);

	bitClr(&mp->D,8);
	bitClr(&mp->B,5);
}