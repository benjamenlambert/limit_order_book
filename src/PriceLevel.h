//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_PRICELEVEL_H
#define LIMIT_ORDER_BOOK_PRICELEVEL_H

#include <unordered_map>

#include "Order.h"

// A single price level within the book.
// Represented as a price and a hash containing orders at that price
class PriceLevel {
public:
    //Changed to return by value versus const ref, couldn't get iter.second.GetQty() in main to work with const ref
    Order AddOrder(const OrderUpdate &update);
    Order ModifyOrder(const OrderUpdate &update);
    int RemoveOrder(const OrderUpdate &update);
    int NumOrders();
    Order GetOrder(int id);
    std::unordered_map<int, Order> GetOrders();

private:
    int size_;
    std::unordered_map<int, Order> orders_;
};


#endif //LIMIT_ORDER_BOOK_PRICELEVEL_H
