#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree", "my_media_types", "%g\t%n", true);

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "1549\ttree\n"
                               "1549\ttree/.gamma\n"
                               "1549\ttree/alpha\n"
                               "1549\ttree/alpha/epsilon\n"
                               "1549\ttree/alpha/iota\n"
                               "1549\ttree/alpha/iota/kappa\n"
                               "1549\ttree/alpha/iota/omega\n"
                               "1549\ttree/beta\n"
                               "1549\ttree/delta\n")

    return 0;
}
