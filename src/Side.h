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
// Implemented as an AVL tree containing all PriceLevels with non-zero quantity.  Each side of the order book is stored
// in the Orderbook
class Side {
 public:
  Side() : root_(nullptr), top_of_book_(nullptr) {
  }
  ~Side();

  void AddLevel(PriceLevel *level);
  PriceLevel *FindLevel(const int &price);
  void RemoveLevel(const int &price);

  [[nodiscard]] PriceLevel *FindMin() const;
  [[nodiscard]] PriceLevel *FindMax() const;

  // Builds a snapshot of the Side consisting of the price_ and size_ of the top n_levels
  void GetSnapshot(const char &side, int n_levels, std::deque<PriceLevel *> &deq) const;
  // Writes the price_ for each PriceLevel on the Side (in-order) to a string.
  void InOrderString(std::string &str) const;
  // Writes the price_ for each PriceLevel on the Side (pre-order) to a string.
  void PreOrderString(std::string &str) const;
  // Prints the price_, size_, num_orders_, and all individual orders for each PriceLevel on the Side
  void PrintSide() const;

  // Pointer to the PriceLevel at the top of the book
  PriceLevel *top_of_book_;

 private:
  // Adds a PriceLevel to the Side
  PriceLevel *Add(PriceLevel *level, PriceLevel *current_level);
  // Finds a PriceLevel on the Side.
  PriceLevel *Find(int price, PriceLevel *current_level);
  // Removes a PriceLevel on the Side
  PriceLevel *Remove(int price, PriceLevel *current_level);

  // Returns the minimum PriceLevel on the Side
  PriceLevel *Min(PriceLevel *current_level) const;
  // Returns the maximum PriceLevel on the Side
  PriceLevel *Max(PriceLevel *current_level) const;

  // Ensures balance in the AVL tree
  void BalanceTree(PriceLevel *&current_level);

  // Tree rotations to restore balance in the AVL tree
  void RotateLeft(PriceLevel *&current_level);
  void RotateRight(PriceLevel *&current_level);
  void RotateRightLeft(PriceLevel *&current_level);
  void RotateLeftRight(PriceLevel *&current_level);

  // AVL tree helper functions
  static int GetHeight(const PriceLevel *level);
  static int GetBalanceFactor(const PriceLevel *level);
  static void UpdateHeight(PriceLevel *current_level);

  // Memory cleanup
  PriceLevel *DestroySide(PriceLevel *current_level);

  // Print functions
  void PrintInOrder(const PriceLevel *level) const;
  void PrintReverseOrder(const PriceLevel *level) const;
  // Print functions for testing
  void InOrderString(const PriceLevel *level, std::string &str) const;
  void PreOrderString(const PriceLevel *level, std::string &str) const;

  void GetSnapshot(PriceLevel *level, char side, int &n_levels, std::deque<PriceLevel *> &deq) const;

  PriceLevel *root_;
};

#endif //LIMIT_ORDER_BOOK_SRC_SIDE_H_
