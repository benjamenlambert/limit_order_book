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
  auto level = bid.FindLevel(1);

  //Assert
  CHECK(level != nullptr);
}
/*
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
 */
/*
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
*/
TEST_CASE ("Print side in order", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);

  // Act
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space

  // Assert
  CHECK(in_order == "1 2 3");
}

TEST_CASE ("Print side pre order", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);

  // Act
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space

  // Assert
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("Remove price level with zero children from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);

  // Act
  bid.RemoveLevel(2);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1");
}

TEST_CASE ("Remove price level with one child from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);

  // Act
  bid.RemoveLevel(3);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1 2 4");
}

TEST_CASE ("Remove price level with two children from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_5 = new PriceLevel(5);
  bid.AddLevel(level_5);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);
  auto *level_6 = new PriceLevel(6);
  bid.AddLevel(level_6);


  // Act
  bid.RemoveLevel(5);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1 2 3 4 6");
}

TEST_CASE ("Remove root price level w/ IOP from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);

  // Act
  bid.RemoveLevel(2);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1 3");
}

TEST_CASE ("Remove root price level w/o IOP from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);

  // Act
  bid.RemoveLevel(1);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "2");
}