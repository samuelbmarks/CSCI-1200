#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0
bool check_root(int a, int b, int c, float root){
  // plug the value into the formula
  float check = a * root * root + b * root + c;
  // see if the absolute value is zero (within a small tolerance)
  if (fabs(check) > 0.0001){
    std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
    return false;
  }
  else{
    return true;
  }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns
true if the roots are real, returns false if the roots are imaginary.  If the roots
are real, they are returned through the reference parameters root_pos and root_neg. */
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg){
  // compute the quantity under the radical of the quadratic formula
  int radical = b*b - 4*a*c;
  // if the radical is negative, the roots are imaginary
  if (radical < 0){
    std::cerr << "ERROR:  Imaginary roots" << std::endl;
    return false;
  }
  float sqrt_radical = sqrt(radical);
  // compute the two roots
  root_pos = (-b + sqrt_radical) / (2*a);
  root_neg = (-b - sqrt_radical) / (2*a);
  return true;
}

int main(){
  // for loop will ask for the input 5 times and store in respective arrays
  int b_array[5], c_array[5];
  int my_a = 1, my_b, my_c;
  for(unsigned int i = 0; i<5; i++){
    std::cout << "Enter the b & c coefficients to quadratic function: a*x^2 + b*x + c = 0" << std::endl;
    std::cin >> my_b >> my_c;
    b_array[i] = my_b;
    c_array[i] = my_c;
  }
  // for loop will compute the roots and store the smaller root in the array
  double smaller_root[5];
  for(unsigned int i = 0; i<5; i++){
    float root_1, root_2;
    bool success = find_roots(my_a, b_array[i], c_array[i], root_1, root_2);
    if(success){
      //Verifies the roots
      if (check_root(my_a, b_array[i], c_array[i], root_1) && check_root(my_a, b_array[i], c_array[i], root_2)){
        //Compares the roots and stores the appropriate one in the array
        if(root_1<root_2){
          smaller_root[i] = root_1;
        }
        else{
          smaller_root[i] = root_2;
        }
        std::cout << "The roots are: " << root_1 << " and " << root_2 << std::endl;
      }
    else{
      std::cerr << "ERROR:  Unable to verify one or both roots." << std::endl;
      // if the program has an error, we choose to exit with a
      // non-zero error code
      exit(1);
      }
    }
  }
  // by convention, main should return zero when the program finishes normally
  return 0;
}