#include "Bunch.h"
using namespace std;
/*
Fing::Fing()
{
    throw "No path provided for Fing. Exiting."s;
}
Fing::Fing(const std::string &path)
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
Fing::Fing(const Fing &old)
{
    p = old.p;
    sb = old.sb;
}
Fing Fing::operator=(const Fing &old)
{
    p = old.p;
    sb = old.sb;
    return *this;
}
*/
Fing::~Fing()
{
}
string Fing::path() const
{
    return p;
}
Dual Fing::perms() const
{
    uint perm = sb.st_mode;
    string permissions;
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFIFO:
        permissions += "f";
        break;
    case S_IFSOCK:
        permissions += "s";
        break;
    case S_IFREG:
        permissions += "-";
        break;
    case S_IFDIR:
        permissions += "d";
        break;
    case S_IFLNK:
        permissions += "l";
        break;
    }
    switch ((sb.st_mode & S_IRWXU) >> 6)
    {
    case 7:
        permissions += "rwx";
        break;
    case 6:
        permissions += "rw-";
        break;
    case 5:
        permissions += "r-x";
        break;
    case 4:
        permissions += "r--";
        break;
    case 3:
        permissions += "-wx";
        break;
    case 2:
        permissions += "-w-";
        break;
    case 1:
        permissions += "--x";
        break;
    case 0:
        permissions += "---";
        break;
    }
    //Determine GROUP permissions.
    switch ((sb.st_mode & S_IRWXG) >> 3)
    {
    case 7:
        permissions += "rwx";
        break;
    case 6:
        permissions += "rw-";
        break;
    case 5:
        permissions += "r-x";
        break;
    case 4:
        permissions += "r--";
        break;
    case 3:
        permissions += "-wx";
        break;
    case 2:
        permissions += "-w-";
        break;
    case 1:
        permissions += "--x";
        break;
    default:
        permissions += "---";
        break;
    }
    //Determine OTHER permissions.
    switch (sb.st_mode & S_IRWXO)
    {
    case 7:
        permissions += "rwx";
        break;
    case 6:
        permissions += "rw-";
        break;
    case 5:
        permissions += "r-x";
        break;
    case 4:
        permissions += "r--";
        break;
    case 3:
        permissions += "-wx";
        break;
    case 2:
        permissions += "-w-";
        break;
    case 1:
        permissions += "--x";
        break;
    default:
        permissions += "---";
        break;
    }
    return Dual(perm, permissions);
}
Dual Fing::mtime() const
{
    //Get time in epoch seconds and convert to readable time.
    uint time = sb.st_mtime;
    auto timevals = localtime(&sb.st_mtime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    string ftime = buf;
    return Dual(time, ftime);
}
Dual Fing::atime() const
{
    //Get time in epoch seconds and convert to readable time.
    uint time = sb.st_atime;
    auto timevals = localtime(&sb.st_atime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    string ftime = buf;
    return Dual(time, ftime);
}
Dual Fing::ctime() const
{
    //Returns char * containing the formatted time of last status change.
    //Get time in epoch seconds and convert to readable time.
    uint time = sb.st_ctime;
    auto timevals = localtime(&sb.st_ctime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    string ftime = buf;
    return Dual(time, ftime);
}
size_t Fing::size() const
{
    return sb.st_size;
}
Dual Fing::uid() const
{
    uint uid = sb.st_uid;
    struct passwd *pwd;
    pwd = getpwuid(sb.st_uid);
    string uname = pwd->pw_name;
    return Dual(uid, uname);
}
Dual Fing::gid() const
{
    uint gid = sb.st_gid;
    struct group *grp;
    grp = getgrgid(sb.st_gid);
    string gname = grp->gr_name;
    return Dual(gid, gname);
}
bool Fing::operator==(const Fing &ofing) const
{
    if ((sb.st_ino == ofing.sb.st_ino) && (sb.st_dev == ofing.sb.st_dev))
    {
        return true;
    }
    return false;
}