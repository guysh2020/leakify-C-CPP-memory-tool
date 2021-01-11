#pragma once

#include<iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

static FILE* fp;

inline void openFile()
{
    printf("%s","open file");
    fp = fopen("allocations.txt","w");
}

inline void* my_malloc(size_t size, const char *file, int line, const char *func)
{
    void *p = malloc(size);
    fprintf (fp,"0 Allocated = %s, %i, %s, #%p[%li]\n", file, line, func, p, size);
    return p;
}
inline void* my_calloc(size_t count, size_t size, const char *file, int line, const char *func)
{
    void *p = calloc(count,size);
    fprintf (fp,"0 Allocated = %s, %i, %s, #%p[%li]\n", file, line, func, p, size);
    return p;
}

inline void my_free(void *ptr, const char *file, int line, const char *func)
{
    fprintf (fp,"1 freeing = %s, %i, %s, #%p\n", file, line, func, ptr);
    free(ptr);
}

inline void* operator new(size_t sz,const char *file, int line, const char *func) 
{
    void *ptr = std::malloc(sz);
    fprintf(fp,"0 Allocated = %s, %i, %s, #%p[%zu]\n",file,line,func,ptr,sz); 
    return ptr;
}

inline void* operator new[](std::size_t sz,const char* file, unsigned int line,const char *func) 
{
    void *ptr = std::malloc(sz);
    fprintf(fp,"0 Allocated = %s, %i, %s, #%p[%zu]\n",file,line,func,ptr,sz); 
    return ptr;
}


inline void operator delete(void* ptr, std::size_t sz) 
{
    fprintf(fp,"1 freeing = #%p[%zu]\n",ptr,sz); 
    free(ptr);
}

inline void operator delete[](void* ptr, std::size_t sz) 
{
    fprintf(fp,"1 freeing = #%p[%zu]\n",ptr,sz);
    free(ptr);
}

static void summerize() 
{
    fclose(fp);
}

// inline FILE *fopen(const char * fileName,const char * mode) 
// {
//     printf("%s","here");
//     FILE * fp = fopen(fileName,mode);
//     printf("%s","here1");
//     return fp;
// }

#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X,Y) my_calloc( X,Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free( X, __FILE__, __LINE__, __FUNCTION__)
#define new new(__FILE__, __LINE__,__FUNCTION__)


