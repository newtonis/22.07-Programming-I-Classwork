#include <stdio.h>
#include "port_utils.h"
#include "output.h"

int main(){
	microPorts_t mp;

	int ans = initPorts(&mp);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	bitSet(&mp.A,1);
	bitSet(&mp.B,1);
	bitSet(&mp.B,);
	maskOff(&mp.D,0xFFF);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	endPorts(&mp); /// free ports memory
	
	
	printf("%d ",ans);
}