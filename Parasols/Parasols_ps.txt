Parasols
As per usual UCF is working on expanding the outside eating location outside the Student
Union. They have set up chairs on a linear path that extends quite far. To prevent the engineering
students from constructing towers from the chairs the SGA has supplied chairs that are bolted to
the ground and can no longer be moved. The only issue is that the sun is overbearing and the rain
can ruin the outside lunches during the summer.
UCF bought k parasol stands to help cover the outside seating. However, UCF has not purchased
any parasol tops nor has determined where to place the parasols. UCF has hired you to help
protect their students from the weather. They want to buy k identical parasol tops to cover all the
seating. Each chair should be completely covered by at least one parasol. UCF does not want to
spend too much money, so you will help determine the minimum integral width of the parasol
heads such that all the chairs can be covered.
Suppose you have 2 parasols stands, and 4 chairs at positions 1, 4, 7, and 11. We could cover all
the chairs with parasol widths of 6. See the following diagram,

However, we could also cover all the chairs with parasol widths of 5. See the following diagram.

You can find out that regardless of placement it is not possible to cover all chairs using 2
parasols with widths less than 5.
Input Specification
The first line of input contains a two positive integers, n and k, (n, k ≤ 200,000) representing the
number of chairs and the number of parasol stands. The following line will contain n positive,
space separated integers representing the position of the chairs in meters from the student union.
Note that each chair’s position will be given in increasing order.

Output Specification
You will output a single positive integer representing the minimum width of the parasols such
that each chair will be completely covered by at least on parasol.
Input Output Example
Input
4 2
1 4 7 11
10 3
1 2 3 6 7 8 12 18 20 21

Output
5
6

Explanation
Case 1
With a parasol of width 5 we are able to cover the 4 chairs using the layout

Case 2
With a parasol of width 6 we can cover the 10 chairs using the following layout. With any
smaller width you cannot cover all the chairs.

Grading Information
Reading from standard input/output – 10 points
No output aside from the answer (e.g. no input prompts) – 10 points
Reads in all the input correctly – 10 points
Using a binary search over the parasol head width – 10 points
Uses some method to verify a good parasol width – 10 points
Your program will be tested on 10 test cases – 5 points each
No points will be awarded to programs that do not compile.
Solutions without a binary search will receive a maximum of 50 points

Only cases that finish within the maximum of {5 times the judge solution, 10 seconds} will be
graded.

