//
// Created by Benjamen Lambert on 3/25/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDER_H_
#define LIMIT_ORDER_BOOK_SRC_ORDER_H_

#include "OrderUpdate.h"

// Class containing the information in an order.  Orders are stored in a hash table of all Orders at a given price,
// using the order id as the key.  This implementation does not require the order id to be stored within the order
// itself, as it is implicitly stored in the key.
class Order {
 public:
  // Creates a new Order from an OrderUpdate
  explicit Order(const OrderUpdate &update)
      : timestamp_(update.timestamp), side_(update.side), price_(update.price), qty_(update.qty) {
  }

  //[[nodiscard]] char GetSide() const;
  [[nodiscard]] int GetPrice() const;
  [[nodiscard]] int GetQty() const;

  // Updates the order quantity in the event of a modify order message.
  void UpdateQty(int qty);

 private:
  unsigned long long int timestamp_; // Microseconds since the market open.
  //int id_;  // Not required in current implementation as orders are stored in a hash table with order id as the key
  char side_;
  int price_;
  int qty_;
};

#endif //LIMIT_ORDER_BOOK_SRC_ORDER_H_
