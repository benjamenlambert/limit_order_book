//
// Created by Benjamen Lambert on 4/28/2020.
//

#include <experimental/filesystem>
#include <fstream>
#include <sstream>

#include "Utilities.h"

std::vector<std::vector<std::string>> utilities::ReadCSV(const std::string &file_name, bool has_column_labels) {
  std::ifstream file;
  file.open(file_name);

  std::vector<std::vector<std::string>> csv;

  if (file.is_open()) {
    std::string line;

    if (has_column_labels) { // Discards the first line if the .csv file contains headers/column names
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
  } else {
    std::cout << "File not open!!!" << std::endl;
  }

  file.close();

  return csv; // Return csv
}

std::string utilities::FormatFileName(const std::string &file_name) {

  if (!std::experimental::filesystem::exists("../output/")) { // Create directory
    std::experimental::filesystem::create_directory("../output/");
  }

  std::string f_name = file_name;
  f_name.erase(f_name.end() - 4, f_name.end());
  f_name.append("_output.csv");
  f_name.replace(f_name.begin(), f_name.begin() + 8, "../output/");

  return f_name;
}
