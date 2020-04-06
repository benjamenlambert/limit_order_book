//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_PRICELEVEL_H_
#define LIMIT_ORDER_BOOK_SRC_PRICELEVEL_H_

#include <unordered_map>

#include "Order.h"

// A single price level within the book.
// Represented as a price and an hash table containing orders at that price.  Price levels are stored in an AVL tree
// containing all price levels on a given side (bid/ask).
class PriceLevel {
 public:
  // Creates a new PriceLevel and adds an Order to the hash table with order id as the key.
  // TODO Should I separate the constructor from AddLevel in it?
  PriceLevel(int order_id, const Order &order);

  //  Adds an Order to an existing PriceLevel
  const Order &AddOrder(int order_id, const Order &order); // TODO Do these need to return the order?
  const Order &ModifyOrder(const OrderUpdate &update); // TODO Or should they just be void?
  int RemoveOrder(int order_id); // TODO Should this just be void?

  const Order &GetOrder(int id);
  // Gets all orders at the PriceLevel
  const std::unordered_map<int, Order> &GetOrders();
  // Returns the total size (sum of the qty of all Orders) at the PriceLevel
  int GetSize();
  int GetPrice();
  // Returns the total number of orders at the PriceLevel
  int NumOrders();

  // Pointers to the PriceLevel's left and right children in the AVL tree
  PriceLevel *left_;
  PriceLevel *right_;
  // Height of the PriceLevel in the AVL tree
  int height_;

 private:
  // The price of the PriceLevel
  int price_;
  // The total size at the PriceLevel
  int size_;
  // Hash table containing the orders using the order is as the key
  std::unordered_map<int, Order> orders_;
};

#endif //LIMIT_ORDER_BOOK_SRC_PRICELEVEL_H_
