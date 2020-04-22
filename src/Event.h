//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_EVENT_H_
#define LIMIT_ORDER_BOOK_SRC_EVENT_H_

#include "OrderUpdate.h"

// Structure for messages.
// For future implementation.
struct Event {
 public:
  static void Update(const OrderUpdate &update);
};

#endif //LIMIT_ORDER_BOOK_SRC_EVENT_H_
