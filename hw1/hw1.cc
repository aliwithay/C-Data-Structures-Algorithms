#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
int main(int argc, char *argv[])
{
    struct stat sb;
    if (argc == 1)
    {
        cerr << "No path provided.\n";
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        int result = lstat(argv[i], &sb);
        if (result != 0)
        {
            cerr << "Error on path " << argv[i] << ".\n";
            return 1;
        }
        switch (sb.st_mode & S_IFMT)
        {
        case S_IFIFO:
            cout << argv[i] << " is a FIFO.\n";
            continue;
        case S_IFSOCK:
            cout << argv[i] << " is a socket.\n";
            continue;
        case S_IFREG:
            cout << "-";
            break;
        case S_IFDIR:
            cout << "d";
            break;
        case S_IFLNK:
            cout << "l";
            break;
        }
        switch ((sb.st_mode & S_IRWXU) >> 6)
        {
        case 7:
            cout << "rwx";
            break;
        case 6:
            cout << "rw-";
            break;
        case 5:
            cout << "r-x";
            break;
        case 4:
            cout << "r--";
            break;
        case 3:
            cout << "-wx";
            break;
        case 2:
            cout << "-w-";
            break;
        case 1:
            cout << "--x";
            break;
        case 0:
            cout << "---";
            break;
        }
        switch ((sb.st_mode & S_IRWXG) >> 3)
        {
        case 7:
            cout << "rwx";
            break;
        case 6:
            cout << "rw-";
            break;
        case 5:
            cout << "r-x";
            break;
        case 4:
            cout << "r--";
            break;
        case 3:
            cout << "-wx";
            break;
        case 2:
            cout << "-w-";
            break;
        case 1:
            cout << "--x";
            break;
        default:
            cout << "---";
            break;
        }
        switch (sb.st_mode & S_IRWXO)
        {
        case 7:
            cout << "rwx";
            break;
        case 6:
            cout << "rw-";
            break;
        case 5:
            cout << "r-x";
            break;
        case 4:
            cout << "r--";
            break;
        case 3:
            cout << "-wx";
            break;
        case 2:
            cout << "-w-";
            break;
        case 1:
            cout << "--x";
            break;
        default:
            cout << "---";
            break;
        }
        auto timevals = localtime(&sb.st_mtime);
        char buf[32];
        strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
        cout << " " << sb.st_size << " " << buf << " " << argv[i] << "\n";
    }
    return 0;
}
