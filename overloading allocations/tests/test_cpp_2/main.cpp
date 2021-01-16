#include<iostream> 
#include<stdlib.h> 

#include "student.h"


#include "overloadingAllocations_cpp.h"


int main() 
{ 
    startRunning();
    int *x = new int[8];
    student * p = new student("Yash", 24); 
    student *a = new student[6];
    
    delete p; 
    delete[] a;

    delete [] x;
    summerize();
    return 0;
} 