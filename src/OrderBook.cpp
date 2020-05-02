//
// Created by Benjamen Lambert on 4/2/2020.
//

#include <iomanip>
#include <iostream>

#include "OrderBook.h"

void OrderBook::UpdateBook(const OrderUpdate &update) {
  if (update.action == 'a') { // If the update is an add
    AddOrder(update); // Add the order
  } else if (update.action == 'd') { // If the update is a delete
    RemoveOrder(update); // Remove the order
  } else {
    ModifyOrder(update); // Modify the order
  }
}

OrderBook::Snapshot OrderBook::GetSnapshot(const int &n_levels) const {

  OrderBook::Snapshot snapshot; // Create an empty snapshot

  bid_.GetSnapshot('b', n_levels, snapshot.first); // Add n_levels to the bid side
  ask_.GetSnapshot('a', n_levels, snapshot.second); // Add n_levels to the ask side

  return snapshot;
}

void OrderBook::FormatOutputFile(std::ofstream &file, const int &n_levels) {
  file << "timestamp,side,action,id,price,quantity,"; // Write column labels for the update to the file

  for (int n = 0; n < n_levels; ++n) { // Write column labels for n_levels of the bid snapshot to the file
    file << ("bp" + std::to_string(n)) << "," << ("bq" + std::to_string(n)) << ",";
  }

  for (int n = 0; n < (n_levels - 1); ++n) { // Write column labels for n_levels-1 of the ask snapshot to the file
    file << ("ap" + std::to_string(n)) << "," << ("aq" + std::to_string(n)) << ",";
  }

  file << ("ap" + std::to_string(n_levels - 1)) << "," << ("aq" + std::to_string(n_levels - 1))
       << "\n"; // Write column labels
  // for the last level of the ask snapshot to the file
}

void OrderBook::WriteToFile(std::ofstream &file,
                            const OrderUpdate &update,
                            OrderBook::Snapshot &snapshot,
                            const int &n_levels) {

  file << update.timestamp << ',' << update.side << ',' << update.action << ',' << update.id << ',' << update.price
       << ','
       << update.qty << ','; // Write the update to the file

  for (int i = 0; i < n_levels; ++i) { // Write n_levels of the bid snapshot to the file
    if (!snapshot.first.empty()) { // If the level is not empty
      file << snapshot.first.front()->GetPrice() << ',' << snapshot.first.front()->GetSize()
           << ','; // Write it to the file
      snapshot.first.pop_front(); // Remove the level from the snapshot
    } else {
      file << ",0,"; // Write a blank price with size of 0
    }
  }
  for (int i = 0; i < (n_levels - 1); ++i) { // Write n_levels-1 of the ask snapshot to the file
    if (!snapshot.second.empty()) {  // If the level is not empty
      file << snapshot.second.front()->GetPrice() << ',' << snapshot.second.front()->GetSize()
           << ','; // Write it to the file
      snapshot.second.pop_front(); // Remove the level from the snapshot
    } else {
      file << ",0,"; // Write a blank price with size of 0
    }
  }
  if (!snapshot.second.empty()) { // If the last level of the ask snapshot is not empty
    file << snapshot.second.front()->GetPrice() << ','
         << snapshot.second.front()->GetSize(); // Write it to the file without a trailing comma
  } else {
    file << ",0"; // Write a blank price with size of 0 without a trailing zero
  }
  file << '\n';
}

void OrderBook::PrintBook() const {
  Print();
}

void OrderBook::PrintReport(const std::string &title, const double &duration) const {
  std::cout << "\n**************** REPORT ****************\n" << std::endl;
  std::cout << " " << title << std::endl;
  std::cout << " " << adds_ << " add order messages." << std::endl;
  std::cout << " " << tob_adds_ << " top of book add order messages." << std::endl;
  std::cout << " " << removes_ << " remove order messages." << std::endl;
  std::cout << " " << tob_removes_ << " top of book remove order messages." << std::endl;
  std::cout << " " << mods_ << " modify order messages." << std::endl;
  std::cout << " " << tob_mods_ << " top of book modify order messages." << std::endl;
  std::cout << " " << (adds_ + removes_ + mods_) << " total messages." << std::endl;
  std::cout << " " << (tob_adds_ + tob_removes_ + tob_mods_) << " total top of book messages." << std::endl;
  std::cout << " " << (duration / 1000000) << " seconds." << std::endl;
  std::cout << " " << std::setprecision(2) << duration / (adds_ + removes_ + mods_) << " microseconds per message.\n"
            << std::endl;
  std::cout << "****************************************\n";
}

