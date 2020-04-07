//
// Created by Benjamen Lambert on 4/7/2020.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/OrderUpdate.h"

OrderUpdate update(0, 'a', 'a', 1, 9999, 1);

TEST_CASE ("OrderUpdate timestamp initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.timestamp == 0);
}

TEST_CASE ("OrderUpdate side initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.side == 'a');
}

TEST_CASE ("OrderUpdate action initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.action == 'a');
}

TEST_CASE ("OrderUpdate id initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.id == 1);
}

TEST_CASE ("OrderUpdate price initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.price == 9999);
}

TEST_CASE ("OrderUpdate qty initialized to correct value", "[OrderUpdateTests]") {

  CHECK(update.qty == 1);
}