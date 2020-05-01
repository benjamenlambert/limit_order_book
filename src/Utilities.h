//
// Created by Benjamen Lambert on 4/28/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_UTILITIES_H_
#define LIMIT_ORDER_BOOK_SRC_UTILITIES_H_

#include <iostream>
#include <vector>

namespace utilities {
// Reads a .csv file containing raw order updates line by line into memory as a vector of vectors.
// Accepts the filename of the .csv file as a string as the sole required argument.
// Optionally accepts has_col_headers as a boolean. Default value is false.  If true, the first line containing
// header/column names will be ignored.
std::vector<std::vector<std::string>> ReadCSV(const std::string &file_name, bool has_column_labels = false);

// Reformats a sting into a desired filename.  Used with entry.path() to reformat file name. name.csv converted to name_output.csv
std::string FormatFileName(const std::string &file_name);
}

#endif //LIMIT_ORDER_BOOK_SRC_UTILITIES_H_
