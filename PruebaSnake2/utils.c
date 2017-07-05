#include "utils.h"


int str_to_int(char *str,int *target){
    int j = 0;
    int good = 1;
    while (str[j] != '\0'){
        if (str[j] < '0' || str[j] > '9'){
            good = 0;
        }
        j++;
    }
    
    if (good){
        int i = 0;
        int ans = 0;
        while (str[i] != '\0'){
            ans *= 10;
            ans += str[i] - '0';
            i++;
        }
        *target = ans;
        return 0;
    }else{
        return 1;
    }
}

void *int_to_str(int value,char *ans){
    int i = 0;
    while (value > 0){
        ans[i++] = value%10;
        value /= 10;
    }
    ans[i] = '\0';
}