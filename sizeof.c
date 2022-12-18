#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  printsize(int size, int unit);
void  getfsize(char *filename, int unit);
int   getunit(char *unitstr);

#define UNIT_KILOBYTE 0
#define UNIT_BYTE     1
#define UNIT_MEGABYTE 2
#define UNIT_GIGABYTE 3
#define UNIT_ALL	  4

int main(int argc, char* argv[]) {

	if (!(argc >= 2)) {
		fprintf(stderr, "Missing argument: <file>\n");
		exit(1);
	} else {
		if (!(argc >= 3)) {
			getfsize(argv[1], UNIT_BYTE);
		} else {
			int unit = getunit(argv[2]);
			if (unit == 69) {
				fprintf(stderr, "Unit %s is not recognized.\n",argv[2]);
				exit(1);
			} else {
				getfsize(argv[1], unit);
			}
		}
	}

	return 0;
}

void getfsize(char *filename, int unit) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot open file: %s\n", filename);
		exit(1);
	}

	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	
	printf("'%s' is ", filename);
	printsize(size, unit);
}

void printsize(int size, int unit) {
	switch (unit) {
		case UNIT_BYTE:
			printf("~%d byte(s)\n", size);
			break;
		case UNIT_KILOBYTE:
			printf("~%.6lf kilobyte(s)\n", (double)size/1000);
			break;
		case UNIT_MEGABYTE:
			printf("~%.6lf megabyte(s)\n", (double)size*0.000001);
			break;
		case UNIT_GIGABYTE:
			printf("~%.6lf gigabyte(s)\n", (double)size/1000000000);
			break;
		case UNIT_ALL:
			printf("\n\t~%d byte(s)\n", size);
			printf("\t~%.6lf kilobyte(s)\n", (double)size/1000);
			printf("\t~%.6lf megabyte(s)\n", (double)size/1E+6);
			printf("\t~%.6lf gigabyte(s)\n", (double)size/1E+9);
			break;
		default:
			break;
	}
}

int getunit(char *unitstr) {
	char* conv = unitstr;

	if (!strcmp(conv, "kb"))
		return UNIT_KILOBYTE;
	else if (!strcmp(conv, "b"))
		return UNIT_BYTE;
	else if (!strcmp(conv, "mb"))
		return UNIT_MEGABYTE;
	else if (!strcmp(conv, "gb"))
		return UNIT_GIGABYTE;
	else if (!strcmp(conv, "all"))
		return UNIT_ALL;
	else {
		return 69;
	}
}
