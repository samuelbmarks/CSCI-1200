#ifndef hashTable_h_
#define hashTable_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>


template < class KeyType, class HashFunc >
class hashTable {
private:
  typedef typename std::list<KeyType>::iterator hashTable_itr;

public:
  // THE ITERATOR CLASS
  class iterator {
  public:
    friend class hashTable;   // allows access to private variables
  private:
    
    // ITERATOR REPRESENTATION
    hashTable* m_hs;          
    int m_index;               // current index in the hash table
    hashTable_itr m_list_itr;  // current iterator at the current index

  private:
    // private constructors for use by the hashTable only
    iterator(hashTable* hs) : m_hs(hs), m_index(-1) {}
    iterator(hashTable* hs, int index, hashTable_itr loc)
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
        hashTable_itr p = m_list_itr; ++p;
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

public:
  // =================================================================
  // HASH SET IMPLEMENTATION
  
  // Constructor for the table accepts the size of the table.  Default
  // constructor for the hash function object is implicitly used.
  hashTable(unsigned int init_size = 10) : m_table(init_size), m_size(0) {}
  
  // Copy constructor just uses the member function copy constructors.
  hashTable(const hashTable<KeyType, HashFunc>& old) 
    : m_table(old.m_table), m_size(old.m_size) {}

  ~hashTable() {}

  hashTable& operator=(const hashTable<KeyType,HashFunc>& old) {
    if (&old != this) {
      this->m_table = old.m_table;
      this->m_size = old.m_size;
      this->m_hash = old.m_hash;
    }
    return *this;
  }

  unsigned int size() const { return m_size; }


  // Insert the key if it is not already there.
  std::pair< iterator, bool > insert(KeyType const& key) {
    const float LOAD_FRACTION_FOR_RESIZE = 1.25;

    if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size())
      this->resize_table(2*m_table.size()+1);

    unsigned int hash_value = m_hash(key);
    unsigned int index = hash_value % m_table.size();

    hashTable_itr hli = m_table[index].begin();
    for(; hli != m_table[index].end(); ++hli){
      if( (*hli) == key ){
        hashTable::iterator itr(this, index, hli);
        return std::make_pair(itr, false);
      }
    }
    m_table[index].push_front(key);
    m_size++;
    hli = m_table[index].begin();
    iterator itr(this, index, hli);
    return std::make_pair(itr, true);
  }

  // Find the key, using hash function, indexing and list find
  iterator find(const KeyType& key) {
    unsigned int hash_value = m_hash(key);
    unsigned int index = hash_value % m_table.size();
    hashTable_itr p = std::find(m_table[index].begin(),
				 m_table[index].end(), key);
    if (p == m_table[index].end())
      return this->end();
    else
      return iterator(this, index, p);
  }

  // Erase the key 
  int erase(const KeyType& key) {
    // Find the key and use the erase iterator function.
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

    // Implement this function for Lab 11, Checkpoint 2, Part 1
    for (unsigned int i = 0; i < m_table.size(); ++i){
      if( !m_table[i].empty() ){
        hashTable_itr hli = m_table[i].begin();
        return iterator(this, i, hli);
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
  
  // A public print utility.
  void print(std::ostream & ostr) {
    for (unsigned int i=0; i<m_table.size(); ++i) {
      ostr << i << ": ";
      for (hashTable_itr p = m_table[i].begin(); p != m_table[i].end(); ++p)
        ostr << "     " << p->getTitle();
      ostr << std::endl;
    }
  }

private:
  void resize_table(unsigned int new_size) {

    // Implement this function for Lab 11, Checkpoint 2, Part 2
    std::vector< std::list<KeyType> > ntable(new_size);
    for(iterator itr = this->begin(); itr != this->end(); ++itr){
      unsigned int hash_value = m_hash(*itr);
      unsigned int index = hash_value % new_size;
      ntable[index].push_front(*itr);
    }
    m_table = ntable;
  }
};
#endif