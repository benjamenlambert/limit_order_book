//
// Created by Benjamen Lambert on 3/31/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_SIDE_H_
#define LIMIT_ORDER_BOOK_SRC_SIDE_H_

#include <deque>
#include <iostream>

#include "PriceLevel.h"
#include "Order.h"

// One side of the book (bid or ask).
// Implemented as an AVL tree containing all PriceLevels with non-zero quantity.  Stored in an OrderBook along with the
// opposing Side.
class Side {
 public:
  Side() : root_(nullptr), top_of_book_(nullptr) {
  }
  ~Side();

  // Wrapper functions
  void AddLevel(PriceLevel *level);
  PriceLevel *FindLevel(int price);
  void RemoveLevel(int price);

  // Find wrapper functions
  PriceLevel *FindMin();
  PriceLevel *FindMax();

  // Print wrapper functions
  void PrintSide();
  // Print wrapper functions for testing
  void ToStringInOrder(std::string &str);
  void ToStringPreOrder(std::string &str);

  void ToDequeInOrder(std::deque<PriceLevel *> &deq);

  // Pointer to the PriceLevel at the top of the book
  PriceLevel *top_of_book_;

 private:
  PriceLevel *Add(PriceLevel *level, PriceLevel *current_level);
  PriceLevel *Find(int price, PriceLevel *current_level);
  PriceLevel *Remove(int price, PriceLevel *current_level);

  // Returns the minimum PriceLevel on the Side
  PriceLevel *Min(PriceLevel *current_level);
  // Returns the maximum PriceLevel on the Side
  PriceLevel *Max(PriceLevel *current_level);

  // Ensures balance in the AVL tree
  void BalanceTree(PriceLevel *&current_level);

  // Restore balance in the AVL tree
  void RotateLeft(PriceLevel *&current_level);
  void RotateRight(PriceLevel *&current_level);
  void RotateRightLeft(PriceLevel *&current_level);
  void RotateLeftRight(PriceLevel *&current_level);

  // AVL tree helper functions
  int GetHeight(PriceLevel *level);
  void UpdateHeight(PriceLevel *current_level);
  int GetBalanceFactor(PriceLevel *level);

  // Memory cleanup
  PriceLevel *DestroySide(PriceLevel *current_level);

  // Print functions
  void InOrder(PriceLevel *level);
  void ReverseOrder(PriceLevel *level);
  // Print functions for testing
  void ToStringInOrder(PriceLevel *level, std::string &str);
  void ToStringPreOrder(PriceLevel *level, std::string &str);

  void ToDequeInOrder(PriceLevel *level, std::deque<PriceLevel *> &deq);

  PriceLevel *root_;
};

#endif //LIMIT_ORDER_BOOK_SRC_SIDE_H_
