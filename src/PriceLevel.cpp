//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "PriceLevel.h"
#include "Order.h"
#include "OrderUpdate.h"

const Order &PriceLevel::AddOrder(const OrderUpdate &update) {
    int id = update.id_;
    Order order(update);
    orders_.insert(std::make_pair(id, order));
    size_ += order.GetQty();
    return orders_.at(id);
}

// TODO Need to be able to move to another price point
// TODO Currently only handles qty change
const Order &PriceLevel::ModifyOrder(const OrderUpdate &update) {
    int id = update.id_;
    int prev_qty = orders_.at(id).GetQty();
    int qty = orders_.at(id).UpdateQty(update.qty_);
    int price = orders_.at(id).UpdatePrice(update.price_);
    size_ += qty - prev_qty;
    return orders_.at(id);
}

int PriceLevel::RemoveOrder(const OrderUpdate &update) {
    int id = update.id_;
    size_ -= orders_.at(id).GetQty();
    return orders_.erase(id);
}

int PriceLevel::NumOrders() {
    return orders_.size();
}

const std::unordered_map<int, Order> &PriceLevel::GetOrders() {
    return orders_;
}

const Order &PriceLevel::GetOrder(int id) {
    return orders_.at(id);
}

int PriceLevel::GetSize() {
    return size_;
}