#include "Bunch.h"
#include "test.h"

using namespace std;

int run_test_case(string &info) {
    Bunch b("tree");
    b.format("%M\t%n");

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "application/elf\ttree/alpha/epsilon\n"
                               "image/png\ttree/alpha/iota/kappa\n"
                               "inode/directory\ttree\n"
                               "inode/directory\ttree/alpha\n"
                               "inode/directory\ttree/alpha/iota\n"
                               "inode/directory\ttree/beta\n"
                               "inode/empty\ttree/delta\n"
                               "text/perl\ttree/alpha/iota/omega\n")

    return 0;
}
