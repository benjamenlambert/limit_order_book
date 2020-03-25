//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "HistoricalData.h"

#include <fstream>
#include <iostream>
#include <sstream>


// **Returns a ptr to a csv on the heap
//std::vector<std::vector<std::string>> *HistoricalData::ReadCSV(const std::string &fileName, bool has_col_headers) {
// **Returns a copy of the csv
std::vector<std::vector<std::string>> HistoricalData::ReadCSV(const std::string &fileName, bool has_col_headers) {
    std::ifstream file;
    file.open(fileName);

    //std::vector<std::vector<std::string>> *csv = new std::vector<std::vector<std::string>>; // **Ptr to csv on the heap
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

            //csv->push_back(row); // **Adds row to csv on heap
            csv.push_back(row);
        }
        std::cout << "Complete." << std::endl;
    }
    else {
        std::cout << "File not open!!!" << std:: endl;
    }

    file.close();

    //return *csv // **Return ptr to csv
    return csv; // Return csv
}

OrderUpdate HistoricalData::ProcessLine(const std::vector<std::string> &line) {

    unsigned long long int timestamp;
    int id, price, qty;
    char side, action;

    timestamp = std::stoull(line[0]);
    side = line[1][0];
    action = line[2][0];
    id = std::stoi(line[3]);
    price = std::stoi(line[4]);
    qty = std::stoi(line[5]);

    OrderUpdate update(timestamp, side, action, id, price, qty); // Creates OrderUpdate object

    return update;
}