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
  return 0;
}