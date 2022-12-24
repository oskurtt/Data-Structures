#ifndef UnrolledLL_h_
#define UnrolledLL_h_
// A simplified implementation of the STL list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
#include <sstream>
#include <iostream>
const int NUM_ELEMENTS_PER_NODE = 6;
// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public://constructors for Node
  Node() : num_elem(), value_(), next_(NULL), prev_(NULL) {
    num_elem = 0;
  }
  Node(const T& v) : num_elem(), next_(NULL), prev_(NULL) {
    num_elem = 1;
    value_[0] = v;
  }
  // REPRESENTATION
  int num_elem;
  T value_[NUM_ELEMENTS_PER_NODE];
  Node<T>* next_;
  Node<T>* prev_;
};
// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  list_iterator(Node<T>* p=NULL, int offset_=0) : ptr_(p), offset(offset_) {}
  // NOTE: the implicit compiler definitions of the copy constructor,
  // assignment operator, and destructor are correct for this class

  // dereferencing operator gives access to the value at the pointer
  T& operator*(){ 
    return ptr_->value_[offset];
  }
  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if (offset >= ptr_->num_elem-1){ //if offset is greater than the number of elements, reset offset to zero
      ptr_ = ptr_->next_;
      offset = 0;
    }
    else{
      offset++;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if (offset >= ptr_->num_elem-1){
      ptr_ = ptr_->next_;
      offset = 0;
    }
    else{
      offset++;
    }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (offset <= 0){ //if offset reaches zero, set the ptr to the previous pointer
      ptr_=ptr_->prev_;
      offset = ptr_->num_elem;
    }
    else{
      offset--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (offset <= 0){
      ptr_=ptr_->prev_;
      offset = ptr_->num_elem;
    }
    else{
      offset--;
    }
    return temp;
  }
  // the dslist class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_; }
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  unsigned int offset;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { destroy_list(); }

  typedef list_iterator<T> iterator;

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->value_[0];  } //returns first value
  T& front() { return head_->value_[0]; }
  const T& back() const { return tail_->value_[tail_->num_elem-1]; } //returns last value
  T& back() { return tail_->value_[tail_->num_elem-1]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();
  void print(std::ostream& cout);

  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(NULL); }

private:
  // private helper functions
  void copy_list(const UnrolledLL<T>& old);
  void destroy_list();

  //REPRESENTATION
  Node<T>* head_;
  Node<T>* tail_;
  unsigned int size_;
};

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    destroy_list();
    copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {
  if (!tail_) { //if empty, make new node
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
  } 
  else{
    //if node is full
    //create a new node and point the new nodes next to the head and the heads previous to the new node
    //set the head to the new node
    Node<T>* newp = new Node<T>(v);
    if(head_->num_elem >= NUM_ELEMENTS_PER_NODE){ 
      newp->next_ = head_;
      head_->prev_ = newp;
      head_ = newp;
    }
    //if not full, move over the elements one space over and set the first value to v
    else{
      for (unsigned int i = 0; i< head_->num_elem;i++){
        newp->value_[i+1] = head_->value_[i];
        newp->num_elem += 1;
      }
      head_->next_->prev_ = newp;
      newp->next_=head_->next_;
      delete head_;
      head_ = newp;
    }
  }
  ++size_;
}

template <class T>
//move the elements over one space and decrement the number of elements
void UnrolledLL<T>::pop_front() {
  if (head_){
    Node<T>* newp = new Node<T>;
    for (unsigned int i = 1; i < head_->num_elem;i++){
      newp->value_[i-1] = head_->value_[i];
      newp->num_elem +=1;
    }
    //set newp's next node to head's next node
    //set head's next's previous to new node and delete the head
    //set the head back to the new node
    newp->next_ = head_->next_;
    head_->next_->prev_ = newp; 
    delete head_;
    head_ = newp;
    --size_;
    //if there is no elements, delete the first node 
    if (head_->num_elem==0){
      Node<T>* temp = head_->next_;
      temp->prev_ = NULL;
      delete head_;
      head_ = temp;
    }
  }
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  // special case: initially empty list
  if (!tail_) {
    Node<T>* newp = new Node<T>(v);
    head_ = tail_ = newp;
  } 
  else {
    // normal case: at least one node already
    //if there is still space in the node, put the new v to the next empty space
    if (tail_->num_elem < NUM_ELEMENTS_PER_NODE){
      tail_ -> value_[tail_->num_elem] = v;
      tail_->num_elem += 1;
    }
    else{
      //else, create a new node and add it to the end and make it the tail
      Node<T>* newp = new Node<T>(v);
      newp->prev_ = tail_;
      tail_->next_ = newp;
      tail_ = newp;
    }
  }
  ++size_;
}

