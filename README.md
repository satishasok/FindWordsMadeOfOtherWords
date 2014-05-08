Find Words Made of Other Words in a large list.

Actual Result the "words for problem.txt" file:

5 longest words that are made of other words in the full list:
ethylenediaminetetraacetates
electroencephalographically
ethylenediaminetetraacetate
immunoelectrophoretically
phosphatidylethanolamines

97107 out of all 173530 words in the "words for problem.txt" file are made of other words in the file.


Design/Approach:

Design is very simple:
  Load the words one by one (line by line) to a vector.
  Sort it by length of the string in descending order.
  Then also create a hash (set) of all the words in the vector.
  
  Now for each word Check if it is made of other words in the list
     * For each word in the vector
     *  check if a substr (that from the start) is found in the hash
     *    if it is found, recursively find if the rest of the word is made of other words in the list
     *       if rest of the word is made of other words in the list then return True
     *       if not return False
     *    if not continue with the next subStr
     
     
Complexity:
 
 If you want to find all the words that are made of other words in the list it is still very fast.
 Basically,
         it is in the order O(n) and a multiple of klog(k) where k is the average length of the words in the list.
         plus O(nlogn) for sorting.
 However the space complexity is:
        O(2n)
 since we have both vector/list and a hash/set
 
 If you just want to find the just the m longest words made of other words then it is very fast 
 and we can stop as m longest words. So it is best case O(nlogn) and worst case (very rare) O(nlogn) + O(n) + O(klogk) where k is everage length of words
         

Implementaion:

I have implementation in both python and C++.
Python implementation is faster because dict (used as a hash) is constant time for write, and read. Where as STL's std::set uses binary tree optimization which is O(nlogn) for insert and find.

In my machine: finding all the words made of other words from the list of 173K words takes about 3 seconds in Python and about 8 seconds in C++. 
I am pretty sure this if we use more optimized set in boost or unordered_set (in C++0x) will make it faster than python.