#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 1024
char* filename;

FILE* open_file(char* path) {
		FILE* fp;

		if (path == NULL) {
				path = ".todo";
				filename = path;
		}

		fp = fopen(path, "r+");

		if (!fp) {
				fp = fopen(path, "w+");
		}
		return fp;
}

int count_lines(FILE* fp) {
		if (fp == NULL) {
				return 0;
		}

		rewind(fp);

		char* buffer = NULL;
		size_t buffsiz = 0;
		ssize_t nbytes;
		int lines = 0;

		while ((nbytes = getline(&buffer, &buffsiz, fp)) != -1) {
			lines++;	 
		}

		return ++lines;
}

int get_longest_line_len(FILE* fp) {
		if (fp == NULL) {
				perror("Null file pointer\n");
				return 0;
		}

		rewind(fp);

		char line[MAX_LINE];

		int longest = 0;

		while (fgets(line, sizeof(line), fp)) {
				if (strlen(line) > longest) {
						longest = strlen(line);
				}
		}

		return longest;
}

void add_null_term_char(char* str) {
		char* ptr;
		if ((ptr = strchr(str, '\n')) != NULL) {
				*ptr = '\0';
		}
}

void get_file_lines_arr(FILE* fp, char* items[]) {
		if (fp == NULL) {
				perror("Null file pointer\n");
				return;
		}

		int i = 0;
		char line[MAX_LINE];

		rewind(fp);

		while(fgets(line, sizeof(line), fp)) {
				items[i] = malloc(strlen(line) * sizeof(char));
				add_null_term_char(line);
				strcpy(items[i], line);
				i++;
		}

		items[i] = (char *) NULL;
}

int write_line_to_file(FILE *fp, char* str) {
		if (fp == NULL) {
				return 1;
		}

		fseek(fp, 0, SEEK_END);
		fprintf(fp, "%s\n", str);
		rewind(fp);

		return 0;
}

int remove_line_from_file(FILE* fp, int line_no) {
		// fp is the original and tmp_fp is the new one
		line_no = line_no + 1;
		char temp_name[] = ".tmp_todo";
		FILE* tmp_fp = fopen(temp_name, "w");
		int ctr = 0;
		int max = get_longest_line_len(fp) + 1;
		char buf[max];

		if (fp == NULL) {
				perror("Passed file pointer is null\n");
				return 1;
		}

		if (tmp_fp == NULL) {
				perror("Failed to open temporary file\n");
				return 1;
		}
		rewind(fp);

		while(!feof(fp)) {
				strcpy(buf, "\0");
				fgets(buf, max, fp);
				if(!feof(fp)) {
						ctr++;
						if (ctr != line_no) {
								fprintf(tmp_fp, "%s", buf);
						}
				}
		}

		fclose(fp);
		fclose(tmp_fp);
		remove(filename);
		rename(temp_name, filename);
		fp = open_file(filename);

		return 0;
}
