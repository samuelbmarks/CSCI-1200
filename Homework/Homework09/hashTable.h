#ifndef hashTable_h_
#define hashTable_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template < class KeyType, class HashFunc >
class hashTable {
private:
  typedef typename std::list<KeyType>::iterator hashTable_list_itr;

public:
  // THE ITERATOR CLASS
  class iterator {
  public:
    friend class hashTable;   // allows access to private variables
  private:
    
    // ITERATOR REPRESENTATION
    hashTable* m_hs;          
    int m_index;               // current index in the hash table
    hashTable_list_itr m_list_itr;  // current iterator at the current index

  private:
    // private constructors for use by the hashTable only
    iterator(hashTable* hs) : m_hs(hs), m_index(-1) {}
    iterator(hashTable* hs, int index, hashTable_list_itr loc)
      : m_hs(hs), m_index(index), m_list_itr(loc) {}

  public:
    // Ordinary constructors & assignment operator
    iterator() : m_hs(0), m_index(-1)  {}
    iterator(iterator const& itr)
      : m_hs(itr.m_hs), m_index(itr.m_index), m_list_itr(itr.m_list_itr) {}
    iterator&  operator=(const iterator& old) {
      m_hs = old.m_hs;
      m_index = old.m_index; 
      m_list_itr = old.m_list_itr;
      return *this;
    }

    // The dereference operator need only worry about the current
    // list iterator, and does not need to check the current index.
    const KeyType& operator*() const { return *m_list_itr; }

    // The comparison operators must account for the list iterators
    // being unassigned at the end.
    friend bool operator== (const iterator& lft, const iterator& rgt)
    { return lft.m_hs == rgt.m_hs && lft.m_index == rgt.m_index && 
	(lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr); }
    friend bool operator!= (const iterator& lft, const iterator& rgt)
    { return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index || 
	(lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr); }
    // increment and decrement
    iterator& operator++() { 
      this->next();
      return *this;
    }
    iterator operator++(int) {
      iterator temp(*this);
      this->next();
      return temp;
    }
    iterator & operator--() { 
      this->prev();
      return *this;
    }
    iterator operator--(int) {
      iterator temp(*this);
      this->prev();
      return temp;
    }

  private:
    // Find the next entry in the table
    void next() {
      ++m_list_itr;  // next item in the list

      // If we are at the end of this list
      if (m_list_itr == m_hs->m_table[m_index].end()) {
        // Find the next non-empty list in the table
        for (++m_index; 
             m_index < int(m_hs->m_table.size()) && m_hs->m_table[m_index].empty();
             ++m_index) {}
        
        // If one is found, assign the m_list_itr to the start
        if (m_index != int(m_hs->m_table.size()))
          m_list_itr = m_hs->m_table[m_index].begin();
        
        // Otherwise, we are at the end
        else
          m_index = -1;
      }
    }

    // Find the previous entry in the table
    void prev() {
      // If we aren't at the start of the current list, just decrement
      // the list iterator
      if (m_list_itr != m_hs->m_table[m_index].begin())
	       m_list_itr-- ;

      else {
        // Otherwise, back down the table until the previous
        // non-empty list in the table is found
        for (--m_index; m_index >= 0 && m_hs->m_table[m_index].empty(); --m_index) {}

        // Go to the last entry in the list.
        m_list_itr = m_hs->m_table[m_index].begin();
        hashTable_list_itr p = m_list_itr; ++p;
        for (; p != m_hs->m_table[m_index].end(); ++p, ++m_list_itr) {}
      }
    }
  };
  // end of ITERATOR CLASS
  // =================================================================
private:
  // =================================================================
  // HASH SET REPRESENTATION
  std::vector< std::list<KeyType> > m_table;  // actual table
  HashFunc m_hash;                            // hash function
  unsigned int m_size;                        // number of keys
  float occupancy;

public:
  // =================================================================
  // HASH SET IMPLEMENTATION
  
  // Constructor for the table accepts the size and occupancy of the table.
  // Default constructor for the hash function object is implicitly used.
  hashTable(unsigned int init_size = 100, float occ = 0.5) : m_table(init_size), m_size(0), occupancy(occ) {}
  
  // Copy constructor just uses the member function copy constructors.
  hashTable(const hashTable<KeyType, HashFunc>& old) 
    : m_table(old.m_table), m_size(old.m_size) {}

  ~hashTable() {}

  //function to change the size of the table
  void editSize(unsigned int init){
    m_table = vector<std::list<KeyType>>(init);
  }

  //function to change the occupancy of the table
  void editOcc(float occ){
    occupancy = occ;
  }

  hashTable& operator=(const hashTable<KeyType,HashFunc>& old) {
    if (&old != this) {
      this->m_table = old.m_table;
      this->m_size = old.m_size;
      this->m_hash = old.m_hash;
    }
    return *this;
  }

  unsigned int size() const { return m_size; }


  // insert: an insert in this table will never fail because no duplicate Movie objects will be inserted 
  // (okay to assume movie file does not contain duplicate movies) and because table will always have space 
  // open for object to be added because of occupancy control
  void insert(KeyType& key) {
    const float LOAD_FRACTION_FOR_RESIZE = occupancy; //setting occupancy

    if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size()) //checks for occupancy rule
      resize_table(2*m_table.size());

