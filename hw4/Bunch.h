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
class Bunch
{
private:
  std::string p, m, f;
  int a;
  std::vector<std::string> files;
  std::string get_file_permissions(struct stat sb);
  char *get_modified_time(struct stat sb);
  char *get_access_time(struct stat sb);
  char *get_change_time(struct stat sb);
  int get_size(struct stat sb);
  int get_user_id(struct stat sb);
  char *get_user_name(struct stat sb);
  int get_group_id(struct stat sb);
  char *get_group_name(struct stat sb);
  std::ifstream read_media_ref(std::string ref_path);
  std::string get_media_type(std::string mediaFile, std::string path, struct stat sb);
  std::string format_output(std::string format, std::string magivNumberFile, std::string path, struct stat sb);
  void recurse_directory(std::string format, std::string mediafile, std::string path, int a);

public:
  Bunch();
  Bunch(const std::string path, const std::string magic = "", const std::string format = "%p %U %G %s %n", const bool all = false);
  ~Bunch();
  Bunch(const Bunch &old);
  Bunch operator=(const Bunch &old);
  void path(const std::string path);
  void magic(const std::string magic);
  void format(const std::string format);
  void all(const bool all);
  size_t size() const;
  bool empty() const;
  std::string entry(const size_t n) const;
};
#endif