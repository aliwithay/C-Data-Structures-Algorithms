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
        auto timevals = localtime(&sb.st_mtime);
        char buf[32];
        strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%S", timevals);
	int permissions = (sb.st_mode & S_IRWXG);
        cout << permissions << " " << sb.st_size << " " << buf << " " << argv[i] << "\n";
    }
    return 0;
}
