#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY

#include<stdlib.h>
typedef struct Dynamic_Array_Base{
    void * arr;
    int allocated;
    int elements;
    size_t type;
}Arr;

int  arr_init     (Arr*, size_t);
int  arr_resize   (Arr*);
int  arr_push     (Arr*, void*);

#endif