//
// Created by Benjamen Lambert on 4/30/2020.
//

#include <sstream>

#include "catch.hpp"

#include "OrderBook.h"

TEST_CASE ("Add order to book", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);

  // Act
  book.UpdateBook(update);

  std::string snapshot_string;
  OrderBook::Snapshot
      snapshot = book.GetSnapshot(1);

  for (int n = 0; n < 1; ++n) {
    if (!snapshot.first.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }

    snapshot_string.append("|");

    if (!snapshot.second.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }
  }

  //Assert
  CHECK(snapshot_string == "1-1|0-0");
}

TEST_CASE ("Remove order from book", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  OrderUpdate update_2(2, 'b', 'a', 2, 1, 1);
  OrderUpdate update_3(3, 'b', 'd', 1, 1, 1);

  // Act
  book.UpdateBook(update_1);
  book.UpdateBook(update_2);
  book.UpdateBook(update_3);

  std::string snapshot_string;
  OrderBook::Snapshot
      snapshot = book.GetSnapshot(1);

  for (int n = 0; n < 1; ++n) {
    if (!snapshot.first.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }

    snapshot_string.append("|");

    if (!snapshot.second.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }
  }

  //Assert
  CHECK(snapshot_string == "1-1|0-0");
}

TEST_CASE ("Modify order in book", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  OrderUpdate update_2(2, 'b', 'm', 1, 1, 2);

  // Act
  book.UpdateBook(update_1);
  book.UpdateBook(update_2);

  std::string snapshot_string;
  OrderBook::Snapshot
      snapshot = book.GetSnapshot(1);

  for (int n = 0; n < 1; ++n) {
    if (!snapshot.first.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }

    snapshot_string.append("|");

    if (!snapshot.second.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }
  }

  //Assert
  CHECK(snapshot_string == "1-2|0-0");
}

TEST_CASE ("Get snapshot of book", "[OrderBookTests]") {
  // Arrange
  OrderBook book;

  // Act
  OrderBook::Snapshot
      snapshot = book.GetSnapshot(1);

  std::string snapshot_string;

  for (int n = 0; n < 1; ++n) {
    if (!snapshot.first.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }

    snapshot_string.append("|");

    if (!snapshot.second.empty()) {
      snapshot_string.append(
          std::to_string(snapshot.first.front()->GetPrice()) + "-" + std::to_string(snapshot.first.front()->GetSize()));
    } else {
      snapshot_string.append("0-0");
    }
  }

  //Assert
  CHECK(snapshot_string == "0-0|0-0");
}

TEST_CASE ("Format output file", "[OrderBookTests]") {
  // Arrange
  std::ofstream output_file;
  output_file.open("format_test.txt");

  // Act
  OrderBook::FormatOutputFile(output_file, 1);
  output_file.close();

  std::ifstream input_file;
  input_file.open("format_test.txt");

  std::string column_lables;
  std::string line;

  while (std::getline(input_file, line)) {
    column_lables.append(line);
  }

  //Assert
  CHECK(column_lables == "timestamp,side,action,id,price,quantity,bp0,bq0,ap0,aq0");
}

TEST_CASE ("Write to file", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  book.UpdateBook(update);
  OrderBook::Snapshot
      snapshot = book.GetSnapshot(1);
  std::ofstream output_file;
  output_file.open("write_snapshot_test.txt");

  // Act
  OrderBook::WriteToFile(output_file, update, snapshot, 1);
  output_file.close();

  std::ifstream input_file;
  input_file.open("write_snapshot_test.txt");

  std::string write;
  std::string line;

  while (std::getline(input_file, line)) {
    write.append(line);
  }

  //Assert
  CHECK(write == "1,b,a,1,1,1,1,1,,0");
}

////********************************************************************************////
//// GetSide must be changed to a public method in order to run the following tests ////
////********************************************************************************////

TEST_CASE ("Get side of book", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  book.UpdateBook(update);

  // Act
  std::string in_order;
  book.GetSide('b')->InOrderString(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space

  // Assert
  CHECK(in_order == "1");
}

TEST_CASE ("Update top of book after initial add", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);

  // Act
  book.UpdateBook(update);

  int tob_price = book.GetSide('b')->top_of_book_->GetPrice();

  // Assert
  CHECK(tob_price == 1);
}

TEST_CASE ("Update top of book after add", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  book.UpdateBook(update_1);
  OrderUpdate update_2(2, 'b', 'a', 2, 2, 1);

  // Act
  book.UpdateBook(update_2);

  int tob_price = book.GetSide('b')->top_of_book_->GetPrice();

  // Assert
  CHECK(tob_price == 2);
}

TEST_CASE ("Update top of book after remove", "[OrderBookTests]") {
  // Arrange
  OrderBook book;
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  book.UpdateBook(update_1);
  OrderUpdate update_2(2, 'b', 'a', 2, 2, 1);
  book.UpdateBook(update_2);
  OrderUpdate update_3(3, 'b', 'd', 2, 2, 1);

  // Act
  book.UpdateBook(update_3);

  int tob_price = book.GetSide('b')->top_of_book_->GetPrice();

  // Assert
  CHECK(tob_price == 1);
}