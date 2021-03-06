//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_
#define LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_

// Structure containing the information included in an order update.
struct OrderUpdate {
  OrderUpdate(const unsigned long long int &timestamp,
              const char &side,
              const char &action,
              const int &id,
              const int &price,
              const int &qty) :
      timestamp(timestamp),
      side(side),
      action(action),
      id(id),
      price(price),
      qty(qty) {
  }

  unsigned long long int timestamp; // Microseconds since the market open.
  char side;
  char action;
  int id;
  int price;
  int qty;
};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_
