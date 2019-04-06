#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("simple");

    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "-rw-r--r-- cs253 class 19 simple\n")

    return 0;
}
