# Open-Address-Hash-Table
A dictionary made out with an Hash Table using the Open-Addressing method with Quadratic probe to solve the collisions.
Featuring Insert and Search (with Longest Common Subsequnce (LCS) algorithm to make a list of nearest possible element that matches the search.)
# Introduction.

A Hash Table (Or Hash table) is a data structure used to match a Key Date With an Given value.  is used for the implementation of Associative abstract data structuresWhat Map Or Set.

These structures are particularly effective for implementing many applications that require only INSERT, SEARCH, and DELETE; Perfect example is that of Problem of Dictionary, where the Hash table is very fast and performing for this type of application.

# Insertion.
In the pseudo-code of the insert algorithm in a Hash table, let's assume that the elements of this last are keys without satellite data; So, the key k Input date, you Identical to the one to be searched inside the table. The algorithm, on each iteration, calculates the position of the key to be inserted thanks to a specific scan or TechniqueLinear, quadratic o Double hashing), adding the index i. The function will then insert into the table only if it will find a slot with a key Nil, Otherwise it will exit the loop and report the overflow error.

# Search.
The algorithm that searches for the key k, Examines The same sequence of slots That examined the insertion algorithm when it entered the key k. But the search, unlike the insertion, can end (Without success) when it finds an empty slot, because the key k would have been Exactly in that slot and not after in its scan sequence (This reasoning therefore assumes that the keys are not erased by a Hash table.) The procedure will instead return The identification slot where the key was entered if successful.

# Cancellation.
Regarding deletion from a Hash table to addressing Open, we can To say it's a difficult operation. 
When a possible key i is cleared from its slot, Not enough Mark it as NIL because we can create a Malfunction In the Hash table, risking not to find any more key k During the insertion we looked at the slot i, Finding him busy. You could mark it as Deleted Any item removed from the Hash table, but this would go to Affect search times, which would no longer depend on the load factor α; For this reason the Chaining is selected more frequently as a technique for when the Keys must be cancelled.

# Load factor.
Given a Hash table T, with M Positions  That Stores N Elements, we define load factor α = n/m, the average number of elements contained in the Hash table. The analysis in a Hash table will be done according to the load factor, which can be Less, greater than or equal to 1.
In the case of an open-addressing Hash table, because collisions are handled through Scans And not Using pointers, the maximum load factor to ensure the insertion without collisions will be less than 0.5.  Once this threshold is exceeded with the insertion of new elements, the Hash table to continue to ensure the insertion will be subjected to a Rehash; Its size will be doubled to allow The insertion without any collisions.

# Open addressing.

For our HashTable, we will choose the technique of Open addressing; It allows us to store all the items in the same Hash table. Each cell in the table will then contain an element of the dynamic set, or the value Nil. In the search and insertion of an element, we will systematically examine the free slots of the table until we find the desired empty position, or the element we searched for (whether or not in the table). 
Unlike tables Direct addressingThat solve collisions with the method of Concatenation (Then by The use of lists In each slot in the table, which insert Overhead The new item in Collision case With an existing one), In open addressing There are neither lists nor items stored outside the table: This can bring the table to fill up to the point that you can not Make other insertions, without any rehashing of the table itself.
How do we manage collisions within our table? 
The advantage of open-addressing Hash tables, is that we can do without the use of lists and pointers. 
So let's solve the problem of collisions Calculating The sequence of slots to examine: The extra memory released for not using pointers, gives the Hash table a large number of slots, allowing you to reduce the number of collisions and accelerate the search operations.
To perform an insertion or search using the open addressing technique, we examine in succession the positions of the Hash table (Or Scan), Until We do not find an empty slot in which to insert the key. 
Instead of following the order in which the cells are placed, 0 1,.... M – 1, The sequence to be examined depends on From the key to insert.
To determine Which one Position examine, extends the hash function So that it assumes as input, Beyond the key itself, the number of positions Already examined, becoming like this: 
 
Then modify the scan sequence of the cells in:  
So that at most each table position is treated as a slot for a new key.  

# Quadratic scan

Given an ordinary Hash function:
 , we'll call Auxiliary Hash function, (which will behave exactly like a Any other hash function Not in the open addressing technique), the quadratic scan method uses the hash function: 
 , 
Where  h′ is the auxiliary function described just above, c 1  (which can be any value) and c 2 ≠ 0, are auxiliary constants carefully chosen at the beginning of the program execution and i = 0.1,..., M-1. 
The initially parsed position is the location within the Hash table With defined value From the auxiliary Hash function T [H(K)], While all the positions subsequently examined are Spaced in a quadratic way Defined by the quadratic scan formula described just above.
This technique, Unlike scanning LinearWorks Much better as it does not suffer from Primary agglomeration (Accumulate values for long within the Hash Table), but in the long run it also has problems, that is of the secondary agglomeration (Accumulation of values for discontinuous strokes within the table). They will also be used as m Separate scan sequences (That is, the Size Of the table in question).

# Longest Common subsequence.

