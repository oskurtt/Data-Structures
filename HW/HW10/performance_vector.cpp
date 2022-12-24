#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


// defined in performance.cpp
void usage();


template <class T>
void vector_sort(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = vec.size();
  for (int i = 0; i < output_count; i++)
    ostr << vec[i] << "\n";
}


template <class T>
void vector_remove_duplicates(const std::vector<T> &vec, std::ostream &ostr, int &output_count) { 
  // don't reorder the elements, just do all pairwise comparisons
  output_count = 0;
  for (int i = 0; i < (int)vec.size(); i++) {
    bool dup = false;
    for (int j = 0; j < i; j++) {
      if (vec[i] == vec[j]) {
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << vec[i] << "\n";
      output_count++;
    }
  }
}


template <class T>
void vector_mode(std::vector<T> &vec, std::ostream &ostr, int &output_count) {
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  int current_count = 1;
  T mode;
  int mode_count = 0;
  // keep track of two iterators into the structure
  typename std::vector<T>::iterator current = vec.begin();
  ++current;
  typename std::vector<T>::iterator previous = vec.begin();
  for (; current != vec.end(); ++current, ++previous) {
    if (*current == *previous) {
      // if they are the same element increment the count
      current_count++;
    } else if (current_count >= mode_count) {
      // found a new mode!
      mode = *previous;
      mode_count = current_count;
      current_count = 1;
    } else {
      current_count = 1;
    }
  }
  if (current_count >= mode_count) {
    // last entry is a new mode!
    mode = *previous;
    mode_count = current_count;
  }
  // save the mode to the output vector
  output_count = 1;
  ostr << mode << "\n";
}


// note: closest_pair is only available for integer data (not string data)
void vector_closest_pair(std::vector<int> &vec, std::ostream &ostr, int &output_count) {
  assert (vec.size() >= 2);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = 2;
  int best;
  int best_index = -1;
  // the two elements with closest value must be next to each other in sorted order
  for (unsigned int i = 0; i < vec.size()-1; i++) {
    int diff = vec[i+1]-vec[i];
    if (best_index == -1 || diff < best) {
      best = diff;
      best_index = i;
    }
  }
  // print the two elements
  output_count = 2;
  ostr << vec[best_index] << "\n";
  ostr << vec[best_index+1] << "\n";
}


template <class T>
void vector_first_sorted(std::vector<T> &vec, std::ostream &ostr, int &output_count, int optional_arg) {
  assert (optional_arg >= 1);
  assert ((int)vec.size() >= optional_arg);
  // use the vector sort algorithm
  sort(vec.begin(),vec.end());
  output_count = optional_arg;
  for (int i = 0; i < output_count; i++) {
    ostr << vec[i] << "\n";
  }
}


// note: longest_substring is only available for string data (not integer data)
void vector_longest_substring(std::vector<std::string> &vec, std::ostream &ostr, int &output_count) {

  //
  // ASSIGNMENT: YOU NEED TO COMPLETE THIS FUNCTION
  //
  //initialize variables
  output_count = 1;
  std::string longest;
  std::string s1;
  std::string s2;
  std::string ans = "";
  std::string tmp_ans = "";
  //loop through each element
  for (unsigned long i = 0; i < (vec.size()-1); i++){
    //loop through remaining elements
    for (unsigned long j = i+1; j < vec.size(); j++){
      s1 = vec[i];
      s2 = vec[j];
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
            //check for the end of loop
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


void vector_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  if (type == "string") {
    // load the data into a vector of strings
    std::vector<std::string> vec;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      vec.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { vector_longest_substring (vec,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::vector<int> vec;
    int v;
    input_count = 0;
    while (istr >> v) {
      vec.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { vector_sort              (vec,ostr,output_count); }
    else if (operation == "remove_duplicates") { vector_remove_duplicates (vec,ostr,output_count); }
    else if (operation == "mode")              { vector_mode              (vec,ostr,output_count); }
    else if (operation == "closest_pair")      { vector_closest_pair      (vec,ostr,output_count); }
    else if (operation == "first_sorted")      { vector_first_sorted      (vec,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
