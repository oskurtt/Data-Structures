#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>

// defined in performance.cpp
void usage();

template <class T>
void pq_sort(std::priority_queue<T,std::vector<T>, std::greater<T>>& pq, std::ostream &ostr, int &output_count) {
  //print out the top and then pop it again
  output_count = pq.size();
  for (int i = 0; i < output_count; i++){
    ostr << pq.top()<< "\n";
    pq.pop();
  }
}

template <class T>
//doesn't exist
void pq_remove_duplicates(std::priority_queue<T,std::vector<T>, std::greater<T>>& pq, std::ostream &ostr, int &output_count) { 
  pq.pop();
  output_count = 0;
  ostr<<"none"<<std::endl;
}


template <class T>
void pq_mode(std::priority_queue<T,std::vector<T>, std::greater<T>>& pq, std::ostream &ostr, int &output_count) {
  int current_count = 1;
  int mode_count = 1; 
  T current;
  T mode = pq.top();
  T previous = pq.top();
  pq.pop();

  //loop through until pq is empty
  while (!pq.empty()){
    current = pq.top();
    //check if current and previous are the same
    if (current == previous){
      current_count ++;
    }
    //reset counter if not the same
    else current_count = 0;
    //update the answer and the count if there exists a new mode
    if (current_count >= mode_count){
      mode = current;
      mode_count = current_count;
    }
    //set the previous to the current and pop the top
    previous = current;
    pq.pop();
    
  }
  output_count = 1;
  ostr<<mode<<"\n";
}

// note: closest_pair is only available for integer data (not string data)
void pq_closest_pair(std::priority_queue<int,std::vector<int>, std::greater<int>>& pq, std::ostream &ostr, int &output_count) {
  output_count = 2;
  int best;
  int current;
  int previous;
  int diff;
  int p1;
  int p2;
  previous = pq.top();
  pq.pop();
  current = pq.top();
  best = current - previous;
  //loop through until pq is empty
  while (!pq.empty()){
    current = pq.top();
    diff = current - previous;
    //if diff is less than the best diff, update best and the answers
    if ((diff != 0) && (diff < best)){
      best = diff;
      p1 = previous;
      p2 = current;
    }
    previous = current;
    pq.pop();
  }
  ostr<<p1<<"\n";
  ostr<<p2<<"\n";
}

template <class T>
void pq_first_sorted(std::priority_queue<T,std::vector<T>, std::greater<T>>& pq, std::ostream &ostr, int &output_count, int optional_arg) {
  output_count = optional_arg;
  int i = 0;
  //print out the first "optional_arg" number of elements
  for (; i < optional_arg; i++){
    ostr << pq.top()<< "\n";
    pq.pop();
  }
}
//doesn't exist
void pq_longest_substring(std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string>>& pq, std::ostream &ostr, int &output_count) {
  output_count = 1;
  pq.pop();
  ostr<<"NONE"<<"\n";
}



void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {

  // HINT: For the string element type, declare your priority_queue like this:

  // std::priority_queue<std::string,std::vector<std::string> > pq;
  // (this will make a "max" priority queue, with big values at the top)

  // OR
  
  // std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
  // (this will make a "min" priority queue, with big values at the bottom)

  if (type == "string") {
    // load the data into a vector of strings
    std::priority_queue<std::string,std::vector<std::string>, std::greater<std::string> > pq;
    std::string s;
    input_count = 0;
    while (istr >> s) {
      pq.push(s);
      input_count++;
    }
    if      (operation == "sort")              { pq_sort <std::string>           (pq,ostr,output_count); }
    else if (operation == "remove_duplicates") { pq_remove_duplicates <std::string> (pq,ostr,output_count); }
    else if (operation == "mode")              { pq_mode     <std::string>         (pq,ostr,output_count); }
    // "closest_pair" not available for strings
    else if (operation == "first_sorted")      { pq_first_sorted <std::string>     (pq,ostr,output_count,optional_arg); }
    else if (operation == "longest_substring") { pq_longest_substring (pq,ostr,output_count); }
    //else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
   else {
    assert (type == "integer");
    // load the data into a vector of integers
    std::priority_queue<int,std::vector<int>, std::greater<int>> pq;
    int v;
    input_count = 0;
    while (istr >> v) {
      pq.push(v);
      input_count++;
    }
    if      (operation == "sort")              { pq_sort  <int>           (pq,ostr,output_count); }
    else if (operation == "remove_duplicates") { pq_remove_duplicates <int> (pq,ostr,output_count); }
    else if (operation == "mode")              { pq_mode  <int>            (pq,ostr,output_count); }
    else if (operation == "closest_pair")      { pq_closest_pair      (pq,ostr,output_count); }
    else if (operation == "first_sorted")      { pq_first_sorted  <int>    (pq,ostr,output_count,optional_arg); }
    // "longest_substring" not available for integers
    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  }
}
