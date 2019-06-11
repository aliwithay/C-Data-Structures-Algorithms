#include "Bunch.h"
using namespace std;
Bunch::Bunch()
{
    throw "No path provided for Bunch. Exiting."s;
    return;
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
    return files[n].get();
}
bool Bunch::operator==(const Bunch &obunch) const
{
    if (files.size() != obunch.files.size())
    {
        return false;
    }
    for (uint i = 0; i < files.size(); i++)
    {
        auto f = files[i].get();
        bool match = false;
        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j].get();
            if (*f == *g)
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
    for (uint i = 0; i < files.size(); i++)
    {
        auto f = files[i].get();
        bool match = false;
        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j].get();
            if (*f == *g)
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
    for (uint i = 0; i < obunch.files.size(); i++)
    {
        auto f = obunch.files[i];
        bool match = false;
        for (uint j = 0; j < b.files.size(); j++)
        {
            auto g = b.files[j];
            if (*(f.get()) == *(g.get()))
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
    for (uint i = 0; i < files.size(); i++)
    {
        auto f = files[i];
        bool match = false;
        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j];
            if (*f.get() == *g.get())
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
    for (uint i = 0; i < obunch.files.size(); i++)
    {
        auto f = obunch.files[i];
        bool match = false;
        for (uint j = 0; j < files.size(); j++)
        {
            auto g = files[j];
            if (*(f.get()) == *(g.get()))
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
        auto f = files[i].get();
        bool match = false;
        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j].get();
            if (*f == *g)
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
Bunch::iterator Bunch::begin() const
{
    return iterator(this);
}
Bunch::iterator Bunch::end() const
{
    return iterator(this, files.size());
}
void Bunch::recurse_directory(string path, int aflag)
{
    //string s = format_output(format, mediafile, path, sb);
    //Check for symlink or reglar
    struct stat sb;
    int result = lstat(path.c_str(), &sb);
    if (result != 0)
    {
        auto saveErr = errno;
        string err = "Could not open " + path + ". " + strerror(saveErr);
        throw err;
    }
    switch (sb.st_mode & S_IFMT)
    {
        case S_IFDIR:
        {
            files.push_back(shared_ptr<Directory> (new Directory(path)));
            break;
        }
        case S_IFLNK:
        {
            files.push_back(shared_ptr<Symlink> (new Symlink(path)));
            return;
        }
        case S_IFREG:
        {
            files.push_back(shared_ptr<Regular> (new Regular(path)));
            return;
        }
    }
    DIR *dir;
    dir = opendir(path.c_str());
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
