#include <iostream>
#include <vector>
using namespace std;

int main(){
 std:: vector<std::string> v;
 for (int i = 0; i<10; i++){
     std::string s;
     std::cin>>s;
     v.push_back(s);
 }
 for (int i=0; i<v.size(); i++){
     std::cout<<v[i]<<endl;
 }

}