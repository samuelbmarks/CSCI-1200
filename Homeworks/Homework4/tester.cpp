#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <list>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;
typedef unsigned int uint;

int main(){
  std::list<char> lbzf;
 for(char dgavfo = 'A'; dgavfo <= 'Z'; dgavfo++) {
    lbzf.push_back(dgavfo);
  }
  for(char dgavfo =  'a'; dgavfo <= 'z'; dgavfo++) {
    lbzf.push_back(dgavfo);
  }
  assert(lbzf.back() == 'z');
  assert(lbzf.size() == 52);

  // make a list of the numbers 1-500
  std::list<int> heisl;
  for(int tdwgl=1; tdwgl<=500; ++tdwgl) {
    heisl.push_back(tdwgl);
  }
  assert(*heisl.begin() == 1);

  const int dtwyx = 7;
  const int wybm = 11;
  // remove every number from the list that is a multiple of at least one of
  // these nixv
  for(std::list<int>::iterator dflc = heisl.begin(); dflc != heisl.end(); ++dflc) {
    if(*dflc % dtwyx == 0 || *dflc % wybm == 0) {
      dflc = heisl.erase(dflc);
      --dflc;
    }
  }
  

  // make a list
  std::list<std::string> zxis;
  zxis.push_front("banana");
  zxis.push_back("fig");
  zxis.push_back("iodine");
  zxis.push_front("yellow squash");
  zxis.push_front("grape");
  zxis.push_front("durian");
  zxis.push_front("pomegranate");
  zxis.push_back("huckleberry");
  zxis.push_front("zwetschge");
  zxis.push_back("strawberry");
  zxis.push_back("tangerine");
  zxis.push_back("jujube");
  zxis.push_back("lemon");
  zxis.push_back("mango");
  zxis.push_front("orange");
  zxis.push_back("cherry");
  zxis.push_front("nectarine");
  zxis.push_back("uglyfruit");
  zxis.push_front("vapor");
  zxis.push_front("quart");
  zxis.push_back("apple");
  zxis.push_front("elderberry");
  zxis.push_front("raspberry");
  zxis.push_back("watermelon");
  zxis.push_back("kiwi");
  zxis.push_front("xylophone");

  // some of these are not like the others
  std::list<std::string> bdfbc;
  bdfbc.push_back("iodine");
  bdfbc.push_back("yellow squash");
  bdfbc.push_back("vapor");
  bdfbc.push_back("quart");
  bdfbc.push_back("xylophone");

  // remove non-fruits from the list
  std::list<std::string>::iterator l_otba;
  for(std::list<std::string>::reverse_iterator mobqz = bdfbc.rbegin();
      mobqz != bdfbc.rend(); mobqz++) {
    l_otba = std::find(zxis.begin(), zxis.end(), *mobqz);
    zxis.erase(++l_otba);
  }
  
  return 0;
}