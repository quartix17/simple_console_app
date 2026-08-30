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

//TODO:: add pipes support, add ls cd pwd touch mkdir rm functions, make a little refactoring

int main(void){

    memory_registration();  //initilized a memory registr

    while(1){
        Arr arr;             //initilized a dynamic array for input string
        if(arr_init(&arr,sizeof(char)) == 1){
            return EXIT_FAILURE;
        }


        int c;
        printf("%s", CONSOLE_COMMAND_HEADER);
        while((c=getchar())!= EOF && c!='\n'){  //writing whole input in dynamic array
            arr_push(&arr,(void*)&c);
        }
        if(feof(stdin)){
            return EXIT_SUCCESS;
        }

        if (arr.elements == arr.allocated) {
            arr_resize(&arr);                //resizing array is needed
        }

        ((char*)arr.arr)[arr.elements] = '\0'; //put '\0' the last character
        if(input_parser(&arr) == 3) break;
    }

    return EXIT_SUCCESS;
}