template <class T>
void UnrolledLL<T>::pop_back() {
  //create a new node and only copy over the array except the last element
  if (tail_){
    Node<T>* newp = new Node<T>;
    for (unsigned int i = 0; i < tail_->num_elem-1;i++){
      newp->value_[i] = tail_->value_[i];
      newp->num_elem +=1;
    }
    newp->prev_ = tail_->prev_;
    tail_->prev_->next_ = newp;
    delete tail_;
    tail_ = newp;
    --size_;
    //if there is no more elemnts at the tail, delete it and make the last node with elements the new tail
    if (tail_->num_elem == 0){
      Node<T>* temp = tail_->prev_;
      temp->next_ = NULL;
      delete tail_;
      tail_ = temp;
    }
  }
}

template <class T>
void UnrolledLL<T>::print(std::ostream& cout){
  //loop through each node and print out its contents
  std::cout<<"UnrolledLL, size: "<<size_<<std::endl;
  Node<T>* temp_ = head_;
  while (temp_ != NULL){
    std::cout<<"node:["<<temp_->num_elem<<"] ";
    for (int i = 0; i < temp_->num_elem; i++){
      std::cout<<temp_->value_[i]<<" ";
    }
    std::cout<<std::endl;
    temp_ = temp_->next_;
  }
}
// do these lists look the same (length & contents)?
template <class T>
bool operator== (UnrolledLL<T>& left, UnrolledLL<T>& right) {
  if (left.size() != right.size()) return false;
  typename UnrolledLL<T>::iterator left_itr = left.begin();
  typename UnrolledLL<T>::iterator right_itr = right.begin();
  // walk over both lists, looking for a mismatched value
  while (left_itr != left.end()) {
    if (*left_itr != *right_itr) return false;
    left_itr++; right_itr++;
  }
  return true;
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ return !(left==right); }

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  //if there is just one element, treat it as a normal ds list
  if (itr.ptr_->num_elem == 1){
    --size_;
    iterator result(itr.ptr_->next_);
    // One node left in the list.
    if (itr.ptr_ == head_ && head_ == tail_) {
      head_ = tail_ = 0;
    }
    // Removing the head in a list with at least two nodes
    else if (itr.ptr_ == head_) {
      head_ = head_->next_;
      head_->prev_ = 0;
    }
    // Removing the tail in a list with at least two nodes
    else if (itr.ptr_ == tail_) {
      tail_ = tail_->prev_;
      tail_->next_ = 0;
    }
    // Normal remove
    else {
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete itr.ptr_;
    return result;
  }
  //else, shift everything starting from the offset over one and decrement size and number of elements
  else{
    if (itr.ptr_->num_elem > 0){
      for (unsigned int i = itr.offset; i<itr.ptr_->num_elem; i++){
        itr.ptr_->value_[i] = itr.ptr_->value_[i+1];
      }
      --itr.ptr_->num_elem;
      --size_;
      //if at the end of the node, increment the itr
      if (itr.offset >= itr.ptr_->num_elem){
        itr++;
      }
    }
    return itr;
  }
  
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  //if there is still space in the node shift everything from the end to the offset by one spot left
  if (itr.ptr_->num_elem < NUM_ELEMENTS_PER_NODE){
    for (unsigned int i = itr.ptr_->num_elem; i > itr.offset; i--){
      itr.ptr_->value_[i] = itr.ptr_->value_[i-1];
    }
    itr.ptr_->value_[itr.offset] = v;
    ++size_;
    ++itr.ptr_->num_elem; 
  }
  //if space is full, create two nodes where one separates left of list and one separataes right of list
  //insert the value in the left node
  else{
    Node<T>* newp1 = new Node<T>;
    Node<T>* newp2 = new Node<T>;
    for (int i = 0; i < itr.offset; i++){
      newp1->value_[i] = itr.ptr_->value_[i];
      ++newp1->num_elem;
    }
    newp1->value_[itr.offset] = v;
    ++newp1->num_elem;
    for (int i = itr.offset; i<itr.ptr_->num_elem; i++){
      newp2->value_[i-itr.offset] = itr.ptr_->value_[i];
      ++newp2->num_elem;
    }
    //logic to connect the nodes and delete the current node
    newp1->prev_ = itr.ptr_->prev_;
    itr.ptr_->prev_->next_= newp1;
    newp1->next_ = newp2;
    newp2->prev_ = newp1;
    newp2->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = newp2;
    delete itr.ptr_;
    itr.ptr_= newp2;
    ++size_;
  }
  return itr;
}


template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {
  size_ = old.size_;
  // Handle the special case of an empty list.
  if (size_ == 0) {
    head_ = tail_ = 0;
    return;
  }
  // Create a new head node.
  head_ = new Node<T>;
  for (int i = 0; i < old.head_->num_elem; i++){
    head_->value_[i] = old.head_->value_[i];
    ++head_->num_elem;
  }
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>;
    for (int i = 0; i< old_p->num_elem; i++){
      tail_->next_->value_[i] = old_p->value_[i];
      ++tail_->next_->num_elem;
    }
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}

template <class T>
void UnrolledLL<T>::destroy_list() {  
  Node<T>* i = head_;
  while(head_ != NULL)
  {
    head_ = i->next_;
    delete i;
    i = head_;
  }
  size_ = 0;
}

#endif