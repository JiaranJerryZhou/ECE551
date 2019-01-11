#include "command.h"

#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
/*
 * This function judges if the command is exit and return true
 */
bool command::isexit() {
  if (argv[0] == "exit") {
    return true;
  }
  else {
    return false;
  }
}

/*
 * This function takes in a variable name,
 * Check if it is valid
 */
bool command::isvalid(std::string value) {
  for (size_t i = 0; i < value.length(); i++) {
    if ((isalnum(value[i]) != 0) || (value[i] == '_')) {
      continue;
    }
    else {
      return false;
    }
  }
  return true;
}

/*
 * This function is called to parse the input again when the command is set
 */
void command::parseSet() {
  std::string currArgv;
  size_t ind = 0;
  while (ind < input.length()) {
    // if the first two argv
    if (setArgv.size() < 2) {
      // if ' '
      if (input[ind] == ' ') {
        // if the first ' ' after non-space character
        // if there are two ' ' after a '\'
        if ((ind > 0 && input[ind - 1] != ' ') || (ind > 1 && input[ind - 2] == '\\')) {
          setArgv.push_back(currArgv);
          currArgv.erase();
        }
        //skip all other ' '
        ind++;
      }
      // if '\'
      else if (input[ind] == '\\') {
        // if '\' is at the end of input
        if (ind == input.length() - 1) {
          return;
        }
        ind++;
        currArgv.push_back(input[ind]);
        ind++;
        if (ind >= input.length()) {
          setArgv.push_back(currArgv);
          currArgv.erase();
        }
      }
      // if other character
      else {
        currArgv.push_back(input[ind]);
        // if already at the end of input
        if (ind == input.length() - 1) {
          setArgv.push_back(currArgv);
          currArgv.erase();
        }
        ind++;
      }
    }
    // if the third argv
    else {
      // find the first char not space
      size_t pos = input.find_first_not_of(' ', ind);
      if (pos == std::string::npos) {
        return;
      }
      else {
        while (pos < input.length()) {
          // skip all escape signs
          if (input[pos] == '\\') {
            pos++;
          }
          else {
            currArgv.push_back(input[pos]);
            pos++;
          }
        }
        if (currArgv.size() > 0) {
          setArgv.push_back(currArgv);
        }
        currArgv.erase();
        return;
      }
    }
  }
}

/*
 * This function set the value of the key to the vars
 */
void command::run_set(std::map<std::string, std::string> & vars) {
  // if the input have less than 3 argvs
  if (setArgv.size() != 3) {
    std::cout << "Usage: set $var value\n";
  }
  else {
    std::string key = setArgv[1];
    std::map<std::string, std::string>::iterator it = vars.find(key);
    // if the variable is already in the vars
    if (it != vars.end()) {
      it->second = setArgv[2];
    }
    else {
      std::pair<std::string, std::string> var(setArgv[1], setArgv[2]);
      vars.insert(var);
    }
  }
}

/*
 * This function export the variable to env
 */
void command::run_export(std::map<std::string, std::string> & vars) {
  if (argv.size() != 2) {
    std::cout << "Usage: export $var\n";
  }
  else {
    std::string key = argv[1];
    std::map<std::string, std::string>::iterator it = vars.find(key);
    // find the name in our vars map
    if (it != vars.end()) {
      std::string value = it->second;
      int result = setenv(key.c_str(), value.c_str(), 1);
      if (result == -1) {
        perror("export failure\n");
      }
    }
    // not find in the map
    else {
      std::cout << "No variable name: " << key << std::endl;
    }
  }
}

/*
 * This function increase one number by one
 */
std::string inc_by_1(std::string prev) {
  std::string ans;
  int num = atoi(prev.c_str()) + 1;
  // if it is a negative integer
  if (num < 0) {
    ans = '-' + ans;
  }
  num = abs(num);
  if (num == 0) {
    ans = ans + '0';
  }
  while (num > 0) {
    char digit = (num % 10) + '0';
    num = num / 10;
    ans = ans + digit;
  }
  return ans;
}

/*
 * This function is called in run_inc
 * It checks if a string is a valid number
 */
bool is_number(std::string str) {
  // if it is an empty string
  if (str.size() == 0) {
    return false;
  }
  // if there is only a '-'
  else if ((str[0] == '-') && str.size() == 1) {
    return false;
  }
  // if the first character is not number and '-'
  else if ((str[0] != '-') && (!isdigit(str[0]))) {
    return false;
  }
  else {
    for (size_t i = 1; i < str.size(); i++) {
      if (!isdigit(str[i])) {
        return false;
      }
    }
    return true;
  }
}
/*
 * This function increase the variable's value by 1
 */
