HOMEWORK 3: RESIZABLE TABLE


NAME:  Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Ujwal Pandey, peer and former DS student
Olenka Soko, peer and fellow/current DS student
Lecture 7 Notes and vector implementation file (vec.h)

For general research on various c++ topics through working on assignment:
cplusplus.com
youtube.com
google.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20


ORDER NOTATION:

Write each answer in terms of n = the number of rows and m = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

get: O(1)

set: O(1)

numRows: O(1)

numColumns: O(1)

push_back_row: O(n*m) 

push_back_column: O(n*m)

pop_back_row: O(n*m)

pop_back_column: O(n*m)

print: O(n*m)


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Table class design & implementation?

In order to check for any memory leaks/errors in my program, I utilized
Valgrind. I was fortunate enough not to have any issues with my destructor
and my destroy() function and their application through my program and 
generated no errors or possible leaks. In order to assure this, I ran my
main.cpp file will Valgrind many times throughout working through my 
implementation files.

Through implementing the push_back and pop_back functions, I heavily
used my print() functions as well as cout, print() to see if I successfully 
added or removed a row and if the values were indeed in the correct location 
in the table and cout to see where an error or segmentation fault may occured
in my program. For example, I may have put cout << "Test" << endl; right before 
an area where I am suspicious a problem has occured to see if the program runs 
up to and prints the test print statement or it if fails prior to that point in 
order to attempt to pinpoint the problem or error.

The "corner cases" of this assignment would most likely refer to the corner of
table, whether that be attempting to change in invalid location in the table or
attempting to add a row or column that does not maintain the rectangular shape.
Throughout my program, there are several error checks that do not allow the user
to take these actions, and the program will exit, providing the user with an error
message explaining what invalid action was attempted. Invalid action test cases were
also made under the StudentTests() function in the main.cpp file (which are 
commented out for the final submission).


EXTRA CREDIT: 
Indicate here if you implemented push_back for multiple rows or
multiple columns and/or rewrote your code using pointers instead of
subscripts for extra credit. Also document the order notation for
your multi-row and multi-column push_back functions.

I have implemented both of the push_back functions for multiple rows and
multiple columns that take a single Table object t as an argument and adds
those rows or columns to the current Table object, given that the Table argument
passed has the correct number of rows or columns in order to preserve the
rectangular shape of the 2D array (error checks are in place in both functions
to assure this is the case).

Brief description of the extra credit functions:
Both functions create a vector of vectors in order to copy information in each 
row of Table object t into each vector in the to_inserts vector. Then, the rows_
or cols_ is updated to the size of the new desired table by adding to it the rows_ 
or cols_ memeber variable of the t object. Next a new table is smade with the new 
dimensions, the old table is deleted, utilizing the destroy() function, and the 
previous values are filled into the newly-made table, much like in previous functions.
Then, the new values, stored in the vector of vectors, is put into the table by 
looping through the empty areas of the table allocated for the new information. Finally 
rows_ is updated to account for the change in size.

Order notation for extra credit:

push_back_rows: O(n*m)

push_back_columns: O(n*m)


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

My print function emulates the output provided in the "sample_output.txt" file.
My test cases in the main.cpp file complete tests with four objects, two of which are
integer types and the other two are string types.
Any other comments are covered in the above sections.

Thank you for your time and consideration,
Samuel Marks
