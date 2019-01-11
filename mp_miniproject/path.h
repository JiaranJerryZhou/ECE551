#ifndef __PATH_H__
#define __PATH_H__
#include <string>
#include <vector>

class path
{
 private:
  std::vector<std::string> paths;
  std::string envPath;

 public:
  /*
   * This default constructor call getPath() to get the environment path
   * and put it in envPath, then call parse(envPath) to split all paths
   */
  path() {
    envPath = getPath();
    parse(envPath);
  };
  /*
   * This function takes in the environment path and split it
   * into a vector of paths
   */
  void parse(const std::string & path);
  /*
   * This function get the environment path from "PATH", and put it in envPath
   */
  std::string getPath();
  /*
   * This function take in a command, search it in the environment path
   * If hit, it will return true, and change command into the full path
   */
  bool search(std::string & command);
  ~path(){};
};

#endif
