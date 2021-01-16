
#include "overloadingAllocations_cpp.h"

int main()
{
  startRunning();
  int* p1 = new int;
  delete p1;


  int* p2 = new int[10]; 
  delete[] p2;
  summerize();
  return 0;
}