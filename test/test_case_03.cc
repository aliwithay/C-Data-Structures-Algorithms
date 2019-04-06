#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b;

    size_t sz {b.size()};

    if (sz != 0) {
        info = "b should have size 0";
        return 1;
    }

    return 0;
}