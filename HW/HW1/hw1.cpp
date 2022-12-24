#include <iostream>
#include <string>
#include <cmath> 
#include <cstdlib>
#include <fstream>
#include <vector>
//replace function
//arguments for function
std::vector<std::string> replace(std::vector<std::string> v, char c, char c2, std::ofstream& outfile){
    for (int i=0; i<v.size();i++){ //loop through each character in vector
        for (int j=0; j<v[0].size();j++){
            if (v[i][j]== c){ //if character is 'X' change to 'O'
                v[i][j] = c2;
            }
            outfile<<v[i][j]; //print to outfile
        }
        outfile<<std::endl; //print a line
    }
    return (v); //return the function
}
//dilation function
//arguments for function
std::vector<std::string> dilation(std::vector<std::string> v, char c, std::ofstream& outfile){
    for (int i=0; i<v.size();i++){ //loops through vector just like in replace function
        for (int j=0; j<v[0].size();j++){
            if (v[i][j]==c){ //if equals to 'X' change its surrounding characters to another letter
                if (v[i+1][j] != c){
                    v[i+1][j] = 'Y';
                }
                if (v[i-1][j] != c){
                    v[i-1][j] = 'Y';
                }
                if (v[i][j+1] != c){
                    v[i][j+1] = 'Y';
                }
                if (v[i][j-1] != c){
                    v[i][j-1] = 'Y';
                }
            }   
        }
    }
    for (int i=0; i<v.size();i++){ //loops through newly created grid and change the changed letter back to 'X'
        for (int j=0; j<v[0].size();j++){
            if (v[i][j]== 'Y'){
                v[i][j] = c;
            }
            outfile<<v[i][j];
        }
        outfile<<std::endl;
    }
    return (v);   
}

//erosion function
//arugments
std::vector<std::string> erosion(std::vector<std::string> v, char c, char c2, std::ofstream& outfile){
    for (int i=0; i<v.size();i++){ //loops through grid and if one surround character is '.', then change it to 'E'
        for (int j=0; j<v[0].size();j++){
            if (v[i][j]==c){
                if ((v[i+1][j] == c2) || (v[i-1][j] == c2) || (v[i][j+1] == c2) || (v[i][j-1] == c2)){
                    v[i][j] = 'E';
                }
            }
                
        }
    }
    for (int i=0; i<v.size();i++){ //loops grid and change all 'E' to '.'
        for (int j=0; j<v[0].size();j++){
            if (v[i][j]== 'E'){
                v[i][j] = c2;
            }
            outfile<<v[i][j];
        }
        outfile<<std::endl;
    }
    return (v);
}
    


int main (int argc, char* argv[])
{
  std::ifstream infile(argv[1]); //intialize arguments
  std::ofstream outfile(argv[2]);
  std::string symb1 = (argv[4]);
  if (argc == 6){ //if there happens to be a sixth argument, create another variable for it
      std::string symb2 = (argv[5]);
  }
  std::string line;

  std::vector<std::string> v1;
  while (std::getline(infile, line)) { //extracts input in the form of line by line
        v1.push_back(line); //push back the line into another vector to create vector of vector
  }

  if (std::string(argv[3])==std::string("replace")){ //if we call for replace, run replace
    replace(v1, argv[4][0], argv[5][0], outfile); 
  }
  

  if (std::string(argv[3])==std::string("dilation")){//if we call for dilation, run replace
    dilation(v1, argv[4][0], outfile);
  }
    
    if (std::string(argv[3])==std::string("erosion")){//if we call for erosion, run replace
    erosion(v1, argv[4][0], argv[5][0], outfile);
  }
}