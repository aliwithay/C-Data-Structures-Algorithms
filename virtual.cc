// This code illustrates what virtual functions do.
// Uncomment the /* virtual */ to change the behavior.
//
// Don’t confuse virtual functions with virtual inheritance.
// They are two very different things.

#include <iostream>
using namespace std;

class A
{
  public:
    virtual const char *foo() { return "alpha"; }
};

class B : public A
{
  public:
    virtual const char *foo() { return "beta"; }
};

int main()
{
    A a;
    B b;
    cout << a.foo() << '\n';
    cout << b.foo() << '\n';
    A *p = &b;
    cout << p->foo() << '\n';

    return 0;
}