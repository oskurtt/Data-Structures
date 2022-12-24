#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();
//list sort
template <class T>
void list_sort(std::list<T> &lst, std::ostream &ostr, int &output_count){
  //sort list and then print
  lst.sort();
  output_count = lst.size();
  for (typename std::list<T>::iterator it = lst.begin(); it != lst.end(); it++)
    ostr << *it << "\n";
}

//list remove duplicates
template <class T>
void list_remove_duplicates(const std::list<T> &lst, std::ostream &ostr, int &output_count) { 
  output_count = 0;
  //iterate through list
  for (typename std::list<T>::const_iterator it = lst.begin(); it != lst.end(); it++) {
    bool dup = false;
    //iterate from beginning up to current iterator
    typename std::list<T>::const_iterator it2 = lst.begin();
    //if there exists the name number, dup equals true
    for (; it2 != it; it2++){
      if (*it2 == *it){
        dup = true;
        break;
      }
    }
    // if it has not already been added to the output list
    if (!dup) {
      ostr << *it << "\n";
      output_count++;
    }
  }
}


//list mode
template <class T>
void list_mode(std::list<T> &lst, std::ostream &ostr, int &output_count) {
  lst.sort();
  T ans;
  int count = 1;
  int max_count = 0;
  typename std::list<T>::iterator current = lst.begin();
  typename std::list<T>::iterator previous = lst.begin();
  current ++;
  //iterate through list and keep track of current and previous elements
  for (; current != lst.end(); current ++, previous++){
    //if current and previous are equal, increment count
    if (*current == *previous){
      count ++;
    }
    //if current count is bigger, update max_count and set answer to previous element
    else if (count >= max_count){
      ans = *previous;
      max_count = count;
      count = 1;
    }
    else count = 1;
  }
  //check for end of iteration
  if (count >= max_count){
    ans = *previous;
    max_count = count;
  }
  output_count = 1;
  ostr<<ans<<"\n";
}


//list closest pair
void list_closest_pair(std::list<int> &lst, std::ostream &ostr, int &output_count) {
  lst.sort();
  //initialize variables
  std::list<int>::iterator current = lst.begin();
  std::list<int>::iterator previous = lst.begin();
  current++;
  int diff;
  int best = *current - *previous;
  int best_num1 = *current;
  int best_num2 = *previous;
  //iterate through list
  for (; current != lst.end(); current++, previous++){
    diff = *current - *previous;
    //if diff is less than the best diff, update best and the answers
    if ((diff < best) && (diff!=0)){
      best = diff;
      best_num1 = *current;
      best_num2 = *previous;
    }
  }
  output_count = 2;
  ostr<<best_num2<<"\n";
  ostr<<best_num1<<"\n";
}
//first sorted
template <class T>
void list_first_sorted(std::list<T> &lst, std::ostream &ostr, int &output_count, int optional_arg) {
  lst.sort();
  output_count = optional_arg;
  int i = 0;
  typename std::list<T>::iterator it = lst.begin();
  //print out the first "optional_arg" number of elements
  while (i < output_count){
    ostr<<*it<<"\n";
    it++;
    i++;
  }
}

//longest substring
void list_longest_substring(std::list<std::string> &lst, std::ostream &ostr, int &output_count) {
  //initialize variables
  output_count = 1;
  std::string longest;
  std::string s1;
  std::string s2;
  std::string ans = "";
  std::string tmp_ans = "";
  std::list<std::string>::iterator it1 = lst.begin();
  std::list<std::string>::iterator it2;
  //iterate through each element
  for (; it1 != lst.end(); it1++){
    it2 = it1;
    it2++;
    //iterate through remaining elements
    for (; it2 != lst.end(); it2++){
      s1 = *it1;
      s2 = *it2;
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


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your list like this:
  // std::list<std::string> lst;

  if (type == "string") {
    // load the data into a vector of strings
    std::list<std::string> lst;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      lst.push_back(s);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }

  else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::list<int> lst;
    int v;
    input_count = 0;
    while (istr >> v) {
      lst.push_back(v);
      input_count++;
    }
    if      (operation == "sort")              { list_sort              (lst,ostr,output_count); }
    else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
    else if (operation == "mode")              { list_mode            (lst,ostr,output_count); }
    else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
    else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
