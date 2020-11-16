#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <math.h>

template <class T>
void print(std::vector<T> &data, const std::string &label) {
  std::cout << label << " ";
  for (unsigned int i = 0; i < data.size(); i++) {
    std::cout << " " << data[i];
  }
  std::cout << std::endl;
}

template <class T>
void reverse(std::vector<T> &data){
  int length = data.size();
  bool flag = false;
  if (length%2 == 0){
    flag = true;
  }
  if(flag){
    int midway = length/2;
    for (int i = (data.size()-1); i>=midway; i--){
      int first = ((data.size()-1) - i);
      std::swap(data[first],data[i]);
    }
  }
  else if(!flag){
    int midway = ceil(length/2);
    for (int i = (data.size()-1); i>=midway; i--){
      int first = ((data.size()-1) - i);
      std::swap(data[first],data[i]);
    }
  }
}


int main() {
  std::vector<int> data;
  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);

  print(data,"before:");
  reverse(data);
  print(data,"after: ");

  std::vector<std::string> data2;
  data2.push_back("apple");
  data2.push_back("banana");
  data2.push_back("carrot");
  data2.push_back("date");

  print(data2,"before:");
  reverse(data2);
  print(data2,"after: ");

  //empty vector
  std::vector<char> data3;
  print(data3,"before:");
  reverse(data3);
  print(data3,"after: ");

  //vector w/ size 1
  std::vector<char> data4;
  data4.push_back('x');

  print(data4,"before:");
  reverse(data4);
  print(data4,"after: ");

  //vector w/ size 2
  std::vector<char> data5;
  data5.push_back('x');
  data5.push_back('y');

  print(data5,"before:");
  reverse(data5);
  print(data5,"after: ");

}