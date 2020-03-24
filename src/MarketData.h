//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_MARKETDATA_H
#define LIMIT_ORDER_BOOK_MARKETDATA_H


#include <fstream>
#include <sstream>
#include "OrderUpdate.h"

// Reads and processes a .csv file containing order updates.
class MarketData {
public:

    // Reads a .csv file line by line.
    // Accepts the filename of the .csv file as a string as the sole required argument.
    // Optionally accepts hasColHeaders as a boolean. Default value is false.  If true, the first line containing
    // header/column names will be ignored
    void ReadCSV(const std::string &fileName, bool has_col_headers=false);

    // Processes a line and returns an OrderUpdate object.
    // Accepts a string, containing the data contained in an OrderUpdate object, as the sole argument and returns
    // an OrderUpdate object.
    // String format expected to be in the following order: timestamp, side, action, order id, price, quantity.
    OrderUpdate ProcessLine(const std::string &line);

    void HandleMessage(const OrderUpdate &update);
};


#endif //LIMIT_ORDER_BOOK_MARKETDATA_H
