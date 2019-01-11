#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void check(const std::pair<size_t, std::string> & currfile,
           std::unordered_map<size_t, std::string> & table) {
  std::unordered_map<size_t, std::string>::iterator it = table.find(currfile.first);
  if (it == table.end()) {
    table.insert(currfile);
  }
  else {
    std::cout << "#Removing " << currfile.second << " (duplicate of " << it->second << ")."
              << std::endl;
    std::cout << "rm " << currfile.second << std::endl;
  }
}

void directSearch(std::unordered_map<size_t, std::string> & table, const std::string & dir) {
  DIR * currDir;
  struct dirent * entry;
  //step1: open directory
  currDir = opendir(dir.c_str());
  if (!currDir) {
    perror("cannot open directory\n");
    closedir(currDir);
    exit(EXIT_FAILURE);
  }
  //step2: read directory
  while ((entry = readdir(currDir)) != NULL) {
    std::string fileName(entry->d_name);
    if (fileName == "." || fileName == "..") {
      continue;
    }
    //if entry is directory, recurse on it
    else if (entry->d_type == DT_DIR) {
      std::string path = dir + "/" + fileName;
      directSearch(table, path);
    }
    //if entry is file, hash it and compare with other files
    else if (entry->d_type == DT_REG) {
      std::string path = dir + "/" + fileName;
      std::ifstream file(path.c_str());
      if (!file.good()) {
        perror("cannot open file\n");
        exit(EXIT_FAILURE);
      }
      std::hash<std::string> str_hash;
      size_t h;
      std::string content;
      std::string line;
      while (!file.eof()) {
        getline(file, line);
        content.append(line);
      }
      h = str_hash(content);
      //create a pair of hash and filename
      std::pair<size_t, std::string> hashToFile(h, path);
      check(hashToFile, table);
    }
    else {
      std::cerr << "unknown type of file\n" << std::endl;
    }
  }
  //step3: close directory
  closedir(currDir);
}

int main(int argc, char ** argv) {
  if (argc < 2) {
    perror("Usage:./dedup directory\n");
    exit(EXIT_FAILURE);
  }
  std::cout << "#!/bin/bash" << std::endl;
  //initialize a hash table
  std::unordered_map<size_t, std::string> hashTable;
  for (int i = 1; i < argc; i++) {
    const std::string dir = argv[i];
    directSearch(hashTable, dir);
  }
  return EXIT_SUCCESS;
}
