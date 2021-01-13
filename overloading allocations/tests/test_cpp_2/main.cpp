//
#pragma once
//
#include<iostream> 
#include<stdlib.h> 

#include "student.h"

//
#include "overloadingAllocations_cpp.h"
//
  
using namespace std; 

  
student::student() 
{ 
    this->name = "default"; 
    this->age = 0; 
} 
student::student(string name, int age) 
{ 
    this->name = name; 
    this->age = age; 
} 
void student::display() 
{ 
    cout<< "Name:" << name << endl; 
    cout<< "Age:" << age << endl; 
}

int main() 
{ 
    openFile();
    student * p = new student("Yash", 24); 
    student *a = new student[6];
    
    delete p; 
    delete[] a;

    summerize();
    return 0;
} 