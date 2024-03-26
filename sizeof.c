#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common.h"

typedef enum
{
  BIT = 0,
  BYTE = 1,
  KILOBYTE = 2,
  MEGABYTE = 3,
  GIGABYTE = 4,
  ALL = 5,
} Unit;

#define streq(s1, s2) (strcmp(s1, s2) == 0)

void usage(void);
Unit string_tounit(char *unit_string);
void print_size_fmt(size_t size, Unit unit);

int main(int argc, char *argv[])
{
	(void) args_shift(&argc, &argv); // consume program name

	if (argc >= 1) {
		char *file_path = args_shift(&argc, &argv);
		FILE *file_handle = fopen(file_path, "r");

		if (file_handle == NULL) {
			fprintf(stderr, "Error! unable to open file: %s\n", file_path);
			fclose(file_handle);
			exit(1);
		}

		size_t size_bytes = file_size(file_handle);

		if (argc >= 1) { // unit format is provided
			char *unit_fmt = args_shift(&argc, &argv);
			Unit unit = string_tounit(unit_fmt);

			print_size_fmt(size_bytes, unit);
			exit(0);
		}

		// no unit format provided, use all by default
		print_size_fmt(size_bytes, ALL);
		exit(0);
	} 
  
	// no file path is provided
	usage();
	exit(1);
}

void usage(void)
{
	printf("Usage:\n");
	printf("\tsizeof <file path> <unit>\n");
	printf("Units:\n");
	printf("\t[bits]\n");
	printf("\t[bytes]     | [b]\n");
	printf("\t[kilobytes] | [kb]\n");
	printf("\t[megabytes] | [mb]\n");
	printf("\t[gigabytes] | [gb]\n");
	printf("\t[all] -> default\n");
	printf("\t# unit specifier can be upper or lower case\n");
}

void print_size_fmt(size_t size, Unit unit)
{
	switch (unit)
  {
		case BIT:
			printf("~%u bits\n", size * 8);
			break;
		
		case BYTE:
			printf("~%u bytes\n", size);
			break;
		
		case KILOBYTE:
			printf("~%.3lf kilobytes\n", (double) size / 1000);
			break;
		
		case MEGABYTE:
			printf("~%.6lf megabytes\n", (double) size / 1E6);
			break;
		
		case GIGABYTE:
			printf("~%.9lf gigabytes\n", (double) size / 1E9);
			break;
	
		case ALL:
    default:
    	print_size_fmt(size, BIT);
      print_size_fmt(size, BYTE);
			print_size_fmt(size, KILOBYTE);
			print_size_fmt(size, MEGABYTE);
			print_size_fmt(size, GIGABYTE);
			break;
	}
}

Unit string_tounit(char *unit_str)
{
	string_tolower(unit_str);

	if (streq(unit_str, "bits"))
		return BIT;

	if (streq(unit_str, "bytes") || streq(unit_str, "b"))
		return BYTE;
	
	if (streq(unit_str, "kilobytes") || streq(unit_str, "kb"))
		return KILOBYTE;
	
	if (streq(unit_str, "megabytes") || streq(unit_str, "mb"))
		return MEGABYTE;
	
	if (streq(unit_str, "gigabytes") || streq(unit_str, "gb"))
		return GIGABYTE;
	
	// no matching string
	return ALL;
}