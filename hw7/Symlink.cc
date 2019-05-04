#include "Bunch.h"
using namespace std;
Symlink::Symlink()
{
    throw "No path provided for Symlink. Exiting."s;
}
Symlink::Symlink(const std::string &path)
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
Symlink::Symlink(const Symlink &old)
{
    p = old.p;
    sb = old.sb;
}
Symlink Symlink::operator=(const Symlink &old)
{
    p = old.p;
    sb = old.sb;
    return *this;
}
Symlink::~Symlink()
{
}