#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("simple");

    try {
        string student_lines = b.entry(1);
    } EXPECT_THROWN_STRING_TO_CONTAIN("1")

    return 0;
}