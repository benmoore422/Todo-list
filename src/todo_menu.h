#ifndef menu_h
#include <menu.h>
#include <curses.h>

#define CTRLD 4

typedef struct Terminal {
		int x;
		int y;
} TERM;

void initialise_ncurses(); 
int sizeof_ptr_arr(char*  arr[]); 
TERM* get_term_size(WINDOW* win); 
void display_menu(FILE* fp); 
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);



#endif
