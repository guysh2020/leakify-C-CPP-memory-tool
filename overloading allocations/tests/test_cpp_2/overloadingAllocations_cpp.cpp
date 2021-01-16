
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

#define FILE_NAME "allocations.txt"

FILE* openFile()
{
    FILE* fp = fopen(FILE_NAME,"a");
    return fp;
}

void startRunning()
{
    FILE* fp = fopen(FILE_NAME,"a");
    std::cout << "here";
    std::string file = __FILE__;
    

    fprintf(fp,"***new test***\n");
}

void *my_malloc(std::size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = malloc(size);
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
    return p;
}
void *my_calloc(std::size_t count, size_t size, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *p = calloc(count, size);
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, p, size);
    return p;
}

void my_free(void *ptr, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =%s,%i,%s,#%p\n", file, line, func, ptr);
    free(ptr);
}

void *operator new(std::size_t sz, const char *file, int line, const char *func)
{
    FILE *fp = openFile();
    void *ptr = std::malloc(sz);
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, ptr, sz);
    fclose(fp);
    std::cout << "in new" << ptr << "\n";

    return ptr;
}

void *operator new[](std::size_t sz,const char *file, int line, const char *func)
{
    void *ptr = std::malloc(sz);
    FILE *fp = openFile();
    fprintf(fp, "0 Allocated =%s,%i,%s,#%p[%li]\n", file, line, func, ptr, sz);
    fclose(fp);
    std::cout << "in new[]" << ptr << "\n";
    return ptr;
}

void operator delete(void *ptr, std::size_t sz)
{
    std::cout << "in delete" << std::endl;
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p[%zu]\n", ptr, sz);
    fclose(fp);
    free(ptr);
}

void operator delete[](void *ptr, std::size_t sz)
{
    std::cout << "in delete[]" << std::endl;
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p[%zu]\n", ptr, sz);
    fclose(fp);
    
    free(ptr);
}

void operator delete[](void *ptr)
{
    std::cout << "in delete[]" << std::endl;
    FILE *fp = openFile();
    fprintf(fp, "1 freeing =#%p\n", ptr);
    fclose(fp);
    
    free(ptr);
}

void summerize()
{
    FILE *fp = fopen(FILE_NAME,"a");
    fclose(fp);
}