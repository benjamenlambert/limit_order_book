//
// Created by Benjamen Lambert on 4/13/2020.
//

#include "catch.hpp"

#include "PriceLevel.h"

TEST_CASE ("Add order to price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order new_order(update);

  // Act
  level.AddOrder(update.id, new_order);

  // Assert
  std::unordered_map<int, Order> orders = level.GetOrders();

  // unordered_map::count(k) returns 1 if an element with a key equivalent to k is found, or zero otherwise
  CHECK(orders.count(update.id) == 1);
}

TEST_CASE ("Modify existing order within price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order new_order(update);
  level.AddOrder(update.id, new_order);
  OrderUpdate modify(2, 'b', 'm', 1, 1, 2);

  // Act
  level.ModifyOrder(modify);

  // Assert
  int order_qty = level.GetOrder(update.id).GetQty();

  CHECK(order_qty == 2);
}

TEST_CASE ("Remove order from price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order(update_1);
  level.AddOrder(update_1.id, new_order);

  OrderUpdate update_2(2, 'b', 'd', 1, 1, 1);

  // Act
  level.RemoveOrder(update_2.id);

  // Assert
  std::unordered_map<int, Order> orders = level.GetOrders();

  // unordered_map::count(k) returns 1 if an element with a key equivalent to k is found, or zero otherwise
  CHECK(orders.count(update_1.id) == 0);
}

TEST_CASE ("Confirm size after adding order to price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order new_order(update);

  // Act
  level.AddOrder(update.id, new_order);

  // Assert
  int level_size = level.GetSize();

  CHECK(level_size == 1);
}

TEST_CASE ("Confirm size after modifying order in price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order_1(update_1);
  level.AddOrder(update_1.id, new_order_1);

  OrderUpdate update_2(2, 'b', 'm', 1, 1, 2);

  // Act
  level.ModifyOrder(update_2);

  // Assert
  int level_size = level.GetSize();

  CHECK(level_size == 2);
}

TEST_CASE ("Confirm size after removing order from price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order_1(update_1);
  level.AddOrder(update_1.id, new_order_1);

  OrderUpdate update_2(2, 'b', 'a', 2, 1, 1);
  Order new_order_2(update_2);
  level.AddOrder(update_2.id, new_order_2);

  OrderUpdate update_3(3, 'b', 'd', 1, 1, 1);

  // Act
  level.RemoveOrder(update_3.id);

  // Assert
  int level_size = level.GetSize();

  CHECK(level_size == 1);
}

TEST_CASE ("Get existing order from price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order new_order(update);
  level.AddOrder(update.id, new_order);

  // Act //Assert
  CHECK_NOTHROW(level.GetOrder(update.id));
}

TEST_CASE ("Get all existing orders from price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order_1(update_1);
  level.AddOrder(update_1.id, new_order_1);

  OrderUpdate update_2(2, 'b', 'a', 2, 1, 1);
  Order new_order_2(update_2);
  level.AddOrder(update_2.id, new_order_2);

  // Act
  std::unordered_map<int, Order> orders = level.GetOrders();

  // Assert
  std::string level_orders;
  for (auto &iter: orders) {
    level_orders += std::to_string(iter.first) + ' ';
  }
  level_orders.pop_back(); // Remove trailing space

  CHECK((level_orders == "1 2"
      || level_orders == "2 1")); // Unordered map can be in any order, allow for all possibilities
}

TEST_CASE ("Get price of price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);

  // Act
  int level_price = level.GetPrice();

  // Assert
  CHECK(level_price == 1);
}

TEST_CASE ("Get total size of price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order_1(update_1);
  level.AddOrder(update_1.id, new_order_1);

  OrderUpdate update_2(2, 'b', 'a', 2, 1, 1);
  Order new_order_2(update_2);
  level.AddOrder(update_2.id, new_order_2);

  // Act
  int level_size = level.GetSize();

  // Assert
  CHECK(level_size == 2);
}

TEST_CASE ("Get number of orders at price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update_1(1, 'b', 'a', 1, 1, 1);
  Order new_order_1(update_1);
  level.AddOrder(update_1.id, new_order_1);

  OrderUpdate update_2(2, 'b', 'a', 2, 1, 1);
  Order new_order_2(update_2);
  level.AddOrder(update_2.id, new_order_2);

  // Act
  int num_orders = level.NumOrders();

  // Assert
  CHECK(num_orders == 2);
}
TEST_CASE ("Correctly copy IOP price", "[PriceLevelTests]") {
  // Arrange
  auto *root_level = new PriceLevel(2);
  OrderUpdate root_update(1, 'b', 'a', 1, 2, 1);
  Order root_order(root_update);
  root_level->AddOrder(root_update.id, root_order);

  auto *iop_level = new PriceLevel(1);
  OrderUpdate iop_update(2, 'b', 'a', 2, 1, 1);
  Order iop_order(iop_update);
  iop_level->AddOrder(iop_update.id, iop_order);

  // Act
  root_level->CopyIOP(iop_level);

  // Assert
  int price = root_level->GetPrice();

  CHECK(price == 1);
}

TEST_CASE ("Correctly copy IOP orders", "[PriceLevelTests]") {
  // Arrange
  auto *root_level = new PriceLevel(2);
  OrderUpdate root_update(1, 'b', 'a', 1, 2, 1);
  Order root_order(root_update);
  root_level->AddOrder(root_update.id, root_order);

  auto *iop_level = new PriceLevel(1);
  OrderUpdate iop_update(2, 'b', 'a', 2, 1, 1);
  Order iop_order(iop_update);
  iop_level->AddOrder(iop_update.id, iop_order);

  // Act
  root_level->CopyIOP(iop_level);

  // Assert
  std::unordered_map<int, Order> orders = root_level->GetOrders();
  std::string root_orders;
  for (auto &iter: orders) {
    root_orders += std::to_string(iter.first) + ' ';
  }
  root_orders.pop_back(); // Remove trailing space

  CHECK(root_orders == "2");
}

TEST_CASE ("Correctly copy IOP size", "[PriceLevelTests]") {
  // Arrange
  auto *root_level = new PriceLevel(2);
  OrderUpdate root_update(1, 'b', 'a', 1, 2, 1);
  Order root_order(root_update);
  root_level->AddOrder(root_update.id, root_order);

  auto *iop_level = new PriceLevel(1);
  OrderUpdate iop_update(2, 'b', 'a', 2, 1, 2);
  Order iop_order(iop_update);
  iop_level->AddOrder(iop_update.id, iop_order);

  // Act
  root_level->CopyIOP(iop_level);

  // Assert
  int size = root_level->GetSize();

  CHECK(size == 2);
}