#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("fortune");
    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "lrwxrwxrwx cs253 class 16 fortune\n")

    return 0;
}
