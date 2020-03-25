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
    // **First version returns a ptr to a csv on the heap (may be required to improve performance by preventing copying
    // **over csv file on ReadCSV stack).
    // **Second version returns a copy of the csv from ReadCSV stack.
    // **Returns a ptr to a csv on the heap
    //std::vector<std::vector<std::string>> *ReadCSV(const std::string &fileName, bool has_col_headers=false);
    // **Returns a copy of the csv
    std::vector<std::vector<std::string>> ReadCSV(const std::string &fileName, bool has_col_headers=false);

    // Processes a line (row from csv as a vector of strings) and returns an OrderUpdate object.
    // Accepts a vector of strings, containing the data contained in an OrderUpdate object, as the sole argument and returns
    // an OrderUpdate object.
    // Vector of strings expected to be in the following order: timestamp, side, action, order id, price, quantity.
    // Expects side and action to be a single character string
    OrderUpdate ProcessLine(const std::vector<std::string> &line);
};


#endif //LIMIT_ORDER_BOOK_HISTORICALDATA_H
