//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_ORDERUPDATE_H
#define LIMIT_ORDER_BOOK_ORDERUPDATE_H


// Contains the information contained in an order update.
class OrderUpdate {
public:
    OrderUpdate();
    OrderUpdate(unsigned long long int timestamp, char side, char action, int id, int price, int qty);

    unsigned long long int timestamp_; // Microseconds since the market open
    char side_;
    char action_;
    int id_; // Can handle up to approx. 2.1 billion unique ids.
    int price_;
    int qty_;
};


#endif //LIMIT_ORDER_BOOK_ORDERUPDATE_H
