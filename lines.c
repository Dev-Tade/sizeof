#include "common.h"

void usage(void);
size_t count_lines(FILE *file_handle, bool close_file);

int main(int argc, char *argv[])
{
	(void) args_shift(&argc, &argv); // consume program name
	
  // No argument provided
  if (argc < 1) {
    usage();
    return 1;
  }

  size_t total_lines = 0;
  
	while (argc >= 1) {
    char *file_path = args_shift(&argc , &argv);
    FILE *file_handle = fopen(file_path, "r");

    if (file_handle == NULL) {
      fprintf(stderr, "[ERROR]: Couldn't open file: %s\n", file_path);
      continue;
    }

    size_t count = count_lines(file_handle, true);
    printf("[%s]: %zu lines\n", file_path, count);
    
    total_lines += count;
	}

  printf("[TOTAL]: %zu lines\n", total_lines);
  return 0;
}

void usage(void)
{
	printf("Usage:\n");
	printf("\tlines filepath...\n");
}

size_t count_lines(FILE *file_handle, bool close_file)
{
  if (file_handle == NULL) {
    return 0;
  }

  size_t count = 1;
  bool done = false;

  while (!done) {
    switch (fgetc(file_handle)) {
      case '\n':
        count += 1;
        break;

      case EOF:
        done = true;
        break;

      default:
        continue;
        break;
    }
  }

  if (close_file) {
    fclose(file_handle);
  }

  return count;
}