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
    sort();
}
Bunch::~Bunch()
{
    
}
Bunch::Bunch(const Bunch &old)
{
    p = old.p;
    a = 0;
    files = old.files;
    sort();
}
Bunch Bunch::operator=(const Bunch &old)
{
    files.clear();
    files = old.files;
    p = old.p;
    a = old.a;
    sort();
    return *this;
}
void Bunch::path(const string &path)
{
    p = path;
    files.clear();
    recurse_directory(p, a);
    sort();
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
    if (files == obunch.files) {
        return true;
    }
    uint fsize = files.size();
    uint osize = obunch.files.size();
    if (fsize != osize)
    {
        return false;
    }
    for (uint i = 0; i < fsize; i++)
    {
        auto f = files[i];
        bool match = false;
        for (uint j = 0; j <osize; j++)
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
    //return (files == obunch.files);
}
bool Bunch::operator!=(const Bunch &obunch) const
{
    if (files == obunch.files) {
        return false;
    }
    uint fsize = files.size();
    uint osize = obunch.files.size();
    if (fsize != osize)
    {
        return true;
    }
    for (uint i = 0; i < fsize; i++)
    {
        auto f = files[i].get();
        bool match = false;
        for (uint j = 0; j <osize; j++)
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
    //return (files != obunch.files);
}
Bunch Bunch::operator+(const Bunch &obunch) const
{
    Bunch b(*this);
    if (b.files == obunch.files) {
        return b;
    }
    for (uint i = 0; i < obunch.files.size(); i++)
    {
        auto f = obunch.files[i];
        bool match = false; //binary_search(files.begin(), files.end(), f, sortFings);
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
    b.sort();
    return b;
}
Bunch Bunch::operator-(const Bunch &obunch) const
{
    Bunch b(*this);
    if (b.files == obunch.files) {
        b.files.clear();
        return b;
    }
    for (uint i = 0; i < b.files.size(); i++)
    {
        auto f = b.files[i];
        bool match = false; //binary_search(obunch.files.begin(), obunch.files.end(), f, sortFings);
        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j];
            if (*f.get() == *g.get())
            {
                match = true;
            }
        }
        if (match)
        {
            b.files.erase(b.files.begin() + i);
            i--;
        }
    }
    b.sort();
    return b;
}
Bunch Bunch::operator+=(const Bunch &obunch)
{
    if (files == obunch.files) {
        return *this;
    }
    for (uint i = 0; i < obunch.files.size(); i++)
    {
        auto f = obunch.files[i];
        bool match = false; // binary_search(files.begin(), files.end(), f, sortFings);
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
    sort();
    return *this;
}
Bunch Bunch::operator-=(const Bunch &obunch)
{
    if (files == obunch.files) {
        files.clear();
        return *this;
    }
    for (uint i = 0; i < files.size(); i++)
    {
        auto f = files[i];
        bool match = false; // binary_search(obunch.files.begin(), obunch.files.end(), f, sortFings);

        for (uint j = 0; j < obunch.files.size(); j++)
        {
            auto g = obunch.files[j].get();
            if (*f.get() == *g)
            {
                match = true;
            }
        }
        if (match)
        {
            files.erase(files.begin() + i);
            i--;
        }
    }
    sort();
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
bool Bunch::sortFings (const shared_ptr<Fing> &lf, const shared_ptr<Fing> &rf)
{
    return (*lf.get() < *rf.get());
}
void Bunch::sort() {
    std::sort(files.begin(), files.end(), sortFings);
}