void command::run_inc(std::map<std::string, std::string> & vars) {
  if (argv.size() != 2) {
    perror("Usage: inc &var\n");
  }
  else {
    std::string key = argv[1];
    std::map<std::string, std::string>::iterator it = vars.find(key);
    // not find the name in the map
    // we need to set its value to 1
    if (it == vars.end()) {
      std::pair<std::string, std::string> var(key, "1");
      vars.insert(var);
    }
    else {
      // if the value is a number
      if (is_number(it->second)) {
        it->second = inc_by_1(it->second);
      }
      // if the value is not a number
      else {
        it->second = "1";
      }
    }
  }
}

/*
 * This function returns the value of the input variable name 
 */
void command::key2var(std::map<std::string, std::string> & vars, std::vector<std::string> & Argv) {
  for (size_t i = 0; i < Argv.size(); i++) {
    std::string output;
    std::string currVar;
    std::string currArgv = Argv[i];
    size_t ind = 0;
    while (ind != currArgv.length()) {
      // where there is a variable, start to count
      if (currArgv[ind] == '$') {
        // check if the '$' should be take as a character
        if ((ind == 1 && currArgv[ind - 1] == '$') || (ind == currArgv.length() - 1) ||
            (ind > 1 && currArgv[ind - 1] == '$' && currArgv[ind - 2] != '$')) {
          output.push_back(currArgv[ind]);
          ind++;
        }
        else {
          size_t start = ind + 1;
          size_t end = start;
          // if the variable name keeps valid
          while ((isvalid(currArgv.substr(start, end - start + 1))) && (end < currArgv.length())) {
            end++;
          }
          std::string key = currArgv.substr(start, end - start);
          std::map<std::string, std::string>::iterator it = vars.find(key);
          // if it is found in the map, return its value
          if (it != vars.end()) {
            currVar = it->second;
          }
          else {
            currVar = "";
          }
          ind = end;
          // put the value in the output
          output.append(currVar);
          currVar.erase();
        }
      }
      // other invalid input such as '-', just append to the output
      else {
        output.push_back(currArgv[ind]);
        ind++;
      }
    }
    Argv[i] = output;
  }
}

/*
 * This function check if the cd command is valid
 * Then change the work directory
 */
void command::run_cd() {
  if (argv.size() > 2) {
    std::cout << "Usage: cd directory" << std::endl;
  }
  else if (argv.size() == 2) {
    if (chdir(argv[1].c_str()) != 0) {
      std::cout << "cannot enter directory\n" << std::endl;
    }
  }
  // cd
  else {
    if (chdir(getenv("HOME")) != 0) {
      perror("cannot enter directory\n");
    }
  }
  // set the current directory to old one
  // then change the work directory
  setenv("OLDPWD", getenv("PWD"), 1);
  char cwd[CHAR_MAX];
  getcwd(cwd, CHAR_MAX);
  setenv("PWD", cwd, 1);
}

/*
 * This function convert argv from vector<string> to char **
 */
char ** command::vec2argv(std::vector<std::string> vecArgv) {
  char ** argv = new char *[vecArgv.size() + 1];
  for (size_t i = 0; i < vecArgv.size(); i++) {
    argv[i] = new char[vecArgv[i].size() + 1];
    argv[i] = std::strncpy(argv[i], vecArgv[i].c_str(), vecArgv[i].size() + 1);
  }
  // set the last argv to NULL
  argv[vecArgv.size()] = NULL;
  return argv;
}

/*
 * This function parse the input command into arguments
 */
void command::parse() {
  std::string currArgv;
  size_t ind = 0;
  while (ind < input.length()) {
    // if ' '
    if (input[ind] == ' ') {
      // if the first ' ' after non-space character
      // if there are two ' ' after a '\'
      if ((ind > 0 && input[ind - 1] != ' ') ||
          (ind > 1 && input[ind - 1] == ' ' && input[ind - 2] == '\\')) {
        argv.push_back(currArgv);
        currArgv.erase();
      }
      //skip all other ' '
      ind++;
    }
    // if '\'
    else if (input[ind] == '\\') {
      // if '\' is at the end of input
      if (ind == input.length() - 1) {
        std::cout << "no character to escape\n";
        return;
      }
      ind++;
      currArgv.push_back(input[ind]);
      ind++;
      if (ind >= input.length()) {
        argv.push_back(currArgv);
        currArgv.erase();
      }
    }
    // if other character
    else {
      currArgv.push_back(input[ind]);
      // if already at the end of input
      if (ind == input.length() - 1) {
        argv.push_back(currArgv);
        currArgv.erase();
      }
      ind++;
    }
  }
}
