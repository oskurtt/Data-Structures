#include <iostream>
#include <string>
#include <cmath> 
#include <cstdlib>
#include <fstream>
#include <vector>

std::vector<std::vector<std::string>> replace(std::vector<std::vector<std::string>> v, std::string c, std::string c2, std::ofstream outfile){
    std::string 
    for (unsigned int i=0; i<v.size();i++){
        for (unsigned int j=0; j<v[i].size();j++){
            if (v[i][j]== c){
                v[i][j] = c2;
            }
            outfile<<v[i][j];
        }
        outfile<<std::endl;
    }
    return v
}

void dilate(std::vector<std::vector<std::string>> v, std::string c){
    for (unsigned int i=0; i<v.size();i++){
        for (unsigned int j=0; j<v[0].size();j++){
            if (v[i][j]=="X"){
                if (v[i+1][j] != "X"){
                    v[i+1][j] = "Y";
                }
                if (v[i-1][j] != "X"){
                    v[i-1][j] = "Y";
                }
                if (v[i][j+1] != "X"){
                    v[i][j+1] = "Y";
                }
                if (v[i][j-1] != "X"){
                    v[i][j-1] = "Y";
                }
            }   
        }
    }
    
}
   
std::vector<std::vector<std::string>> erosion(std::vector<std::vector<std::string>> v, std::string c, std::string c2){
    for (unsigned int i=0; i<v.size();i++){
        for (unsigned int j=0; j<v[0].size();j++){
            if (v[i][j]==c){
                if ((v[i+1][j] == c2) || (v[i-1][j] == c2) || (v[i][j+1] == c2) || (v[i][j-1] == c2)){
                    v[i][j] = "E";
                }
            }
                
        }
    }
    return (v);
}
    
int main (int argc, char* argv[])
{
  std::ifstream infile(argv[1]);
  std::ofstream outfile(argv[2]);
  std::string func = argv[3];
  std::string c4 = argv[4];
  std::string c5;
  if (func=="replace" || func == "erosion"){
      c5 = argv[5];
  }
  if (!infile.good()) {
    std::cerr << "Can't open " << argv[1] << " to read.\n";
    exit(1);
  }
  if (!outfile.good()) {
    std::cerr << "Can't open " << argv[2] << " to write.\n";
    exit(1);
  }

  std::string line;
  std::vector<std::vector<std::string>> v2;
  while (std::getline(infile, line)) {
      std::vector<std::string> v1;
      for (unsigned int i=0; i<line.size(); i++){
          std::string temp;
          temp = line[i];
          v1.push_back(temp);
      }
      v2.push_back(v1);
  }

    if (func == "replace"){
        replace(v2, c4, c5, outfile);
    }


  /*
    replace(v2, 'X','O');
    std::cout<<std::endl;
    dilate(v2, 'X');
    std::cout<<std::endl;
    erosion(v2, 'X', '.');
    std::cout<<std::endl; */
    
}

/*
int main ()
{
  std::ifstream infile("input4.txt");
  std::string line;
  std::vector<std::vector<char>> v2;
  while (std::getline(infile, line)) {
      std::vector<char> v1;
      for (auto i: line){
          v1.push_back(i);
      }
      v2.push_back(v1);
  }

  
    replace(v2, 'X','O');
    std::cout<<std::endl;
    dilate(v2, 'X');
    std::cout<<std::endl;
    erosion(v2, 'X', '.');
    std::cout<<std::endl;
    
}
*/