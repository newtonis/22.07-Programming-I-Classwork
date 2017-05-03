#include <stdio.h>

char *myStringCt(char *dest,const char *src);

int main(){
	char test[2000] = "oh test please ";
	char *ans = myStringCt(test , "helfghfghfghlo ");
	printf("%s \n",ans);
}


char *myStringCt(char *dest,const char *src){
	int i = sz_dest;
	int j = 0;
	while (j < sz_src){
		dest[i] = src[j];
		i ++; 
		j ++;
	}

	return dest;
}