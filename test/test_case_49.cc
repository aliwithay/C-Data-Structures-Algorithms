#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree", "my_media_types", "%m\t%n", true);

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "2019-01-06T12:09:47\ttree/beta\n"
                               "2019-01-06T12:09:58\ttree/.gamma\n"
                               "2019-01-06T12:11:10\ttree\n"
                               "2019-01-06T12:11:10\ttree/delta\n"
                               "2019-01-06T12:11:36\ttree/alpha/epsilon\n"
                               "2019-01-06T12:11:44\ttree/alpha\n"
                               "2019-01-06T12:12:12\ttree/alpha/iota/kappa\n"
                               "2019-01-06T12:16:48\ttree/alpha/iota\n"
                               "2019-01-06T12:16:48\ttree/alpha/iota/omega\n")

    return 0;
}
