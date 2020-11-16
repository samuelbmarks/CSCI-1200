HOMEWORK 5: UNROLLED LINKED LISTS


NAME: Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Ujwal Pandey, fellow student and former data structures student
Alexander Monaco, graduate student and former data structures student
Eric Partride, fellow student and former data structures student
Jacob Shomstein, fellow student and former data structures student

Other resources:
Lecture 11 dslist class
cpluscplus.com
youtube.com
google.com

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  25


TESTING & DEBUGGING STRATEGY:
I heavily utilized my print function in assessing whether or not the program
was working properly. Also, when pinpointing errors in my code, I utilized the
gdb debugger as well as "test" print statements. For example, if a segmentation
fault was occuring, I would use a print statement to determine where the problem
was by using the logic of "if the statement is printed, the program is seg faulting
after this area of code." This assignment was very tricky for me, so I used a lot 
of trial and error.



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

n = number of nodes
v = number of values in the (current) node

push_back: O(1)
push_front: O(v)
pop_back: O(v)
pop_front: O(V)
print: O(n*v)
erase: O(v)
insert: O(v)

This data structure would be most ineffecient when a value is being inserted to
the front of a list because all values needed to be shifted to account for the newly
added item.


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
I really struggled on this assignment. I tried doing this using several different ways after 
receiving help from people who advised me to use different logic than the previous person.
This resulted in me not being able to complete the implementation for all the functions. 
I was able to complete push_back, push_front, pop_back, pop_front, erase, and print. I showed
effective use of each of these functions in the MoreTests() function in the main.cpp file. As far
as the BasicTests() function, I was able to complete all of the tests with the exception of the insert
tests. If you were to comment out the insert test section of this function, the 'erasing that removes a 
node" does in fact work. My insert function was working at one point, then some changes were made and
I could not reverse or ammend these changes and make it again functional. I was not able to ammend memory 
errors and/or leaks due to lack of time and inability to finish other buggy aspects of my program.