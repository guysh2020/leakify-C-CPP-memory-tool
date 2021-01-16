//#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

// static FILE *fp;

// void openFile(FILE *fp_t)
// {
//     fp = fp_t;
//     //    fp = fopen("../userData/allocations.txt","w");
// }

// void *my_malloc(size_t size, const char *file, int line, const char *func)
// {
//     void *p = malloc(size);
//     fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
//     return p;
// }
// void *my_calloc(size_t count, size_t size, const char *file, int line, const char *func)
// {
//     void *p = calloc(count, size);
//     fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
//     return p;
// }

// void my_free(void *ptr, const char *file, int line, const char *func)
// {
//     fprintf(fp, "1 freeing =%s,%i,%s,#%p\n", file, line, func, ptr);
//     free(ptr);
// }

void *operator new(size_t sz, const char *file, int line, const char *func)
{
    void *ptr = std::malloc(sz);
    FILE* fp = fopen("../userData/allocations.txt","a");
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%zu]\n", file, line, func, ptr, sz);
    fclose(fp);

    return ptr;
}

void *operator new[](std::size_t sz, const char *file, unsigned int line, const char *func)
{
    void *ptr = std::malloc(sz);
    FILE* fp = fopen("../userData/allocations.txt","a");
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%zu]\n", file, line, func, ptr, sz);
    fclose(fp);
    return ptr;
}

void operator delete(void *ptr, std::size_t sz)
{
    std::cout << "in delete" << std::endl;
    FILE* fp = fopen("../userData/allocations.txt","a");
    fprintf(fp, "1 freeing =#%p[%zu]\n", ptr, sz);
    fclose(fp);
    free(ptr);
}

void operator delete[](void *ptr)
{
    std::cout << "in delete[]" << std::endl;
    FILE* fp = fopen("../userData/allocations.txt","a");
    fprintf(fp, "1 freeing =#%p[]\n", ptr);
    fclose(fp);
    
    free(ptr);
}

// void summerize()
// {
//     fclose(fp);
// }