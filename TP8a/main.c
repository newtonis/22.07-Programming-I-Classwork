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


	maskToggle(&mp.A,0xFF);
	maskToggle(&mp.B,0xFF);

	show_port(&mp.A);
	show_port(&mp.B);
	show_port(&mp.D);

	end_ports(&mp); /// free ports memory
	endPorts(&mp); /// free ports memory
	
	
	printf("%d ",ans);
}