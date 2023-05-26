#include "sizeof.h"

void usage(void);
void lines(string fpath);

int main(int argc, string argv[])
{
	argc--;
	
	if (argc < 1)
  {
		usage();
		exit(1);
	}
  else
  {
		argc--;
		lines(argv[1]);
	}

	exit(0);
}

void usage(void)
{
	printf("Usage:\n");
	printf("\t./lines <FILE>\n");
  return;
}

void lines(string fpath)
{
  size_t nlines = 0;
  size_t bytes = sizeIn(fpath);
  char *buff = (char*)malloc(bytes);
  FILE *file = fopen(fpath, "rb");

  if (fread(buff, sizeof(char), bytes, file) != bytes)
  {
    fprintf(stderr, "Error reading file (R<C)\n");
    free(buff);
    fclose(file);
    exit(1);
  }

  for (int i=0; i<bytes; ++i)
    if (buff[i] == 0xA) ++nlines;

  printf("%s -> %d lines\n", fpath, nlines);

  free(buff);
  return;
}
