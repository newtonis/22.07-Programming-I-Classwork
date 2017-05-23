#ifndef OUTPUT_H
#define OUTPUT_H

void show_port(port_t *port){
	
	printf("%c :",port->name);
	if (port->dir != NULL){
		int i;
		uint16_t bit;
		for (i = 0;i < port->sz;i++){
			printf("%d",((*port->dir)&bit)!=0);
			bit <<= 1;
		}
	}else{
		printf("NULL");
	}
	printf("\n");
}


#endif // OUTPUT_H