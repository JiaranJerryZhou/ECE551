#include "path.h"

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string path::getPath() {
  char * path = getenv("ECE551PATH");
  std::string envPath(path);
  return envPath;
}

/*
 * This function takes in the environment path and parse it
 */
void path::parse(const std::string & path) {
  std::string currPath;
  std::istringstream ss(path);
  while (std::getline(ss, currPath, ':')) {
    paths.push_back(currPath);
  }
}

/*
 * This function takes in a command, search it in the environment path
 */

bool path::search(std::string & command) {
  DIR * currdir;
  struct dirent * entry;
  bool find = false;
  // if the command is full path
  if (command.find('/') != std::string::npos) {
    std::ifstream file(command.c_str());
    if (file.good()) {
      find = true;
    }
  }
  // if the command is not full path, we should find in environment path
  else {
    for (size_t i = 0; i < paths.size(); i++) {
      // step1: open directory
      currdir = opendir(paths[i].c_str());
      if (!currdir) {
        perror("cannot open directory\n");
        closedir(currdir);
        return false;
      }
      // step2: read directory
      while ((entry = readdir(currdir)) != NULL) {
        std::string filename(entry->d_name);
        if (command == filename) {
          find = true;
          std::string fullPath = paths[i] + "/" + command;
          command = fullPath;
        }
      }
      // step3: close directory
      closedir(currdir);
    }
  }
  return find;
}
