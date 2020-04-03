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

  PriceLevel *InsertLevel(PriceLevel &level);
  PriceLevel *FindLevel(int price);
  PriceLevel *FindTop(char side);
  PriceLevel *FindMin();
  PriceLevel *FindMax();
  int RemoveLevel(int price);

  void PrintSide();

  PriceLevel *top_of_book_;

 private:
  PriceLevel *&Find(int price, PriceLevel *&current_level);
  PriceLevel *Min(PriceLevel *current_level);
  PriceLevel *Max(PriceLevel *current_level);
  PriceLevel *&Remove(PriceLevel *&current_level);
  PriceLevel *DestroySide(PriceLevel *current_level);

  void Print(PriceLevel *level);

  PriceLevel *root_;
};

#endif //LIMIT_ORDER_BOOK_SRC_SIDE_H_
