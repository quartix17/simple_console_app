#ifndef CALCULATOR
#define CALCULATOR

void   calculator                       (char**,int);
double calculate_expression             (double*, int*, char*, int*);
double get_complete_integer             (char* src,int* j);
double perform_operation                (double, double, char);
void   process_high_priority_operations (double*, int*, char*, int*);
void   process_low_priority_operations  (double*, int*, char*, int*);

#endif