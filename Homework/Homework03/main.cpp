// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases 
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "table.h"

using namespace std;


// helper testing functions
void SimpleTest();
void StudentTests();
void BatchTest(const char* filename, int num);
void ExtraCreditTests();


int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
    std::cout << "Simple test completed." << std::endl;
    cout << endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;    
    
    //
    // uncomment if you have implemented the extra credit features
    //
    ExtraCreditTests();
    //

 } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << std::endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}

void SimpleTest() {

  // create a table with dimensions 2x5, where all entries are '.'
  Table<char> t(2,5,'.');
  assert (t.get(0,0) == '.');
  assert (t.get(1,4) == '.');
  assert (t.get(1,2) == '.');
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;
  
  // intialize the values in the table
  t.set(0,0,'a');
  t.set(0,1,'b');
  t.set(0,2,'c');
  t.set(0,3,'d');
  t.set(0,4,'e');
  t.set(1,0,'f');
  t.set(1,1,'g');
  t.set(1,2,'h');
  t.set(1,3,'i');
  t.set(1,4,'j');
  assert (t.get(0,0) == 'a');
  assert (t.get(1,2) == 'h');
  assert (t.get(1,4) == 'j');
  t.print();
  std::cout << "set & get tests completed" << std::endl;
  
  // =======================================================  
  // 
  //     UNCOMMENT THE SECTIONS BELOW AS YOU 
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================  

  // add a row
  std::vector<char> new_row; 
  new_row.push_back('A');
  new_row.push_back('B');
  new_row.push_back('C');
  new_row.push_back('D');
  new_row.push_back('E');
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;

  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;

  // add a column
  std::vector<char> new_col;
  new_col.push_back('X');
  new_col.push_back('Y');
  new_col.push_back('Z');
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;

  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;
  

  // example of the copy constructor
  Table<char> another(t);
  
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  //but future edits show they are different!
  another.set(1,2,'Q');
  assert (t.get(1,2) != another.get(1,2));
  

  std::vector<char> new_row2; 
  new_row2.push_back('A');
  new_row2.push_back('B');
  new_row2.push_back('C');
  new_row2.push_back('D');
  new_row2.push_back('E');
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;


  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.

}

void StudentTests() {

  //creating tables that store types other than char (int and string)
  Table<int> i1(5,5,1);
  Table<int> i2(3,4,10);
  Table<string> s1(5,5,"test");
  Table<string> s2(3,4,"string");
  assert (i1.get(0,0) == 1);
  assert (i1.get(2,3) == 1);
  assert (i2.get(0,0) == 10);
  assert (i2.get(2,3) == 10);
  assert (s1.get(0,0) == "test");
  assert (s1.get(2,3) == "test");
  assert (s2.get(0,0) == "string");
  assert (s2.get(2,3) == "string");
  i1.print();
  i2.print();
  s1.print();
  s2.print();
  cout << "constructor w/ other types test complete" << endl;

  //get & set tests with other types
  i1.set(0,0,2);
  i1.set(1,2,3);
  i2.set(1,3,20);
  i2.set(2,1,30);
  s1.set(0,4,"1234");
  s1.set(1,0,"5678");
  s2.set(1,1,"123456");
  s2.set(1,2,"789123");
  assert (i1.get(0,0) == 2);
  assert (i1.get(1,2) == 3);
  assert (i2.get(1,3) == 20);
  assert (i2.get(2,1) == 30);
  assert (s1.get(0,4) == "1234");
  assert (s1.get(1,0) == "5678");
  assert (s2.get(1,1) == "123456");
  assert (s2.get(1,2) == "789123");
  i1.print();
  i2.print();
  s1.print();
  s2.print();
  cout << "get & set w/ other types test complete" << endl;

  //copy constructor test
  Table<int> copy1(i1);
  assert (i1.numRows() == copy1.numRows());
  assert (i1.numColumns() == copy1.numColumns());
  for (unsigned  i = 0; i < i1.numRows(); i++) {   
    for (unsigned  j = 0; j < i1.numColumns(); j++) {
      assert (i1.get(i,j) == copy1.get(i,j));
    }
  }
  copy1.set(3,4,9);
    assert (i1.get(3,4) != copy1.get(3,4));

  Table<string> copy2(s1);
  assert (s1.numRows() == copy2.numRows());
  assert (s1.numColumns() == copy2.numColumns());
  for (unsigned  i = 0; i < s1.numRows(); i++) {   
    for (unsigned  j = 0; j < s1.numColumns(); j++) {
      assert (s1.get(i,j) == copy2.get(i,j));
    }
  }
  copy2.set(3,4,"meme");
    assert (s1.get(3,4) != copy2.get(3,4));
  
  i1.print();
  copy1.print();
  s1.print();
  copy2.print();
  cout << "copy constructor w/ other types test complete" << endl;

  //assignment operator tests
  i1 = i2;
  assert (i1.numRows() == i2.numRows());
  assert (i1.numColumns() == i2.numColumns());
  for (unsigned  i = 0; i < i2.numRows(); i++) {
    for (unsigned  j = 0; j < i2.numColumns(); j++) {
      assert (i1.get(i,j) == i2.get(i,j));
    }
  }
  i1.set(0,0,9);
    assert (i1.get(0,0) != i2.get(0,0));

  s1 = s2;
  assert (s1.numRows() == s2.numRows());
  assert (s1.numColumns() == s2.numColumns());
  for (unsigned  i = 0; i < s2.numRows(); i++) {
    for (unsigned  j = 0; j < s2.numColumns(); j++) {
      assert (s1.get(i,j) == s2.get(i,j));
    }
  }
  s1.set(0,0,"shhh");
    assert (s1.get(0,0) != s2.get(0,0));

  std::cout << "assignment operator test completed" << std::endl;

  /*
  //invalid request tests (commented out for final submission)
  Table<int> table1(10,10,4);
  
  //set & get invalid requests
  table1.set(12,15,9);
  table1.get(7,13);

  //push_back invalid requests
  vector<int> vec(4,4);

  table1.push_back_row(vec);
  table1.push_back_column(vec);

  //pop_back invalid requests
  Table<int> table2(0,0,3);

  table2.pop_back_row();
  table2.pop_back_column();
  */
}


