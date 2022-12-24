#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();
//hash table sort
template <class T>
void ht_sort(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count){
  output_count = ht.size();
  //
  for (typename std::unordered_map<T, int>::iterator it = ht.begin(); it != ht.end(); it++)
    ostr << (*it).first << "\n";
}

//hash table remove duplicates
template <class T>
void ht_remove_duplicates(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count, std::istream &istr, int &input_count) { 
  T val; 
  //print out whatever the input file is, except when it is already in the hash table
  while (istr>>val){
    input_count ++;
    if (ht.find(val) == ht.end()){
      ostr<<val<<"\n";
      output_count++;
      ht[val] = 1;
    }
    ht[val]++;
  }
}

//hash table mode
template <class T>
void ht_mode(std::unordered_map<T, int> &bst, std::ostream &ostr, int &output_count) {
  typename std::unordered_map<T, int>::iterator it = bst.begin();
  int count = 0;
  T ans;
  //iterate through the hash table and update largest count based on the key and its value
  for (; it != bst.end(); it++){
    if ((*it).second >= count){
      count = (*it).second;
      ans = (*it).first;
    }
  }
  output_count = 1;
  ostr<<ans<<"\n";
}

//first sorted
template <class T>
void ht_first_sorted(std::unordered_map<T, int> &ht, std::ostream &ostr, int &output_count, int optional_arg) {
  output_count = optional_arg;
  int i = 0;
  typename std::unordered_map<T, int>::iterator it = ht.begin();
  //print out the first "optional_arg" number of elements
  while (i < output_count){
    for (int j = 0; j < (*it).second; j++){
      ostr<<(*it).first<<"\n";
      i++;
      if (i >= output_count) break;
    }
    it++;
  }
}
//list closest pair
void ht_closest_pair(std::unordered_map<int, int> &ht, std::ostream &ostr, int &output_count) {
  std::unordered_map<int, int>::iterator current = ht.begin();
  std::unordered_map<int, int>::iterator next = current;
  next++;
  int diff;
  int best = abs((*next).first - (*current).first);
  int best_num1 = (*current).first;
  int best_num2 = (*next).first;
  //iterate through list
  for (; current != ht.end(); current++){
    for (next = current; next != ht.end(); next++){
      //if diff is less than the best diff, update best and the answers
      diff = abs((*next).first - (*current).first);
      if ((diff < best) && (diff!=0)){
        best = diff;
        best_num1 = (*current).first;
        best_num2 = (*next).first;
      }
    }
    
  }
  output_count = 2;
  if (best_num1 < best_num2) ostr<<best_num1<<"\n"<<best_num2<<"\n";
  else ostr<<best_num2<<"\n"<<best_num1<<"\n";
}
//longest substring
void ht_longest_substring(std::unordered_map<std::string,int> &ht, std::ostream &ostr, int &output_count) {
  //initialize variables
  output_count = 1;
  std::string longest;
  std::string s1;
  std::string s2;
  std::string ans = "";
  std::string tmp_ans = "";
  std::unordered_map<std::string, int>::iterator it1 = ht.begin();
  std::unordered_map<std::string, int>::iterator it2;
  //iterate through each element
  for (; it1 != ht.end(); it1++){
    it2 = it1;
    it2++;
    //iterate through remaining elements
    for (; it2 != ht.end(); it2++){
      s1 = (*it1).first;
      s2 = (*it2).first;
      //loop through the first string
      for (unsigned long k = 0; k < s1.size(); k++){
        //loop through the second strnig
        for (unsigned long l = 0; l < s2.size(); l++){
          //if they are the same, add to the tmp answer string
          if (s1[k] == s2[l]){
            tmp_ans += s1[k];
            int count = 1;
            //continuing looping through the rest of the second string
            for (unsigned long m = l+1; m < s2.size(); m++){
              //if it's the same character, add to the tmp answer string
              if (s1[k+count] == s2[m]){
                tmp_ans += s2[m];
                count ++;
              }
              else{
                //check if the tmp answer string is larger than the answer string
                if (tmp_ans.size() > ans.size()){
                  ans = tmp_ans;
                }
                //reset tmp answer string
                tmp_ans = "";
                break;
              }
            }
            //check for the end of iteration
            if (tmp_ans.size() > ans.size()){
                  ans = tmp_ans;
            }
            tmp_ans = "";
            break;
          }
        }
      }
    }
  }
  ostr<<ans<<"\n";
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your hash table like this:
  // std::unordered_set<std::string> ht;
  // OR 
  // std::unordered_map<std::string,int> ht;

   if (type == "string") {
    // load the data into a vector of strings
    std::unordered_map<std::string, int> ht;
    std::string s;
    input_count = 0;
    if (operation == "remove_duplicates"){
      ht_remove_duplicates (ht,ostr,output_count, istr, input_count);
    }
    else{
      while (istr >> s) {
        ht[s]++;
        input_count++;
      }
      if      (operation == "sort")              { ht_sort              (ht,ostr,output_count); }
      else if (operation == "mode")              { ht_mode              (ht,ostr,output_count); }
      // "closest_pair" not available for strings
      else if (operation == "first_sorted")      { ht_first_sorted      (ht,ostr,output_count,optional_arg); }
      else if (operation == "longest_substring") { ht_longest_substring (ht,ostr,output_count); }
      //else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::unordered_map<int, int> ht;
    int v;
    input_count = 0;
    if (operation == "remove_duplicates"){
      ht_remove_duplicates (ht,ostr,output_count, istr, input_count);
    }
    else{
      while (istr >> v) {
        ht[v]++;
        input_count++;
      }
      if      (operation == "sort")              { ht_sort              (ht,ostr,output_count); }
      else if (operation == "mode")              { ht_mode              (ht,ostr,output_count); }
      else if (operation == "closest_pair")      { ht_closest_pair      (ht,ostr,output_count); }
      else if (operation == "first_sorted")      { ht_first_sorted      (ht,ostr,output_count,optional_arg); }
      // "longest_substring" not available for integers
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
}
