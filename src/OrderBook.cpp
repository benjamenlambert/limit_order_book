//
// Created by Benjamen Lambert on 4/2/2020.
//

#include "OrderBook.h"

Side *OrderBook::GetSide(char side) {
  if (side == 'b') {
    return &bid_;
  } else {
    return &ask_;
  }
}