//
// Created by Benjamen Lambert on 3/25/2020.
//

#include "Order.h"

int Order::GetPrice() const {
  return price_;
}

int Order::GetQty() const {
  return qty_;
}

char Order::GetSide() const {
  return side_;
}

void Order::UpdateQty(const int &qty) {
  qty_ = qty;
}