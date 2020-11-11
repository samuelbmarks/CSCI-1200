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
  Node() : num_values_(0), next_(NULL), prev_(NULL) {
    values_ = new T[NUM_ELEMENTS_PER_NODE];
  }
  //creates a new node given a value (used in push_front and push_back when unrolled list is empty or node is full)
  Node(const T& v) : num_values_(0), next_(NULL), prev_(NULL) {
    values_ = new T[NUM_ELEMENTS_PER_NODE];
    values_[0] = v;
    num_values_++;
  }

  // REPRESENTATION
  T* values_; //stores values
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
  unsigned int nodes() const { return num_nodes_; }
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
  void print(ostream& out) const;

  typedef list_iterator<T> iterator;
  iterator erase(iterator itr);
  iterator insert(iterator itr, const T& v);
  iterator begin() { return iterator(head_,0); }
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

// -----------------------------------------------------------------
// LIST CLASS IMPLEMENTATION
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
void UnrolledLL<T>::push_front(const T& v) {
  // if list is empty, creates a new node will new value
  if (empty()){
    head_ = tail_ = new Node<T>(v);
    num_nodes_++;
    size_++;
  }
  // if list is not empty
  else{
    //copy values in head node into copy array, set first offset in head node each to value, 
    //and reassin values in copy back into the correct, shifted index location
    if (head_->num_values_ < 6){
      T* copy = head_->values_;
      head_->values_ = new T[NUM_ELEMENTS_PER_NODE];
      head_->num_values_++;
      size_++;
      head_->values_[0] = v;
      for (unsigned int i = 1; i < head_->num_values_; i++){
        head_->values_[i] = copy[i-1];
      }
      delete [] copy;
    }
    // if node is full
    else{
      //create a new node with new value and attach it to current nodes and assign it to head
      Node<T>* newNode = new Node<T>(v);
      num_nodes_++;
      size_++;
      newNode->next_ = head_;
      head_->prev_ = newNode;
      head_ = newNode;
    }
  }
}

template <class T>
void UnrolledLL<T>::pop_front() {
  //create iterator at the front of the list and call erase, removing that value
  iterator pop(head_, 0);
  erase(pop);
}

template <class T>
void UnrolledLL<T>::push_back(const T& v) {
  //if list is empty
  if (empty()){
    //create a new node with given value
    head_ = tail_ = new Node<T>(v);
    num_nodes_++;
  }
  //if list is not empty
  else{
    //if node is not full, assign new value to the next open index at the end of array
    if (tail_->num_values_ < 6){
      tail_->values_[tail_->num_values_] = v;
      tail_->num_values_++;
    }
    //if node is full, create a new node with new value and attach and assign it to the list (tail)
    else{
      Node<T>* newNode = new Node<T>(v);
      num_nodes_++;
      newNode->prev_ = tail_;
      tail_->next_ = newNode;
      tail_ = newNode;
    }
  }
  size_++;
}

