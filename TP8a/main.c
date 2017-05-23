#include <stdio.h>
#include "port_utils.h"
#include "output.h"

#define ESCAPE (27)

int main(){
	microPorts_t mp;

	int ans = initPorts(&mp);

	int end =0;
	char c;
	c=getchar();
	while(!end){


		if(('0'<=c)&&(c<='7')){
			bitSet(&mp.A,(int)(c-'0'));
			showPort(&mp.A);
		}else if(c=='b'){
			int i=0;
			int mask_aux=0;
			for(int i;i<8;i++){
				if(bitGet(&mp.A,i)==1){
					mask_aux |=(1<<(7-i)); 
											// 01110000
				}						   // 
			}
			printf("%d",mask_aux);
			maskToggle(&mp.A,mask_aux);
			showPort(&mp.A);
		}else if(c=='c'){
			maskOff(&mp.A,0xFF);
			showPort(&mp.A);
		}else if(c=='s'){
			maskOn(&mp.A,0xFF);
			showPort(&mp.A);
		}else if((int)c==ESCAPE){
			end=0;
		}
		c=getchar();
	}
/*
*/
	endPorts(&mp); /// free ports memory
	
}