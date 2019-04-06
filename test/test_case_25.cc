#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b(".hidden_dir");
    b.all(true);

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "-rw-r--r-- cs253 class 40 .hidden_dir/.hidden\n"
                               "drwxr-xr-x cs253 class 4096 .hidden_dir\n")

    return 0;
}