The problem of the Longest Common subsequence (or Lcs abbreviated), is to find the longest common subsequence of two strings. Unlike a normal substring, which sees the characters of the two strings in a Sequence Narrow, that of LCS represents the Longest subsequence of characters common to the two strings.
Formally proposed, DAte two sequences X e Y, let's say that Z Is One Common subsequence X And Y, If Z is a subsequence of both sequences X And Y.  
As an example, you give two sequences,
X =〈A, B, C, B, D, A, b〉And  Y =〈B, D, C, A, B, a〉, The sequence Z =〈B, C, A〉is a common subsequence of X And Y.
However, the sequence Z is not the longest common subsequence belonging a X And Y, since it has length = 3. From a closer look in fact, it would prove that the sequence Z =〈B, C, B, A〉Longer than the previous, having length = 4, establishing itself as the most Long Common subsequence (LCS) of X And Y. 
The sequence Z =〈B, C, B, A〉Though It's not The UNICa Longest common subsequence of X And Y: In fact, we also find the sequence 〈B, D, A, b〉Which is also LCS of X And Y; So we can say that in two string dates, they can exist More Longer common subsequences, but the length of these maximum subsequences will always be Equal Between them.

# LCS and dynamic programming.

How to solve the problem of LCS? 

The first approach that comes to mind is to use a brute force technique to solve the problem of the longest common subsequence: Enumerate all the subsequences of X and check the latter to see if they are also subsequences of Y, keeping track of the longest subsequence found. But this particular technique is not very convenient because of its exponential time, making it inexpensive for long sequences.

With a more careful analysis though, we notice that The problem of the LCS enjoys the property of the excellent structure: The "natural" classes of its subproblems correspond to pairs of "prefixes of Two sequence of input (X and Y). 
By deepening, given a sequence X =〈x1, X2,..., XM〉where X represents our string, and X1, x2,..., XM The occurrences of characters in the string itself, we'll define Xi =〈X1, X2,..., XI〉Thei-TH prefix of XFor i = 0.1,... M.
To give an example, taking up the sequence of before, X =〈A, B, C, B, D, A, b〉, a prefix of this sequence, for example = 3 (so Xi = X3) would see the first three letters of sequence X in succession, in this way: X3 =〈A, B, C〉, where X0 It's the empty sequence.
The prefixes will then be useful in solving the problem of calculating the LCS, where at each iteration we will deal with separate permutations of two strings X and Y, going to operate cyclically with their prefixes: X1 Y1 At the first iteration, X1 Y2 To the second and so on, until you get to the complete analysis of the two strings; XThe And Yi.

**Step 1:**
haracterization of a very good substructure
The LCS, then, like any other problem solvable with dynamic programming, enjoys the Excellent substructure; And this property is given by the following theorem:

 
This theorem shows that an LCS of two sequences contains an LCS of prefixes of the sequences analyzed (as described above).

**Step 2:**
Recursive solution
Having thus ascertained the existence of a great substructure, we can therefore affirm that The Problem of calculating the longest common subsequence enjoy Of the property of repetitive subproblems. To find a LCS of X And Y You may need to find one of its prefixes, for example X And Yn-1, or vice versa XM-1 And Y. We can therefore see how each of the problems just analyzed, has the task To necessarily find The LCS of XM-1 And Yn-1, attesting and confirming that the LCS Enjoy the ownership of repetitive subproblems. 
So let's define how CI, J] The length of a sequence LCS Xi And YjWhere c [] will be an array in which Retain occurrences of characters If they are Equal or differAnd The And j will be the final positions of our matrix, or where the Length of the LCS will be contained.
The optimal structure of the problem allows us to write a recursive formula:
 
This formula tells us that: 
	If one of the two substrings is empty, the LCS between a string and an empty string is 0.
	If the length of the string X And the length of the string Y are greater than zero, and The Thei-th occurrence of both strings corresponds, then the occurrences until now found will be equal to the number that is in the upper diagonal of the array (compared to the current cell) + 1 (the number of the occurrence just found).
	If the length of the string X And the length of the string Y are greater than zero, but the characters at theThei-th occurrence do not correspond, then the occurrences until now found will be equal to the maximum value between the two cells adjacent to the current cell (upper and left).
The LCS, then, is a dynamic programming algorithm that excludes subproblems based on the condition of the problem.

**Step 3:**
Calculate the length of an LCS.
Having characterized a great substructure and having recursively defined the solution to the problems, we can now move on to define the writing of an algorithm that helps us to calculate the actual length of an LCS. Having IsMn) Separate subprobolems, we can use dynamic programming to compute solutions with a method Bottom-up.
The procedure we're going to describe now, takes two sequences into input, X =〈x1, X2,..., XM〉EY =〈Y1, y2,..., yn〉and stores the values in a table C0... m][0... N] Whose positions are calculated according to The order of the lines (That is, a row is first filled first before moving on to the next line), From left to right.
The procedure in question also initializes a table b[0... m][0... N] where they will eventually Saved cell indexes in which you Find or not an occurrence; This table will be useful then in the reconstruction of a good solution.  Formally therefore, b[I, J] Points to Location Of the table that corresponds to the optimal solution of the subproblem. The procedure then returns the tables b And c; The table C, at position C[I, J] (so the last position of Table C) Will contain the length of the LCS.

Below, the pseudo-code of the LCS:
 

**Step 4:**
Build the LCS.
The table b Returned by the procedure LCS-Lenght, can be used to construct the correct Lcs of sequences X =〈x1, X2,..., XM〉EY =〈Y1, y2,..., yn〉. Starting from where the length of the LCS is kept, b[M, n], where m is the length of the first string, and n the length of the second, we cross the table following our "metaphorical arrows. Every time we meet a Arrow  “↖” In the position b[I, J], Then it means that Xi = Yi. (The characters of the two sequences X e Y correspond) and therefore is an element of the LCS. Being a recursive solution, the elements of the LCS of X e Y They will meet in the "reverse" order with this method; The Recursion describes with naturalness The proceedings Described above, going to print the characters of the subsequence from the last recursive call coming up to the first, Reconstructing the entire LCS.
