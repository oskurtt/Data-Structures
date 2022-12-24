#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>


template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

  void percolate_up (int index){
    int parent = (index-1)/2;
    while (parent >= 0){
      if (m_heap[parent] > m_heap[index]){
        int tmp = m_heap[index];
        m_heap[index] = m_heap[parent];
        m_heap[parent] = tmp;
        index = parent;
        parent = (parent-1)/2;
      }
      else break;
    }

  }

  void percolate_down (int index){
    int left = (index*2) + 1;
    int right = (index*2) + 2;
    int child;

    while (left < m_heap.size()) {
      if (right < m_heap.size() && m_heap[right] < m_heap[left])
          child = right; 
      else 
          child = left; 

      if (m_heap[index] >= m_heap[child]) {
          int temp = m_heap[index]; 
          m_heap[index] = m_heap[child]; 
          m_heap[child] = temp;

          index = child; 
          left = (index*2)+1; 
          right = (index*2)+2; 
      }
      else break; 
    }
}
public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    for (int i = 0; i < values.size(); i++){
      push(values[i]);
    }  
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry);
    percolate_up(m_heap.size()-1);
  }

  void pop() 
  {
    m_heap[0] = m_heap.back(); 
    m_heap.pop_back(); 
    percolate_down(0); 
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap(this->m_heap);
    {
        int size = m_heap.size(); 
        int left;
        int right; 

        for (int i = 0; i < size; i++) {
            left = (2*i)+1; 
            right = (2*i)+2;  

            if ((left < size && m_heap[i] >= m_heap[left]) || (right < size && m_heap[i] >= m_heap[right]))
                return false; 
        }
        return true; 
    }
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
        int size = heap.size(); 
        int left;
        int right; 

        for (int i = 0; i < size; i++) {
            left = (2*i)+1; 
            right = (2*i)+2;  

            if ((left < size && heap[i] >= heap[left]) || (right < size && heap[i] >= heap[right]))
                return false; 
        }
        return true; 
    }

  //  A utility to print the contents of the heap.  Use it for debugging.
  void print_heap( std::ostream & ostr )
  {
    for ( unsigned int i=0; i<m_heap.size(); ++i )
      ostr << i << ": " << m_heap[i] << std::endl;
  }
  
};


template <class T>
void heap_sort( std::vector<T> & v )
{
  for (int index = v.size()-1; index >= 0; index--){
    int left = (index*2) + 1;
    int right = (index*2) + 2;
    int child;

    while (left < v.size()) {
      if (right < v.size() && v[right] < v[left])
          child = right; 
      else 
          child = left; 

      if (v[index] >= v[child]) {
          T temp = v[index]; 
          v[index] = v[child]; 
          v[child] = temp;

          index = child; 
          left = (index*2)+1; 
          right = (index*2)+2; 
      }
      else break; 
    }
  }
  int s = v.size();
  while (s>0){
      int tmp = v[0];
      v[0] = v[s-1];
      v[s-1] = tmp;
      int index = 0;
      int left = (index*2) + 1;
      int right = (index*2) + 2;
      int child;
      s--;
      while (left < s) {
        if (right < s && v[right] < v[left])
            child = right; 
        else 
            child = left; 

        if (v[index] >= v[child]) {
            T temp = v[index]; 
            v[index] = v[child]; 
            v[child] = temp;

            index = child; 
            left = (index*2)+1; 
            right = (index*2)+2; 
        }
        else {
          break;
        }
      }
      
  }/*
  priority_queue<T> pq = v; 
  v.clear();  
  while (pq.size()!=0) {
      v.push_back(pq.top()); 
      pq.pop(); 
  }*/
}

#endif
