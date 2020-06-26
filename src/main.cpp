#include <chrono>
#include <filesystem>

#include "Utilities.h"
#include "OrderBook.h"

int main() {

  for (const auto
        &
        entry : std::filesystem::directory_iterator("../data/")) { // Process all data files in ../data/
    if (entry.path().extension() == ".csv") { // Only process .csv files
      std::vector<std::vector<std::string>>
          csv = utilities::ReadCSV(entry.path().string(), true);

      std::ofstream file;
      std::string file_name = entry.path().string();
      file.open(utilities::FormatFileName(file_name));

      int n_levels =
          5; // Number of levels to be retrieved in snapshot and written to file
      OrderBook::FormatOutputFile(file, n_levels);

      OrderBook book;

      auto start =
          std::chrono::steady_clock::now(); // Total time to read updates, process book, and write to file

      for (const auto &row : csv) {
        OrderUpdate update(std::stoull(row[0]),
                           row[1][0],
                           row[2][0],
                           std::stoi(row[3]),
                           std::stoi(row[4]),
                           std::stoi(row[5]));

        book.UpdateBook(update); // Process the update
        OrderBook::Snapshot
            snapshot = book.GetSnapshot(n_levels); // Create snapshot of book
        OrderBook::WriteToFile(file,
                               update,
                               snapshot,
                               n_levels); // Write snapshot to file
      }

      auto stop = std::chrono::steady_clock::now();
      double duration = std::chrono::duration_cast<std::chrono::microseconds>(
          stop - start).count();

      file.close();

      book.PrintReport(file_name, duration); // Summary information
    }
  }

/*
  Side bid;
  auto level_1 = new PriceLevel(1);
  auto level_2 = new PriceLevel(2);
  auto level_3 = new PriceLevel(3);
  auto level_4 = new PriceLevel(4);
  auto level_5 = new PriceLevel(5);
  auto level_6 = new PriceLevel(6);
  auto level_7 = new PriceLevel(7);

  bid.AddLevel(level_3);
  bid.AddLevel(level_2);
  bid.AddLevel(level_5);
  bid.AddLevel(level_1);
  bid.AddLevel(level_4);
  bid.AddLevel(level_6);
  bid.AddLevel(level_7);

  bid.PrintParent();

  std::string pre_order;
  bid.PreOrderString(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  std::cout << pre_order << std::endl;

  std::cout << "----------------------------" << std::endl;
  bid.RemoveLevel(1);

  bid.PrintParent();

  pre_order.clear();
  bid.PreOrderString(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  std::cout << pre_order << std::endl;
  */

  return 0;
}