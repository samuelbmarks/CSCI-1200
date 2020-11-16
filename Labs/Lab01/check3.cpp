#include <iostream> // library for reading & writing from the console/keyboard
#include <cmath> // library with the square root function & absolute value
#include <cstdlib> // library with the exit function
using namespace std;

int main(){
  int numofnums;
  cout << "Enter the number of values in the sequence" << std::endl;
  cin >> numofnums;

  double num_vect[numofnums];
  double mynum, average, sum =0;
  cout << "Enter the values" << endl;
  for(int i = 0; i<numofnums; i++){
    cin >> mynum;
    num_vect[i] = mynum;
  }

  for(int i = 0; i<numofnums; i++){
    sum += num_vect[i];
  }
  average = sum / numofnums;
  cout << "The average is: " << average << endl;

  for(int i = 0; i<numofnums; i++){
    if(num_vect[i]<average){
      cout << num_vect[i] << " is less than the average" << endl;
    }
  }

  return 0;
}