HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  < Oscar Li >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Mohammad >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order: O(q+olog(o))
q stands for the order that we are pushing into orders list
olog(o) is for the sort function that sorts each order in the list

add_item: O(1+clog(c))
1 is for pushing back the items (you only push back once)
clog(c) refers to sorting the cooking items

print_orders_by_time: O(olog(o)+oq)
olog(o) is for the sort function that sorts each order in the list
oq are two nested for loops for which the first loop is looping through the orders
and the second loop is for each individual item in that order

print_orders_by_id: O(olog(o)+oq)
olog(o) is for the sort function that sorts each order in the list
oq are two nested for loops for which the first loop is looping through the orders
and the second loop is for each individual item in that order

print_kitchen_is_cooking: O(c)
for loops the list of cooking foods

print_kitchen_has_completed: O(d)
loops thought cooked food

run_until_next: O(2o+c+p+oq)
there are two loops that iterate through the orders list
we also loop through the cooking list
we also find the first instance we complete an event, thus p
finally we have oq for the two nested loops used in CanFillOrder that loops through the order
and the max number of items that need to be removed

run_for_time: O(time((c)+o(oq)))
time is a variable i used to incriment time and inside that loop, i also looped the cooking list
inside that time loop, I also have a loop of orders that check if each order can be fullfilled, that's why
i multiplied it by oq (CanFillOrder loops).

MISC. COMMENTS TO GRADER:  
Optional, please be concise!






