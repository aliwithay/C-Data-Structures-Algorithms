#include "Bunch.h"
#include "test.h"
#include <pwd.h>

using namespace std;

int run_test_case(string &info) {
    const auto home = getpwnam("cs253")->pw_dir;
    Bunch b(home + "/pub/hamlet.txt"s, "my_media_types", "%a\t%n");

    multiset<string> student_entries;
    for (size_t i=0; i<b.size(); i++) {
        student_entries.insert(b.entry(i));
    }

    string student_lines;
    student_lines += student_entries;

    CHECK_LINES(student_lines, "2019-03-28T10:06:00\t/s/bach/a/class/cs253/pub/hamlet.txt\n")

    return 0;
}
