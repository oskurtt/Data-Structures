HOMEWORK 6: STAR BATTLE


NAME:  < Oscar Li >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< William Li >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 20 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone (t) 
The number of stars per zone(s)? 
etc.
My int main starts by looping through each coordinate in the first zone and 
using that point as a starting point for finding other solutions using recursion. O(t)
My algorithim then tests three cases. 
Case 1: It's possible to place current star and puzzle is solved. 
Bool Possible Function: O(w + h) <- separate for loops to find total stars in the column or row
Pushback the solution grid and revert back to previous board and move on to next point and recurse: O(zt) <- moves on to the next point the zone until all zones and
its points are checked. Solved function: O(t)
Case 2: Possible to place but not solved O(zt) <- moves on to the next point the zone until all zones and
its points are checked
Case 3: Not possible to place: O(zt) <- moves on to the next point the zone until all zones and
its points are checked
Because the of the way I nested these cases, the O notation for this algorithm is O(w+h+t+zt)

DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).
The biggest concern for my program is to make it run efficiently. To do this, I wanted to 
solve a puzzle with a huge number of rows and columns and a bunch of different zones. The goal
is for my program to solve it in a fast time. Although it may not have given me every single
possible solution, the fact that it ran under 10 seconds was good enough for me. 

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.
My first problem I've encountered is that my algorithm is not getting all the solutions
when the stars are more than 1. I tried to run custom1.txt for 2 stars and it was missing 
one solution. Although my algorithm doesn't necessarily get every single solution, it still 
performs really quickly, alot less than 10 seconds. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


