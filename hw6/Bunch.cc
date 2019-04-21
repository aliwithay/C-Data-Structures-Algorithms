#include "Bunch.h"
using namespace std;
Bunch::Bunch()
{
    throw "No path provided for Bunch. Exiting."s;
}
Bunch::Bunch(const string &path)
{
    a = 0;
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
        files.push_back(old.files[i]);
    }
    p = old.p;
    a = old.a;
}
Bunch Bunch::operator=(const Bunch &old)
{
    files.clear();
    for (size_t i = 0; i < old.size(); i++)
    {
        files.push_back(old.files[i]);
    }
    p = old.p;
    a = old.a;
    return *this;
}
void Bunch::path(const string &path)
{
    p = path;
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
const Fing *Bunch::entry(size_t n) const
{
    if (files.size() <= n)
    {
        string err = "Index out of bounds! n: ";
        err += to_string(n);
        err += ", Max index: ";
        err += to_string(files.size() - 1);
        throw err;
    }
    return &files[n];
}
bool Bunch::operator==(const Bunch &obunch) const
{
    if (files.size() != obunch.files.size())
    {
        return false;
    }
    for (Fing f : files)
    {
        bool match = false;
        for (Fing g : obunch.files)
        {
            if (f == g)
            {
                match = true;
            }
        }
        if (!match)
        {
            return false;
        }
    }
    return true;
}
bool Bunch::operator!=(const Bunch &obunch) const
{
    if (files.size() != obunch.files.size())
    {
        return true;
    }
    for (Fing f : files)
    {
        bool match = false;
        for (Fing g : obunch.files)
        {
            if (f == g)
            {
                match = true;
            }
        }
        if (!match)
        {
            return true;
        }
    }
    return false;
}
Bunch Bunch::operator+(const Bunch &obunch) const
{
    Bunch b(p);
    for (Fing f : obunch.files)
    {
        bool match = false;
        for (Fing g : b.files)
        {
            if (f == g)
            {
                match = true;
            }
        }
        if (!match)
        {
            b.files.push_back(f);
        }
    }
    return b;
}
Bunch Bunch::operator-(const Bunch &obunch) const
{
    Bunch b(p);
    b.files.clear();
    for (Fing f : files)
    {
        bool match = false;
        for (Fing g : obunch.files)
        {
            if (f == g)
            {
                match = true;
            }
        }
        if (!match)
        {
            b.files.push_back(f);
        }
    }
    return b;
}
Bunch Bunch::operator+=(const Bunch &obunch)
{
    for (Fing f : obunch.files)
    {
        bool match = false;
        for (Fing g : files)
        {
            if (f == g)
            {
                match = true;
            }
        }
        if (!match)
        {
            files.push_back(f);
        }
    }
    return *this;
}
Bunch Bunch::operator-=(const Bunch &obunch)
{
    for (uint i = 0; i < files.size(); i++)
    {
        bool match = false;
        for (Fing g : obunch.files)
        {
            if (files[i] == g)
            {
                match = true;
            }
        }
        if (match)
        {
            files.erase(files.begin() + i);
        }
    }
    return *this;
}
Bunch::operator bool() const
{
    if (files.size() == 0)
    {
        return false;
    }
    return true;
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
