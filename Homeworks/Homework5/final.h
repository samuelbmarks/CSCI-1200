#ifndef UnrolledLL_h_
#define UnrolledLL_h_
// A simplified implementation of a generic list container class,
// including the iterator, but not the const_iterators.  Three
// separate classes are defined: a Node class, an iterator class, and
// the actual list class.  The underlying list is doubly-linked, but
// there is no dummy head node and the list is not circular.
#include <cassert>
using namespace std;

const int NUM_ELEMENTS_PER_NODE = 6;

// -----------------------------------------------------------------
// NODE CLASS
template <class T>
class Node {
public:
  //initializers and copy constructer
  Node() : num_values_(0), next_(NULL), prev_(NULL) {}
  Node(const Node<T>& old) : num_values_(old.num_values_), next_(old.next_), prev_(old.prev_) {
    for (unsigned int i = 0; i < num_values_; i++)
      values_[i] = old.values_[i];
  }

  // REPRESENTATION
  T values_[NUM_ELEMENTS_PER_NODE];
  Node<T>* next_;
  Node<T>* prev_;
  unsigned int num_values_;
};

// A "forward declaration" of this class is needed
template <class T> class UnrolledLL;

// -----------------------------------------------------------------
// LIST ITERATOR
template <class T>
class list_iterator {
public:
  // default constructor, copy constructor, & destructor
  list_iterator() : ptr_(NULL), offset_(0) {}
  list_iterator(Node<T>* p) : ptr_(p), offset_(0) {}
  list_iterator(Node<T>* p, unsigned int o) : ptr_(p), offset_(o) {}
  list_iterator(const list_iterator<T>& old) : ptr_(old.ptr_), offset_(old.offset_) {}
  ~list_iterator() {}
  
  // assignment operator
  list_iterator<T>& operator=(const list_iterator<T>& old) {
    ptr_ = old.ptr_;  
    offset_ = old.offset_;
    return *this; 
  }

  // dereferencing operator gives access to the value at the pointer
  T& operator*()  { return ptr_->values_[offset_]; }

  // increment & decrement operators
  list_iterator<T>& operator++() { // pre-increment, e.g., ++iter
    if (offset_ == ptr_->num_values_-1){
      if (ptr_ != NULL){
        ptr_ = ptr_->next_;
        offset_ = 0;
      }
    }
    else{
      offset_++;
    }
    return *this;
  }
  list_iterator<T> operator++(int) { // post-increment, e.g., iter++
    list_iterator<T> temp(*this);
    if (offset_ == ptr_->num_values_-1){
      if (ptr_ != NULL){
        ptr_ = ptr_->next_;
        offset_ = 0;
      }
    }
    else{
      offset_++;
    }
    return temp;
  }
  list_iterator<T>& operator--() { // pre-decrement, e.g., --iter
    if (offset_ == 0){
      if (ptr_ != NULL){
        ptr_ = ptr_->prev_;
        offset_ = ptr_->num_values_-1;
      }
    }
    else{
      offset_--;
    }
    return *this;
  }
  list_iterator<T> operator--(int) { // post-decrement, e.g., iter--
    list_iterator<T> temp(*this);
    if (offset_ == 0){
      if (ptr_ != NULL){
        ptr_ = ptr_->prev_;
        offset_ = ptr_->num_values_-1;
      }
    }
    else{
      offset_--;
    }
    return temp;
  }

  // the UnrolledLL class needs access to the private ptr_ member variable
  friend class UnrolledLL<T>;

  // Comparions operators are straightforward
  bool operator==(const list_iterator<T>& r) const {
    return ptr_ == r.ptr_ && offset_ == r.offset_;}
  bool operator!=(const list_iterator<T>& r) const {
    return ptr_ != r.ptr_ || offset_ != r.offset_; }

private:
  // REPRESENTATION
  Node<T>* ptr_;    // ptr to node in the list
  unsigned int offset_;
};

