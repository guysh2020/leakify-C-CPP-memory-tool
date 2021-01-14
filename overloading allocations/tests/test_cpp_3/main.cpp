#pragma once
using namespace std;

#include "overloadingAllocations_cpp.h"

int main()
{
    openFile();
   int* p1 = new int;
     delete p1;
 
     int* p2 = new int[10]; // guaranteed to call the replacement in C++11
     delete[] p2;
    summerize();
    return 0;
}