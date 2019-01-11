#include "myShell.h"

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

/*
 * This function initialize the vars field with environ
 */
void myShell::vars_init() {
  setenv("ECE551PATH", getenv("PATH"), 1);
  char ** env = environ;
  while (*env != NULL) {
    std::string line(*env);
    size_t len = line.find('=', 0);
    std::string key = line.substr(0, len);
    char * value = getenv(key.c_str());
    std::pair<std::string, std::string> var(key, std::string(value));
    vars.insert(var);
    env++;
  }
}
/*
 * This function check if the command is our designed command
 * If one of them, run it
 */
bool myShell::myCommand(command & command, std::map<std::string, std::string> & vars) {
  std::vector<std::string> & currCmd = command.getVector();
  // handle cd
  if (currCmd[0] == "cd") {
    command.run_cd();
    return true;
  }
  // handle set
  else if (currCmd[0] == "set") {
    command.parseSet();
    command.key2var(vars, command.getSet());
    command.run_set(vars);
    return true;
  }
  else if (currCmd[0] == "export") {
    command.run_export(vars);
    return true;
  }
  else if (currCmd[0] == "inc") {
    command.run_inc(vars);
    return true;
  }
  return false;
}

/*
 * This function run the shell with the provided env
 */
void myShell::run() {
  while (true) {
    char * currDir = getenv("PWD");
    std::cout << "myShell:" << currDir << "$ ";
    std::string line;
    std::getline(std::cin, line);
    // instanciate a command class with input line
    command currCmd(line);
    // parse the input into a vector
    currCmd.parse();
    // change each variable name to value if there is '$'
    std::vector<std::string> & vecArgv = currCmd.getVector();
    currCmd.key2var(vars, vecArgv);
    // handle EOF
    if (std::cin.eof()) {
      return;
    }
    // if empty input, do nothing
    if ((vecArgv.size() == 0) || (vecArgv[0].size() == 0)) {
      continue;
    }
    // handle exit
    if (currCmd.isexit()) {
      return;
    }
    if (myCommand(currCmd, vars)) {
      continue;
    }
    path envPath;
    // can not find executable file
    if (!envPath.search(vecArgv[0])) {
      std::cout << "Command " << vecArgv[0] << " not found" << std::endl;
      continue;
    }
    // non-executable file
    if (access(vecArgv[0].c_str(), X_OK)) {
      std::cout << "permission denied" << std::endl;
      continue;
    }
    // get the cmd and argv from the parsed input
    char ** argv = currCmd.vec2argv(vecArgv);
    char * cmd = argv[0];
    pid_t fork_result = fork();
    if (fork_result == -1) {
      perror("cannot fork\n");
      continue;
    }
    // execute the child when executing another program in myShell
    else if (fork_result == 0) {
      int exe = execve(cmd, argv, environ);
      if (exe == -1) {
        perror("cannot execute the input\n");
        exit(EXIT_FAILURE);
      }
    }
    // return to parent after child has been executed
    else {
      int wstatus;
      pid_t w;
      w = waitpid(fork_result, &wstatus, 0);
      if (w == -1) {
        perror("waitpid\n");
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(wstatus)) {
        std::cout << "Program exited with status " << WEXITSTATUS(wstatus) << std::endl;
      }
      else if (WIFSIGNALED(wstatus)) {
        std::cout << "Program was killed by signal " << WTERMSIG(wstatus) << std::endl;
      }
    }
    // free the momery allocated to argv
    for (size_t i = 0; i < vecArgv.size(); i++) {
      delete[] argv[i];
    }
    delete[] argv;
  }
}

int main(int argc, char ** argv, char ** envp) {
  if (argc != 1) {
    perror("Usage: ./myShell\n");
    exit(EXIT_FAILURE);
  }
  myShell shell;
  shell.vars_init();
  shell.run();
  return EXIT_SUCCESS;
}
