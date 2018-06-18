#include <form.h>
#include <string.h>
#include "todo_menu.h"
#include "file_handler.h"

void new_item_form(FILE* fp) {
		FIELD *field[2];
		FORM  *my_form;
		TERM* my_term = get_term_size(NULL);
		WINDOW *my_form_win;
		int ch, rows, cols;
		
		field[0] = new_field(1, my_term->x-3, 3, 1, 0, 0);
		field[1] = NULL;

		set_field_back(field[0], A_UNDERLINE);
		field_opts_off(field[0], O_AUTOSKIP); 
		
		my_form = new_form(field);
		
		scale_form(my_form, &rows, &cols);

		my_form_win	= newwin(my_term->y-4, my_term->x-2, 2, 1);
    	keypad(my_form_win, TRUE);

    	set_form_win(my_form, my_form_win);
    	set_form_sub(my_form, derwin(my_form_win, rows, cols, 2, 2));

    	box(my_form_win, 0, 0);
		
		post_form(my_form);
		wrefresh(my_form_win);

		refresh();

		mvwprintw(my_form_win, 1, 1, "%s", "Add a new item to the list:");
		mvwprintw(my_form_win, 5, 1, "%s", "Press esc to quit or hit return to save item");
		char *input;

		/* Loop through to get user requests */
		while((ch = wgetch(my_form_win)) != 27)
		{	switch(ch)
			{	case KEY_DOWN:
					form_driver(my_form, REQ_NEXT_FIELD);
					form_driver(my_form, REQ_END_LINE);
					break;
				case KEY_UP:
					form_driver(my_form, REQ_PREV_FIELD);
					form_driver(my_form, REQ_END_LINE);
					break;
				case KEY_BACKSPACE:
				case 127:
					form_driver(my_form, REQ_DEL_PREV);
					break;
				case 10:
					form_driver(my_form, REQ_NEXT_FIELD);
					input = field_buffer(field[0], 0);
					write_line_to_file(fp, input);
				    unpost_form(my_form);
		    		free_form(my_form);
				    free_field(field[0]);
					return;
					break;
				default:
					form_driver(my_form, ch);
					break;
			}
		}

		unpost_form(my_form);
		free_form(my_form);
		free_field(field[0]);
}
