#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree", "my_media_types", "%u\t%n", true);

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "1509\ttree\n"
                               "1509\ttree/.gamma\n"
                               "1509\ttree/alpha\n"
                               "1509\ttree/alpha/epsilon\n"
                               "1509\ttree/alpha/iota\n"
                               "1509\ttree/alpha/iota/kappa\n"
                               "1509\ttree/alpha/iota/omega\n"
                               "1509\ttree/beta\n"
                               "1509\ttree/delta\n")

    return 0;
}
