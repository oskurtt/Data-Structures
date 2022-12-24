HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Oscar Li>


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?
O(wpm)


What is the order notation for performance (running time) of each of
the commands?

Load: O(n) <- while loop to store every single word in the text

Print: 
Window 2: O(p+p) Two separate for loops for looping through selected word
Window 3: O(p^2 +p) <- worse case if there is only one given word to print, this means we need to find another by loop
	  O(p+p) <- best case if there are two given words and you jsut need two for loops
Random:
Window 2: O(xp) <- Double loop to find next occuring word randomly 'x' amount of times. vector pushback is O(n^2)
Window 3: O(p^2) to find second word if not given
	  O(xpp) <- First loop is for our lenght of words to print out, then we loop through the second map, and then loop 
		    again for the third map

Most Common:
Window 2: O(xp)<- Same logic to Random but instead of pushing words back to vector, reupdate the most frequent word
Window 3: O(p^2) <- find second word if not given
	  O(xp) <- loop once for the length of words we ened to produce and then loop through selected word once to find most frequent


EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


