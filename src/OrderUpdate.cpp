//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "OrderUpdate.h"


OrderUpdate::OrderUpdate(unsigned long long int timestamp, char side, char action, int id, int price, int qty) {
    timestamp_ = timestamp;
    side_ = side;
    action_ = action;
    id_ = id;
    price_ = price;
    qty_ = qty;
}

unsigned long long int OrderUpdate::GetTimestamp() const {
    return timestamp_;
}

char OrderUpdate::GetSide() const {
    return side_;
}

char OrderUpdate::GetAction() const {
    return action_;
}

int OrderUpdate::GetID() const {
    return id_;
}

int OrderUpdate::GetPrice() const {
    return price_;
}

int OrderUpdate::GetQty() const {
    return qty_;
}