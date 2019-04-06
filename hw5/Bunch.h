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
  Fing();
  Fing(std::string path);
  Fing(const Fing &old);
  Fing operator=(const Fing &old);
  ~Fing();
  std::string path() const;
  Dual perms() const;
  Dual mtime() const;
  Dual atime() const;
  Dual ctime() const;
  size_t size() const;
  Dual uid() const;
  Dual gid() const;

private:
  struct stat sb;
  std::string p;
};
class Bunch
{
private:
  std::string p;
  int a;
  std::vector<Fing> files;
  void recurse_directory(std::string path, int a);

public:
  Bunch();
  Bunch(const std::string path, const bool all = false);
  ~Bunch();
  Bunch(const Bunch &old);
  Bunch operator=(const Bunch &old);
  void path(const std::string path);
  void all(const bool all);
  size_t size() const;
  bool empty() const;
  Fing entry(size_t n) const;
};
#endif