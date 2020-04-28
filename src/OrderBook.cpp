//
// Created by Benjamen Lambert on 4/2/2020.
//

#include <fstream>
#include <iomanip>

#include "OrderBook.h"

void OrderBook::FormatOutputFile(std::ofstream &file, int n_levels) {
  std::string col_headers = "timestamp,side,action,id,price,quantity,";

  for (int n = 0; n < n_levels; n++) {
    col_headers.append("bp" + std::to_string(n) + ",");
    col_headers.append("bq" + std::to_string(n) + ",");
  }

  for (int n = 0; n < n_levels; n++) {
    col_headers.append("ap" + std::to_string(n) + ",");
    col_headers.append("aq" + std::to_string(n) + ",");
  }

  col_headers.pop_back();
  col_headers.append("\n");

  file << col_headers;
}

void OrderBook::UpdateBook(const OrderUpdate &update) {
  if (update.action == 'a') {
    AddOrder(update);
  } else if (update.action == 'd') {
    RemoveOrder(update);
  } else { // Modify
    ModifyOrder(update);
  }
}

void OrderBook::PrintReport(std::string file_name, double duration) {
  std::cout << "************ REPORT ************\n" << std::endl;
  std::cout << " " << file_name << std::endl;
  std::cout << " " << adds_ << " add order messages." << std::endl;
  std::cout << " " << removes_ << " remove order messages." << std::endl;
  std::cout << " " << mods_ << " modify order messages." << std::endl;
  std::cout << " " << tob_updates_ << " top of book updates." << std::endl;
  std::cout << " " << (adds_ + removes_ + mods_) << " total messages." << std::endl;
  std::cout << " " << (duration / 1000000) << " seconds." << std::endl;
  std::cout << " " << std::setprecision(2) << duration / (adds_ + removes_ + mods_) << " microseconds per message.\n"
            << std::endl;
  std::cout << "********************************\n" << std::endl;
}

void OrderBook::WriteToFile(std::ofstream &file,
                            const OrderUpdate &update,
                            OrderBook::Snapshot &snapshot,
                            int n_levels) {

  file << update.timestamp << ',' << update.side << ',' << update.action << ',' << update.id << ',' << update.price
       << ','
       << update.qty << ',';

  for (int i = 0; i < n_levels; i++) {
    if (!snapshot.first.empty()) {
      file << snapshot.first.front()->GetPrice() << ',' << snapshot.first.front()->GetSize() << ',';
      snapshot.first.pop_front();
    } else {
      file << ",0,";
    }
  }
  for (int i = 0; i < (n_levels - 1); i++) {
    if (!snapshot.second.empty()) {
      file << snapshot.second.front()->GetPrice() << ',' << snapshot.second.front()->GetSize() << ',';
      snapshot.second.pop_front();
    } else {
      file << ",0,";
    }
  }
  if (!snapshot.second.empty()) {
    file << snapshot.second.front()->GetPrice() << ',' << snapshot.second.front()->GetSize();
    snapshot.second.pop_front();
  } else {
    file << ",0";
  }
  file << '\n';
}

std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> OrderBook::GetSnapshot(int n_levels) {

  OrderBook::Snapshot snapshot;

  bid_.ToDequeInOrder('b', n_levels, snapshot.first);
  ask_.ToDequeInOrder('a', n_levels, snapshot.second);

  return snapshot;
}

Side *OrderBook::GetSide(char side) {
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
      //std::cout << "Adding order " << update.id << " to top of book on the " << (update.side == 'b' ? "bid" : "ask")
      //          << " side-> (" << top_of_book_price << ")" << std::endl;
      tob_updates_++;
    } else { // The order is not at the top of the book, so have to find its level
      PriceLevel *level = side->FindLevel(order_price);  // Find the price level

      if (level != nullptr) { // If it exists, add the order
        level->AddOrder(update.id, order);
      } else {
        auto *new_level = new PriceLevel(order_price); // Create the price level
        new_level->AddOrder(update.id, order); // Add the order to the price level
        side->AddLevel(new_level); // Add the price level to the book

        // Check to see if the level is a new top of book
        if (order.GetSide() == 'b') {
          if (order_price > top_of_book_price) {
            side->top_of_book_ = new_level; // Update top_of_book_ on the bid side
            //std::cout << "New top of book on the bid side after adding order " << update.id << ".  ("
            //          << top_of_book_price << ")" << std::endl;
          }
        } else if (order_price < top_of_book_price) {
          side->top_of_book_ = new_level; // Update top_of_book_ on the ask side
          //std::cout << "New top of book on the ask side after adding order " << update.id << ".  ("
          //          << top_of_book_price << ")" << std::endl;
        }
      }
    }
  } else { // top_of_book is nullptr, this is the first order being added to the book, so I know it must be a new level
    auto *new_level = new PriceLevel(order.GetPrice()); // Create the price level
    new_level->AddOrder(update.id, order); // Add the order to the price level
    side->AddLevel(new_level); // Add the price level to the book
    side->top_of_book_ = new_level; // Update the top_of_book_

    //std::cout << "Creating top of book on " << (update.side == 'b' ? "bid" : "ask") << " side with order "
    //          << update.id << std::endl;
  }
  adds_++;
}

void OrderBook::RemoveOrder(const OrderUpdate &update) {
  Side *side = GetSide(update.side);
  int top_of_book_price = side->top_of_book_->GetPrice();

  if (update.price
      == top_of_book_price) { // If the order price is equal to the top of the book, go straight there
    side->top_of_book_->RemoveOrder(update.id); // Remove the order
    //std::cout << "Removing order " << update.id << " from top of book on the " << (update.side == 'b' ? "bid" : "ask") << " side->" << std::endl;
    if (side->top_of_book_->GetSize() == 0) { // If the size of the top_of_book_ is now 0
      side->RemoveLevel(top_of_book_price); // Remove the level (Even though we know where the level is, we have to remove recursively to ensure tree balance)
      if (update.side == 'b') {
        side->top_of_book_ = side->FindMax(); // Update top_of_book_ on the bid side
        //std::cout << "New top of book on the bid side after deleting order " << update.id << ". ("
        //          << top_of_book_price << ")" << std::endl;
      } else {
        side->top_of_book_ = side->FindMin(); // Update top_of_book_ on the ask side
        //std::cout << "New top of book on the ask side after deleting order " << update.id << ". ("
        //          << top_of_book_price << ")" << std::endl;
      }
    }
    tob_updates_++;
  } else { // The order is not at the top of the book, so have to find its level
    PriceLevel *level = side->FindLevel(update.price);

    level->RemoveOrder(update.id); // Delete the order

    if (level->GetSize() == 0) { // If the size == 0
      side->RemoveLevel(update.price); // Delete the level
    }
  }
  removes_++;
}

void OrderBook::ModifyOrder(const OrderUpdate &update) {
  Side *side = GetSide(update.side);

  if (update.price
      == side->top_of_book_->GetPrice()) { // If the order price is equal to the top of the book, go straight there
    side->top_of_book_->ModifyOrder(update); // Update the order
    tob_updates_++;
  } else {
    PriceLevel *level = side->FindLevel(update.price);

    level->ModifyOrder(update); // Modify the order

  }
  mods_++;
}



