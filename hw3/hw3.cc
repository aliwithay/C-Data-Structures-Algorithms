#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <getopt.h>
#include <cstring>
#include <dirent.h>
using namespace std;
string get_file_permissions(struct stat sb)
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
char *get_modified_time(struct stat sb)
{
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_mtime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
char *get_access_time(struct stat sb)
{
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_atime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
char *get_change_time(struct stat sb)
{
    //Returns char * containing the formatted time of last status change.
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_ctime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
int get_size(struct stat sb)
{
    return sb.st_size;
}
int get_user_id(struct stat sb)
{
    return sb.st_uid;
}
char *get_user_name(struct stat sb)
{
    struct passwd *pwd;
    pwd = getpwuid(sb.st_uid);
    return pwd->pw_name;
}
int get_group_id(struct stat sb)
{
    return sb.st_gid;
}
char *get_group_name(struct stat sb)
{
    struct group *grp;
    grp = getgrgid(sb.st_gid);
    return grp->gr_name;
}
ifstream read_media_ref(string ref_path)
{
    ifstream ref(ref_path);
    if (!ref)
    {
        const auto saveErr = errno;
        cerr << "Cannot open media type reference file. " << strerror(saveErr) << ".\n";
    }
    return ref;
}
string get_media_type(string mediaFile, string path, struct stat sb)
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
            cerr << "Cannot open " << path << " file. " << strerror(saveErr);
            return "";
        }
        string identifier;
        in >> identifier;
        ifstream ref = read_media_ref(mediaFile);
        if (!ref)
        {
            return "";
        }
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
                    char a;
                    if (c == '%')
                    {
                        try
                        {
                            a = (stoi(s.substr(++k, 2), nullptr, 16));
                            comparator.push_back(a);
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
void format_output(string format, string magicNumberFile, string path, struct stat sb)
{
    for (unsigned int k = 0; k < format.size(); k++)
    {
        char c = format[k];
        if (c == '%')
        {
            switch (format[++k])
            {
            case 'n':
                cout << path;
                break;
            case 'p':
                cout << get_file_permissions(sb);
                break;
            case 'u':
                cout << get_user_id(sb);
                break;
            case 'U':
                cout << get_user_name(sb);
                break;
            case 'g':
                cout << get_group_id(sb);
                break;
            case 'G':
                cout << get_group_name(sb);
                break;
            case 's':
                cout << get_size(sb);
                break;
            case 'a':
                cout << get_access_time(sb);
                break;
            case 'm':
                cout << get_modified_time(sb);
                break;
            case 'c':
                cout << get_change_time(sb);
                break;
            case 'M':
                cout << get_media_type(magicNumberFile, path, sb);
                break;
            default:
                continue;
            }
        }
        else
        {
            cout << c;
        }
    }
    cout << "\n";
}
void recurse_directory(char *pname, string format, string mediafile, string path, int a)
{
    struct stat sb;
    int result = lstat(path.c_str(), &sb);
    if (result != 0)
    {
        auto saveErr = errno;
        cerr << pname
             << " encounterd an error on path " << path << ". " << strerror(saveErr) << ".\n";
        return;
    }
    format_output(format, mediafile, path, sb);
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
        if (r == d || r == dd || (a == 0 && r[0] == '.'))
        {
            continue;
        }
        r = path + "/" + r;
        recurse_directory(pname, format, mediafile, r, a);
    }
    closedir(dir);
    return;
}
int main(int argc, char *argv[])
{
    //Produce usage error if no path provided.
    if (argc == 1)
    {
        cerr << "Usage: " << argv[0] << "[-a][-f FORMAT][-m MAGIC FILE][PATH(s)]...\n"
             << "List information about the FILEs.\n"
             << "Format optional. (DEFAULT: '%p %U %G %s %n')\n";
        return 1;
    }
    int aflag = 0;
    int mflag = 0;
    int fflag = 0;
    int opt = 0;
    string mediafile = getpwnam("cs253")->pw_dir;
    mediafile += "/pub/media-types";
    //string mediafile = "/mnt/c/users/alyam/'OneDrive - Colostate'/CS253/hw3/media-types";
    string format = "%p %U %G %s %n";
    while ((opt = getopt(argc, argv, "f:m:a")) != -1)
    {
        switch (opt)
        {
        case 'a':
            aflag = 1;
            break;
        case 'm':
        {
            if (mflag == 1)
            {
                cerr << "Too many MAGIC FILE specifications. \n" << "Usage: " << argv[0] << " [-a][-f FORMAT][-m MAGIC FILE][PATH(s)]...\n"
                 << "List information about the FILEs.\n"
                 << "Format optional. (DEFAULT: '%p %U %G %s %n')\n";
                 return 1;
            }
            mflag = 1;
            mediafile = optarg;
            ifstream ref(mediafile);
            if (!ref)
            {
                int saveError = errno;
                cerr << "Cannot open media types file! " << strerror(saveError) << ".\n";
                ref.close();
                return 1;
            }
            ref.close();
            break;
        }
        case 'f':
        {
            if (fflag == 1)
            {
                cerr << "Too many FORMAT specifications" << "Usage: " << argv[0] << " [-a][-f FORMAT][-m MAGIC FILE][PATH(s)]...\n"
                 << "List information about the FILEs.\n"
                 << "Format optional. (DEFAULT: '%p %U %G %s %n')\n";
                 return 1;
            }
            fflag = 1;
            format = optarg;
            break;
        }
        default: /* '?' */
            cerr << argv[optind] << " is an invalid option.\n" << "Usage: " << argv[0] << " [-a][-f FORMAT][-m MAGIC FILE][PATH(s)]...\n"
                 << "List information about the FILEs.\n"
                 << "Format optional. (DEFAULT: '%p %U %G %s %n')\n";
            return 1;
        }
    }
    string s;
    for (int i = optind; i < argc; i++)
    {
        s = argv[i];
        if (s.find('%') != string::npos)
        {
            cerr << "Usage: " << argv[0] << " [-a][-f FORMAT][-m MAGIC FILE][PATH(s)]...\n"
                 << "List information about the FILEs.\n"
                 << "Format optional. (DEFAULT: '%p %U %G %s %n')\n";
                 return 1;
        }
        recurse_directory(argv[0], format, mediafile, s, aflag);
    }
    return 0;
}
