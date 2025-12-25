#ifndef FILES
#define FILES

#include <unistd.h>

ssize_t read_segment_from_file(int fd_src, char* buffer, long buffer_size);
void print_file(int fd_src, int lseek_offset);
ssize_t cat( int files_count, char** files);
ssize_t head( char* file, char* arg_str);
ssize_t tail(char* file, char* arg_str);
ssize_t copy_from_file_to_file(char* src, char* dest);
ssize_t move_file(char* src, char* dest);


#endif