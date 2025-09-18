#include <iostream>
#include <fstream>

bool is(char* first, const char* second) {
  int ind = 0;
  bool flag = true;
  while (first[ind] != '\0' && second[ind] != '\0') {
    if (first[ind] != second[ind]) {
      flag = false;
    }
    ind++;
  }
  return flag && first[ind] == '\0' && second[ind] == '\0';
}
int main(int argc, char** argv) {
    char* word;
    char* file_name;
    const char* word_arg = "--word";
    const char* file_arg = "--file";
    if (argc != 5) {
      std::cout << "ERR\n";
      return -1;
    }
    for (int i = 1; i < 5; i++) {
      char* arg = argv[i];
      if (is(arg, word_arg)) {
        word = argv[++i];
      }
      else if (is(arg, file_arg)) {
        file_name = argv[++i];
      }
      else {
        std::cout << "ERR";
        return -1;
      }
    }
    //std::cout << word << " " << file_name << '\n';

    std::fstream file(file_name, std::ios::in);
    int count = 0;
    if (file.is_open()) {
      while (!file.eof()) {
        char c;
        file.get(c);
        bool matches[32];
        for (int i = 0; i < 32; i++) {
          matches[i] = false;
        }
        while (!(c == ' ' || c == '\n')) {
          int ind = 0;
          while (word[ind] != '\0') {
            if (c == word[ind]) {
              matches[ind] = true;
            }
            ind++;
          }
          file.get(c);
        }
        int ind = 0;
        bool flag = true;
        while (word[ind] != '\0') {
          flag = flag && matches[ind];
          ind++;
        }
        if (flag) {
          count++;
        }
      }
      std::cout << count;

    }
    else {
      std::cout << "ERR";
      return -1;
    }



    

}
