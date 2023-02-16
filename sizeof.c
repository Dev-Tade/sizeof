#include "sizeof.h"

int main(int argc, string argv[]) {
	argc--;
	
	if (argc < 1) {
		usage();
		exit(1);
	} else {
		argc--;
		size_t fsize = sizeIn(argv[1]);
		if (argc < 1) {
			sizeOut(fsize, ALL);
			exit(0);
		}
		
		Unit unit = string2Unit(argv[2]);
		sizeOut(fsize, unit);
		exit(0);
	}

	exit(0);
}

void usage(void) {
	printf("Usage:\n");
	printf("\t./sizeof <FILE-PATH> <UNIT>\n");
	printf("Units:\n");
	printf("\tBIT\n\tBYTES     | B\n");
	printf("\tKILOBYTES | KB\n");
	printf("\tMEGABYTES | MB\n");
	printf("\tGIGABYTES | GB\n");
	printf("\tALL (DEFAULT)\n");
	printf("\t(Units can be upper-case or lower-case)\n");
}

Unit string2Unit(const string unitStr) {
	string2Lower(unitStr);

	if (!strcmp(unitStr, "bits"))
		return BIT;
	if (!strcmp(unitStr, "bytes") 	   || !strcmp(unitStr, "b"))
		return BYTE;
	if (!strcmp(unitStr, "kilobytes")  || !strcmp(unitStr, "kb"))
		return KILOBYTE;
	if (!strcmp(unitStr, "megabytes")  || !strcmp(unitStr, "mb"))
		return MEGABYTE;
	if (!strcmp(unitStr, "gigabyte")   || !strcmp(unitStr, "gb"))
		return GIGABYTE;
	
	if (!strcmp(unitStr, "all"))
		return ALL;
	else
		return ALL;
}

void string2Lower(string str) {
	for (size_t i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

size_t sizeIn(const string filePath) {
	FILE* fptr = fopen(filePath, "r");
	size_t size;
	
	fseek(fptr, 0, SEEK_END);
	size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	
	fclose(fptr);
	
	return size;
}

void sizeOut(size_t size, Unit unit) {
	switch (unit) {
		case BIT:
			printf("~%zu bits\n", size*8);
			break;
		
		case BYTE:
			printf("~%zu bytes\n", size);
			break;
		
		case KILOBYTE:
			printf("~%.4lf kilobytes\n", (double)size/1000);
			break;
		
		case MEGABYTE:
			printf("~%.8lf megabytes\n", (double)size/1E6);
			break;
		
		case GIGABYTE:
			printf("~%.12lf gigabytes\n", (double)size/1E9);
			break;
	
		case ALL:
			sizeOut(size, BIT);
			sizeOut(size, BYTE);
			sizeOut(size, KILOBYTE);
			sizeOut(size, MEGABYTE);
			sizeOut(size, GIGABYTE);
			break;
			
		default:
			sizeOut(size, BIT);
			sizeOut(size, BYTE);
			sizeOut(size, KILOBYTE);
			sizeOut(size, MEGABYTE);
			sizeOut(size, GIGABYTE);
			break;
	}
}