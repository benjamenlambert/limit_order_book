//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "PriceLevel.h"
#include "Order.h"
#include "OrderUpdate.h"

PriceLevel::PriceLevel() {

}

PriceLevel::PriceLevel(int order_id, const Order &order) {
    AddOrder(order_id, order);
}

const Order &PriceLevel::AddOrder(int order_id, const Order &order) {
    int id = order_id;
    orders_.insert(std::make_pair(id, order));
    size_ += orders_.at(id).GetQty();
    return orders_.at(id);
}

const Order &PriceLevel::ModifyOrder(const OrderUpdate &update) {
    int id = update.id;
    int prev_qty = orders_.at(id).GetQty();
    int qty = orders_.at(id).UpdateQty(update.qty);
    int price = orders_.at(id).UpdatePrice(update.price);
    size_ += qty - prev_qty;
    return orders_.at(id);
}

int PriceLevel::RemoveOrder(int order_id) {
    int id = order_id;
    size_ -= orders_.at(id).GetQty();
    return orders_.erase(id);
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

int PriceLevel::NumOrders() {
    return orders_.size();
}