// -----------------------------------------------------------------
// LIST CLASS DECLARATION
// Note that it explicitly maintains the size of the list.
template <class T>
class UnrolledLL {
public:
  // default constructor, copy constructor, assignment operator, & destructor
  UnrolledLL() : head_(NULL), tail_(NULL), size_(0), num_nodes_(0) {}
  UnrolledLL(const UnrolledLL<T>& old) { this->copy_list(old); }
  UnrolledLL& operator= (const UnrolledLL<T>& old);
  ~UnrolledLL() { this->destroy_list(); }

  // simple accessors & modifiers
  unsigned int size() const { return size_; }
  bool empty() const { return head_ == NULL; }
  void clear() { this->destroy_list(); }

  // read/write access to contents
  const T& front() const { return head_->values_[0];  }
  T& front() { return head_->values_[0]; }
  const T& back() const { return tail_->values_[tail_->num_values_-1]; }
  T& back() { return tail_->values_[tail_->num_values_-1]; }

  // modify the linked list structure
  void push_front(const T& v);
  void pop_front();
  void push_back(const T& v);
  void pop_back();

  // print helper function
  void print(ostream& out);
  void print_node(list_iterator<T> iter, ostream& out);

  typedef list_iterator<T> iterator;
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
  unsigned int num_nodes_;
};

template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator= (const UnrolledLL<T>& old) {
  // check for self-assignment
  if (&old != this) {
    this->destroy_list();
    this->copy_list(old);
  }
  return *this;
}

template <class T>
void UnrolledLL<T>::push_front(const T& v) {                     //PUSH_FRONT()
  if (empty()){
    head_ = tail_ = new Node<T>();
    head_->values_[0] = v;
    size_++;
    num_nodes_++;
  }
  else{
    if (head_->num_values_ < 6){
      Node<T>* temp = new Node<T>();
      temp = head_;
      head_->num_values_++;
      size_++;
      head_->values_[0] = v;
      for (unsigned int i = 1; i < head_->num_values_; i++){
        head_->values_[i] = temp->values_[i-1];
      }
    }
    else{
      Node<T>* newNode = new Node<T>;
      head_->values_[0] = v;
      size_++;
      num_nodes_++;
      newNode->next_ = head_;
      head_->prev_ = newNode;
      head_ = newNode;
    }
  }
}

template <class T>
void UnrolledLL<T>::pop_front() {                                //POP_FRONT()
  iterator pop(head_, 0);
  erase(pop);
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {                     //PUSH_BACK()
  if (empty()) {
    Node<T>* newNode = new Node<T>;
    head_ = tail_ = newNode;
    tail_->values_[0] = v;
    tail_->num_values_++;
    size_++;
    num_nodes_++;
  }
  // normal case:  at least one node already
  else {
    if (tail_->num_values_ < NUM_ELEMENTS_PER_NODE){
      tail_->values_[tail_->num_values_] = v;
      tail_->num_values_++;
      size_++;
    }
    else {
      Node<T>* newNode = new Node<T>;
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
      tail_->values_[0] = v;
      tail_->num_values_++;
      size_++;
      num_nodes_++;
    }
  }
}

template <class T>
void UnrolledLL<T>::pop_back() {                                 //POP_BACK()
  iterator pop(tail_, tail_->num_values_-1);
  erase(pop);
}

template <class T>
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ 
  return !(left==right); 
}

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
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {

}

template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& old) {

}

template <class T>
void UnrolledLL<T>::destroy_list() {

}

template <class T>
void UnrolledLL<T>::print(ostream& out) {
  typename UnrolledLL<T>::iterator itr = begin();
  out << "UnrolledLL, size: " << size_ << endl;
  for (unsigned int i = 0; i < num_nodes_; i++){
    print_node(itr,out);
    itr.ptr_->next_;
  }
}

template <class T>
void UnrolledLL<T>::print_node(list_iterator<T> iter, ostream& out) {
  out << "node:[" << iter.ptr_->num_values_ << "]";
  for (unsigned int i = 0; i < iter.ptr_->num_values_-1; i++){
    out << " " << iter.ptr_->values_[i];
  }
  out << endl;
}

#endif