#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree");
    b.format("%p\t%n");

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "-r--r--r--\ttree/alpha/iota/kappa\n"
                               "-r--r--r--\ttree/delta\n"
                               "-rw-r--r--\ttree/alpha/iota/omega\n"
                               "-rwxr--r-x\ttree/alpha/epsilon\n"
                               "dr-xr-xr-x\ttree/alpha\n"
                               "drwxr-xr--\ttree/beta\n"
                               "drwxr-xr-x\ttree\n"
                               "drwxr-xr-x\ttree/alpha/iota\n")

    return 0;
}
