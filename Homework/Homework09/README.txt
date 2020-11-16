HOMEWORK 9: IMDB SEARCH


NAME:  Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

Ujwal Pandey, fellow student and former data structures student
Alex Monaco, fellow student and former data structures student
Sooryakumar Pari, fellow student and current data structures student
cplusplus.com
Code from Lab 10 and Lecture 20 (ds_hashset.h)

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  20+


HASH FUNCTION DESCRIPTION

My hash function was rather similar to the one from http://www.partow.net/programming/hashfunctions/ that we utilized during Lab 10 with clear modifications. Instead of taking an the entire key (pair<pair<Movie,Movie>,unsigned int>), I only passed in one Movie object. The reasoning why I choose this key is explained below. As for the the hash function, I combined each element of the Movie object (title, year, runtime, genre data, actor data, and role data) into one string and hashed the string from there, returning a hash_value. 


HASH TABLE IMPLEMENTATION

To initially start the assignment, I utilized the implementation of the ds_hashset, only making minor changes as I went to tailor it to my needs. I maintained the design of using a vector<list<KeyType>>.

In order to create a fast lookup, I decided to create/insert 64 instances of every Movie object to account for every possible variation of "completeness" and store each in the table. As a result this made me choose the key type of a pair<pair<Movie,Movie>,unsigned int>. This way, I could store a "partial" Movie object, the original movie object, and its hash_value. I would then only has by the "partial" Movie object's data so that it would match that of the "partial" object that is being used to query. 

When inserting, I insert at the index determined by the hash_value if that index is empty. If it is not empty, the way I determine if it belongs at that index (shares the same "partial" Movie characters) is by comparing the hash_value. If it does not have the same hash_value, I use linearing probing to find either the next index that the key belongs to (by continuously comparing hash_values) or the next empty bucket.

Because of the setup, searching became relatively easy. I would simply use the hash function to hash the Movie object to return an index that the matching keys should be. If the bucket at that index was empty, there was no match. If the hash_values at that bucket matched that of the query, the keys in that bucket are the matches. If the hash_values did not match, I again utilized linear probning to find either that there was no matches (empty bucket) or the index that does match.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)
Thanks for your time and consideration, as always!

Samuel Marks

