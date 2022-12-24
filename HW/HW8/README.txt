HOMEWORK 8: ROPES


NAME:  < Oscar Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >

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

Copy Constructor:
O(p)
The runtime for this depends mostly on the layers of the tree. The more layers, the more runtime
Construct from Node*:
O(p)
Setting the root is O(1) but finding the rope size will need to be recursed through each leaf node,
in that case, run time will depend on the path to the leaf nodes. The more balanced, the less run time
Index:
O(p)
Goes to the bottom of the tree going left and right depending on index size. More balanced, less run time
Report:
O(n)
My report function iterates through each leaf node and keep tracks of the strings. More string, more run time. Tree 
balance doesn't really affect the run time.
iterator operator++:
O(p)
You either go left until you can't anymore or go up to your parent
The more unbalanced, the more u time u use
Split:
O(p)
Only iterating through nodes parents and cutting off ropes. 
Concat:
O(p)
concat uses copy rope and the function set rope size. These both are O(p). 

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?
For my student tests, I tried splitting a leaf node and I tried splitting the left node of a parent as oppose to the right parent
to make sure it works for all nodes.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

