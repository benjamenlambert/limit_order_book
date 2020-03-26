//
// Created by Benjamen Lambert on 3/25/2020.
//

#include "Order.h"

Order::Order() {
    timestamp_ = -99999999;
    side_ = 'n';
    action_ = 'n';
    price_ = -99999999;
    qty_ = -99999999;
}

Order::Order(const OrderUpdate &update) {
    timestamp_ = update.timestamp_;
    side_ = update.side_;
    action_ = update.action_;
    price_ = update.price_;
    qty_ = update.qty_;
}

int Order::GetQty() {
    return qty_;
}