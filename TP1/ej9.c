#include <stdio.h>

// GRUPO 3 - TP1 - EJERCICIO 9 //
// Regueira, Nowik, Mestanza

/* 
Funcionamiento:
   Idea inicial:
     - el casteo int en principio sirve para redondear para abajo
     - Pero podemos ampliarlo! Solo es cuestion de desfasarlo en, 
         - +0.5 (para redondear al entero mas cercano)
	     - +1.0 (para redondear para arriba)
     
   Problemas:
     - (A) Si n es entero, en el caso +1.0 (para arriba), obtengo (n+1.0) y no n.
     - (B) Si n es negativo, entonces el casteo int redondea para arriba, ya que solo remueve los bits menos significativos
   
   Soluciones:
     - (de A) restamos a n en ese caso un numero muy pequenio. Corrige en caso n entero, y convierte extremadamente
            improvable la existencia de un contra-ejemplo

     - (de B) Si n es negativo, entonces resto 1 al casteo que fue para arriba y obtengo un casteo para abajo!
            , Para ampliarlo al caso donde n  es entero, entonces sumo numero muy pequenio

	Nota: el programa redondea .5 para arriba si n>0 y para abajo si n<0.
*/



#define small 1e-10 /// minima nocion de numeros distintos

int main(){
	double calcule = -3.5;
	
	int ans_a , ans_b, ans_c;
	double ans_d, ans_e ;
	double corr; // variable auxiliar de correccion de la formula para los negativos

	corr = calcule > 0 ? 0 : (-1 + small);
	
	ans_a = (int)(corr + calcule + 0.5); // redondeado
	ans_b = (int)(corr + calcule + 1.0 - small); // superior
	ans_c = (int)(corr + calcule); // inferior
	ans_d = calcule - (int)(calcule); // parte decimal
	ans_e = (double) ( (int) (corr + 0.5 + (calcule*100.0))  ) / 100.0; // redondeado a dos decimales
 	
 	printf("Numero original: %lf\n",calcule);
 	printf("-------------------------\n");
	printf("Redondeado: %d\n", ans_a);
	printf("Superior: %d\n",ans_b);
	printf("Inferior: %d\n", ans_c);
	printf("Parte decimal: %f\n",ans_d);
	printf("A dos decimales:%f \n",ans_e);
}