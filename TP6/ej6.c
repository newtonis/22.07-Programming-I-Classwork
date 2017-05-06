#include <stdio.h>

#define MAX_SZ 500
#define C_ASCI 256

enum {FALSE,TRUE};

int cnt;
char aux[MAX_SZ];
char str[MAX_SZ];

char *myStringTokenize(char *str,const char *delimiters);

int main(){
	char str[] = "- Esto,un ejemplo.";
	
	char *tok;
	printf("Separando '%s' en tokens:\n",str);
	tok = myStringTokenize(str," ,.-");
	while (tok != NULL){
		printf("%s\n",tok);
		tok = myStringTokenize(NULL," ,.-");
	}
	return 0;
}


char *myStringTokenize(char *str,const char *delimiters){
	char *ans;
	if (str != NULL){
		int i = 0;
		while (str[i] != '\0'){ // copy to aux global
			aux[i] = str[i];
			i ++;
		}
		cnt = 0;
	}
	if (str[cnt] != '\0'){
		int fb[C_ASCI];
		int i;
		for (i = 0;i < C_ASCI;i++){
			fb[i] = FALSE;
		}
		int k = 0;
		while (delimiters[k] != '\0'){
			fb[(int)delimiters[k]] = TRUE; 
			k++;
		}
		int j = 0;
		while ( str[cnt] != '\0' && !fb[(int)str[cnt]] ){
			aux[j++] = str[cnt++];
		}
		ans = aux;
	}else{
		ans = NULL;
	}
	return ans;
}


