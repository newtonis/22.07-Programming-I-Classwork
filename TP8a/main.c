#include <stdio.h>
#include "port_utils.h"
#include "output.h"
#include "testing.h"

int main(){
	microPorts_t mp;

	int ans = initPorts(&mp);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

	testBitClear(&mp);

	showPort(&mp.A);
	showPort(&mp.B);
	showPort(&mp.D);

<<<<<<< HEAD

	maskToggle(&mp.A,0xFF);
	maskToggle(&mp.B,0xFF);

	show_port(&mp.A);
	show_port(&mp.B);
	show_port(&mp.D);

	end_ports(&mp); /// free ports memory
=======
	endPorts(&mp); /// free ports memory
>>>>>>> 0af5b444ef6be6b42d1e75cebd1c680ba1879fe5
	
	
	printf("%d ",ans);
}