#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void string_tolower(char *str);
char *args_shift(int *argc, char ***argv);
size_t file_size(FILE *file_handle);

void string_tolower(char *str)
{
	while (*str != 0) {
		*str = tolower(*str);
		str += 1;
	}
}

size_t file_size(FILE *file_handle)
{
  if (file_handle == NULL) {
    fprintf(stderr, "[file_size]: NULL file handle\n");
    fclose(file_handle);
    exit(1);
  }

	size_t size = 0;
	
	fseek(file_handle, 0, SEEK_END);
	size = ftell(file_handle);
	rewind(file_handle);
	
	fclose(file_handle);
	return size;
}

char *args_shift(int *argc, char ***argv)
{
	if (*argc > 0) {
		char *shift = **argv;
		
		*argc -= 1;
		*argv += 1;

		return shift;
	}

	return NULL;
}

#endif // !COMMON_H
