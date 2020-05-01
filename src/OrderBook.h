//
// Created by Benjamen Lambert on 4/2/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
#define LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_

#include <fstream>

#include "Side.h"

// The order book containing both sides (bid and ask) of the book.
class OrderBook {
 public:
  typedef std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> Snapshot;

  OrderBook() : adds_(0), removes_(0), mods_(0), tob_adds_(0), tob_removes_(0), tob_mods_(0) {
  }

  // Updates the book following an OrderUpdate
  void UpdateBook(const OrderUpdate &update);

  // Returns a pair of deques each with n_levels of PriceLevels.  Will return the max of n_levels or the number of levels currently on that side of the book
  [[nodiscard]] Snapshot GetSnapshot(const int &n_levels) const;

  // Writes column labels for the update and n_levels of a snapshot to the output file
  static void FormatOutputFile(std::ofstream &file, const int &n_levels);
  // Writes the update and n_levels of the resulting snapshot to a file
  static void WriteToFile(std::ofstream &file, const OrderUpdate &update, Snapshot &snapshot, const int &n_levels);

  // Prints the price_, size_, num_orders_, and all individual orders for each PriceLevel on each Side of the OrderBook
  void PrintBook() const;
  // Prints a summary of the OrderBook including the number of add, remove, modify, and top of book messages.  Also includes
  // the total time (not including the time to read the data) and the average processing time per update (not including
  // the time to read the data)
  void PrintReport(const std::string &file_name, const double &duration) const;

 private:
  // Returns the requested side of the book
  Side *GetSide(const char &side); // Make public in order to test top of book functionality

  void AddOrder(const OrderUpdate &update);
  void RemoveOrder(const OrderUpdate &update);
  void ModifyOrder(const OrderUpdate &update);

  void Print() const;

  Side bid_;
  Side ask_;

  int adds_;
  int removes_;
  int mods_;
  int tob_adds_;
  int tob_removes_;
  int tob_mods_;

};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERBOOK_H_
