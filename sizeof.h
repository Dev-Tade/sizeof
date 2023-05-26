#ifndef SIZEOF_H
#define SIZEOF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum
{
    BIT = 0,
    BYTE = 1,
    KILOBYTE = 2,
    MEGABYTE = 3,
    GIGABYTE = 4,
    ALL = 5,
} Unit;

typedef char* string;

Unit string2Unit(const string unitStr);
void string2Lower(string str);
size_t sizeIn(const string filePath);
void sizeOut(size_t size, Unit unit);

Unit string2Unit(const string unitStr)
{
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

void string2Lower(string str)
{
	for (size_t i = 0; i < strlen(str); i++)
		str[i] = tolower(str[i]);
}

size_t sizeIn(const string filePath)
{
	FILE* fptr = fopen(filePath, "r");
  if (fptr == NULL)
  {
    fprintf(stderr, "Unable to open file: %s\n", filePath);
    fclose(fptr);
    exit(1);
  }

	size_t size;
	
	fseek(fptr, 0, SEEK_END);
	size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	
	fclose(fptr);
	
	return size;
}

void sizeOut(size_t size, Unit unit)
{
	switch (unit)
  {
		case BIT:
			printf("~%u bits\n", size*8);
			break;
		
		case BYTE:
			printf("~%u bytes\n", size);
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
	
    default:
		case ALL:
    	sizeOut(size, BIT);
      sizeOut(size, BYTE);
			sizeOut(size, KILOBYTE);
			sizeOut(size, MEGABYTE);
			sizeOut(size, GIGABYTE);
			break;
			
	}
}

#endif // !SIZEOF_H
