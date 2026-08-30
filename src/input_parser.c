#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#include "../include/dynamic_array.h"
#include "../include/input_parser.h"
#include "../include/calculator.h"
#include "../include/config.h"
#include "../include/files.h"

int input_parser(Arr* arr){
    char* command = (char*)arr->arr;

    Arr command_parts;
    arr_init(&command_parts,sizeof (char*) );

    int i = 0;

    while(command[i] != '\0'){
        while(isspace(command[i])){
            i++;
        }
        if (command[i] == '\0') break;

        int j = 0;
        char Word[ARRAY_MAX_SIZE + 1];

        while(!isspace(command[i]) && command[i] != '\0'){
            if(j>=ARRAY_MAX_SIZE){
                fprintf(stderr, "Too long word\n"); // buffer overflow checker
                return -1;
            }
            Word[j++] = command[i++];
        }

        Word[j] = '\0';

        char * str = strdup(Word);
        if(str == NULL){
            fprintf(stderr, "Strdup = NULL\n");
            return -1;
        }
        arr_push(&command_parts,&str);
        memory_pointer_push((void**)&str);
        if(str == NULL){
            return -1;
        }
    }
    return input_reader((char**)command_parts.arr,command_parts.elements);

}

int  input_reader(char** str,int size){
    if(size == 0){
        return 1;
    }

    if(strcmp(str[0], "exit") == 0){
        return 3;
    }

     else if(strcmp(str[0],"help") == 0){
        cat(1,str);
    }

    else if(strcmp(str[0],"clear") == 0){
        printf("\033[H\033[J");
    }

    else if(strcmp(str[0], "calc" ) == 0){
        for(int i = 1; i<size - 1;i++){
            str[i][strlen(str[i])] = ' ';
        }
        calculator(str,size);
    }

    else if(strcmp(str[0], "print" ) == 0){
        for(int i = 1;i < size;i++){
            printf("%s ",str[i]);
        }
        printf("\n");
    }
    else if(strcmp(str[0], "mv") == 0){
        move_file(str[1], str[2]);
    }
    else if(strcmp(str[0], "cp") == 0){
        copy_from_file_to_file(str[1], str[2]);
    }
    else if(strcmp(str[0], "cat") == 0){
        cat(size - 1, str + 1 );
    }
    else if(strcmp(str[0], "head") == 0){
        head(str[1], str[2]);
    }
    else if(strcmp(str[0], "tail") == 0){
        tail(str[1], str[2]);
    }

    else{
        fprintf(stderr, "Unknown command\n");
    }
    return 0;
}
