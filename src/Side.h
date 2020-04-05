//
// Created by Benjamen Lambert on 3/31/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_SIDE_H_
#define LIMIT_ORDER_BOOK_SRC_SIDE_H_

#include <iostream>

#include "PriceLevel.h"
#include "Order.h"

class Side {
 public:
  Side();;
  ~Side();

  void InsertLevel(PriceLevel *level);
  PriceLevel *FindLevel(int price);
  PriceLevel *FindMin();
  PriceLevel *FindMax();
  void RemoveLevel(int price);

  void PrintSide();

 private:
  PriceLevel *Insert(PriceLevel *level, PriceLevel *current_level);
  PriceLevel *Find(int price, PriceLevel *current_level);
  PriceLevel *Remove(int price, PriceLevel *current_level);

  int GetHeight(PriceLevel *level);
  void UpdateHeight(PriceLevel *current_level);
  int GetBalanceFactor(PriceLevel *level);
  void BalanceTree(PriceLevel *&current_level);

  void RotateLeft(PriceLevel *&current_level);
  void RotateRight(PriceLevel *&current_level);
  void RotateRightLeft(PriceLevel *&current_level);
  void RotateLeftRight(PriceLevel *&current_level);

  PriceLevel *Min(PriceLevel *current_level);
  PriceLevel *Max(PriceLevel *current_level);

  PriceLevel *DestroySide(PriceLevel *current_level);

  void Print(PriceLevel *level);

  PriceLevel *root_;
};

#endif //LIMIT_ORDER_BOOK_SRC_SIDE_H_
