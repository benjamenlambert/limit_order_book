#include <chrono>
#include <iomanip>

#include "HistoricalData.h"
#include "Order.h"
#include "OrderBook.h"

int main() {
  std::vector<std::vector<std::string>> csv = HistoricalData::ReadCSV("../data/res_20190614.csv", true);

  int num_rows = csv.size();

  std::cout << "CSV contains " << num_rows << " rows.\n\n" << std::endl;

  auto start = std::chrono::steady_clock::now();

  OrderBook book;

  int adds = 0;
  int removes = 0;
  int mods = 0;
  int tob_updates = 0;

  for (int i = 0; i < num_rows; i++) {
    OrderUpdate update(std::stoull(csv[i][0]),
                       csv[i][1][0],
                       csv[i][2][0],
                       std::stoi(csv[i][3]),
                       std::stoi(csv[i][4]),
                       std::stoi(csv[i][5]));

    Side *side = book.GetSide(update.side);

    /*
    if (update.action == 'a') {
      Order order(update);
      PriceLevel *level = side->FindLevel(order.GetPrice());  // Find the price level

      if (level != nullptr) { // If it exists, add the order
        level->AddOrder(update.id, order);
      } else { // Create the level, add the order, and add it to the side
        auto *new_level = new PriceLevel(order.GetPrice());
        new_level->AddOrder(update.id, order);

        side->AddLevel(new_level);
      }
      adds++;
    } else if (update.action == 'd') {
      PriceLevel *level = side->FindLevel(update.price);

      level->RemoveOrder(update.id); // Delete the order

      if (level->GetSize() == 0) { // If the size == 0, delete the level
        //std::cout << "Price level " << level->GetPrice() << " removed." << std::endl;
        side->RemoveLevel(update.price);
      }
      removes++;
    } else {
      side->FindLevel(update.price)->ModifyOrder(update);

      mods++;
    }
  }
  */


    if (update.action == 'a') {
      Order order(update);

      if (side->top_of_book_ != nullptr) { // If top_of_book_ is not nullptr
        if (order.GetPrice()
            == side->top_of_book_->GetPrice()) { // If the order price is equal to the top of the book, go straight there
          side->top_of_book_->AddOrder(update.id, order); // Insert the order
          std::cout << "Adding order " << update.id << " to top of book on the " << (update.side == 'b' ? "bid" : "ask")
                    << " side. (" << side->top_of_book_->GetPrice() << ")" << std::endl;
          tob_updates++;
        } else { // The order is not at the top of the book, so have to find its level
          PriceLevel *level = side->FindLevel(order.GetPrice());  // Find the price level

          if (level != nullptr) { // If it exists, add the order
            level->AddOrder(update.id, order);
          } else {
            auto *new_level = new PriceLevel(order.GetPrice()); // Create the price level
            new_level->AddOrder(update.id, order); // Add the order to the price level
            side->AddLevel(new_level); // Add the price level to the book

            // Check to see if the level is a new top of book
            if (order.GetSide() == 'b') {
              if (order.GetPrice() > side->top_of_book_->GetPrice()) {
                side->top_of_book_ = new_level; // Update top_of_book_ on the bid side
                std::cout << "New top of book on the bid side after adding order " << update.id << ".  ("
                          << side->top_of_book_->GetPrice() << ")" << std::endl;
              }
            } else if (order.GetPrice() < side->top_of_book_->GetPrice()) {
              side->top_of_book_ = new_level; // Update top_of_book_ on the ask side
              std::cout << "New top of book on the ask side after adding order " << update.id << ".  ("
                        << side->top_of_book_->GetPrice() << ")" << std::endl;
            }
          }
        }
      } else { // top_of_book is nullptr, this is the first order being added to the book, so I know it must be a new level
        auto *new_level = new PriceLevel(order.GetPrice()); // Create the price level
        new_level->AddOrder(update.id, order); // Add the order to the price level
        side->AddLevel(new_level); // Add the price level to the book
        side->top_of_book_ = new_level; // Update the top_of_book_

        std::cout << "Creating top of book on " << (update.side == 'b' ? "bid" : "ask") << " side with order "
                  << update.id << std::endl;
        //side->top_of_book_ = new_level;
        //std::cout << "Top of book on " << (update.side == 'b' ? " bid" : "ask") << " side : " << side->top_of_book_->GetPrice() << std::endl;
      }

      adds++;
    } else if (update.action == 'd') {
      if (update.price
          == side->top_of_book_->GetPrice()) { // If the order price is equal to the top of the book, go straight there
        side->top_of_book_->RemoveOrder(update.id); // Remove the order
        //std::cout << "Removing order " << update.id << " from top of book on the " << (update.side == 'b' ? "bid" : "ask") << " side." << std::endl;
        if (side->top_of_book_->GetSize() == 0) { // If the size of the top_of_book_ is now 0
          side->RemoveLevel(side->top_of_book_->GetPrice()); // Remove the level (Even though we know where the level is, we have to remove recursively to ensure tree balance)
          if (update.side == 'b') {
            side->top_of_book_ = side->FindMax(); // Update top_of_book_ on the bid side
            std::cout << "New top of book on the bid side after deleting order " << update.id << ". ("
                      << side->top_of_book_->GetPrice() << ")" << std::endl;
          } else {
            side->top_of_book_ = side->FindMin(); // Update top_of_book_ on the ask side
            std::cout << "New top of book on the ask side after deleting order " << update.id << ". ("
                      << side->top_of_book_->GetPrice() << ")" << std::endl;
          }
        }
        tob_updates++;
      } else { // The order is not at the top of the book, so have to find its level
        PriceLevel *level = side->FindLevel(update.price);

        level->RemoveOrder(update.id); // Delete the order

        if (level->GetSize() == 0) { // If the size == 0
          side->RemoveLevel(update.price); // Delete the level
        }
      }

      removes++;
    } else { // Modify
      if (update.price
          == side->top_of_book_->GetPrice()) { // If the order price is equal to the top of the book, go straight there
        side->top_of_book_->ModifyOrder(update); // Update the order
        tob_updates++;
      } else {
        PriceLevel *level = side->FindLevel(update.price);

        level->ModifyOrder(update); // Modify the order

      }
      mods++;
    }
  }

  auto stop = std::chrono::steady_clock::now();

  double duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();

  std::cout << "************ REPORT ************\n" << std::endl;
  std::cout << " " << adds << " add order messages." << std::endl;
  std::cout << " " << removes << " remove order messages." << std::endl;
  std::cout << " " << mods << " modify order messages." << std::endl;
  std::cout << " " << tob_updates << " top of book updates." << std::endl;
  std::cout << " " << (adds + removes + mods) << " total messages." << std::endl;
  std::cout << " " << duration << " microseconds." << std::endl;
  std::cout << " " << std::setprecision(2) << duration / (adds + removes + mods) << " microseconds per message.\n"
            << std::endl;
  std::cout << "********************************" << std::endl;

  //book.GetSide('a')->PrintSide();

  //std::cout << "\n****************************************************************\n" << std::endl;

  //book.GetSide('b')->PrintSide();

  return 0;
}
