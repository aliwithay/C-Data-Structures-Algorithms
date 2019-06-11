#include "Bunch.h"
using namespace std;
Regular::Regular()
{
    throw "No path provided for Regular. Exiting."s;
}
Regular::Regular(const std::string &path)
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
Regular::Regular(const Regular &old)
{
    p = old.p;
    sb = old.sb;
}
Regular Regular::operator=(const Regular &old)
{
    p = old.p;
    sb = old.sb;
    return *this;
}
Regular::~Regular()
{
}
