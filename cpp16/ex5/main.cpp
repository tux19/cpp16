//
// Created by Christian Ott on 02.11.2016.
//
#include <iostream>
#include "Object.h"
#include "dumb_pointer.h"
#include "smart_pointer.h"
void print(pointer::smart_pointer<Object> p) {
    std::cout << p.counter() << ": " << *p << std::endl;
}

void foo() {
    Object *o1=new Object(1);
    Object *o2=new Object(2);
    pointer::smart_pointer<Object> p(o1);
    std::cout << p.counter() << std::endl;
// let's create our 1st object
// let's create our 2nd object
// ref counter is 1 for 1st object
// displays 1
// another smart pointer pointing to o1 (overload copy constructor)
    pointer::smart_pointer<Object> q(p);
// counter() returns how many smart pointers refer to the object
    std::cout << p.counter() << std::endl;
    std::cout << q.counter() << std::endl;
    pointer::smart_pointer<Object> r(o2);
    std::cout << r.counter() << std::endl;
// displays 2
// displays 2
// ref counter is 1 for 2nd object
// displays 1
// overload the assignment operator
    q=r;
    std::cout << p.counter() << std::endl;
    std::cout << q.counter() << std::endl;
    std::cout << r.counter() << std::endl;
// decrease counter for 1st object and
// increase counter for 2nd object
// displays 1
// displays 2
// displays 2
    print(p);
    print(q);
    print(r);
// ensure that the above 3 functions, don’t delete the objects
// displays 2, and the 1st object
// displays 3, and the 2nd object
// displays 3, and the 2nd object
// overload operator*
    std::cout << *p << *r << std::endl; // display 1st and 2nd object
    // overload operator->
    std::cout << p->method1() << q->method2() << r->method3() << std::endl;
    // invoke method1 on 1st object and
    // invoke method2 on 2nd object and
    // invoke method3 on 2nd object
} // now the destructors of p, q, and r are called, make sure that 1st
// and 2nd object is each deleted once
// (i.e., when the counter reaches 0)
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
    std::cout << "------------------------------------------------------------\n|	   TASK 5.1 \n ------------------------------------------------------------"
              << std::endl;
    // Dumb pointer test
    Object *ob = new Object(42);

    pointer::dumb_pointer<Object> pob(ob);

    std::cout << "Start dumb_pointer tests" << std::endl;

    std::cout << *pob << std::endl;
    std::cout << pob->description() << std::endl;

    std::cout << "End dumb_pointer tests" << std::endl;

    std::cout << "Start smart_pointer tests" << std::endl;
    foo();
    std::cout << "End smart_pointer tests" << std::endl;

    std::cout << "------------------------------------------------------------\n|	   TASK 5.2 \n ------------------------------------------------------------"
              << std::endl;
    int a = 3;
    int b = 5;

    c_swap(&a, &b);

    std::cout << a << " " << b << std::endl;

    swap(a, b);

    std::cout << a << " " << b << std::endl;
    return 0;
}