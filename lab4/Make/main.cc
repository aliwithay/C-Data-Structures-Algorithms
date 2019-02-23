#include <iostream>

using namespace std;

#include "bar.h"

int main() {
    cout << "Hi from " << __func__ << " at " __FILE__ ":" << __LINE__ << '\n';
    bar();
    return 0;
}
