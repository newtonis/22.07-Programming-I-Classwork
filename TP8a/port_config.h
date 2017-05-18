/////////////////////////
// PORT CONFIG LIBRARY //
// =================== //
/////////////////////////
#include <stdint.h>

// PORT STRUCTURE //
// -------------- //
// Port D = [A:B]
// portD_t.D ==> D port
// portD_t.Dbytes.A ==> A port
// portD_t.Dbytes.B ==> B port
// -------------- //
typedef union{

	uint16_t D;
	struct{
		
		uint8_t B;
		uint8_t A;

	} Dbytes;
/*
	struct{
	
	uint8_t b0 : 1;
	uint8_t b1 : 1;
	uint8_t b2 : 1;
	uint8_t b3 : 1;
	uint8_t b4 : 1;
	uint8_t b5 : 1;
	uint8_t b6 : 1;
	uint8_t b7 : 1;

	uint8_t a0 : 1;
	uint8_t a1 : 1;
	uint8_t a2 : 1;
	uint8_t a3 : 1;
	uint8_t a4 : 1;
	uint8_t a5 : 1;
	uint8_t a6 : 1;
	uint8_t a7 : 1;
	} Dbits;
*/
} portD_t;
// -------------- //

// BIT FUNCTIONS //
// ------------- //
void bitSet(portD_t *port, int bit);
void bitClr(portD_t *port, int bit);
int bitGet(portD_t *port, int bit);
// ------------- //

// MASK FUNCIONS // 
// ------------- //
void maskOn(portD_t *port, int mask);
void maskOff(portD_t *port, int mask);
void maskToggle(portD_t *port, int mask);
// ------------- //