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
  typedef std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> Snapshot;

  OrderBook() : adds_(0), removes_(0), mods_(0), tob_updates_(0) {
  }

  // Wrapper function
  void UpdateBook(const OrderUpdate &update);

  void PrintReport(std::string file_name, double duration);
  void WriteToFile(std::ofstream &file, const OrderUpdate &update, Snapshot &snapshot, int n_levels);
  void FormatOutputFile(std::ofstream &file, int n_levels);

  // Returns a pair of deques each with n_levels of PriceLevels.  Will return the max of n_levels or the number of levels currently on that side of the book
  Snapshot GetSnapshot(int n_levels);

 private:
  // Returns the requested side of the book
  Side *GetSide(char side);

  void AddOrder(const OrderUpdate &update);
  void RemoveOrder(const OrderUpdate &update);
  void ModifyOrder(const OrderUpdate &update);


  Side bid_;
  Side ask_;

  int adds_;
  int removes_;
  int mods_;
  int tob_updates_;

};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
