#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <ctype.h>


#include "../include/calculator.h"
#include "../include/config.h"


double perform_operation(double a, double b, char act){
    switch (act){
        case '+': return a+b;
        case '-': return a-b;           
        case '*': return a*b;           
        case '/':
            if (b == 0) {
            fprintf(stderr,"Error: Division by zero\n");
            exit(EXIT_FAILURE);
        }
            return a/b;
    }
    return 0;
}

void process_high_priority_operations(double* Nums,int* Num_Size,char* Act, int* Act_Size){
    for(int i = 0; i < *Act_Size; i++){
        if(Act[i] == '/' || Act[i] == '*'){
            double New_Val = perform_operation(Nums[i],Nums[i+1],Act[i]);
            Nums[i] = New_Val;
            memmove(&Nums[i+1],&Nums[i+2],(*Num_Size - (i + 2)) * sizeof(Nums[i]));
            (*Num_Size)--;
            memmove(&Act[i],&Act[i+1],(*Act_Size - (i + 1)) * sizeof(Act[i]));
            (*Act_Size)--;
            process_high_priority_operations(Nums,Num_Size,Act,Act_Size);
            return;
        }       
    }
}

void process_low_priority_operations(double* Nums,int* Num_Size,char* Act, int* Act_Size){
    for(int i = 0; i < *Act_Size; i++){
        if(Act[i] == '+' || Act[i] == '-'){
            double New_val = perform_operation(Nums[i],Nums[i+1],Act[i]);
            Nums[i] = New_val;
            memmove(&Nums[i+1],&Nums[i+2],(*Num_Size - (i + 2)) * sizeof(Nums[i]));   
            (*Num_Size)--;
            memmove(&Act[i],&Act[i+1],(*Act_Size - (i + 1)) * sizeof(Act[i]));
            (*Act_Size)--;
            process_low_priority_operations(Nums,Num_Size,Act,Act_Size);
            return;
        }  
    }
}

double calculate_expression(double* Nums,int* NumSize,char* Act, int* ActSize){
    
    process_high_priority_operations(Nums,NumSize,Act,ActSize); // counting * and / operations
    process_low_priority_operations(Nums,NumSize,Act,ActSize); // + and - aperations
    
    return Nums[0];
}



void calculator(char** src,int size){
    int source_overflow_detector = 0;
    for(int i = 1;i < size; i++){
        source_overflow_detector += (int)strlen(src[i]); // buffer overflow detection,if count of symbols in argument is more than ARRAY_MAX_SIZE - exit function
    }
    if(source_overflow_detector >= ARRAY_MAX_SIZE){
        fprintf(stderr, "Too many arguments in function \"calculator\"\n");
        return;
    }
    char source[ARRAY_MAX_SIZE];
    int sourse_length = 0;
    for(int i = 1; i < size;i++){
        for(int j = 0; j<(int)strlen(src[i]);j++){
            
                source[sourse_length++] = src[i][j]; // make a char* from char** 

            
        }
    }
    source[sourse_length] = '\0';
    
    double nums [ARRAY_MAX_SIZE];
    int nums_s = 0;

    char act[ARRAY_MAX_SIZE];
    int act_s = 0;
    
    char* tmp = (char*)source;
    while(*tmp!= '\0'){
        while(isspace(*tmp)) tmp++;
        if(*tmp == '\0') break;

        char* endptr;

        double x = strtod(tmp, &endptr);
        if(tmp == endptr){
            fprintf(stderr, "Not a number\n");
            return;
        }

        nums[nums_s++] = x;
        tmp = endptr;

        while(isspace(*tmp)) tmp++;
        if(*tmp == '\0') break;

        if(*tmp == '-' || *tmp == '+' || *tmp == '/' || *tmp == '*'){
            
            act[act_s++] = *tmp;
            tmp++; 
        }
        else {
            fprintf(stderr, "Error: unexpected character '%c'\n", *tmp);
            return;
        }
        
    }
    printf("%g\n",calculate_expression(nums,&nums_s,act,&act_s));

}
