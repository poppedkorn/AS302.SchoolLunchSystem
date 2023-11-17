#include<iostream>
#include<fstream>
using namespace std;
int main() {

    ofstream file_;
    file_.open("test.txt");
    if(file_.is_open()) {
    file_ << "john deer";
    }
    // file_.close();
    // cin.get();
    
      return 0;
}