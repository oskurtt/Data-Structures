#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
    map<string, vector<string>> map;
    vector<string> v = {"b", "a", "c"};
    map["anna"] = v;
    map<vector<string>::iterator it = map["anna"];
}