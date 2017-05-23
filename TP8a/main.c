#include <stdio.h>
#include "port_utils.h"
#include "output.h"
#include "testing.h"

int main(){
	microPorts_t mp;

	int ans = initPorts(&mp);

	bitSet(&mp.A,7);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	maskOn(&mp.A,0xFF);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);



	bitClr(&mp.A,0);
	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	maskOff(&mp.A,0xFF);
	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	maskToggle(&mp.A,0x1);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	printf("%d\n",bitGet(&mp.A,0x0));

/*
	maskToggle(&mp.A,0xFF);
	maskToggle(&mp.B,0xFF);

	show_port(&mp.A);
	show_port(&mp.B);
	show_port(&mp.D);

*/
	endPorts(&mp); /// free ports memory
	
	
	printf("%d ",ans);
}