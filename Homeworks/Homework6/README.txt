HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  Samuel Marks



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Ujwal Pandey, fellow student and former DS student
https://web.stanford.edu/class/archive/cs/cs106b/cs106b.1174/lectures/10/Small10.pdf
Lecture 15 Material
Lab 7 Material 

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  30+



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Etc. 

To determine of performance of my algorithm, I need to look at and analysis the performance of every function that I utalize when finding the solutions. In my all_solutions function, I use a count function that has an order notation if O(log(g)), g being the number of vector<vector<char>> solution grids that are present in the list_grids list. I also use, check_word, which has a Od(*p), where d is the number of Word objects in the directory (list<Word>, which mirrors the dictionary) and p is the number of points stored in the Word object. The updated_constraints function has a runtime of O(c). The update_grid function has a runtime of O(l), where l is the length of the word. The update_directory function has a runtime of O(d), where d is the number of words in the directory. In all, the order notation of my algorithm is O(d*d!).



DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
I utilized this "appears_multiple.txt" puzzle to test whether my program could find all instances of a word and produce three seperate solutions, each finding the difference instance of the word. In this case, the only word in the dictionary was "HOMEWORK." My program succeed this test.

!Source:SamuelMarks
+8
XXHOMEWORKXXXXXXXXXXXXXX
XXXXXXXXXXXXXXXXXXXXXXXX
XXXXHXXXXXXXHOMEWORKXXXX
XXXXOXXXXXXXXXXXXXXXXXXX
XXXXMXXXXXXXXXXXXXXXXXXX
XXXXEXXXXXXXXXXXXXXXXXXX
XXXXWXXXXXXXXXXXXXXXXXXX
XXXXOXXXXXXXXXXXXXXXXXXX
XXXXRXXXXXXXXXXXXXXXXXXX
XXXXKXXXXXXXXXXXXXXXXXXX

I utilized this "all_corners.txt" puzzle to test the "corner cases" of the grid. My dictionary consisted of the four words present of the edges of the grid. What should be printed is one solution with only the edge characters not blacked out, which my program again succeed.

!Source:Me
+4
+4
+4
+4
SICK
IXCI
GVDD
NOES


SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:

All of the files that I tested my program with are listed below:

(All solution counts are assuming the command line argument for solution mode was all_solutions)

all_corners.txt, all_corners_dict.txt				< 1sec	1 solution

appears_multiple, appears_multiple_dict.txt			< 1sec	3 solutions

blackout1.txt, blackout_dict1.txt					< 1sec	3 solutions

nyt_mini1, nyt_mini1_dict							 38sec	1 solution





MISC. COMMENTS TO GRADER:  
I was not able to test my code using all the provided files due to time constraints. 

Thank you for your time and consideration,
Samuel Marks

