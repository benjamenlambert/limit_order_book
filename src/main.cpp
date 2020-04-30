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

      auto start =
          std::chrono::steady_clock::now(); // Total time process read updates from memory, process book, and write to file

      OrderBook book;

      std::ofstream file;
      std::string file_name = entry.path().string();
      file.open(utilities::FormatFileName(file_name));

      int n_levels =
          5; // Number of levels to be retrieved in snapshot and written to file
      OrderBook::FormatOutputFile(file, n_levels);

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

      file.close();

      auto stop = std::chrono::steady_clock::now();
      double duration = std::chrono::duration_cast<std::chrono::microseconds>(
          stop - start).count();

      book.PrintReport(file_name, duration); // Summary information
    }
  }
  /*
  std::vector<std::vector<std::string>>
      csv = utilities::ReadCSV("../data/res_20190610.csv", true);

  //auto start =
  //    std::chrono::steady_clock::now(); // Total time process read updates from memory, process book, and write to file

  //OrderBook book;

  //std::ofstream file;
  //std::string file_name = "../data/res_20190610.csv";
  //file.open(utilities::FormatFileName(file_name));

  //int n_levels =
  //    5; // Number of levels to be retrieved in snapshot and written to file
  //    OrderBook::FormatOutputFile(file, n_levels);

  std::unordered_map<int, Order> orders;

  int adds = 0;
  int removes = 0;
  int mods = 0;
  int price_changes = 0;

  for (const auto &row : csv) {
    OrderUpdate update(std::stoull(row[0]),
                       row[1][0],
                       row[2][0],
                       std::stoi(row[3]),
                       std::stoi(row[4]),
                       std::stoi(row[5]));

    Order order(update);

    if (update.action == 'a') {
      orders.insert(std::make_pair(update.id, order));
      adds++;
    }
    else if (update.action == 'd') {
      orders.erase(update.id);
      removes++;
    }
    else {
      mods++;
      int prev_price = orders.at(update.id).GetPrice();
      int price = update.price;
      int price_change = prev_price - price;
      if (price_change != 0) {
        std::cout << "Price Change!!!" << std::endl;
        price_changes++;
      }
    }


    //book.UpdateBook(update); // Process the update
    //OrderBook::Snapshot
    //    snapshot = book.GetSnapshot(n_levels); // Create snapshot of book
    //OrderBook::WriteToFile(file,
    //                 update,
    //                 snapshot,
    //                 n_levels); // Write snapshot to file
  }

  std::cout << adds << " add order messages." << std::endl;
  std::cout << removes << " remove order messages." << std::endl;
  std::cout << mods << " modify order messages." << std::endl;
  std::cout << price_changes << " price changes." << std::endl;
  std::cout << (adds + removes + mods) << " total messages." << std::endl;
  //file.close();

  //auto stop = std::chrono::steady_clock::now();
  //double duration = std::chrono::duration_cast<std::chrono::microseconds>(
  //    stop - start).count();

  //book.PrintReport(file_name, duration); // Summary information

  //book.PrintBook();
  */
  return 0;
}