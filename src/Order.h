//
// Created by Benjamen Lambert on 3/25/2020.
//

#ifndef LIMIT_ORDER_BOOK_ORDER_H
#define LIMIT_ORDER_BOOK_ORDER_H

#include "OrderUpdate.h"

class Order {
public:
    explicit Order(const OrderUpdate &update);

    [[nodiscard]] char GetSide() const;
    [[nodiscard]] int GetPrice() const;
    [[nodiscard]] int GetQty() const;

    int UpdatePrice(int price);
    int UpdateQty(int qty);

private:

    unsigned long long int timestamp_; // Microseconds since the market open.
    char side_;
    int price_;
    int qty_;
};


#endif //LIMIT_ORDER_BOOK_ORDER_H