// Private methods

Side *OrderBook::GetSide(const char &side) {
  if (side == 'b') {
    return &bid_;
  } else {
    return &ask_;
  }
}

void OrderBook::AddOrder(const OrderUpdate &update) {
  Order order(update);
  Side *side = GetSide(update.side);

  if (side->top_of_book_ != nullptr) { // If top_of_book_ is not nullptr
    int order_price = order.GetPrice();
    int top_of_book_price = side->top_of_book_->GetPrice();

    if (order_price
        == top_of_book_price) { // If the order price is equal to the top of the book, go straight there
      side->top_of_book_->AddOrder(update.id, order); // Insert the order
      tob_adds_++; // Update top of book adds count
    } else { // The order is not equal to the top of the book
      PriceLevel *level = side->FindLevel(order_price);  // Find the price level

      if (level != nullptr) { // If it exists
        level->AddOrder(update.id, order); // Add the order
      } else { // The price level does not exist
        auto *new_level = new PriceLevel(order_price); // Create the price level
        new_level->AddOrder(update.id, order); // Add the order to the price level
        side->AddLevel(new_level); // Add the price level to the book recursively to ensure tree balance

        // Check to see if the new level is a new top of book
        if (order.GetSide() == 'b') { // If the order is a bid
          if (order_price > top_of_book_price) { // And its price is greater than the current top of book price
            side->top_of_book_ = new_level; // Update top_of_book_ on the bid side
          }
        } else if (order_price
            < top_of_book_price) { // The order is an ask.  If its price is less than the current top of the book
          side->top_of_book_ = new_level; // Update top_of_book_ on the ask side
        }
      }
    }
  } else { // top_of_book is nullptr. This is the first order being added to this side of the book
    auto *new_level = new PriceLevel(order.GetPrice()); // Create the price level
    new_level->AddOrder(update.id, order); // Add the order to the price level
    side->AddLevel(new_level); // Add the price level to the book
    side->top_of_book_ = new_level; // Update the top_of_book_
  }
  adds_++;
}

void OrderBook::RemoveOrder(const OrderUpdate &update) {
  Side *side = GetSide(update.side);
  int top_of_book_price = side->top_of_book_->GetPrice();

  if (update.price
      == top_of_book_price) { // If the order price is equal to the top of the book, go straight there
    side->top_of_book_->RemoveOrder(update.id); // Remove the order
    if (side->top_of_book_->GetSize() == 0) { // If the size of the top_of_book_ is now 0
      side->RemoveLevel(top_of_book_price); // Remove the level recursively to ensure tree balance
      if (update.side == 'b') {
        side->top_of_book_ = side->FindMax(); // And update top_of_book_ on the bid side to the new highest bid
      } else {
        side->top_of_book_ = side->FindMin(); // Or update top_of_book_ on the ask side to the new lowest ask
      }
    }
    tob_removes_++;
  } else { // The order is not at the top of the book
    PriceLevel *level = side->FindLevel(update.price); // Find the price level

    level->RemoveOrder(update.id); // Delete the order

    if (level->GetSize() == 0) { // If the size is now 0
      side->RemoveLevel(update.price); // Remove the level
    }
  }
  removes_++;
}

void OrderBook::ModifyOrder(const OrderUpdate &update) {
  Side *side = GetSide(update.side);

  if (update.price
      == side->top_of_book_->GetPrice()) { // If the order price is equal to the top of the book, go straight there
    side->top_of_book_->ModifyOrder(update); // Update the order
    tob_mods_++;
  } else { // The order is not at the top of the book
    PriceLevel *level = side->FindLevel(update.price); // Find the price level

    level->ModifyOrder(update); // Modify the order
  }
  mods_++;
}

void OrderBook::Print() const {

  ask_.PrintSide();

  std::cout << "\n       ********Asks********       \n";
  std::cout << "**********************************\n";
  std::cout << "       ********Bids********       \n" << std::endl;

  bid_.PrintSide();
}


