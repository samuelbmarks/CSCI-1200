// A simple "caller ID" program

#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

// add a number, name pair to the phonebook
void add(vector<string> &phonebook, int number, string const& name) {
  phonebook[number] = name;
}

// given a phone number, determine who is calling
void identify(const vector<string> & phonebook, int number) {
  if (phonebook[number] == "UNASSIGNED") 
    cout << "unknown caller!" << endl;
  else 
    cout << phonebook[number] << " is calling!" << endl;
}



// Checkpoint 3
void map_add(std::map<int, string> &map, int num, string const& id) {
  map.insert(std::make_pair(num,id));
}

void map_identify(const std::map<int, string> &map, int num) {
  if (map.find(num) == map.end()) {
    cout << "unknown caller!" << endl;
  }
  else {
    cout << map.find(num)->second << " is calling!" << endl;
  }
}

int main() {
  // create the phonebook; initially all numbers are unassigned
  vector<string> phonebook(10000, "UNASSIGNED");

  // add several names to the phonebook
  add(phonebook, 1111, "fred");
  add(phonebook, 2222, "sally");
  add(phonebook, 3333, "george");

  // test the phonebook
  identify(phonebook, 2222);
  identify(phonebook, 4444);
  
  cout << "Check 3" << endl;
  std::map<int, string> map;

  map_add(map, 1234567, "bob");
  map_add(map, 8592754, "amy");
  
  map_identify(map, 1234567);
  map_identify(map, 0000000);
  map_identify(map, 8592754);
}