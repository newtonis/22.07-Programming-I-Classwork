#include <stdio.h>

int myStringComp(const char *s,const char *t);

int main(){
	int ans = myStringComp("test","testA");
	printf("%d \n",ans);
}

int myStringComp(const char *s,const char *t){

	int i;
	int ans = 0;

	while (!ans && s[i] != '\0' && t[i] != '\0'){
		if (s[i] > t[i]){
			ans = 1;
		}else if(s[i] < t[i]){ // t > s
			ans = -1;
		}
		i ++;
	}	
	if (ans == 0){
		if (t[i] != '\0'){ // t es mas largo => t > s
			ans = -1;
		}else if(s[i] != '\0'){ // s es mas largo => s > t
			ans = 1;
		}
	}
	return ans;
}