#pragma once

#include<iostream> 
#include<stdlib.h> 
// #include "overloadingAllocations_cpp.h"

using namespace std; 
class student 
{ 
    string name; 
    int age; 
public: 
    student();
    student(string name, int age) ; 
    void display() ;
    student* copy();
}; 

