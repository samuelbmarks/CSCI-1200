#ifndef priority_queue_h_
#define priority_queue_h_

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

template <class T>
class priority_queue {
private:
  std::vector<T> m_heap;

public:
  priority_queue() {}

  priority_queue( std::vector<T> const& values )
  {
    m_heap = std::vector<T>(values.size()); //creating vectors of size of the the vector passed in
    for (int i = values.size()-1; i >= 0; --i) //moving backwards through values, assgining values into m_heap
      m_heap[i] = values[i];

    for (int i = 0; i < values.size(); i++)
      percolate_up(i);
  }

  const T& top() const 
  {
    assert( !m_heap.empty() );
    return m_heap[0]; 
  }

  void percolate_up(unsigned int i){
    while (i != 0 && m_heap[i] < m_heap[(i-1)/2]){
        swap(m_heap[i],m_heap[(i-1)/2]);
        i = (i-1)/2;  //checking that i is greater than zero (not the first index/top)
    }
  }

  void push( const T& entry )
  {
    m_heap.push_back(entry); //adding entry
    unsigned int i = m_heap.size()-1; //setting i to back of vector
    percolate_up(i); //percolate up from i
  }

  void percolate_down(unsigned int i){
    while(i <= m_heap.size()/2){ //while i is less than or equal to halfway point in heap
      unsigned int j = 0;

      if (2*i+2 < m_heap.size() && m_heap[2*i+2] < m_heap[2*i+1] ) //if right child is greater than left child
        j = 2*i+2; 
      else
        j = 2*i+1;

      if(m_heap[j] < m_heap[i]){
        T temp = m_heap[i];
        m_heap[i] = m_heap[j];
        m_heap[j] = temp;
        i = j;
      } 
      else
        break;
    }
  }

  void pop() 
  {
    assert( !m_heap.empty() );
    m_heap[0] = m_heap[m_heap.size()-1];
    m_heap.pop_back();
    percolate_down(0);
  }

  int size() { return m_heap.size(); }
  bool empty() { return m_heap.empty(); }


  //  The following three functions are used for debugging.

  //  Check to see that internally the heap property is realized.
  bool check_heap( )
  {
    return this->check_heap( this->m_heap );
  }

  //  Check an external vector to see that the heap property is realized.
  bool check_heap( const std::vector<T>& heap )
  {
    if (heap.size() <= 1) { return true; }
    
    for(unsigned int i = 0; i < heap.size()/2; ++i){
      if (2*i+1 < heap.size() && heap[i] > heap[2*i+1] ) { return false; } 
      if (2*i+2 < heap.size() && heap[i] > heap[2*i+2] ) { return false; }
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

#endif