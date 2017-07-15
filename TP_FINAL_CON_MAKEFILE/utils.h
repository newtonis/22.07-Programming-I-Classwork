// Utils.h: here there are some very general utilities


#ifndef UTILS_H
#define UTILS_H


#define min(a,b) ((a<b)?(a):(b))
#define max(a,b) ((a>b)?(a):(b))

int str_to_int(char *str,int *target);
void int_to_str(int value,char *ans,int min_size);

int fix_value(int a,int b,int c);
void init_empty_array(int *arr,int sz);
void copy_str(char *a,char *b); // copy string from a to b

#endif /* UTILS_H */

