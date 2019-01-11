#ifndef __COMMAND_H__
#define __COMMAND_H__

#include <map>
#include <string>
#include <vector>
class command
{
 private:
  const std::string input;
  std::vector<std::string> argv;
  std::vector<std::string> setArgv;

 public:
  command() : input(NULL){};

  /*
   * This function is called when the command is cd
   * It will change the work directory if cd command is valid
   */
  void run_cd();

  /*
   * This function is called in the run_set function
   * It parses the input to handle the set command
   */
  void parseSet();

  /*
   * This function is called when the command is set
   * It will reparse the input
   * Check if the variable is valid
   * Put its value in vars
   */
  void run_set(std::map<std::string, std::string> & vars);

  /*
   * This function is called when the command is export
   * It will evaluate the variable, then add it to env
   */
  void run_export(std::map<std::string, std::string> & vars);

  /*
   * This function is called when the command is inc
   * It will check the value if its a number and increase it by 1
   * Or it will change it to 1
   */
  void run_inc(std::map<std::string, std::string> & vars);

  /*
   * This function check if the input variable name is valid
   */
  bool isvalid(std::string value);
  /*
   * This function provide access to variables
   * If user input a name of a variable after '$', the value is output
   * We can also concatenate sevaral variables or invalid characters
   */
  void key2var(std::map<std::string, std::string> & vars, std::vector<std::string> & Argv);

  /*
   * This constructor takes in the user input and store it in a string
   */
  command(std::string usrInput) : input(usrInput){};

  ~command(){};

  /*
   * This function returns true if the user input is "exit"
   */
  bool isexit();

  /*
   * This function split the input line into an array of strings
   * The input line is splited by space
   * But the space after an escape character is also a part of argument
   */
  void parse();

  /*
   * This function returns the characters of input string
   * Can be used for debug
   */
  char * getcmd() { return (char *)input.c_str(); }

  /*
   * This function returns the vector of arguments
   */
  std::vector<std::string> & getVector() { return argv; }
  std::vector<std::string> & getSet() { return setArgv; }
  /*
   * This function converts the vector of strings into char**
   */
  char ** vec2argv(std::vector<std::string> vecArgv);
};

#endif
