//
// Created by Benjamen Lambert on 3/25/2020.
//

#ifndef LIMIT_ORDER_BOOK_ORDER_H
#define LIMIT_ORDER_BOOK_ORDER_H

#include "OrderUpdate.h"

class Order {
public:
    Order();
    explicit Order(const OrderUpdate &update);
    [[nodiscard]] int GetQty() const;
    [[nodiscard]] int GetPrice() const;
    int UpdateQty(int qty);
    int UpdatePrice(int price);

private:

    unsigned long long int timestamp_; // Microseconds since the market open.
    char side_;
    char action_;
    int price_;
    int qty_;
};


#endif //LIMIT_ORDER_BOOK_ORDER_H