    unsigned int hash_value = m_hash(key.first.first); //getting hash_value by passing in the first of the two Movie objects
    unsigned int index = hash_value % m_table.size(); //getting index

    key.second = hash_value; //storing the hash value in order to compare when checking if object belongs in bucket 

    hashTable_list_itr itr = m_table[index].begin(); //setting an iterator to start of bucket

    if (m_table[index].empty()){ //nothing in bucket, okay to add
      m_table[index].push_front(key); //adding key
      m_size++; //increasing table size
    }
    else if (!m_table[index].empty() && itr->second == key.second){ //bucket is not empty but key belongs
      m_table[index].push_front(key); //adding key, hash_value match
      m_size++; //increasing table size
    }
    else{ //LINEAR PROBING
      bool found = false;
      while (!m_table[index].empty() && index < m_table.size()){ //checking each bucket to see if key belongs until it finds an empty bucket
        hashTable_list_itr itr = m_table[index].begin();
        if (itr->second == key.second){
          m_table[index].push_front(key); //adding key, hash_value matches
          m_size++; //increasing table size
          found = true;
          break;
        }
        index++;
      }
      if (!found && index < m_table.size()){ //if the index is less than the size of the table and a bucket has not been found yet
        m_table[index].push_front(key); //add key, bucket is empty
        m_size++; //increase table size
      }
      else if (!found){ //the index is passed the end of the table, so now we must go back to the front of the table to check for an open space
        index = 0; //index is set back to zero
        while (!m_table[index].empty() && index < m_table.size()){ //finding the nearest index of the table whose list is empty (before end of table)
          hashTable_list_itr itr = m_table[index].begin();
          if (itr->second == key.second){
            m_table[index].push_front(key); //adding key, hash_value matches
            m_size++; //increasing table size
          break;
        }
          index++;
        }
        m_table[index].push_front(key); //insert key at the first empty bucket
        m_size++; //increase table size
      }
    }
  }

  // Find the key(s) that match the input, returned is the index that contain the matching key(s) (-1 if otherwise)
  int find(KeyType& key) {
    unsigned int hash_value = m_hash(key.first.first); //getting hash_value
    unsigned int index = hash_value % m_table.size(); //getting index

    key.second = hash_value; //storing hash_value


    hashTable_list_itr itr = m_table[index].begin();
    if (itr->second == key.second){ //hash_values match, all keys in bucket match
      return index;
    }
    while (index < m_table.size()){ //key did not match, so you must linearly probe to find, check each index until the end
      if (m_table[index].empty()){
        return -1;
      }  
      else{
        hashTable_list_itr itr = m_table[index].begin();
        if (itr->second == key.second){
          return index;
        }
        else{
          index++;
        }
      } 
    }
    index = 0; //index is set back to zero, start probing from beginning
    while (!m_table[index].empty()){
      hashTable_list_itr itr = m_table[index].begin();
      if (itr->second == key.second){
        return index;
      }
      else{
        index++;
      } 
    }
    return -1;
  }

  // Erase the key 
  int erase(const KeyType& key) {
    iterator p = find(key);
    if (p == end())
      return 0;
    else {
      erase(p);
      return 1;
    }
  }

  // Erase at the iterator
  void erase(iterator p) {
    m_table[ p.m_index ].erase(p.m_list_itr);
  }

  // Find the first entry in the table and create an associated iterator
  iterator begin() {
    for (unsigned int i = 0; i < m_table.size(); ++i){
      if( !m_table[i].empty() ){
        hashTable_list_itr itr = m_table[i].begin();
        return iterator(this, i, itr);
      }
    }
    return iterator(NULL);
  }

  // Create an end iterator.
  iterator end() {
    iterator p(this);
    p.m_index = -1;
    return p;
  }
  
  // helper function for visualization
  void print(std::ostream & ostr) {
    int counter = 0;
    for (unsigned int i=0; i<m_table.size(); ++i) {
      ostr << i << ": ";
      if (m_table[i].size() > 0)
      for (hashTable_list_itr p = m_table[i].begin(); p != m_table[i].end(); ++p){
          counter++;
          ostr << "    " << p->first.second.getTitle() << " " << counter << " " << p->second;
      }
      ostr << std::endl;
    }
  }

  // void print function that helps print all of the keys in a particular bucket, i
  // also takes in a map of actor information in order to print full actor information
  void printIndex(unsigned int i, map<string,string>& actors){
    cout << "Printing " << m_table[i].size() << " result(s):" << endl;
    hashTable_list_itr itr = m_table[i].begin();
    while (itr != m_table[i].end()){
      itr->first.second.print(actors); //printing second Movie object, as this is the object will all of the information filled in
      itr++;
    }
  }

private:
  // void function that resizes the table to a new size that is passed in
  void resize_table(unsigned int new_size) {
    vector<KeyType> tmp;
    for (iterator itr = begin(); itr != end(); itr++){
      tmp.push_back(*itr);
    }
    m_table = vector<std::list<KeyType>>(new_size);
    m_size = 0;
    for (unsigned int i = 0; i < tmp.size(); i++){
      insert(tmp[i]);
    }
  }
};

#endif