//
// Created by Benjamen Lambert on 4/2/2020.
//

#include <iomanip>

#include "OrderBook.h"

void OrderBook::UpdateBook(const OrderUpdate &update) {
  if (update.action == 'a') {
    AddOrder(update);
  } else if (update.action == 'd') {
    RemoveOrder(update);
  } else { // Modify
    ModifyOrder(update);
  }
}

void OrderBook::PrintReport(double duration) {
  std::cout << "************ REPORT ************\n" << std::endl;
  std::cout << " " << adds_ << " add order messages." << std::endl;
  std::cout << " " << removes_ << " remove order messages." << std::endl;
  std::cout << " " << mods_ << " modify order messages." << std::endl;
  std::cout << " " << tob_updates_ << " top of book updates." << std::endl;
  std::cout << " " << (adds_ + removes_ + mods_) << " total messages." << std::endl;
  std::cout << " " << duration << " microseconds." << std::endl;
  std::cout << " " << std::setprecision(2) << duration / (adds_ + removes_ + mods_) << " microseconds per message.\n"
            << std::endl;
  std::cout << "********************************" << std::endl;
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

void OrderBook::PrintBook() {
  Print();
}

void OrderBook::Print() {

  ask_.PrintSide();

  std::cout << "\n****************************************************************\n" << std::endl;

  bid_.PrintSide();

}
std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> OrderBook::GetMarketDepth(int n_levels) {

  std::deque<PriceLevel *> bids, asks;
  bid_.ToDequeInOrder(bids);
  ask_.ToDequeInOrder(asks);

  std::pair<std::deque<PriceLevel *>, std::deque<PriceLevel *>> book;

  for (int n = 0; n < n_levels; n++) {
    if (!bids.empty()) {
      book.first.push_back(bids.back());
      bids.pop_back();
    }
  }

  for (int n = 0; n < n_levels; n++) {
    if (!asks.empty()) {
      book.second.push_back(asks.front());
      asks.pop_front();
    }
  }
  return book;
}
