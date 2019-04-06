#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("simple");
    b.format("%n");

    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "simple\n")

    return 0;
}