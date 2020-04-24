#include <chrono>
#include <fstream>

#include "HistoricalData.h"
#include "OrderBook.h"

int main() {
  std::vector<std::vector<std::string>> csv = HistoricalData::ReadCSV("../data/res_20190612.csv", true);
  int num_rows = csv.size();
  std::cout << "CSV contains " << num_rows << " rows.\n" << std::endl;

  std::ofstream file;
  file.open("../output/test_write.csv");

  auto start = std::chrono::steady_clock::now();

  file
      << "timestamp,side,action,id,price,quantity,bp0,bq0,bp1,bq1,bp2,bq2,bp3,bq3,bp4,bq4,ap0,aq0,ap1,aq1,ap2,aq2,ap3,aq3,ap4,aq4\n";

  OrderBook book;

  for (int i = 0; i < num_rows; i++) {
    OrderUpdate update(std::stoull(csv[i][0]),
                       csv[i][1][0],
                       csv[i][2][0],
                       std::stoi(csv[i][3]),
                       std::stoi(csv[i][4]),
                       std::stoi(csv[i][5]));

    book.UpdateBook(update);

    file << csv[i][0] << ',' << csv[i][1] << ',' << csv[i][2] << ',' << csv[i][3] << ',' << csv[i][4] << ','
         << csv[i][5] << ',';

    std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> depth = book.GetMarketDepth(5);

    for (int i = 0; i < 5; i++) {
      if (!depth.first.empty()) {
        file << depth.first.front()->GetPrice() << ',' << depth.first.front()->GetSize() << ',';
        depth.first.pop_front();
      } else {
        file << ",0,";
      }
    }
    for (int i = 0; i < 4; i++) {
      if (!depth.second.empty()) {
        file << depth.second.front()->GetPrice() << ',' << depth.second.front()->GetSize() << ',';
        depth.second.pop_front();
      } else {
        file << ",0,";
      }
    }
    if (!depth.second.empty()) {
      file << depth.second.front()->GetPrice() << ',' << depth.second.front()->GetSize();
      depth.second.pop_front();
    } else {
      file << ",0";
    }
    file << '\n';
  }

  auto stop = std::chrono::steady_clock::now();
  double duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

  book.PrintReport(duration);

  file.close();

  return 0;
}
