#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("treasure");
    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "lrwxrwxrwx cs253 class 20 treasure\n")

    return 0;
}
