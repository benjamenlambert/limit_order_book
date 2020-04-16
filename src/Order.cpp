//
// Created by Benjamen Lambert on 3/25/2020.
//

#include "Order.h"

//char Order::GetSide() const {
//  return side_;
//}

int Order::GetPrice() const {
  return price_;
}

int Order::GetQty() const {
  return qty_;
}

void Order::UpdateQty(int qty) {
  qty_ = qty;
}