#include "sizeof.h"

void usage(void);

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
		size_t fsize = sizeIn(argv[1]);
		if (argc < 1)
    {
			sizeOut(fsize, ALL);
			exit(0);
		}
		
		Unit unit = string2Unit(argv[2]);
		sizeOut(fsize, unit);
		exit(0);
	}

	exit(0);
}

void usage(void)
{
	printf("Usage:\n");
	printf("\t./sizeof <FILE-PATH> <UNIT>\n");
	printf("Units:\n");
	printf("\tBITS\n\tBYTES     | B\n");
	printf("\tKILOBYTES | KB\n");
	printf("\tMEGABYTES | MB\n");
	printf("\tGIGABYTES | GB\n");
	printf("\tALL (DEFAULT)\n");
	printf("\t(Units can be upper-case or lower-case)\n");
}
