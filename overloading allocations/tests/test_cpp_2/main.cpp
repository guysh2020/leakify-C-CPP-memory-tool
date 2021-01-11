//
#pragma once
//
#include<iostream> 
#include<stdlib.h> 

#include "student.h"

//
#include "overloadingAllocations.h"
//
  
using namespace std; 

  
int main() 
{ 
    openFile();
    FILE *fp = fopen("sivan.txt","r");
    int *x = new int(10);
    student * p = new student("Yash", 24); 

    p->display(); 
    student *a = new student[6];
    for (int i=0 ;i<5;i++) {
        a[i].display();
    }

    delete p; 
    delete[] a;

    summerize();
    return 0;
} 