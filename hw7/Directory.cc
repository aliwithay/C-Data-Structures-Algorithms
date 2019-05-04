#include "Bunch.h"
using namespace std;
Directory::Directory()
{
    throw "No path provided for Directory. Exiting."s;
}
Directory::Directory(const std::string &path)
{
    p = path;
    int result = lstat(path.c_str(), &sb);
    if (result != 0)
    {
        auto saveErr = errno;
        string err = "Could not open " + path + ". " + strerror(saveErr);
        throw err;
        return;
    }
}
Directory::Directory(const Directory &old)
{
    p = old.p;
    sb = old.sb;
}
Directory Directory::operator=(const Directory &old)
{
    p = old.p;
    sb = old.sb;
    return *this;
}
Directory::~Directory()
{
}