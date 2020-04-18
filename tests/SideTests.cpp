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

TEST_CASE ("Remove price level with one right child from side", "[SideTests]") {
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

TEST_CASE ("Remove price level with one left child from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);


  // Act
  bid.RemoveLevel(4);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1 2 3");
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

TEST_CASE ("Remove root price level w/ IOP (two children) from side", "[SideTests]") {
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

TEST_CASE ("Remove root price level w/ IOP (one child) from side", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);

  // Act
  bid.RemoveLevel(2);

  // Assert
  std::string in_order;
  bid.ToStringInOrder(in_order); // Save node key values to in_order
  in_order.pop_back(); // Remove trailing space
  CHECK(in_order == "1");
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

TEST_CASE ("Confirm price level has correct orders after CopyIOP", "[SideTests]") {
  // Arrange
  Side bid;

  OrderUpdate update_2(1, 'b', 'a', 1, 2, 1);
  Order order_2(update_2);
  auto *level_2 = new PriceLevel(2);
  level_2->AddOrder(update_2.id, order_2);
  bid.AddLevel(level_2);

  OrderUpdate update_1(2, 'b', 'a', 2, 1, 1);
  Order order_1(update_1);
  auto *level_1 = new PriceLevel(1);
  level_1->AddOrder(update_1.id, order_1);
  bid.AddLevel(level_1);

  OrderUpdate update_3(3, 'b', 'a', 3, 3, 1);
  Order order_3(update_3);
  auto *level_3 = new PriceLevel(3);
  level_3->AddOrder(update_3.id, order_3);
  bid.AddLevel(level_3);

  // Act
  bid.RemoveLevel(2);
  std::unordered_map<int, Order> orders = bid.FindLevel(1)->GetOrders(); // IOP

  // Assert
  std::string order_ids;
  for (auto &iter: orders) {
    order_ids += std::to_string(iter.first);
  }

  CHECK(order_ids == "2");
}

TEST_CASE ("Confirm price level has correct size after CopyIOP", "[SideTests]") {
  // Arrange
  Side bid;

  OrderUpdate update_2(1, 'b', 'a', 1, 2, 1);
  Order order_2(update_2);
  auto *level_2 = new PriceLevel(2);
  level_2->AddOrder(update_2.id, order_2);
  bid.AddLevel(level_2);

  OrderUpdate update_1(2, 'b', 'a', 2, 1, 1);
  Order order_1(update_1);
  OrderUpdate update_1_2(3, 'b', 'a', 3, 1, 1);
  Order order_1_2(update_1_2);
  auto *level_1 = new PriceLevel(1);
  level_1->AddOrder(update_1.id, order_1);
  level_1->AddOrder(update_1_2.id, order_1_2);
  bid.AddLevel(level_1);

  OrderUpdate update_3(4, 'b', 'a', 4, 3, 1);
  Order order_3(update_3);
  auto *level_3 = new PriceLevel(3);
  level_3->AddOrder(update_3.id, order_3);
  bid.AddLevel(level_3);

  // Act
  bid.RemoveLevel(2);
  int level_size = bid.FindLevel(1)->GetSize();

  // Assert
  CHECK(level_size == 2);
}

TEST_CASE ("Left rotation after insert", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_3 = new PriceLevel(3);

  // Act
  bid.AddLevel(level_3);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("Left rotation after remove", "[SideTests]") {
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
  bid.RemoveLevel(1);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "3 2 4");
}

TEST_CASE ("Right rotation after insert", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);

  // Act
  bid.AddLevel(level_1);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("Right rotation after remove", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);

  // Act
  bid.RemoveLevel(4);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("LeftRight rotation after insert", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);

  // Act
  bid.AddLevel(level_2);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("LeftRight rotation after remove", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);


  // Act
  bid.RemoveLevel(4);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("RightLeft rotation after insert", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);
  auto *level_2 = new PriceLevel(2);

  // Act
  bid.AddLevel(level_2);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "2 1 3");
}

TEST_CASE ("RightLeft rotation after remove", "[SideTests]") {
  // Arrange
  Side bid;
  auto *level_2 = new PriceLevel(2);
  bid.AddLevel(level_2);
  auto *level_1 = new PriceLevel(1);
  bid.AddLevel(level_1);
  auto *level_4 = new PriceLevel(4);
  bid.AddLevel(level_4);
  auto *level_3 = new PriceLevel(3);
  bid.AddLevel(level_3);

  // Act
  bid.RemoveLevel(1);

  // Assert
  std::string pre_order;
  bid.ToStringPreOrder(pre_order); // Save node key values to in_order
  pre_order.pop_back(); // Remove trailing space
  CHECK(pre_order == "3 2 4");
}