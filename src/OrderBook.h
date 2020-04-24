//
// Created by Benjamen Lambert on 4/2/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
#define LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_

#include <queue>

#include "Side.h"

// The order book containing both sides (bid and ask) of the book.
class OrderBook {
 public:
  OrderBook() : adds_(0), removes_(0), mods_(0), tob_updates_(0) {
  }

  // Wrapper function
  void UpdateBook(const OrderUpdate &update);

  Side *GetSide(char side);
  void PrintReport(double duration);
  void PrintBook();

  std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> GetMarketDepth(int levels);

 private:

  void AddOrder(const OrderUpdate &update);
  void RemoveOrder(const OrderUpdate &update);
  void ModifyOrder(const OrderUpdate &update);

  void Print();

  Side bid_;
  Side ask_;

  int adds_;
  int removes_;
  int mods_;
  int tob_updates_;

};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
