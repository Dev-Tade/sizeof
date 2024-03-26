#include "common.h"
#include <stdbool.h>

void usage(void);
void lines(char *fpath);

int main(int argc, char *argv[])
{
	(void) args_shift(&argc, &argv); // consume program name
	
	if (argc >= 1) {
    char *file_path = args_shift(&argc , &argv);
    FILE *file_handle = fopen(file_path, "r");

    unsigned long int line_count = 1;
    bool done = false;

    while (!done) {
      switch (fgetc(file_handle)) {
        case '\n':
          line_count += 1;
          break;

        case EOF:
          done = true;
          break;

        default:
          continue;
          break;
      }
    }

    fclose(file_handle);

    printf("%s -> %u lines\n", file_path, line_count);
    exit(0);
	}

  // no file provided
	usage();
	exit(1);
}

void usage(void)
{
	printf("Usage:\n");
	printf("\tlines <file path>\n");
}