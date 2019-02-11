#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
void get_file_type(struct stat sb, string &permissions)
{
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
}
void get_file_permissions(struct stat sb, string &permissions)
{
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
    //Get time in epoch seconds and convert to readable time.
    auto timevals = localtime(&sb.st_ctime);
    static char buf[32];
    //Format time in required form and store in buf.
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
    return buf;
}
void get_size(struct stat sb, int &size)
{
    size = sb.st_size;
}
void read_media_type_ref()
{
    /*
    ifstream fRef("~/CS253/hw2/media-types");
    if(!fRef.is_open())
    {
	cout << "Cannot open reference file!\n";
	return;
    }
    string str;
    while (getline(fRef, str))
    {
	for (size_t i = 0; i < str.size(); i++)
	{
	    cout << str[i];
	}
        cout << "\n";
    }
    return;
    //getline(fRef, str);
    */
}
int main()
{
    /*
    int argc, char *argv[]
    struct stat sb;
    //Produce usage error if no path provided.
    if (argc == 1)
    {
        cerr << "Usage: " << argv[0] << " [FILE]...\n"
             << "List information about the FILEs. \n";
        return 1;
    }
    //Loop through all paths provided.
    for (int i = 1; i < argc; i++)
    {
        //run lstat and store information in sb.
        int result = lstat(argv[i], &sb);
        //check if lstat returned error.
        if (result != 0)
        {
            cerr << argv[0] << " encounterd an error on path " << argv[i] << ".\n";
            continue;
        }
        //Determine file type and generate error for undefined files.
        //Determine first bit of permissions.
        string type;
        get_file_type(sb, type);
        //Determine USER permissions.
        string permissions;
        get_file_permissions(sb, permissions);
        //Get the time for last modification.
        auto time = get_modified_time(sb);
        //Determine file size.
        int size;
        get_size(sb, size);
        //Print final output string with size, time and path.
        cout << type << permissions << " " << size << " " << time << " " << argv[i] << "\n";
    }
    */
    cout << "run\n";
    read_media_type_ref();
    return 0;
}
