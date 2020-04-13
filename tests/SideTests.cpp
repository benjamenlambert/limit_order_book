//
// Created by Benjamen Lambert on 4/13/2020.
//

#include "catch.hpp"

#include "Side.h"

TEST_CASE ("Add price level to side", "[SideTests]") {
  // Arrange
  Side bid;
  auto level_1 = new PriceLevel(1);

  // Act
  bid.AddLevel(level_1);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1");
}

TEST_CASE ("Find price level on side", "[SideTests]") {
  //Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);

  // Act
  int price = bid.FindLevel(1)->GetPrice();

  //Assert
  CHECK(price == 1);
}

TEST_CASE ("Find maximum price on side", "[SideTests]") {
  //Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);

  // Act
  int max = bid.FindMax()->GetPrice();

  //Assert
  CHECK(max == 2);
}

TEST_CASE ("Find minimum price on side", "[SideTests]") {
  //Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);

  // Act
  int min = bid.FindMin()->GetPrice();

  //Assert
  CHECK(min == 1);
}