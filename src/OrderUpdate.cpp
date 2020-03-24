//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "OrderUpdate.h"

OrderUpdate::OrderUpdate() {
    timestamp_ = -99999999;
    side_ = 'n';
    action_ = 'n';
    id_ = -99999999;
    price_ = -99999999;
    qty_ = -99999999;
};

OrderUpdate::OrderUpdate(unsigned long long int timestamp, char side, char action, int id, int price,
                         int qty) {
    timestamp_ = timestamp;
    side_ = side;
    action_ = action;
    id_ = id;
    price_ = price;
    qty_ = qty;
};
