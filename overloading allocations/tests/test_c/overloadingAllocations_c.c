#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define FILE_NAME "allocations.txt"

FILE* openFile()
{
    FILE* fp = fopen(FILE_NAME,"a");
    return fp;
}

void startRunning()
{   
    FILE *fp = openFile(); 
    fprintf(fp,"***new running***\n");
}
void* my_malloc(size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = malloc(size);
    fprintf (fp,"0 Allocated = %s, %i, %s, #%p[%li]\n", file, line, func, p, size);
    fclose(fp);

    return p;
}

void *my_calloc(size_t count, size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = calloc(count, size);
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
    fclose(fp);

    return p;
}

void my_free(void *ptr, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =%s,%i,%s,#%p\n", file, line, func, ptr);
    fclose(fp);

    free(ptr);
}
#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X,Y) my_calloc( X,Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)

