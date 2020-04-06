//
// Created by Benjamen Lambert on 3/25/2020.
//

#include "Order.h"

Order::Order(const OrderUpdate &update) {
  timestamp_ = update.timestamp;
  //id_ = update.id;
  side_ = update.side;
  price_ = update.price;
  qty_ = update.qty;
}

char Order::GetSide() const {
  return side_;
}

int Order::GetPrice() const {
  return price_;
}

int Order::GetQty() const {
  return qty_;
}

void Order::UpdateQty(int qty) {
  qty_ = qty;
}