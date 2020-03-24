//
// Created by Benjamen Lambert on 3/24/2020.
//

#include "HistoricalData.h"

#include <fstream>
#include <iostream>
#include <sstream>


void HistoricalData::ReadCSV(const std::string &fileName, bool has_col_headers) {
    std::ifstream file;
    file.open(fileName);

    if(file.is_open()) {
        std::cout << "Reading file..." << std::endl;
        std::string line;

        if (has_col_headers) { // Discards the first line if the .csv file contains headers/column names
            std::getline(file, line);
            line.clear();
        }

        while(std::getline(file, line)) { // Reads each line of .csv file

            OrderUpdate update = HistoricalData::ProcessLine(line); // Processes line and returns an OrderUpdate object

            update.HandleUpdate(update); // Handles the update
        }
        std::cout << "Complete.";
    }
    else {
        std::cout << "File not open!!!" << std:: endl;
    }

    file.close();
}

OrderUpdate HistoricalData::ProcessLine(const std::string &line) {
    std::stringstream ss(line);
    std::string str;

    unsigned long long int timestamp;
    int id, price, qty;
    std::string side, action;

    std::getline(ss, str, ','); // Reads timestamp
    timestamp = std::stoull(str); // Converts timestamp to unsigned long long int
    std::getline(ss, side, ','); // Reads side
    std::getline(ss, action, ','); // Reads action
    std::getline(ss, str, ','); // Reads id
    id = std::stoi(str); // Converts id to int
    std::getline(ss, str, ','); // Reads price
    price = std::stoi(str); // Converts price to int
    std::getline(ss, str); // Reads quantity
    qty = std::stoi(str); // Converts quantity to int

    OrderUpdate update(timestamp, side[0], action[0], id, price, qty); // Creates OrderUpdate object

    return update;
}