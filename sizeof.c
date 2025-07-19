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

void usage(void);
Unit string_unit(char *unit_string);
void print_size_fmt(char *filepath, size_t size_in_bytes, Unit unit);

int main(int argc, char *argv[])
{
	(void) args_shift(&argc, &argv); // consume program name

	// No argument provided
	if (argc < 1) {
		usage();
		return 1;
	}

	if (argc >= 1) {
		char *file_path = args_shift(&argc, &argv);
		FILE *file_handle = fopen(file_path, "r");

		if (file_handle == NULL) {
			fprintf(stderr, "[ERROR]: Couldn't open file: %s\n", file_path);
			return 1;
		}

		size_t size_in_bytes = 0;
		if (!get_file_size(file_handle, &size_in_bytes, true)) {
			// This code may be unreacheable
			// No file close because only fails if file handle is null  
			fprintf(stderr, "[ERROR]: Couldn't get size of file: %s\n", file_path);
			return 1;
		}

		// No unit format is provided, use ALL as default
		if (argc < 1) { 
			print_size_fmt(file_path, size_in_bytes, ALL);
			return 0;
		}

		// Unit format provided
		char *unit_fmt = args_shift(&argc, &argv);
		Unit unit = string_unit(unit_fmt);

		print_size_fmt(file_path, size_in_bytes, unit);
		return 0;
	}
}

void usage(void)
{
	printf("Usage:\n");
	printf("\tsizeof filepath unit\n");
	printf("Units:\n");
	printf("\t[bits]\n");
	printf("\t[bytes]     | [b]\n");
	printf("\t[kilobytes] | [kb]\n");
	printf("\t[megabytes] | [mb]\n");
	printf("\t[gigabytes] | [gb]\n");
	printf("\t[all] -> default\n");
}

void print_size_fmt(char *filepath, size_t size_in_bytes, Unit unit)
{
	switch (unit) {
		case BIT:
			printf("[%s]: ~%zu bits\n", filepath, size_in_bytes * 8);
			break;
		
		case BYTE:
			printf("[%s]: ~%zu bytes\n", filepath, size_in_bytes);
			break;
		
		case KILOBYTE:
			printf("[%s]: ~%.3lf kilobytes\n", filepath, (double)size_in_bytes / 1000.0);
			break;
			
		case MEGABYTE:
			printf("[%s]: ~%.6lf megabytes\n", filepath, (double)size_in_bytes / 1.0E6);
			break;
			
		case GIGABYTE:
			printf("[%s]: ~%.9lf gigabytes\n", filepath, (double)size_in_bytes / 1.0E9);
			break;
	
		case ALL:
    default:
    	print_size_fmt(filepath, size_in_bytes, BIT);
    	print_size_fmt(filepath, size_in_bytes, BYTE);
    	print_size_fmt(filepath, size_in_bytes, KILOBYTE);
    	print_size_fmt(filepath, size_in_bytes, MEGABYTE);
    	print_size_fmt(filepath, size_in_bytes, GIGABYTE);
			break;
	}
}

bool streq(char *src1, char *src2);

Unit string_unit(char *unit_str)
{
	string_lowercase(unit_str);

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

bool streq(char *src1, char *src2)
{
	while (*src1 && *src2) {
		if (*src1 != *src2) {
			return false;
		}

		src1++;
		src2++;
	}

	return *src1 == *src2;
}