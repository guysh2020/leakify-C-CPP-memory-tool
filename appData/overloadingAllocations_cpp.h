<<<<<<< HEAD
#pragma once
=======
//#pragma once
>>>>>>> 6a5cc2cd28e8568e352b87d147f40adf25460c7b

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>

<<<<<<< HEAD

void openFile();

void startRunning();

void *my_malloc(std::size_t size, const char *file, int line, const char *func);

void *my_calloc(std::size_t count, std::size_t size, const char *file, int line, const char *func);

void my_free(void *ptr, const char *file, int line, const char *func);

void *operator new(std::size_t sz, const char *file, int line, const char *func);

void *operator new[](std::size_t sz, const char *file, int line, const char *func);

void operator delete(void *ptr, std::size_t sz);

void operator delete[](void *ptr, std::size_t sz);

void operator delete[](void *ptr);

=======
// inline void openFile(FILE* fp_t);

// inline void* my_malloc(size_t size, const char *file, int line, const char *func);
// inline void* my_calloc(size_t count, size_t size, const char *file, int line, const char *func);

// inline void my_free(void *ptr, const char *file, int line, const char *func);

// inline void* operator new(size_t sz,const char *file, int line, const char *func);

// inline void* operator new[](std::size_t sz,const char* file, unsigned int line,const char *func);

// inline void operator delete(void* ptr, std::size_t sz) ;

// inline void operator delete[](void* ptr);

// static void summerize() ;

void openFile(FILE *fp_t);

void *my_malloc(size_t size, const char *file, int line, const char *func);
void *my_calloc(size_t count, size_t size, const char *file, int line, const char *func);

void my_free(void *ptr, const char *file, int line, const char *func);

void *operator new(size_t sz, const char *file, int line, const char *func);

void *operator new[](std::size_t sz, const char *file, unsigned int line, const char *func);

void operator delete(void *ptr, std::size_t sz);

void operator delete[](void *ptr);

void summerize();

// inline FILE *fopen(const char * fileName,const char * mode)
// {
//     printf("%s","here");
//     FILE * fp = fopen(fileName,mode);
//     printf("%s","here1");
//     return fp;
// }
>>>>>>> 6a5cc2cd28e8568e352b87d147f40adf25460c7b

#define malloc(X) my_malloc(X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X, Y) my_calloc(X, Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free(X, __FILE__, __LINE__, __FUNCTION__)
#define new new (__FILE__, __LINE__, __FUNCTION__)
