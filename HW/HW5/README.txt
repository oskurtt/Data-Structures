HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Oscar Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



TESTING & DEBUGGING STRATEGY:
Please be concise!  
When nodes are appearing and dissapearing where it shouldn't I would 
use Notepad to draw out the nodes and point the nexts and prevs to 
full understand the structure. Memory leaks are solved by using Dr. Memory



ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 
My order notation for the member functions all do not exceed O(n) time. 
One big difference between the three lists is that ds list only take account
of a node with one value as opposed of the cases where the value may not
necessarily be just one number. In this, we have an array. In this case, we would
have alot more if conditions as opposed to the dslist as well as looping 
through the elements and add/remove accordingly. Although the unrolled list
does in fact take longer than the ds list, it isn't a significant difference.
In the worse case, we would have a bunch of nodes that are not full. For example,
we might have six nodes each holding one value with an array size of six. To make 
this more efficient, you would just put all those six values in one node and eliminate
other unecessary nodes. Thus the iterator must jump from node to node and there would
be alot more deleting of nodes. In that case, the average number of elements per node 
would be 3, half of what our array would hold. 


EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
I am attached a jpeg of called "my_test" that shows what my test case
is supposed to look like.

