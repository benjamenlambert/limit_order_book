//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "PriceLevel.h"
#include "Order.h"
#include "OrderUpdate.h"

void PriceLevel::AddOrder(int order_id, const Order &order) {
  orders_.insert(std::make_pair(order_id, order));
  size_ += orders_.at(order_id).GetQty(); // Update the PriceLevel size_ to reflect addition of new order
}

void PriceLevel::ModifyOrder(const OrderUpdate &update) {
  int prev_qty = orders_.at(update.id).GetQty(); // Get previous quantity
  orders_.at(update.id).UpdateQty(update.qty); // Update quantity
  size_ += orders_.at(update.id).GetQty() - prev_qty; // Update the PriceLevel size_ to reflect change in order qty
}

void PriceLevel::RemoveOrder(int order_id) {
  size_ -= orders_.at(order_id).GetQty(); // Update the PriceLevel size_ to reflect removal of order
  orders_.erase(order_id); // Remove the order
}

const Order &PriceLevel::GetOrder(int id) {
  return orders_.at(id);
}

const std::unordered_map<int, Order> &PriceLevel::GetOrders() {
  return orders_;
}

int PriceLevel::GetSize() {
  return size_;
}

int PriceLevel::GetPrice() {
  return price_;
}

int PriceLevel::NumOrders() {
  return orders_.size();
}