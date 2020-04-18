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
  std::unordered_map<int, Order> orders = level.GetOrders();

  // Assert
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
  int order_qty = level.GetOrder(update.id).GetQty();

  // Assert
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
  std::unordered_map<int, Order> orders = level.GetOrders();

  // Assert
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
  int level_size = level.GetSize();

  // Assert
  CHECK(level_size == 1);
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
  int level_size = level.GetSize();

  // Assert
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
  int level_size = level.GetSize();

  // Assert
  CHECK(level_size == 2);
}

TEST_CASE ("Get existing order from price level", "[PriceLevelTests]") {
  // Arrange
  PriceLevel level(1);
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order new_order(update);
  level.AddOrder(update.id, new_order);

  // Act/Assert
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
TEST_CASE ("Correctly copied IOP price", "[PriceLevelTests]") {
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
  int price = root_level->GetPrice();

  // Assert
  CHECK(price == 1);
}

TEST_CASE ("Correctly copied IOP orders", "[PriceLevelTests]") {
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
  std::unordered_map<int, Order> orders = root_level->GetOrders();

  // Assert
  std::string root_orders;
  for (auto &iter: orders) {
    root_orders += std::to_string(iter.first) + ' ';
  }
  root_orders.pop_back(); // Remove trailing space

  CHECK(root_orders == "2");
}

TEST_CASE ("Correctly copied IOP size", "[PriceLevelTests]") {
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
  int size = root_level->GetSize();

  // Assert
  CHECK(size == 2);
}