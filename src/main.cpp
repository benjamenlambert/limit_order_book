#include "HistoricalData.h"
#include "Order.h"
#include "PriceLevel.h"
#include "Side.h"
#include "OrderBook.h"

int main() {

  HistoricalData data;

  //data.ReadCSV("../data/hash_data.csv"); // Partial file
  //std::vector<std::vector<std::string>>
  //    csv = data.ReadCSV("../data/data_9990.csv", true); // Partial file with headers
  //std::vector<std::vector<std::string>>
  //    csv = data.ReadCSV("../data/res_20190612_bids.csv", true); // Partial file with headers
  std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/res_20190614.csv", true); // Full file

  int num_rows = csv.size();

  std::cout << "CSV contains " << num_rows << " rows.\n\n" << std::endl;

  OrderBook book;

  int adds = 0;
  int removes = 0;
  int mods = 0;

  for (int i = 0; i < num_rows; i++) {
    OrderUpdate update(std::stoull(csv[i][0]),
                       csv[i][1][0],
                       csv[i][2][0],
                       std::stoi(csv[i][3]),
                       std::stoi(csv[i][4]),
                       std::stoi(csv[i][5]));

    Side *side = book.GetSide(update.side);

    if (update.action == 'a') {
      Order order(update);
      PriceLevel *level = side->FindLevel(order.GetPrice());  // Find the price level

      if (level != nullptr) { // If it exists, add the order
        level->AddOrder(update.id, order);
      } else { // Create the level and add it to the side
        auto *new_level = new PriceLevel(update.id, order);

        side->InsertLevel(*new_level);
      }
      adds++;
    } else if (update.action == 'd') {
      PriceLevel *level = side->FindLevel(update.price);

      level->RemoveOrder(update.id); // Delete the order

      if (level->GetSize() == 0) { // If the size == 0, delete the level
        side->RemoveLevel(update.price);
      }
      removes++;
    } else {
      side->FindLevel(update.price)->ModifyOrder(update);

      mods++;
    }
  }

  std::cout << "************ REPORT ************\n" << std::endl;
  std::cout << " " << adds << " add order messages." << std::endl;
  std::cout << " " << removes << " remove order messages." << std::endl;
  std::cout << " " << mods << " modify order messages." << std::endl;
  std::cout << " " << (adds + removes + mods) << " total messages.\n"
            << std::endl;
  std::cout << "********************************" << std::endl;

  book.GetSide('b')->PrintSide();

  std::cout << "\n****************************************************************\n" << std::endl;

  book.GetSide('a')->PrintSide();

  return 0;
}
