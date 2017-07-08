
#ifndef UTILS_H
#define UTILS_H


#define min(a,b) ((a<b)?(a):(b))
#define max(a,b) ((a>b)?(a):(b))

int str_to_int(char *str,int *target);
void *int_to_str(int value,char *ans);
int fix_value(int a,int b,int c);

#endif /* UTILS_H */

