#include <chrono>

#include "Event.h"
#include "HistoricalData.h"
#include "Order.h"
#include "OrderBook.h"

int main() {
  std::vector<std::vector<std::string>> csv = HistoricalData::ReadCSV("../data/res_20190614.csv", true);

  int num_rows = csv.size();

  std::cout << "CSV contains " << num_rows << " rows.\n\n" << std::endl;

  auto start = std::chrono::steady_clock::now();

  OrderBook book;

  for (int i = 0; i < num_rows; i++) {
    OrderUpdate update(std::stoull(csv[i][0]),
                       csv[i][1][0],
                       csv[i][2][0],
                       std::stoi(csv[i][3]),
                       std::stoi(csv[i][4]),
                       std::stoi(csv[i][5]));

    book.UpdateBook(update);
  }

  auto stop = std::chrono::steady_clock::now();

  double duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

  book.PrintReport(duration);

  //book.GetSide('a')->PrintSide();

  //std::cout << "\n****************************************************************\n" << std::endl;

  //book.GetSide('b')->PrintSide();

  return 0;
}
