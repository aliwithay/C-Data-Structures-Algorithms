#include "Directory.h"
#include <iostream>
#include <regex>

using namespace std;

// The directory iterator pre-fetches the name.  That is, readdir()
// is called when you first create the iterator, and upon ++.
//
// An end() iterator is designated by a null pointer for its DIR *.
// When readdir() fails, we set our pointer to null.

DirectoryIterator::DirectoryIterator(DIR *dp_arg) : dp(dp_arg) {
    ++*this;				// get that first entry
}

DirectoryIterator &DirectoryIterator::operator++() {	// pre-increment
    while (auto p = readdir(dp)) {	// Read a directory entry.
	name = p->d_name;		// C-string ⇒ C++ string
	if (!this->wanted(name))		// Stupid entry for current directory?
	    continue;			// Nobody wants that.
	return *this;			// Everything else, I like!
    }
    dp = nullptr;			// readdir failed; don’t try again.
    return *this;
}

std::string DirectoryIterator::operator*() const {
    return name;			// Fetched in a previous ++.
}

bool DirectoryIterator::operator!=(const DirectoryIterator &rhs) const {
    return dp != rhs.dp;
}

bool DirectoryIterator::wanted(string fname, string pattern)
{
    if (fname == "." || fname == "..")
    {
        return false;
    }
    regex p (pattern);
    smatch m;
    if(!regex_search(fname, m, p)){
        return false;
    }
    return true;
}



//////////////// Directory methods

Directory::Directory(const char dirname[]) : dp(opendir(dirname)) {
    if (!dp) {
        cout << "Invalid Directory\n";
        exit(1);
    }
}

Directory::~Directory() {
    if (dp)				// Only if opendir() succeeded:
	closedir(dp);			//   should we close it.
}

Directory::iterator Directory::begin() const {
    // Should I open it here, instead?  Later seems better.
    return iterator(dp);
}

Directory::iterator Directory::end() const {
    return iterator();
}

