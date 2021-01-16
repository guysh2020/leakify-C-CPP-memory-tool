
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME "allocations.txt"

FILE* openFile();

void* my_malloc(size_t size, const char *file, int line, const char *func);


void *my_calloc(size_t count, size_t size, const char *file, int line, const char *func);


void my_free(void *ptr, const char *file, int line, const char *func);

#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X,Y) my_calloc( X,Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)

