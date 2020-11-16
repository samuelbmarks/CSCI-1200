HOMEWORK 10: JOB PRIORITIZATION


NAME:  Samuel Marks


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.
Online resources should have specific URLs

Ujwal Pandey, fellow stduent and former DS studnet

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  8


EXTRA CREDIT
As described in the hw.pdf create a new ElegantQueue that can function as a TimeQueue or
as an UrgentQueue. Describe the changes you had to make to main/Job, and how your ElegantQueue
supports both getting the highest urgency Job and getting the earliest Job.

My ElegantQueue class simply contains to heaps (two vector of Job object pointers), one of while priorities by time and the other which priorities by urgency. The same private member functions are present as in both the TimeQueue and UrgentQueue classes, one for each of the heaps. All of these functions are implemented in ElegantQueue.cpp.

In terms of changes to the Job class, minimal changes were made, as instructed. Obviously, only one forward class declaration was needed (for the ElegantQueue class). In addition, only one pointer to the queue class was required, which I appropriately named elegant_ptr. In the main file, I updated the function names accordingly to match the correct names of the functions in my ElegantQueue class. I also adjusted the arguments when need be, like for example for AddToQueue() which originally took two queue class objects as arguments and now would only take one queue class object.


MISC. COMMENTS TO GRADER:  
Thank you for your time and consideration, as always.

Sam
