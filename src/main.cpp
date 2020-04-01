#include "HistoricalData.h"
#include "Order.h"
#include "PriceLevel.h"
#include "Side.h"

int main() {

  HistoricalData data;

  //data.ReadCSV("../data/hash_data.csv"); // Partial file
  std::vector<std::vector<std::string>>
      csv = data.ReadCSV("../data/res_20190612_bids.csv", true); // Partial file with headers
  //std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/res_20190612.csv", true); // Full file

  int num_rows = csv.size();

  std::cout << "CSV contains " << num_rows << " rows.\n\n" << std::endl;

  // Output csv contents
  /*
  int num_cols = csv[0].size();

  for (int i = 0; i < num_rows; i++) {
      for (int j = 0; j < num_cols; j++)
          std::cout << csv[i][j] << " ";
      std::cout << std::endl;
  }
   */

  Side bid;
  //PriceLevel level;

  int adds = 0;
  int removes = 0;
  int mods = 0;
  int price_changes = 0;

  for (int i = 0; i < num_rows; i++) {
    OrderUpdate update(std::stoull(csv[i][0]),
                       csv[i][1][0],
                       csv[i][2][0],
                       std::stoi(csv[i][3]),
                       std::stoi(csv[i][4]),
                       std::stoi(csv[i][5]));

    if (update.action == 'a') {
      Order order(update);

      PriceLevel *level = bid.FindLevel(order.GetPrice());  // Find the price level

      if (level != nullptr) { // If it exists, add the order
        level->AddOrder(update.id, order);
        //std::cout << "Adding order " << update.id << " with price " << update.price << " to level : "
        //          << level->GetPrice() << std::endl;
      } else { // Create the level and add it to the side
        auto *new_level = new PriceLevel(update.id, order);
        bid.InsertLevel(*new_level);
        //std::cout << "Price not found. Adding price level " << new_level->GetPrice() << std::endl;
        //std::cout << "Now adding order " << update.id << " with price " << update.price << " to level : "
        //          << bid.FindLevel(order.GetPrice())->GetPrice() << std::endl;
      }
      adds++;
    } else if (update.action == 'd') {

      //std::cout << "Removing order " << update.id << " with price " << update.price << " from level "
      //          << bid.FindLevel(update.price)->GetPrice() << std::endl;
      bid.FindLevel(update.price)->RemoveOrder(update.id);

      removes++;
    } else {

      int prev_price = bid.FindLevel(update.price)->GetOrder(update.id).GetPrice();

      //std::cout << "Modifying order " << update.id << " with price " << update.price << " from level "
      //          << bid.FindLevel(update.price)->GetPrice() << std::endl;

      //std::cout << "Previous qty = " << bid.FindLevel(update.price)->GetOrder(update.id).GetQty()
      //          << " Previous price = " << bid.FindLevel(update.price)->GetOrder(update.id).GetPrice() << std::endl;

      bid.FindLevel(update.price)->ModifyOrder(update);

      int new_price = bid.FindLevel(update.price)->GetOrder(update.id).GetPrice();

      //std::cout << "New qty = " << bid.FindLevel(update.price)->GetOrder(update.id).GetQty() << " New price = "
      //          << bid.FindLevel(update.price)->GetOrder(update.id).GetPrice() << std::endl;

      if (new_price != prev_price) {
        std::cout << "***** PRICE CHANGE ***** PRICE CHANGE ***** PRICE CHANGE *****" << std::endl;
        price_changes++;
      }
      mods++;
    }
  }

  std::cout << "************ REPORT ************\n" << std::endl;
  std::cout << " " << adds << " add order messages." << std::endl;
  std::cout << " " << removes << " remove order messages." << std::endl;
  std::cout << " " << mods << " modify qty messages." << std::endl;
  std::cout << " " << price_changes << " modify price messages." << std::endl;
  std::cout << " " << (adds + removes + mods) << " total messages.\n"
            << std::endl;
  std::cout << "********************************" << std::endl;

  //std::cout << "Price level contains the following " << level.NumOrders() << " orders:" << std::endl;

  //for (auto &iter: level.GetOrders()) {
  //    std::cout << "id: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
  //}

  bid.PrintSide();

  return 0;
}
