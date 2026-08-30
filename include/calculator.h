#ifndef CALCULATOR
#define CALCULATOR

int    calculator                       (char**,int);
double calculate_expression             (double*, int*, char*, int*);
double get_complete_integer             (char* src,int* j);
double perform_operation                (double, double, char);
int    process_high_priority_operations (double*, int*, char*, int*);
int    process_low_priority_operations  (double*, int*, char*, int*);

#endif
