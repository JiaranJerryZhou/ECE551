#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
int main(int argc, char ** argv) {
  vector<string> vec;
  string current;
  int count = 0;
  if (argc == 1) {
    //int count = 0;
    //string current = NULL;
    while (getline(cin, current)) {
      //getline(cin, current);
      vec.push_back(current);
      count++;
    }
    sort(vec.begin(), vec.end());
    for (size_t i = 0; i < vec.size(); i++) {
      cout << vec[i] << endl;
    }
  }
  else {
    for (int i = 1; i < argc; i++) {
      ifstream currFile;
      count = 0;
      vec.clear();
      currFile.open(argv[i]);
      if (!currFile) {
        cerr << "Unable to open file" << endl;
        exit(EXIT_FAILURE);
      }
      while (getline(currFile, current)) {
        //getline(currFile, current);
        vec.push_back(current);
        count++;
      }
      sort(vec.begin(), vec.end());
      for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << endl;
      }
      currFile.close();
    }
  }
  return EXIT_SUCCESS;
}
