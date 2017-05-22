
// PORT FUNCTIONS //
// ------------- //
void bitSet(portD_t *port, int bit);
void bitClr(portD_t *port, int bit);
int bitGet(portD_t *port, int bit);

void maskOn(portD_t *port, int mask);
void maskOff(portD_t *port, int mask);
void maskToggle(portD_t *port, int mask);
// ------------- //