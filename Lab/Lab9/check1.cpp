#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <utility>
int main(int argc, char* argv[]){
    std::ifstream infile (argv[1]);
    std::map<int, int> m; 
    std::pair<int, int> pair;
    int num;
    int min;

    /*
    while (infile >> num){
        ++m[num];
    }

    min = m.begin()->second;
    std::map<int, int>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it){
        if (it->second > min){
        min = it->second;
        }
    }
    for (it = m.begin(); it!= m.end(); ++it){
        if (it->second == min){
            std::cout<<it->first<<"\t"<<it->second<<std::endl;
        }
    }
    */

   while (infile >> num){
        if (m.find(num)==m.end()){
            m.insert(std::make_pair(num, 1));
        }
        else{
            m.find(num)->second ++;
        }
    }

    min = m.begin()->second;
    std::map<int, int>::const_iterator it;
    for (it = m.begin(); it != m.end(); ++it){
        if (it->second > min){
        min = it->second;
        }
    }
    for (it = m.begin(); it!= m.end(); ++it){
        if (it->second == min){
            std::cout<<it->first<<"\t"<<it->second<<std::endl;
        }
    }


}