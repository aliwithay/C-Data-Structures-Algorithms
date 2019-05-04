#ifndef BUNCH
#define BUNCH
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
#include <vector>
//The code for Dual class was copied from lecture on proxy objects
//Credits: Jack Applin
class Dual
{
  const uint u;
  const std::string s;

public:
  Dual(uint uu, const std::string &ss) : u(uu), s(ss) {}
  operator uint() const { return u; }
  operator std::string() const { return s; }
};
class Fing
{
public:
  //Fing();
  //Fing(const std::string &path);
  //Fing(const Fing &old);
  //Fing operator=(const Fing &old);
  virtual ~Fing();
  virtual std::string type() const = 0;
  std::string path() const;
  Dual perms() const;
  Dual mtime() const;
  Dual atime() const;
  Dual ctime() const;
  size_t size() const;
  Dual uid() const;
  Dual gid() const;
  bool operator==(const Fing &ofing) const;

protected:
  struct stat sb;
  std::string p;
};
class Regular : public Fing
{
public:
  Regular();
  Regular(const std::string &path);
  Regular(const Regular &old);
  Regular operator=(const Regular &old);
  ~Regular();
  std::string type() const
  {
    return "Regular";
  }
};
class Directory : public Fing
{
public:
  Directory();
  Directory(const std::string &path);
  Directory(const Directory &old);
  Directory operator=(const Directory &old);
  ~Directory();
  std::string type() const
  {
    return "Directory";
  }
};
class Symlink : public Fing
{
public:
  Symlink();
  Symlink(const std::string &path);
  Symlink(const Symlink &old);
  Symlink operator=(const Symlink &old);
  ~Symlink();
  std::string type() const
  {
    return "Symlink";
  }
};
class Bunch
{
private:
  std::string p;
  int a;
  std::vector<const Fing *> files;
  void recurse_directory(std::string path, int a);

public:
  Bunch();
  Bunch(const std::string &path);
  ~Bunch();
  Bunch(const Bunch &old);
  Bunch operator=(const Bunch &old);
  void path(const std::string &path);
  size_t size() const;
  bool empty() const;
  const Fing *entry(size_t n) const;
  bool operator==(const Bunch &obunch) const;
  bool operator!=(const Bunch &obunch) const;
  Bunch operator+(const Bunch &obunch) const;
  Bunch operator-(const Bunch &obunch) const;
  Bunch operator+=(const Bunch &obunch);
  Bunch operator-=(const Bunch &obunch);
  operator bool() const;
  class iterator
  {
  public:
    iterator() : base(nullptr), index(0) {}
    iterator(const Bunch *b, uint i = 0) : base(b), index(i) {}
    iterator(const iterator &io) : base(io.base), index(io.index) {}
    iterator operator=(const iterator &io)
    {
      iterator i(io.base, io.index);
      return i;
    }
    iterator &operator++()
    {
      index++;
      return *this;
    }
    iterator operator++(int)
    {
      iterator i(this->base, index++);
      return i;
    }
    iterator &operator--()
    {
      index--;
      return *this;
    }
    iterator operator--(int)
    {
      iterator i(this->base, index--);
      return i;
    }
    const Fing *operator*() const
    {
      return base->files[index];
    }
    bool operator==(const Bunch::iterator &io) const
    {
      if (*(base->files[index]) == *(io.base->files[index]))
      {
        return true;
      }
      return false;
    }
    bool operator!=(const Bunch::iterator &io) const
    {
      if (*(base->files[index]) == *(io.base->files[index]))
      {
        return false;
      }
      return true;
    }

  private:
    const Bunch *base;
    uint index;
  };
  iterator begin() const;
  iterator end() const;
};
#endif