#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree");
    b.format("%s\t%n");

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "0\ttree/delta\n"
                               "166\ttree/alpha/iota/omega\n"
                               "4096\ttree\n"
                               "4096\ttree/alpha\n"
                               "4096\ttree/alpha/iota\n"
                               "4096\ttree/beta\n"
                               "42320\ttree/alpha/epsilon\n"
                               "46138\ttree/alpha/iota/kappa\n")

    return 0;
}