void ExtraCreditTests() {

  // =======================================================  
  // 
  //            UNCOMMENT THIS SECTION IF YOU 
  //      COMPLETE THE EXTRA CREDIT IMPLEMENTATION
  //
  // =======================================================  

  cout << "\n\n";
  Table<char> x(2,5,'x');
  assert (x.numRows() == 2);
  assert (x.numColumns() == 5);
  x.set(0,0,'.');
  x.set(1,4,'X');
  x.print();

  Table<char> y(4,5,'y');
  y.set(0,0,'.');
  y.set(3,4,'Y');
  y.print();
  x.push_back_rows(y);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 5);
  x.print();

  Table<char> z(6,2,'z');
  z.set(0,0,'.');
  z.set(5,1,'Z');
  x.push_back_columns(z);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 7);
  x.print();

  assert (x.get(0,0) == '.');
  assert (x.get(1,0) == 'x');
  assert (x.get(0,1) == 'x');
  assert (x.get(1,4) == 'X');

  assert (x.get(2,0) == '.');
  assert (x.get(2,1) == 'y');
  assert (x.get(3,0) == 'y');
  assert (x.get(5,4) == 'Y');

  assert (x.get(0,5) == '.');
  assert (x.get(1,5) == 'z');
  assert (x.get(0,6) == 'z');
  assert (x.get(5,6) == 'Z');

  std::cout << "extra credit tests completed" << std::endl;
}



// Batch test will repeatedly load & process a file with Table
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.

void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int i,j,num;

    // create the initial table
    istr >> token >> i >> j >> c;
    assert (token == "create");
    // note: here we explicitly allocate memory for the Table object
    Table<char> *table = new Table<char>(i,j,c);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "set") {
        istr >> i >> j >> c;
        table->set(i,j,c);	
      } else if (token == "get") {
        istr >> i >> j >> c;
        char c2 = table->get(i,j);
        assert (c == c2);
      } else if (token == "push_back_row") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_row(tmp);
      } else if (token == "push_back_column") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++) 
          istr >> tmp[i];
        table->push_back_column(tmp);
      } else if (token == "pop_back_row") {
        table->pop_back_row();
      } else if (token == "pop_back_column") {
        table->pop_back_column();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    if (iters == 0)
      table->print();

    // Because the Table memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete table;

  }
}


