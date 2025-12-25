#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>

#include "../include/config.h"
#include "../include/files.h"





ssize_t read_segment_from_file(int fd_src, char* buffer, long buffer_size){
    
    if(fd_src < 0){
        fprintf(stderr, "File descriptor must be greater than 0\n");
        return -1;
    }

    ssize_t received;
    if((received = read(fd_src, buffer, buffer_size)) < 0){
        fprintf(stderr, "Error reading file\n");
    }

    return received;
}

void print_file(int fd_src, int lseek_offset){
    lseek(fd_src, lseek_offset, SEEK_SET);

    char buffer[BUFFER_SIZE + 1];

    ssize_t received,sent;

    while ((received = read_segment_from_file(fd_src, buffer, BUFFER_SIZE) ) > 0){
        sent = write(STDOUT_FILENO, buffer, received);
        if(sent!= received){
            fprintf(stderr, "Error writing file\n");
            return;
        }
    }

}

ssize_t cat( int files_count, char** files){
        
    ssize_t printed_files_count = 0;

    int fd_src;

    for(int i = 0; i < files_count; i++){

        if((fd_src = open(files[i], O_RDONLY)) < 0){
            fprintf(stderr, "cat: \"%s\": No such file or directory\n", files[i]);
        }else{
            print_file(fd_src, 0);
        }

    
        close(fd_src);
    }
    return printed_files_count;
}




ssize_t head( char* file, char* arg_str){
    char* tmp = NULL;
    int argument = strtol(arg_str, &tmp,10);


    if(*tmp != '\0'){
        printf("\"%s\": Invalid number of lines\n", arg_str);
        return EXIT_FAILURE;
    }
    if(argument == 0) return EXIT_SUCCESS;
    


    

    char buffer[BUFFER_SIZE+1];

    ssize_t received = 0,sent = 0;
    int chars_to_write = 0;

    int fd_file = open(file, O_RDONLY);
    if(fd_file < 0){
        printf("\"%s\": No such file or directory\n", file);
        return EXIT_FAILURE;
    }

    
    
    

 
    
    while((received = read_segment_from_file(fd_file, buffer, BUFFER_SIZE)) > 0){
        unsigned i = 0;
        for(i = 0; i < received; i++){
            if(buffer[i] == '\n'){
                if(--argument == 0 ){
                    break;
                }
            }
        }
        chars_to_write = i+1;
        sent = write(STDOUT_FILENO, buffer, chars_to_write);
        if(sent != chars_to_write){
            
                printf("Print error\n");
                close(fd_file);
                return EXIT_FAILURE;
            
        }

        if(argument == 0){
            break;
        }
    }
    
  
    if (fd_file >= 0) close(fd_file);
    return 0;
}

ssize_t tail(char* file, char* arg_str){
    bool special_case = false;

    if(arg_str[0] == '+'){
        
         special_case = true;

    }

    char* tmp = NULL;
    int argument = strtol(arg_str, &tmp,10);
    special_case ? argument-- : argument++;


    if(*tmp != '\0'){
        printf("\"%s\": Invadid number of lines\n", arg_str);
        return EXIT_FAILURE;
    }

    int fd_data = open(file, O_RDONLY);
    if(fd_data< 0){
        printf("Error cannot open file\n");
        return EXIT_FAILURE;
    }



    long size = lseek(fd_data, 0, SEEK_END);
    char buffer[BUFFER_SIZE + 1];
    int received, buffer_pos;
    long current = size;
    if(special_case){
        current = 0;
        lseek(fd_data, 0, SEEK_SET);
        while((received = read_segment_from_file(fd_data, buffer, BUFFER_SIZE)) > 0){
        
            for(buffer_pos = 0; buffer_pos < received; buffer_pos++){
                if(buffer[buffer_pos] == '\n'){
                    if(--argument == 0){
                        break;
                    }
                }
            }
            current += buffer_pos;
            if(argument == 0){
                current++;
                break;
            }
        }
        
        


    }else{

        while(current){
            current -= BUFFER_SIZE;
            int get = (current >= 0 ? BUFFER_SIZE : size % BUFFER_SIZE);
            if (current < 0){
                current = 0;
            }

            lseek(fd_data, current, SEEK_SET);
            if((received = read_segment_from_file(fd_data, buffer, get)) < 0 ){
                return EXIT_FAILURE;
            }

            for(buffer_pos = received - 1; buffer_pos>=0;buffer_pos--){
                if(buffer[buffer_pos] == '\n'){  
                    if(--argument == 0){
                        break;
                    }
                }
            }

            if(argument == 0){
                    break;
            }
        }

        current += buffer_pos + 1;
        
    }

    print_file(fd_data, current);

    close(fd_data);
    return EXIT_SUCCESS;
} 


ssize_t copy_from_file_to_file(char* src, char* dest){

     int fd_src,fd_dest;

    if((fd_src = open(src, O_RDONLY,0)) < 0){
        printf("cp: Cant open \"%s\": no such file or directory\n",src);
        return EXIT_FAILURE;
    }
    if((fd_dest = creat(dest, 0644)) < 0){
        printf("cp: Cant create \"%s\"\n",dest);
        close(fd_src);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    ssize_t received, wrote;

    while((received = read(fd_src, buffer, BUFFER_SIZE)) != 0){
         if(received == -1){
                fprintf(stderr, "cp: Error while reading file \"%s\"", src);
                close(fd_src);
                close(fd_dest);
                return EXIT_FAILURE;
        }
        wrote = write(fd_dest, buffer, received);
        if(wrote!=received){
            close(fd_src);
            close(fd_dest);
            fprintf(stderr, "cp: Error writing in file \"%s\"\n", dest);
            return EXIT_FAILURE;

        } 
    }

    close(fd_src);
    close(fd_dest);
    return EXIT_SUCCESS;
}


ssize_t move_file(char* src, char* dest){

    if(rename(src, dest) == 0){
        return EXIT_SUCCESS;
    }else{
        fprintf(stderr,"Cannot rename file \"%s\"\n", src);
        return EXIT_FAILURE;
    }
}




