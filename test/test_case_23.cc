#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b(".hidden_dir");
    string student_lines = b.entry(0);
    student_lines += "\n";

    CHECK_LINES(student_lines, "drwxr-xr-x cs253 class 4096 .hidden_dir\n")

    return 0;
}
