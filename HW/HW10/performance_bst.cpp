#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();

//bst sort
template <class T>
void bst_sort(std::map<T, int> &bst, std::ostream &ostr, int &output_count){
  output_count = bst.size();
  for (typename std::map<T, int>::iterator it = bst.begin(); it != bst.end(); it++)
    for (int i = 0; i < (*it).second; i++){
      ostr << (*it).first << "\n";
    }
    
}

//bst remove duplicates
template <class T>
void bst_remove_duplicates(std::map<T, int> &bst, std::ostream &ostr, int &output_count,std::istream &istr,int &input_count) { 
  /*typename std::map<T, int>::const_iterator mitgate_warning;
  mitgate_warning= bst.begin();
  output_count = 0;
  T s;
  typename std::map<int, T> unordered;
  while (istr >> s) {
    input_count++;
    unordered[input_count] = s;
  }
  for (typename std::map<int, T>::iterator it = unordered.begin(); it != unordered.end(); it++) {
    bool dup = false;
    typename std::map<int, T>::iterator it2 = unordered.begin();
    for (; it2 != it; it2++){
      if ((*it2).second == (*it).second){
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << (*it).second << "\n";
      output_count++;
    }
  }*/
  T val; 
  //print out whatever the input file is, except when it is already in the binary search tree
  while (istr>>val){
    input_count ++;
    if (bst.find(val) == bst.end()){
      ostr<<val<<"\n";
      output_count++;
      bst[val] = 1;
    }
    bst[val]++;
  }
}

//bst mode
template <class T>
void bst_mode(std::map<T, int> &bst, std::ostream &ostr, int &output_count) {
  typename std::map<T, int>::iterator it = bst.begin();
  int count = 0;
  T ans;
  //iterate through the binary search tree and update largest count based on the key and its value
  for (; it != bst.end(); it++){
    if ((*it).second >= count){
      count = (*it).second;
      ans = (*it).first;
    }
  }
  output_count = 1;
  ostr<<ans<<"\n";
}

//list closest pair
void bst_closest_pair(std::map<int, int> &bst, std::ostream &ostr, int &output_count) {
  std::map<int, int>::iterator current = bst.begin();
  std::map<int, int>::iterator previous = bst.begin();
  current++;
  int diff;
  int best = (*current).first - (*previous).first;
  int best_num1 = (*current).first;
  int best_num2 = (*previous).first;
  //iterate through list
  for (; current != bst.end(); current++, previous++){
    diff = (*current).first - (*previous).first;
    //if diff is less than the best diff, update best and the answers
    if ((diff < best) && (diff!=0)){
      best = diff;
      best_num1 = (*current).first;
      best_num2 = (*previous).first;
    }
  }
  output_count = 2;
  ostr<<best_num2<<"\n";
  ostr<<best_num1<<"\n";
}
//first sorted
template <class T>
void bst_first_sorted(std::map<T, int> &bst, std::ostream &ostr, int &output_count, int optional_arg) {
  output_count = optional_arg;
  int i = 0;
  typename std::map<T, int>::iterator it = bst.begin();
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


//longest substring
void bst_longest_substring(std::map<std::string,int> &bst, std::ostream &ostr, int &output_count) {
  //initialize variables
  output_count = 1;
  std::string longest;
  std::string s1;
  std::string s2;
  std::string ans = "";
  std::string tmp_ans = "";
  std::map<std::string, int>::iterator it1 = bst.begin();
  std::map<std::string, int>::iterator it2;
  //iterate through each element
  for (; it1 != bst.end(); it1++){
    it2 = it1;
    it2++;
    //iterate through remaining elements
    for (; it2 != bst.end(); it2++){
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

void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your binary search tree (BST) like this:
  // std::set<std::string> st;
  // OR 
  // std::map<std::string,int> mp;

  if (type == "string") {
    // load the data into a vector of strings
    std::map<std::string, int> bst;
    std::string s;
    input_count = 0;
    if (operation == "remove_duplicates"){
      bst_remove_duplicates (bst,ostr,output_count, istr, input_count);
    }
    else{
      while (istr >> s) {
        bst[s]++;
        input_count++;
      }
      if      (operation == "sort")              { bst_sort            (bst,ostr,output_count); }
      //else if (operation == "remove_duplicates") { bst_remove_duplicates (unordered,ostr,output_count); }
      else if (operation == "mode")              { bst_mode              (bst,ostr,output_count); }
      // "closest_pair" not available for strings
      else if (operation == "first_sorted")      { bst_first_sorted      (bst,ostr,output_count,optional_arg); }
      else if (operation == "longest_substring") { bst_longest_substring (bst,ostr,output_count); }
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }
   else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::map<int, int> bst;
    int v;
    input_count = 0;
    if (operation == "remove_duplicates"){
      bst_remove_duplicates (bst,ostr,output_count, istr, input_count);
    }
    else{
      while (istr >> v) {
        bst[v]++;
        input_count++;
      }
      if      (operation == "sort")              { bst_sort              (bst,ostr,output_count); }
      //else if (operation == "remove_duplicates") { bst_remove_duplicates (unordered,ostr,output_count); }
      else if (operation == "mode")              { bst_mode              (bst,ostr,output_count); }
      else if (operation == "closest_pair")      { bst_closest_pair      (bst,ostr,output_count); }
      else if (operation == "first_sorted")      { bst_first_sorted      (bst,ostr,output_count,optional_arg); }
      // "longest_substring" not available for integers
      else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
    }
  }

}
