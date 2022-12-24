// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <utility>
#include <assert.h> 
#include <time.h>

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef  std::map<std::string, std::map<std::string, int>>  MY_MAP;
typedef  std::map<std::string, std::map<std::string, std::map<std::string, int>>>  MY_MAP_3;

int window;


// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
	// break words at whitespace
	return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
	istr.get(c);
	word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}



// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, const std::string &parse_method, MY_MAP_3 &data3) {
  // open the file stream
  std::ifstream istr(filename.c_str());
  if (!istr) { 
    std::cerr << "ERROR cannot open file: " << filename << std::endl; 
    exit(1);
  } 
  // verify the window parameter is appropriate
  if (window < 2) {
    std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
  }
  // verify that the parse method is appropriate
  bool ignore_punctuation = false;
  if (parse_method == "ignore_punctuation") {
    ignore_punctuation = true;
  } else {
    std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
    exit(1);
  }

  std::cout<<"Loaded "<<filename<<" with window = "<<window<<" and parse method = "<<parse_method<<std::endl;

  //
  // ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
  //initialize the first word into the map by using the first two words of the text
  if (window == 2){
    std::string word;
    std::string prev;
    ReadNextWord(istr, prev);
    ReadNextWord(istr, word);
    data[prev][word]= 1;
    prev = word;
    //
    while (ReadNextWord(istr,word)) {
      // skip the quotation marks (not used for this part)
      if (word == "\"") continue;
      //
      // ASSIGNMENT: PROCESS ALL THE NON PUNCTUATION WORDS
      // INSERTING THESE WORDS INTO THE DATA STRUCTURE
      //
      //if data is not found, create it in the map and set its int to 1
      if (data.find(prev) == data.end()){
        data[prev][word] = 1;
      }
      //else add counter to that map
      else{
          data[prev][word] ++;
        }
      prev = word;
    }
    std::cout<<std::endl;
  }
  else if (window == 3){
    //intialize first item in map by using first two words in the text
    std::string word, prev, prev_prev;
    ReadNextWord(istr, prev_prev);
    ReadNextWord(istr, prev);
    ReadNextWord(istr, word);
    data3[prev_prev][prev][word] = 1;
    data3[prev][word];
    data3[word];
    prev_prev = prev;
    prev = word;
    while (ReadNextWord(istr, word)){
      if (word == "\"") continue;
      //checks if the set of three words are already in the map
      //create maps and add counters
      //if first word is in map
      if (data3.find(prev_prev) != data3.end()){
        //if second word is in first word
        if (data3[prev_prev].find(prev) != data3[prev_prev].end()){
          //if third word is in second word
          if (data3[prev_prev][prev].find(word) != data3[prev_prev][prev].end()){
            data3[prev_prev][prev][word] ++;
          }
          else{
            data3[prev_prev][prev][word] = 1;
          }
        }
        else{
          data3[prev_prev][prev][word] = 1;
        }
      }
      else{
        data3[prev_prev][prev][word] = 1;
      }
      prev_prev = prev;
      prev = word;
    }
    std::cout<<std::endl;
  }
}

std::string NextWord(std::vector<std::string> v){
  //randomly choose a word in the vector
  int x = 0;
  int total = v.size();
  x = std::rand() % total;
  return v[x];
}

