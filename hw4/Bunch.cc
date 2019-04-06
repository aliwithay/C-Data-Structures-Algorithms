#include "Bunch.h"
using namespace std;
Bunch::Bunch()
{
    m = getpwnam("cs253")->pw_dir;
    m += "/pub/media-types";
    f = "%p %U %G %s %n";
    a = 0;
    p = "";
    files.clear();
}
Bunch::Bunch(const string path, const string magic, const string format, const bool all)
{
    if (magic == "")
    {
        m = getpwnam("cs253")->pw_dir;
        m += "/pub/media-types";
    }
    else
    {
        m = magic;
    }
    f = format;
    if (all)
    {
        a = 1;
    }
    else
    {
        a = 0;
    }
    p = path;
    files.clear();
    recurse_directory(f, m, p, a);
}
Bunch::Bunch(const Bunch &old)
{
    for (size_t i = 0; i < old.size(); i++)
    {
        files.push_back(old.entry(i));
    }
    f = old.f;
    p = old.p;
    m = old.m;
    a = old.a;
}
Bunch Bunch::operator=(const Bunch &old)
{
    Bunch newBunch(old);
    return newBunch;
}
void Bunch::path(const string path)
{
    p = path;
    files.clear();
    recurse_directory(f, m, p, a);
}
void Bunch::magic(const string magic)
{
    m = magic;
    files.clear();
    recurse_directory(f, m, p, a);
}
void Bunch::format(const string format)
{
    f = format;
    files.clear();
    recurse_directory(f, m, p, a);
}
void Bunch::all(const bool all)
{
    if (all == true)
    {
        a = 1;
    }
    files.clear();
    recurse_directory(f, m, p, a);
}
size_t Bunch::size() const
{
    return files.size();
}
bool Bunch::empty() const
{
    if (files.size() == 0)
    {
        return true;
    }
    return false;
}
string Bunch::entry(const size_t n) const
{

    if (files.size() == 0)
    {
        throw "Bunch is empty. No files.";
    }
    if (files.size() < n + 1)
    {
        string err = "Index out of bounds! n: ";
        err += to_string(n);
        err += ", Number of entries: ";
        err += to_string(files.size() - 1);
        throw err;
    }
    return files[n];
}
string Bunch::get_file_permissions(struct stat sb)
{
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
    return permissions;
}
char *Bunch::get_modified_time(struct stat sb)
{
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_mtime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
char *Bunch::get_access_time(struct stat sb)
{
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_atime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
char *Bunch::get_change_time(struct stat sb)
{
    //Returns char * containing the formatted time of last status change.
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_ctime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
int Bunch::get_size(struct stat sb)
{
    return sb.st_size;
}
int Bunch::get_user_id(struct stat sb)
{
    return sb.st_uid;
}
char *Bunch::get_user_name(struct stat sb)
{
    struct passwd *pwd;
    pwd = getpwuid(sb.st_uid);
    return pwd->pw_name;
}
int Bunch::get_group_id(struct stat sb)
{
    return sb.st_gid;
}
char *Bunch::get_group_name(struct stat sb)
{
    struct group *grp;
    grp = getgrgid(sb.st_gid);
    return grp->gr_name;
}
ifstream Bunch::read_media_ref(string ref_path)
{
    ifstream ref(ref_path);
    if (!ref)
    {
        const auto saveErr = errno;
        string err = "Cannot open media type reference file. ";
        err += strerror(saveErr);
        err += "\n";
        throw err;
    }
    return ref;
}
string Bunch::get_media_type(string mediaFile, string path, struct stat sb)
{
    switch (sb.st_mode & S_IFMT)
    {
    case S_IFDIR:
        return "inode/directory";
    case S_IFLNK:
        return "inode/symlink";
    case S_IFREG:
    {
        if (sb.st_size == 0)
        {
            return "inode/empty";
        }
        ifstream in(path);
        if (!in)
        {
            const auto saveErr = errno;
            string err = "Cannot open ";
            err += path;
            err += " file. ";
            err += strerror(saveErr);
            err += "\n";
            throw err;
        }
        char iden[32];
        in.read(iden, 32);
        string identifier = iden;
        ifstream ref = read_media_ref(mediaFile);
        string s;
        int flag = 0;
        while (ref >> s)
        {
            string comparator;
            if (s.find('%') != string::npos)
            {
                for (unsigned int k = 0; k < s.length(); k++)
                {
                    char c = s[k];
                    char al;
                    if (c == '%')
                    {
                        try
                        {
                            al = (stoi(s.substr(++k, 2), nullptr, 16));
                            comparator.push_back(al);
                            k++;
                        }
                        catch (const invalid_argument &ia)
                        {
                            comparator.push_back(s[k]);
                            continue;
                        }
                    }
                    else
                    {
                        comparator.push_back(c);
                    }
                }
            }
            else
            {
                comparator = s;
            }
            if (flag == 1)
            {
                return comparator;
            }
            if (identifier.find(comparator) != string::npos)
            {
                flag = 1;
            }
        }
        return "application/octet-data";
    }
    default:
        return "Unknown file type.";
    }
}
string Bunch::format_output(string format, string magicNumberFile, string path, struct stat sb)
{
    string output = "";
    for (unsigned int k = 0; k < format.size(); k++)
    {
        char c = format[k];
        if (c == '%')
        {
            switch (format[++k])
            {
            case 'n':
                output += path;
                break;
            case 'p':
                output += get_file_permissions(sb);
                break;
            case 'u':
                output += to_string(get_user_id(sb));
                break;
            case 'U':
                output += get_user_name(sb);
                break;
            case 'g':
                output += to_string(get_group_id(sb));
                break;
            case 'G':
                output += get_group_name(sb);
                break;
            case 's':
                output += to_string(get_size(sb));
                break;
            case 'a':
                output += get_access_time(sb);
                break;
            case 'm':
                output += get_modified_time(sb);
                break;
            case 'c':
                output += get_change_time(sb);
                break;
            case 'M':
                output += get_media_type(magicNumberFile, path, sb);
                break;
            default:
                continue;
            }
        }
        else
        {
            output += c;
        }
    }
    return output;
}
void Bunch::recurse_directory(string format, string mediafile, string path, int aflag)
{
    struct stat sb;
    int result = lstat(path.c_str(), &sb);
    if (result != 0)
    {
        auto saveErr = errno;
        string err = "Could not open " + path + ". " + strerror(saveErr);
        throw err;
        return;
    }
    string s = format_output(format, mediafile, path, sb);
    files.push_back(s);
    DIR *dir;
    dir = opendir(path.c_str());
    if (dir == NULL)
    {
        //cout << "dir = NULL \n";
        return;
    }
    struct dirent *rdir;
    string d = ".";
    string dd = "..";
    while ((rdir = readdir(dir)) != NULL)
    {
        string r = rdir->d_name;
        if (r == d || r == dd || (aflag == 0 && r[0] == '.'))
        {
            continue;
        }
        r = path + "/" + r;
        recurse_directory(format, mediafile, r, aflag);
    }
    closedir(dir);
    return;
}
