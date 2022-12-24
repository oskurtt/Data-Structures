HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Oscar Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< William Li >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          |          |          |          |          |    nlogn |          |
| vector   |   nlogn  |    n^2   |   nlogn  |    nlogn |          | l^2*n^2  |
------------------------------------------------------------------------------
|          |          |          |          |          |          | l^2*n^2  |
| list     |   nlogn  |    n^2   |   nlogn  |    nlogn |    nlogn |          |
------------------------------------------------------------------------------
|          |          |          |          |          |    nlogn |          |
| bst      |   nlogn  |   nlogn  |   nlogn  |   nlogn  |          | n*l^2log(n*l^2)|
------------------------------------------------------------------------------
|          |          |          |          |          |          |          |
| pq       |   nlogn  |     X    |   nlogn  |    nlogn |  n+flogn |     X    |
------------------------------------------------------------------------------
|          |     X     |    n     |          |          |          |         |
| hash     |           |          |     n    |    X     |     X    |  other  |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >
---------------------------------------------------------------------------------------------------------
|          |          	| remove   	|          	| closest  	| first f  	| longest  	|
|          | sort     	| dups     	| mode     	| pair     	| sorted   	| substr   	| 
---------------------------------------------------------------------------------------------------------
|          |  0.471494  |    13.6084    |   0.439153    |     0.418417  |    0.444012   |    12.1238    |
| vector   |   nlogn    |     n^2       |   nlogn  	|    nlogn 	|   nlogn       | l^2*n^2  	|
---------------------------------------------------------------------------------------------------------
|          |  1.02786   |    22.4885    | 0.927983      |  0.827755     |   0.883003    | 11.7517	|
| list     |   nlogn  	|    n^2   	|   nlogn  	|    nlogn 	|    nlogn 	| l^2*n^2       |
---------------------------------------------------------------------------------------------------------
|          | 1.05596|   |   0.075826    |  0.787996     |   0.877847 	|   0.955959    |  11.8629
| bst      |   nlogn  	|   nlogn  	|   nlogn  	|   nlogn  	|    nlogn      | n*l^2log(n*l^2)|
---------------------------------------------------------------------------------------------------------
|          |1.00797     |          	|    0.985882   |  0.72214      | 0.222103      |               |
| pq       |   nlogn  	|     X    	|   nlogn  	|    nlogn 	|  n+flogn 	|     X    	|
---------------------------------------------------------------------------------------------------------
|          |          	|    0.038945   |    0.367864   |          	|          	|   12.37      	|
| hash     |     X     	|    n     	|     n    	|    X     	|     X    	|  other  	|
----------------------------------------------------------------------------------------------------------

DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words. 

< insert your discussion of the results, including your answers to the
above questions >

I had to go back and forth many times with editing my table. However, my code may not be 100% correlated with 
my table because I just couldn't think of a faster way to code mine.  
I realized that for some tests, the biggest file tested are only a length of 50,000 as opposed to 
500,000. Therefore, I will only be speaking on behalf of the test cases that was tested with a length
of 500,000. That said, the overall performance did in fact match my intuition because where there was a
longer time complexity, for example nlogn vs n^2, n^2 took a way longer time than nlogn. As for structures that
had the same time complexity, the time it took to run was fairly close to one another. One example you can see that
is list, bst, and pq for sort. However, one time that really surprised me was how long these tests actually took. 
Many took well over 10 or even 20 seconds. One thing I want to know is if anyone can code these structures in a way
that every structure and every operation will take less than 10 seconds, or if possible, 5 seconds. In the future, 
I will carefully think about which structure to use to minimize run time. That said, I must also consider which structures
not to use. For example, for hash tables, it is impractical or nearly impossible to sort an unordered hash table wihtout
using any other structures. There is a reason why it's called an unordered_map. 


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
