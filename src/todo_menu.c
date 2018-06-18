#include <menu.h>
#include <curses.h>
#include <stdlib.h>
#include <string.h>
#include "todo_menu.h"
#include "todo_form.h"
#include "file_handler.h"

#define KEY_RETURN 10

void initialise_ncurses() {
		initscr();
		cbreak();
		noecho();
		keypad(stdscr, TRUE);
}

// get the size of an array of pointers
int sizeof_ptr_arr(char*  arr[]) {
		int count;
		for(count = 1;arr[++count]!= NULL;);
		return ++count;
}

TERM* get_term_size(WINDOW* win) {
		if (win == NULL) {
				win = stdscr;
		}
		int x,y;
		TERM* t = malloc(sizeof(TERM));
		getmaxyx(win, y, x);
		t->x = x;
		t->y = y;
		return t;
}

// display the todo list
void display_menu(FILE* fp) {
start:
		clear();
		char *choices[count_lines(fp)];
		get_file_lines_arr(fp, choices);
		int c, i, n_choices;
		char title[] = "Todo List";
		char info[] = "(n)New item (d)Delete (q)Quit";
		MENU* my_menu;
		ITEM **my_items;
		TERM* my_term;
		WINDOW *my_menu_win;

		init_pair(1, COLOR_RED, COLOR_BLACK);

		// create menu items
		n_choices = sizeof_ptr_arr(choices);
		my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM*));

		for(i = 0;i < n_choices; ++i) {
				my_items[i] = new_item(choices[i], NULL);
		}

		my_items[n_choices] = (ITEM *) NULL;

		my_menu = new_menu((ITEM **)my_items);

		// get size of window
		my_term = get_term_size(NULL);

		// print title
		mvprintw(0, (my_term->x-strlen(title))/2, "%s", title);

		// create menu window
		my_menu_win = newwin(my_term->y-2, my_term->x, 1, 0);
		keypad(my_menu_win, TRUE);


		set_menu_win(my_menu, my_menu_win);

		set_menu_sub(my_menu, derwin(my_menu_win, sizeof_ptr_arr(choices), my_term->x-2, 1, 1));

		set_menu_mark(my_menu, " * ");

		box(my_menu_win, 0, 0);

		mvprintw(my_term->y-1, 0, "%s", info);
		refresh();

		post_menu(my_menu);
		wrefresh(my_menu_win);
		int menu_cnt = 0;

		while((c = wgetch(my_menu_win)) != 113) {
			switch(c) {
				case 106:
				case KEY_DOWN :
 		   	        menu_driver(my_menu, REQ_DOWN_ITEM);
					if (menu_cnt < (n_choices-1))
						menu_cnt++;
 		   			break;
				case 107:
 		   		case KEY_UP:
 		   			menu_driver(my_menu, REQ_UP_ITEM);
					if (menu_cnt > 0)
						menu_cnt--;
 		   			break;
				case 110:
					new_item_form(fp);
					goto start;
					break;
				case 100:
					remove_line_from_file(fp, menu_cnt);
					goto start;
					break;
			}		
		}
		wrefresh(my_menu_win);

		unpost_menu(my_menu);
 		free_menu(my_menu);
		for(i = 0; i < n_choices; ++i) {	
			free_item(my_items[i]);
		}
}
