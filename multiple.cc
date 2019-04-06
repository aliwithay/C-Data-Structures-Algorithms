// This example illustrates multiple inheritance.

#include <iostream>
using namespace std;

class Citizen {
  public:
    void vote() { cout << "Stupid electoral college!\n"; };
};

class Teacher {
  public:
    void lecture() { cout << ".eof() is much misunderstood.\n"; };
};

class Jack : public Citizen, public Teacher {
    // I need no methods of my own.
};

int main() {
    Jack j;
    j.vote();
    j.lecture();

    Citizen *c = &j;
    c->vote();
    // c->lecture();
    Teacher *t = &j;
    // t->vote();
    t->lecture();
}