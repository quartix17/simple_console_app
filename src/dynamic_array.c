#include<stdio.h>
#include<stdlib.h>
#include<string.h> 

#include "../include/dynamic_array.h"
#include "../include/memory_register.h"
#include "../include/config.h"


int arr_init(Arr * arr, size_t arr_type_size){
    arr->type = arr_type_size;
    arr->allocated = ARRAY_DEFAULT_ALLOCATION;
    arr->arr = malloc(arr->allocated * arr->type + (arr->type == sizeof(char) ? 1:0));
    
    if(arr->arr == NULL){
        fprintf(stderr, "Arr memory allocation failed");
        return EXIT_FAILURE;
    }

    arr->elements = 0;
    memory_pointer_push(&arr->arr);
    if(arr->arr == NULL){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int arr_resize(Arr * arr){
    int New_Alloc = arr->allocated * 2;
    void * New_Arr = realloc(arr->arr,New_Alloc * arr->type + (arr->type == sizeof(char) ? 1:0)); // (arr->type == sizeof ? : ) is for adding a bite for \0 if its a string
    if(New_Arr == NULL){
        fprintf(stderr, "Array reallocation failed\n");
        return EXIT_FAILURE;
    }

    memory_pointer_remove(arr->arr);  
    arr->arr = New_Arr;
    arr->allocated = New_Alloc;
    memory_pointer_push(&arr->arr);
    if(arr->arr == NULL){
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}

int arr_push(Arr * arr, void * val){
    if(arr->elements == arr->allocated){
        if(arr_resize(arr) == EXIT_FAILURE){
            return EXIT_FAILURE;
        }
    }

    memcpy( ((char*)arr->arr) + arr->elements * arr->type,val, arr->type);
    arr->elements++;
    return EXIT_SUCCESS;
}