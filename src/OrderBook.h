//
// Created by Benjamen Lambert on 4/2/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
#define LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_

#include "Side.h"

class OrderBook {
 public:
  Side *GetSide(char side);

 private:
  Side bid_;
  Side ask_;
};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
