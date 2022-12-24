HOMEWORK 3: CONNECT FOUR


NAME:  Oscar Li


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

<William Li>

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
O(mn)
insert (including checking for connected four)
O(mn)
numTokensInColum
O(m)
numTokensInRow
O(n)
numColumns
O(1)
numRows
O(1)
print
O(mn)
clear
O(m)

TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?
I had a majority of errors with memory leak so I used Dr.Memory. It showed which lines leaked memory and I would go to those lines and 
fix them. Usually, by fixing the topmost error, the following errors also go away. 

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

