//
// Created by Benjamen Lambert on 3/25/2020.
//

#include "Order.h"

Order::Order(const OrderUpdate &update) {
    timestamp_ = update.GetTimestamp();
    side_ = update.GetSide();
    price_ = update.GetPrice();
    qty_ = update.GetQty();
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

int Order::UpdatePrice(int price) {
    price_ = price;
    return price_;
}

int Order::UpdateQty(int qty) {
    qty_ = qty;
    return qty_;
}