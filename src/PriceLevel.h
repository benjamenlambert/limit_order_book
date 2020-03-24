//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_PRICELEVEL_H
#define LIMIT_ORDER_BOOK_PRICELEVEL_H

#include <unordered_map>

// A single price level within the book.
// Represented as a price and a hash containing orders at that price
class PriceLevel {
public:
    PriceLevel();

    int price_;

private:
    std::unordered_map<int, int> orders_;

};


#endif //LIMIT_ORDER_BOOK_PRICELEVEL_H
