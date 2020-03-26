//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_HISTORICALDATA_H
#define LIMIT_ORDER_BOOK_HISTORICALDATA_H


#include <iostream>
#include <vector>

#include "MarketData.h"
#include "OrderUpdate.h"

// Reads and processes a .csv file containing order updates.
class HistoricalData : public MarketData {
public:

    // Reads a .csv file containing raw order updates line by line into memory as a vector of vectors.
    // Accepts the filename of the .csv file as a string as the sole required argument.
    // Optionally accepts hasColHeaders as a boolean. Default value is false.  If true, the first line containing
    // header/column names will be ignored.
    std::vector<std::vector<std::string>> ReadCSV(const std::string &fileName, bool has_col_headers=false);
};


#endif //LIMIT_ORDER_BOOK_HISTORICALDATA_H
