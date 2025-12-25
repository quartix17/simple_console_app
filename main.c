#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

#include "include/memory_register.h"
#include "include/input_parser.h"
#include "include/calculator.h"
#include "include/dynamic_array.h"
#include "include/files.h"
#include "include/config.h"


int main(void){

    memory_registration();

    while(1){
        Arr arr;
        if(arr_init(&arr,sizeof(char)) == EXIT_FAILURE){
            return EXIT_FAILURE;
        }


        int c;
        printf("%s", CONSOLE_COMMAND_HEADER);
        while((c=getchar())!= EOF && c!='\n'){
            arr_push(&arr,(void*)&c);
        }
        if(feof(stdin)){
            return EXIT_SUCCESS;
        }

        if (arr.elements == arr.allocated) {
            arr_resize(&arr);
        }

        ((char*)arr.arr)[arr.elements] = '\0';
        if(input_parser(&arr) == 3) break;
    }
    
    return EXIT_SUCCESS;
}
