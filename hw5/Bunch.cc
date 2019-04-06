#include "Bunch.h"
using namespace std;
Bunch::Bunch()
{
    throw "No path provided for Bunch. Exiting.";
}
Bunch::Bunch(const string path, const bool all)
{
    if (all)
    {
        a = 1;
    }
    else
    {
        a = 0;
    }
    p = path;
    recurse_directory(p, a);
}
Bunch::~Bunch()
{
}
Bunch::Bunch(const Bunch &old)
{
    for (size_t i = 0; i < old.size(); i++)
    {
        files.push_back(old.entry(i));
    }
    p = old.p;
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
    recurse_directory(p, a);
}
void Bunch::all(const bool all)
{
    if (all == true)
    {
        a = 1;
    }
    files.clear();
    recurse_directory(p, a);
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
Fing Bunch::entry(const size_t n) const
{
    if (files.size() <= n)
    {
        string err = "Index out of bounds! n: ";
        err += to_string(n);
        err += ", Max index: ";
        err += to_string(files.size() - 1);
        throw err;
    }
    Fing f = files[n];
    return f;
}
void Bunch::recurse_directory(string path, int aflag)
{
    //string s = format_output(format, mediafile, path, sb);
    Fing f(path);
    files.push_back(f);
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
        recurse_directory(r, aflag);
    }
    closedir(dir);
    return;
}
