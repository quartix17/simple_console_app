#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#include "../include/memory_register.h"
#include "../include/config.h"

MEM_REG * memory_registration(void){   //define pointer in first call,and returns same pointer every time
    static MEM_REG * result = NULL;
    if(result == NULL){
        result =  (MEM_REG*)calloc(1,sizeof(MEM_REG));
        if(result == NULL){
            fprintf(stderr, "Memory register allocation failed\n");
            return NULL;
        }
        result->length = 0;
        result->data = (void**)malloc(sizeof(void*));
        if(result->data == NULL){
            fprintf(stderr, "Memory register array allocation failed\n");
            free(result);
            return NULL;
        }
        atexit(memory_clear);
    }
    return result;
}

void memory_pointer_push(void ** val){ //push memory pointer in register
    MEM_REG * mem = memory_registration();
    void ** tmp = (void**)realloc(mem->data,sizeof(void*) * ( mem->length + 1));
    if(tmp==NULL){
        fprintf(stderr, "Memory registration push pointer failed\n");
        free(*val);
        *val = NULL;
        return;
    }
    mem->data = tmp;
    mem->data[mem->length++] = *val;

}

void memory_pointer_remove(void * pointer){ // remove pointer from register (if free() was used to pointer)
    MEM_REG * mem = memory_registration();

    for(int i =0; i<mem->length; i++){
        if(((void**)mem->data)[i] == pointer){
            memmove(&((void**)mem->data)[i],&((void**)mem->data)[i+1],(mem->length - (i+1)) * sizeof(void*));
            mem->length--;
            return;
        }
    }
    fprintf(stderr, "Memory pointer remove failed: No pointer found\n");

}

void memory_clear(void){  //clear all the allocated memory
    MEM_REG * mem = memory_registration();
    if(mem->data != NULL){
        if(mem->length != 0){
            for(int i = mem->length - 1; i >= 0; i--){
                free(((void**)mem->data)[i]);
                ((void**)mem->data)[i] = NULL;
            }
        }
        free(mem->data);
        mem->data = NULL;
    }
    free(mem);
}
