//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_PRICELEVEL_H
#define LIMIT_ORDER_BOOK_PRICELEVEL_H

#include <unordered_map>

#include "Order.h"

// A single price level within the book.
// Represented as a price and an unordered map containing orders at that price
class PriceLevel {
 public:
  PriceLevel();
  PriceLevel(int order_id, const Order &order);

  const Order &AddOrder(int order_id, const Order &order);
  const Order &ModifyOrder(const OrderUpdate &update);
  int RemoveOrder(int order_id);

  const Order &GetOrder(int id);
  const std::unordered_map<int, Order> &GetOrders();
  int GetSize();
  int GetPrice();

  PriceLevel *left_;
  PriceLevel *right_;

  int NumOrders();

 private:
  int price_;
  int size_;
  std::unordered_map<int, Order> orders_;
};

#endif //LIMIT_ORDER_BOOK_PRICELEVEL_H