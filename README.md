# About

Limit order book written in C++.  

# Design

Each side of the order book is implemented as an AVL tree containing all price levels on that side of the book with 
non-zero quantity.  Each side of the book also contains a pointer to the top of the book (highest price level on the bid 
side or lowest price level on the ask side).  Each price level contains a hash table which contains all orders at that 
price, using the order ID as the key.  Each price level also contains a pointer to its parent price level.

# Design Considerations

An AVL tree is used to hold all price levels with non-zero quantity on a particular side of the book.  If most activity 
takes place at or near the top of the book, a linked list may be preferred to an AVL tree.  However, this particular 
implementation contains a pointer the the top of the book, which ensures the same performance as a linked list for 
orders at the top of the book (with the exception of an order which creates a new top of book price level).  

# Performance

Insertions of the first order at a particular price level are performed in O(lg n) time, where n is the number of price 
levels on the side of the book where the order is being inserted.  Subsequent order insertions at that price level are 
also performed in O(lg n) time _except in the case of insertions at the current top of book, which are performed in O(1) 
time_.  Removals and modifications of orders are performed in O(lg n) time _except in the case of removals and modifications 
at the current top of book, which are performed in O(1) time._  Finding the new top of book following the deletion of 
the previous top of book is performed in O(1) time.

# Functionality

GetSnapshot can be used to return a snapshot of the book containing the desired number of price levels or the current 
number of price levels on the given side of the book, whichever is less.  The snapshot is returned as a pair of deques 
containing the desired number of price levels or the current number of price levels on the given side of the book, 
whichever is less.

WriteToFile writes an order update and the price, size, and number of orders of the desired number of price levels of 
the resulting snapshot to a file.  If the number of price levels in the book (or the number of price levels returned by 
GetSnapshot) is less than the number of price levels requested, the price for the empty price levels is left blank and 
the size and number of orders are reported as 0. 

PrintBook prints the current state of the book, which includes the price, size, number of orders, and the 
individual order ID and size for each order which comprises the price level for each price level in the book.

PrintReport prints a summary of the orders processed including the number of adds, top of book adds, removes, top of book
removes, modifies, top of book modifies, total number of orders processed, total number of top of book orders processed, 
total processing time, and processing time per order. 

# Tests

Unit tests are implemented using the Catch2 test framework (https://github.com/catchorg/Catch2).  Note that some test 
related to top of book functionality require the OrderBook::GetSide method be made public. 