HOMEWORK 9: IMDB SEARCH


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


HASH FUNCTION DESCRIPTION
I first read through all the data and store it in a movie object. I then 
create all 64 possibilities of that query and insert them into the hash
table. Insert will hash the query that you want to insert, and go to that 
index. If index is empty, insert the pair of query, movie. If not, check
if the query existing is equal to your query. If yes, pushback the movie, 
if not, find the next open index. When searching for a query, you would
hash the query and go to that index and print all the movies in that index.






MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


