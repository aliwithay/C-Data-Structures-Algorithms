#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    const Bunch b1("tree");

    const Bunch b2 = b1;

    multiset<string> student_entries;
    for (size_t i=0; i<b2.size(); i++) {
        student_entries.insert(b2.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "-r--r--r-- cs253 class 0 tree/delta\n"
                               "-r--r--r-- cs253 class 46138 tree/alpha/iota/kappa\n"
                               "-rw-r--r-- cs253 class 166 tree/alpha/iota/omega\n"
                               "-rwxr--r-x cs253 class 42320 tree/alpha/epsilon\n"
                               "dr-xr-xr-x cs253 class 4096 tree/alpha\n"
                               "drwxr-xr-- cs253 class 4096 tree/beta\n"
                               "drwxr-xr-x cs253 class 4096 tree\n"
                               "drwxr-xr-x cs253 class 4096 tree/alpha/iota\n")

    return 0;
}
