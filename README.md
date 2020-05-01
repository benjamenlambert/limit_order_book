# About

Limit order book written in C++.  

# Design

Each side of the order book is implemented as an AVL tree containing all price levels on that side of the book with 
non-zero quantity.  Each side of the book also contains a pointer to the top of the book (highest price level on the bid 
side or lowest price level on the ask side).  Each price level contains a hash table which contains all orders at that 
price, using the order ID as the key.  By default, the hash tables have space for 50 orders before a resize/rehash is 
required.  This can be changed to suit the characteristics of the order book.

# Design Considerations

An AVL tree is used to hold all price levels with non-zero quantity on a particular side of the book.  Alternative data 
structures that could also be used include a red-black tree, linked list, or hash table.  

If more insertions and removals of price levels than insertions and removals orders at existing price levels is expected, 
a red-black tree would be preferred over an AVL tree.

If most activity takes place at or near the top of the book, a linked list may be preferred to an AVL tree.  However, 
this particular implementation contains a pointer the the top of the book, which ensures the same performance as a 
linked list for orders at the top of the book (excluding orders which create a new top of book).

If only the price of the top of the book matters, a hash table of price levels would be preferred.

# Performance

Insertions of the first order at a particular price level are performed in O(lg n) time, where n is the number of price 
levels on the side of the book where the order is being inserted.  Subsequent order insertions at that price level are 
also performed in O(lg n) time _except in the case of insertions at the current top of book, which are performed in O(1) 
time_.  Removals and modifications of orders are performed in O(lg n) time _except in the case of removals and modifications 
at the current top of book, which are performed in O(1) time_.

# Functionality

GetSnapshot can be used to return a snapshot of the book containing the desired number of price levels or the current 
number of price levels on the given side of the book, whichever is less.  The snapshot is returned as a pair of deques 
containing the desired number of price levels or the current number of price levels on the given side of the book, 
whichever is less.

WriteToFile writes an order update and the resulting price and size of the the desired number of price levels on the 
side of the book to a file.  If the number of price levels in the book (or the number of price levels returned by 
GetSnapshot) is less than the number of price levels requested, the price for the empty price levels is left blank and 
the size is reported at 0. 

# Tests

Unit tests are implemented using the Catch2 test framework (https://github.com/catchorg/Catch2).

# Additional Features to be Added

Storage of a pointer to the next highest (in the case of an ask) or next lowest (in the case of a bid) price level within 
the PriceLevel class would improve finding the new top of book in the event that the current top of book is removed from 
O(lg n) to O(1) time.