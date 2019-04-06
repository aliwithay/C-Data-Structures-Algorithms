#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("end");
    b.format("%m");
    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "2018-12-31T08:00:00\n")

    return 0;
}