template <class T>
void UnrolledLL<T>::pop_back() {
  //create iterator at the end of the list and call erase, removing that value
  iterator pop(tail_, tail_->num_values_-1);
  erase(pop);
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
bool operator!= (UnrolledLL<T>& left, UnrolledLL<T>& right){ 
  return !(left==right); 
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr) {
  // can only delete value if the iterator is not NULL and the node is not empty
  assert (itr.ptr_ != NULL && !empty());
  //regular case (if there is more than one value left in node)
  if (itr.ptr_->num_values_ > 1) {
    T* copy = new T[NUM_ELEMENTS_PER_NODE];
    for (int i = 0; i < itr.offset_; i++){
      copy[i] = itr.ptr_->values_[i];
    }
    for(int i = itr.offset_+1; i < itr.ptr_->num_values_; i++){
      copy[i-1] = itr.ptr_->values_[i];  
    }
    for(int i = 0; i < itr.ptr_->num_values_-1; i++){
      itr.ptr_->values_[i] = copy[i];
    }
    delete [] copy;
    if(itr.offset_>0){
        itr.offset_--;
    }
    itr.ptr_->num_values_--;
    size_--;
    return itr;
  }
  // case if there is only one value left in node (node must be removed completely)
  else {  
    // case if the node with one value is the head node
    if (itr.ptr_ == head_){
      head_= itr.ptr_->next_;
      head_->next_->prev_ = NULL; 
      delete itr.ptr_;
    }
    // case if the node with one value is the tail node
    else if (itr.ptr_ == tail_){
      tail_ = itr.ptr_->prev_;
      itr.ptr_->prev_->next_ = NULL;
    }
    // case if there is only one node, hence the node is the head and the tail node
    else if (itr.ptr_ == head_ && itr.ptr_ == tail_){
      head_ = tail_ = NULL;
    }
    // "else" case (if the node is neither the head nor the tail node)
    else{
      itr.ptr_->prev_->next_ = itr.ptr_->next_;
      itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    }
    delete [] itr.ptr_->values_;
    delete itr.ptr_;
    num_nodes_--;
    size_--;
    return itr;
  }  
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v) {
  // can only insert a value if the iterator is not NULL
  if (itr != NULL){
    // case if node is empty, create new node with new value
    if (empty()){
      head_ = tail_ = new Node<T>(v);
      num_nodes_++;
      size_++;
    }
    // cases if the node is full
    if (itr.ptr_->num_values_ == NUM_ELEMENTS_PER_NODE){
      // pointers to store values
      T* original = itr.ptr_->values_;
      T* copy = itr.ptr_->values_;
     //copy values 
      for (unsigned int i = 0; i < itr.offset_; i++){
        itr.ptr_->values_[i] = copy[i];
      }
      // create new node for the rest of the values after new value
      Node<T>* newNode = new Node<T>();
      T* newArr = new T[NUM_ELEMENTS_PER_NODE];
      newArr[itr.offset_]=v;
      newNode->values_=newArr;
      newNode->num_values_++;
      num_nodes_++;
      // connect new node
      Node<T>* tmp = itr.ptr_->next_->next_;
      itr.ptr_->next_=newNode;
      newNode->prev_=itr.ptr_;
      newNode->next_=tmp;
      tmp->prev_=newNode;
       
    }
    // cases if node is not full, hence no creation of new nodes are necessary
    else{
      unsigned int amount = itr.ptr_->num_values_;
      T* copy = itr.ptr_->values_;
      itr.ptr_->values_ = new T[NUM_ELEMENTS_PER_NODE];
      for (unsigned int i = 0; i < itr.offset_; i++){
        head_->values_[i] = copy[i];
      }
      itr.ptr_->values_[itr.offset_] = v;
      for (unsigned int i = itr.offset_; i < amount; i++){
        itr.ptr_->values_[i-itr.offset_] = copy[i];
      }
      delete [] copy;
    }
  }
  size_++;
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
  head_ = new Node<T>(old.head_);
  // tail_ will point to the last node created and therefore will move
  // down the new list as it is built
  tail_ = head_;
  // old_p will point to the next node to be copied in the old list
  Node<T>* old_p = old.head_->next_;
  // copy the remainder of the old list, one node at a time
  while (old_p) {
    tail_->next_ = new Node<T>(old_p);
    tail_->next_->prev_ = tail_;
    tail_ = tail_->next_;
    old_p = old_p->next_;
  }
}

template <class T>
void UnrolledLL<T>::destroy_list() {
/*  iterator itr = begin();
  while(itr != end()) {
    itr = erase(itr);
  }*/
}

template <class T>
void UnrolledLL<T>::print(ostream& ostr) const {
  iterator itr(head_,0);
  if (!empty()){
    ostr << "UnrolledLL, size: " << size_ << endl;
    for(int i = 1; i <= num_nodes_; ++i){
      ostr << " node: [" << itr.ptr_->num_values_ << "] ";
      for(int j = 0; j < itr.ptr_->num_values_; ++j){
        ostr << " " << itr.ptr_->values_[j];
      }
      ostr << endl;
      if (itr.ptr_->next_){
        itr.ptr_ = itr.ptr_->next_;
      }
    }
  }
  else{
    ostr << "UnrolledLL is empty." << endl << endl;
  }
}

#endif