int main () {
  std::srand(time(NULL));
  // ASSIGNMENT: THE MAIN DATA STRUCTURE
  MY_MAP data;
  MY_MAP_3 data3;

  // Parse each command
  std::string command;    
  while (std::cin >> command) {

    // load the sample text file
    if (command == "load") {
      std::string filename;
      std::string parse_method;
      std::cin >> filename >> window >> parse_method;      
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      LoadSampleText(data, filename, window, parse_method, data3);
    } 

    // print the portion of the map structure with the choices for the
    // next word given a particular sequence.
    else if (command == "print") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);

      if (window == 2){
        //
        // ASSIGNMENT: ADD YOUR COMMANDS HERE
        int count = 0;
        std::string s = sentence[0];
        std::map<std::string, int>::iterator it;
        //count all the words proceding the current word
        for (it = data[s].begin(); it != data[s].end(); ++it){
          count += (*it).second;
        }
        std::cout<<s<<" ("<<count<<")"<<std::endl;
        //cout all the words after the current word and the frequencies of it
        for (it = data[s].begin(); it != data[s].end(); ++it){
          std::cout<<s<<" "<<(*it).first<<" ("<<(*it).second<<")"<<std::endl;
        }
        //
      }
      else if (window == 3){
        int count = 0;
        std::string s1;
        std::string s2;
        MY_MAP::iterator it1;
        std::map<std::string, int>::iterator it2;
        s1 = sentence[0];
        //does same as window two but we added another for loop to access all the windows to count frequencies
        if (sentence.size() == 1){
          for (it1 = data3[s1].begin(); it1 != data3[s1].end(); ++it1){
            for (it2 = data3[s1][(*it1).first].begin(); it2 != data3[s1][(*it1).first].end(); ++it2){
              count += (*it2).second;
            }
          }
          std::cout<<s1<<" ("<<count<<")"<<std::endl;
          for (it1 = data3[s1].begin(); it1 != data3[s1].end(); ++it1){
            std::cout<<s1<<" "<<(*it1).first<<" ("<<(*it1).second.size()<<")"<<std::endl;
          }

        }
        else {
          s2 = sentence[1];
          for (it2 = data3[s1][s2].begin(); it2 != data3[s1][s2].end(); ++it2){
            count += (*it2).second;
          }
          std::cout<<s1<<" "<<s2<<" ("<<count<<")"<<std::endl;
          for (it2 = data3[s1][s2].begin(); it2 != data3[s1][s2].end(); ++it2){
            std::cout<<s1<<" "<<s2<<" "<<(*it2).first<<" ("<<(*it2).second<<")"<<std::endl;
          }
        }
      }
      std::cout<<std::endl;
    }

    // generate the specified number of words 
    else if (command == "generate") {
      std::vector<std::string> sentence = ReadQuotedWords(std::cin);
      // how many additional words to generate
      int length;
      std::cin >> length;
      std::string selection_method;
      std::cin >> selection_method;
      bool random_flag;
      if (selection_method == "random") {
	      random_flag = true;
      } 
      else {
        assert (selection_method == "most_common");
        random_flag = false;
      }
      //
      // ASSIGNMENT: ADD YOUR COMMANDS HERE
      //initalize variables
      if (window == 2){
        int size = 0;
        std::string s = sentence[0];
        std::map<std::string, int>::iterator it;
        std::vector<std::string> v;
        std::string tmp_string = s;

        if (random_flag){
          //if word doesn't exist, break the loop
          std::cout<<s;
          for (int i = 0; i<length; i++){
            if (data.find(s) == data.end()){
              break;
            }
            //pushback all the possible next words into a vector. Push it as many times as its frequency
            for (it = data[tmp_string].begin(); it != data[tmp_string].end(); ++it){
              for (int i = 0; i < (*it).second; ++i){
                v.push_back((*it).first);
              }
              if (v.size() == 0){
                break;
              }
            }
            //set the string to the next randomly chosen word
            s = NextWord(v);
            tmp_string = s;
            std::cout<<" "<<s;
            v.clear();
          }
        }
        else {
          //if most common for window 2
          std::cout<<s;
          for (int i = 0; i < length; i++){
            size = 0;
            if (data.find(s) == data.end()){
              break;
            }
            //set string to the word with the greatest frequencies
            for (it = data[tmp_string].begin(); it != data[tmp_string].end(); ++it){
              if ((*it).second > size){
                size = (*it).second;
                s = (*it).first;
              }  
            }
            tmp_string = s;
            std::cout<<" "<<s;
          }
        }
        std::cout<<std::endl<<std::endl;
      }
      else if (window == 3){
        //window 3
        int size = 0;
        std::string s1 = sentence[0];
        if (sentence.size() == 2){
          std::string s2 = sentence[1];
        }
        MY_MAP::iterator it1;
        std::map<std::string, int>::iterator it2;
        std::vector<std::string> v;
        std::string tmp_string1;
        std::string tmp_string2;
        if (random_flag){
          //window 3 and random
          std::cout<<s1;
          tmp_string1 = s1;
          //if not given a second word, find it by randomly picking the next word
          if (sentence.size() == 1){
            length--;
            //loop through and pushback all the possible 2nd word by how many times it appears
            for (it1 = data3[tmp_string1].begin(); it1 != data3[tmp_string1].end(); ++it1){
              for (it2 = data3[tmp_string1][(*it1).first].begin(); it2 != data3[tmp_string1][(*it1).first].end(); ++it2){
                v.push_back((*it1).first);
              }
              if (v.size() == 0){
                break;
              }
            }
            tmp_string2 = NextWord(v);
          }
          else{
            tmp_string2 = sentence[1];
          }
          std::cout<<" "<<tmp_string2;
          //loop for how many words we need to find
          for (int i = 0; i<length; i++){
            //if can't find word, break
            if (data3.find(tmp_string1) == data3.end()){
              break;
            }
            else if (data3[tmp_string1].find(tmp_string2) == data3[tmp_string1].end()){
              break;
            }
            //loop through and find the next word randomly 
            for (it2 = data3[tmp_string1][tmp_string2].begin(); it2 != data3[tmp_string1][tmp_string2].end(); ++it2){
              for (int i = 0; i < (*it2).second; ++i){
                v.push_back((*it2).first);
              }
              if (v.size() == 0){
                break;
              }
            }
            s1 = NextWord(v);
            std::cout<<" "<<s1;
            tmp_string1 = tmp_string2;
            tmp_string2 = s1;
            v.clear();
          }
        }
        else{
          //generate based on frequency
          tmp_string1 = s1;
          std::cout<<s1;
          if (sentence.size() == 1){
            length--;
            //find the second most frequent word
            for (it1 = data3[s1].begin(); it1 != data3[s1].end(); ++it1){
              for (it2 = data3[tmp_string1][(*it1).first].begin(); it2 != data3[tmp_string1][(*it1).first].end(); ++it2){
                if ((*it2).second > size){
                  size = (*it2).second;
                  tmp_string2 = (*it1).first;
                }
              }
            }
          }
          else{
            tmp_string2 = sentence[1];
          }
          std::cout<<" "<<tmp_string2;
          for (int i = 0; i < length; ++i){
            size = 0;
            if (data3.find(tmp_string1) == data3.end()){
              break;
            }
            else if (data3[tmp_string1].find(tmp_string2) == data3[tmp_string1].end()){
              break;
            }
            //loop through and update the word with most frequency
            for (it2 = data3[tmp_string1][tmp_string2].begin(); it2 != data3[tmp_string1][tmp_string2].end(); ++it2){
              if ((*it2).second > size){
                size = (*it2).second;
                s1 = (*it2).first;
              }
            }
            std::cout<<" "<<s1;
            tmp_string1 = tmp_string2;
            tmp_string2 = s1;
          }
        }
        std::cout<<std::endl<<std::endl;
      }
    } 
    else if (command == "quit") {
      break;
    } 
    else {
      std::cout << "WARNING: Unknown command: " << command << std::endl;
    }
  }
}
