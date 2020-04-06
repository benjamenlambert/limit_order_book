//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_
#define LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_

#include "Message.h"

// Structure containing the information in an order update.
struct OrderUpdate : public Message {
  unsigned long long int timestamp; // Microseconds since the market open.
  char side;
  char action;
  int id;
  int price;
  int qty;

  OrderUpdate(unsigned long long int timestamp, char side, char action, int id, int price, int qty) :
      timestamp(timestamp),
      side(side),
      action(action),
      id(id),
      price(price),
      qty(qty) {}
};

#endif //LIMIT_ORDER_BOOK_SRC_ORDERUPDATE_H_
