//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "PriceLevel.h"

void PriceLevel::AddOrder(const int &order_id, const Order &order) {
  orders_.insert(std::make_pair(order_id, order)); // Add the order to the hash table
  size_ += orders_.at(order_id).GetQty(); // Update size_ to reflect addition of new order
}

void PriceLevel::ModifyOrder(const OrderUpdate &update) {
  int prev_qty = orders_.at(update.id).GetQty(); // Get previous quantity
  orders_.at(update.id).UpdateQty(update.qty); // Update quantity of order in the hash table
  size_ += orders_.at(update.id).GetQty() - prev_qty; // Update size_ to reflect change in order qty
}

void PriceLevel::RemoveOrder(const int &order_id) {
  size_ -= orders_.at(order_id).GetQty(); // Update size_ to reflect removal of order
  orders_.erase(order_id); // Remove the order
}

const Order &PriceLevel::GetOrder(const int &id) const {
  return orders_.at(id);
}

const std::unordered_map<int, Order> &PriceLevel::GetOrders() const {
  return orders_;
}

int PriceLevel::GetPrice() const {
  return price_;
}

int PriceLevel::GetSize() const {
  return size_;
}

int PriceLevel::NumOrders() const {
  return orders_.size();
}

void PriceLevel::CopyIOP(const PriceLevel *iop) {
  // Copy the price_, size_, and orders_ of the IOP to the price level to be removed.  The pointers will remain intact.
  // After this, there will be two price levels with identical price_, size_ and orders_ pointing to different price levels.
  // The original IOP will then be removed which will effectively remove the original price level.
  price_ = iop->price_;
  orders_ = iop->orders_;
  size_ = iop->size_;
}