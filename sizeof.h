#ifndef SIZEOF_H
#define SIZEOF_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    BIT = 0,
    BYTE = 1,
    KILOBYTE = 2,
    MEGABYTE = 3,
    GIGABYTE = 4,
    ALL = 5,
} Unit;

typedef char* string;

void usage(void);

Unit string2Unit(const string unitStr);
void string2Lower(string str);
size_t sizeIn(const string filePath);
void sizeOut(size_t size, Unit unit);

#endif // !SIZEOF_H