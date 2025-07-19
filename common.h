#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>

/*
	-- Lowercase string contents --
	NOTE: Definetly unsafe if `string` it's on a readonly section
*/
static inline void string_lowercase(char *string)
{
	char c = 0;

	while ( (c = *string) != 0 ) {
		*string = tolower(c);
		string += 1;
	}
}

/*
	-- Get file size in bytes --
*/
static bool get_file_size(FILE *file_handle, size_t *output, bool close_file)
{
  if (file_handle == NULL) {
    *output = 0;
		return false;
  }

	fseek(file_handle, 0, SEEK_END);
	*output = ftell(file_handle);
	fseek(file_handle, 0, SEEK_SET);
	
	if (close_file) {
		fclose(file_handle);
	}

	return true;
}

static char *args_shift(int *argc, char ***argv)
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