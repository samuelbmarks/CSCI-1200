HOMEWORK 7: SPATIALLY-EMBEDDED ADJACENCY MAPS


NAME:  Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

cplusplus.com


Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  6



ORDER NOTATION ANALYSIS:
Consider the following variables and give the complexity along with a short
justification for each of the functions below:

n: The total number of users
l: The total number of users with a location
d: The total number of users with degree >= 1
m: The total number of connections
p: The number of users that a function will print out

loadConnections(): O(m * log(n)) - In the worst case, the function will loop through every connection in the file (m), do a find to see if that user that has that connection is already in the map (log(n)), then an insert if the user ID is not found (log(n)). 

loadLocations(): O(l * log(l)) - The function reads in information from the file containing each user with a location (l) and inserts the user and its location into the map (log(l)).

printAllUsersWithinDistance(): O(l * log(l)) - The function loops through the map containing each user with a location (l) and does a find to see if that user has been added to an updated map (log(l)) and does an insert if the element is not found (log(l)).

printDegreesHistogram(): O(m * log(d)) - The function loops through the number of connections, stored in the adj_lists, (m) and uses operator[] to insert values into the map (log(d)).

printDegreesOfAll(): O(m) - The function loops through the number of connections, stored in the adj_lists, (m). 

printFriendsWithDegree(): O(n * log(n)) - In the worst case, one user is friends with all the other users. Therefore, the loop would loop through the total number of users (n), do a find to locate each of those users within the list of users (log(n)), and do an insert if that user has the correct length degree (log(n)). 

printFriendsWithinDistance(): O(n * log(l)) - In the worst case, one user is friends with all the other users and all of the users has a location. Therefore, the loop would loop through the total number of users (n), do a find to check if the user was already included in the new map (log(l)), and insert the user if it is not found (log(l)).

printUsersWithinIDRange(): O(m) - The function loops through the number of connections, stored in the adj_lists, (m). 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

All of my complexity answers and explanations consider the worst case. 

Thank you for your time and consideration, as always.

Sam
