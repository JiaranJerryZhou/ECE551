#ifndef __MYSHELL_H__
#define __MYSHELL_H__

#include "command.h"
#include "path.h"
class myShell
{
 private:
  std::map<std::string, std::string> vars;

 public:
  myShell(){};
  void run();
  bool myCommand(command & command, std::map<std::string, std::string> & vars);
  void vars_init();
  void run_cd();
  ~myShell(){};
};

#endif
