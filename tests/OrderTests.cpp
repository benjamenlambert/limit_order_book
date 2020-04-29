//
// Created by Benjamen Lambert on 4/11/2020.
//


#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Order.h"

TEST_CASE ("Get price of order", "[OrderTests]") {
  // Arrange
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order order(update);

  // Act
  int price = order.GetPrice();

  // Assert
  CHECK(price == 1);
}

TEST_CASE ("Get quantity of order", "[OrderTests]") {
  // Arrange
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order order(update);

  // Act
  int qty = order.GetQty();

  // Assert
  CHECK(qty == 1);
}

TEST_CASE ("Get side of order", "[OrderTests]") {
  // Arrange
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order order(update);

  // Act
  char side = order.GetSide();

  // Assert
  CHECK(side == 'b');
}

TEST_CASE ("Update order quantity", "[OrderTests]") {
  // Arrange
  OrderUpdate update(1, 'b', 'a', 1, 1, 1);
  Order order(update);

  // Act
  order.UpdateQty(2);
  int qty = order.GetQty();

  // Assert
  CHECK(qty == 2);
}
