#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

int main() {
  fstream file_;

  file_.open("test.txt", ios::out);

  if(file_.is_open()) {
    file_ << "john deer";
  };

  file_.close();
  cin.get();
  
  return 0;
}