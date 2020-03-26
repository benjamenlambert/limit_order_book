//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "HistoricalData.h"

#include <fstream>
#include <iostream>
#include <sstream>


std::vector<std::vector<std::string>> HistoricalData::ReadCSV(const std::string &fileName, bool has_col_headers) {
    std::ifstream file;
    file.open(fileName);

    std::vector<std::vector<std::string>> csv;

    if(file.is_open()) {
        std::cout << "Reading file..." << std::endl;
        std::string line;

        if (has_col_headers) { // Discards the first line if the .csv file contains headers/column names
            std::getline(file, line);
            line.clear();
        }

        while (std::getline(file, line)) { // Reads each line of .csv file
            std::stringstream ss(line);
            std::string str;

            std::vector<std::string> row;

            while (std::getline(ss, str, ',')) {
                row.push_back(str);
            }

            csv.push_back(row);
        }
        std::cout << "Complete." << std::endl;
    }
    else {
        std::cout << "File not open!!!" << std:: endl;
    }

    file.close();

    return csv; // Return csv
}