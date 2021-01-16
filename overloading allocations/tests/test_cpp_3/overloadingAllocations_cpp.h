#pragma once

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <stdint.h>


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

void summerize();


#define malloc(X) my_malloc(X, __FILE__, __LINE__, __FUNCTION__)
#define calloc(X, Y) my_calloc(X, Y, __FILE__, __LINE__, __FUNCTION__)
#define free(X) my_free(X, __FILE__, __LINE__, __FUNCTION__)
#define new new (__FILE__, __LINE__, __FUNCTION__)
