#include "todo_menu.h"
#include "menu_options.h"
#include "file_handler.h"
#include <stdlib.h>


int main() {
		initialise_ncurses();
		FILE* fp =  open_file(NULL);
		display_menu(fp);
		endwin();
}
