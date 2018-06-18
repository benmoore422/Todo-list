#ifndef file_handler_h
#define file_handler_h

FILE* open_file(char* path);
int count_lines(FILE* fp);
int get_longest_line_len(FILE* fp);
void add_null_term_char(char* ptr);
void get_file_lines_arr(FILE* fp, char* items[]);
int write_line_to_file(FILE *fp, char* str); 
int remove_line_from_file(FILE* fp, int line_num); 

#endif
