//
// Created by Christian Ott on 02.11.2016.
//
#include <iostream>

void c_swap(int *a, int *b) {
  int c=*a;
  *a=*b;
  *b=c;
}

void swap(int& a, int& b) {
  int c = a;
  a = b;
  b = c;
}

int main(int argc, const char * argv[])
{
  int a = 3;
  int b = 5;

  c_swap(&a, &b);

  std::cout << a << " " << b << std::endl;

  swap(a, b);

  std::cout << a << " " << b << std::endl;
  return 0;
}