#include "student.h"
#include "overloadingAllocations_cpp.h"

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

