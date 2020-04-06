//
// Created by Benjamen Lambert on 3/31/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_SIDE_H_
#define LIMIT_ORDER_BOOK_SRC_SIDE_H_

#include <iostream>

#include "PriceLevel.h"
#include "Order.h"

// One side of the book (bid or ask).
// Implemented as an AVL tree containing all PriceLevels with non-zero quantity.  Stored in an OrderBook along with the
// opposing Side.
class Side {
 public:
  Side();
  ~Side();

  void InsertLevel(PriceLevel *level);
  PriceLevel *FindLevel(int price);
  void RemoveLevel(int price);

  // Returns the minimum PriceLevel on the Side
  PriceLevel *FindMin();
  // Returns the maximum PriceLevel on the Side
  PriceLevel *FindMax();

  void PrintSide();

 private:
  PriceLevel *Insert(PriceLevel *level, PriceLevel *current_level);
  PriceLevel *Find(int price, PriceLevel *current_level);
  PriceLevel *Remove(int price, PriceLevel *current_level);

  PriceLevel *Min(PriceLevel *current_level);
  PriceLevel *Max(PriceLevel *current_level);

  // Ensures balance in the AVL tree after every insertion/deletion
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

  PriceLevel *DestroySide(PriceLevel *current_level);

  void InOrder(PriceLevel *level);
  void ReverseOrder(PriceLevel *level);

  PriceLevel *root_;
};

#endif //LIMIT_ORDER_BOOK_SRC_SIDE_H_
