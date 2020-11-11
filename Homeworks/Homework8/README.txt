HOMEWORK 8: ROPES


NAME:  Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Lecture 18 & 19 (ds_set)
Sooryakumar Pari, peer and fellow data structures student
Ujwal Pandey, peer and former data structures student
Jacob Shomstein, peer and former data structures student
cplusplus.com


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20+

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

An unbalanced rope is when the values are not spread out amongst leaf nodes. For example, if all the branches were in one direction towards a leaf node with all the values that make up the string.

Copy Constructor: 
1) O(2^p) Function is recursively branching in two directions for each layer in the rope, which is p, or the height of the rope.

2) O(p) For an unbalanced tree, the function would move down in one direction to the leaf node with all the characters, therefore running through each of the layers of the tree, or the height of the tree. 

Construct from Node*:
1) O(p) Updating size by just moving to the right each time down the height of the tree.

2) O(p) Same as a balanced tree because you are just moving to the right regardless for the length of the tree.

Index:
1) O(p) Moving down from node to node for the length of the tree in one direction or the other.

2) O(p) Same as unbalanced, your just move in one direction.

Report:
1) O(l*p) where l is the length of the substring that the user of the function wants and you are calling index each time to find that character (index is p).

2) O(l*p) Same as balanced tree because your still moving down height of rope each time regardless.

iterator operator++:
1) O(1) operator++ is always O(1) for tree

2) O(1) operator++ is always O(1) for tree

Split:
1) O(p) Moving down from node to node for the length of the tree in one direction or the other.

2) O(p) Same as unbalanced, your just move in one direction.

Concat:
1) O(2^p + p) Using copy constructor to copy the right rope, and then we are moving down the ride side of the rope, or the height.

2) O(p) Coping for unbalanced tree is p, and you would move down the right side of the rope even for unbalanced rope, which is also p.

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

For my index tests, in order to test the "corner cases," I tested it using the 0th and the last (21st) index in the rope. I also wanted to test if my code properly handled a case were a user attempts to access an index outside the range of the string in the rope.

For my report tests, the "corner cases" would be when the user is accessing substrings at either end of the string in the rope (either the beginning or last index). To test this, I attempted to get a substring of the entire string (0th index through the 21st index). I also checked to make sure the function handled a case where a user attempts to access characters of the string that do not exist (i.e. the range of indicies go outside the scope of the indicies of the string in the rope). 

I decided to test my concat and split functions together, as split utilizes the concat functions. The two cases I wanted to test were a case that splits a node when splitting and a case that does not require the split of a node. My evaluation of the tests were visuable checks by printing out the resulting Rope objectsand seeing if the functions were behaving properly. I used this section of my code to debug this function, and unfortunately, although the behavior of the function is correct, I was not able to figure out how to properly update the weights of all of the nodes in the tree. I was able, however, to properly update the size of each of the resulting trees. As a result, I am failing the ValidRope() check on Submitty and not receiving those points.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

Memory: As far as memory is concerned, I got to a point in the assignment when it was not the most outstanding prioriety. I do unstand its importance in the assignment (and in real world applications), but with the time constraints in completing the assignment, my main goal became to just get the functions working as best as possible. As a result, the I have a lot of memory issues that I just didn't get to even begin to address.

Report: I know that the commented instructions say to be mindful of the running time, and if I had the time to recode this function, I would. I would use index to find the leaf node (and value at that leaf node) that the index is at, and use in order traversal to move through the nodes, meanwhile checking if I am at a leaf node. If I am, I would append/push_back values from that leaf node to a string holding the current substring until that substring is the proper length (i-j+1). In all, I am aware of the ineffeciency of my function.

Split: As stated above, my split function is working properly with the exception of not updating the all of the node's weights correctly. If you look at the code commented out of the update_size() function, this is where I believe I was close in completing this part, but in the end came up short.

All in all, time got the better of me and if I could redo the assignment, I would.

Thanks for your time and consideration, as always,

Sam
