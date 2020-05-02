#include <chrono>

#include "OrderBook.h"

int main() {

  // Create some order updates
  std::deque<OrderUpdate> updates;

  OrderUpdate update_1(1, 'b', 'a', 1, 100, 5);
  updates.push_back(update_1);
  OrderUpdate update_2(2, 'b', 'a', 2, 100, 10);
  updates.push_back(update_2);
  OrderUpdate update_3(3, 'a', 'a', 3, 105, 15);
  updates.push_back(update_3);
  OrderUpdate update_4(4, 'a', 'a', 4, 105, 10);
  updates.push_back(update_4);
  OrderUpdate update_5(5, 'b', 'a', 5, 95, 25);
  updates.push_back(update_5);
  OrderUpdate update_6(6, 'b', 'd', 1, 100, 5);
  updates.push_back(update_6);
  OrderUpdate update_7(7, 'a', 'm', 3, 105, 25);
  updates.push_back(update_7);
  OrderUpdate update_8(8, 'b', 'd', 2, 100, 10);
  updates.push_back(update_8);
  OrderUpdate update_9(9, 'a', 'a', 9, 100, 5);
  updates.push_back(update_9);
  OrderUpdate update_10(10, 'b', 'a', 10, 90, 20);
  updates.push_back(update_10);

  OrderBook book;

  std::ofstream file;
  file.open("demo.csv");

  auto start =
      std::chrono::steady_clock::now(); // Total time process read updates from memory, process book, and write to file

  int n_levels = 2; // Number of levels to be retrieved in snapshot and written to file

  OrderBook::FormatOutputFile(file, n_levels);

  for (const auto &update : updates) {
    book.UpdateBook(update); // Process the update
    OrderBook::Snapshot snapshot = book.GetSnapshot(n_levels); // Create snapshot of book
    OrderBook::WriteToFile(file, update, snapshot, n_levels); // Write snapshot to file
  }

  auto stop = std::chrono::steady_clock::now();
  double duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

  file.close();

  book.PrintBook();
  book.PrintReport("Demonstration", duration);

  return 0;
}