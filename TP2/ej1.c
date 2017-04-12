#include <stdio.h>

int main ( void ){
	char c ;
	for ( c = '1'; c <= '4'; c ++){
		switch ( c ){
			case '1': case '2':
				printf ( "Caso a - %c \n " ,c ) ;
		
			case '3':
				printf ( "Caso b - %c \n " ,c ) ;
	
			default :
				printf ( "Caso c - %c \n " ,c ) ;
		}
	}
}