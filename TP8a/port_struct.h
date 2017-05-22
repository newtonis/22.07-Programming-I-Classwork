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
} portD_t;
// -------------- //
