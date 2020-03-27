//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_ORDERUPDATE_H
#define LIMIT_ORDER_BOOK_ORDERUPDATE_H


#include "Message.h"

// Contains the information contained in an order update.
struct OrderUpdate : public Message {
    unsigned long long int timestamp; // Microseconds since the market open.
    char side;
    char action;
    int id; // Can handle up to approx. 2.1 billion unique ids.
    int price;
    int qty;

    OrderUpdate(unsigned long long int timestamp, char side, char action, int id, int price, int qty) :
        timestamp(timestamp),
        side(side),
        action(action),
        id(id),
        price(price),
        qty(qty) {}
};


#endif //LIMIT_ORDER_BOOK_ORDERUPDATE_H
