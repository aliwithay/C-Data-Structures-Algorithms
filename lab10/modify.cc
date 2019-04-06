#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc != 3) {
	cerr << "usage: " << argv[0] << " infile outfile\n";
	return 1;
    }
    ifstream in(argv[1]);
    if (!in) {
	cerr << argv[0] << ": can't open " << argv[1] << '\n';
	return 1;
    }
    ofstream out(argv[2]);
    if (!out) {
	cerr << argv[0] << ": can't open " << argv[2] << '\n';
	return 2;
    }

    string s;
    while (getline(in, s)) {
	size_t n;
	while ( (n=s.find("global")) != string::npos )
	    s.replace(n, 6, "denial");
	out << s << '\n';
    }

    return 0;
}
