#include <stdio.h>
#include "port_utils.h"

int main(){
	microPorts_t mp;
	int ans = initPorts(&mp);
	printf("%d ",ans);
}