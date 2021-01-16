//#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

FILE* fp;

void openFile()
{
    printf("%s","open file");
    fp = fopen("allocations.txt","w");
}

void* my_malloc(size_t size, const char *file, int line, const char *func)
{
    void *p = malloc(size);
    fprintf (fp,"0 Allocated = %s, %i, %s, #%p[%li]\n", file, line, func, p, size);
    return p;
}
void* my_calloc(size_t count, size_t size, const char *file, int line, const char *func)
{
    void *p = calloc(count,size);
    fprintf (fp,"0 Allocated = %s, %i, %s, #%p[%li]\n", file, line, func, p, size);
    return p;
}

void my_free(void *ptr, const char *file, int line, const char *func)
{
    fprintf (fp,"1 freeing = %s, %i, %s, #%p\n", file, line, func, ptr);
    free(ptr);
}

void summerize() 
{
    fclose(fp);
}

#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X,Y) my_calloc( X,Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)

