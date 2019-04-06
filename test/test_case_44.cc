#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree");

    try {
        string s = b.entry(100);
    } EXPECT_THROWN_STRING_TO_CONTAIN("100")

    return 0;
}
