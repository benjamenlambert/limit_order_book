//
// Created by Benjamen Lambert on 3/24/2020.
//

#ifndef LIMIT_ORDER_BOOK_SRC_PRICELEVEL_H_
#define LIMIT_ORDER_BOOK_SRC_PRICELEVEL_H_

#include <iostream>
#include <unordered_map>

#include "Order.h"

// A single price level within the book.
// Represented as a price and an hash table containing orders at that price.  Price levels are stored in an AVL tree
// containing all price levels on a given side (bid/ask).
class PriceLevel {
 public:
  explicit PriceLevel(int price) : size_(0), price_(price), height_(0), left_(nullptr), right_(nullptr) {
    orders_.max_load_factor(0.6); // Set max load factor
    orders_.reserve(50); // Reserve space for n orders in map before a rehash is required
  }

  //  Adds an Order to the hash table with order id as the key.
  void AddOrder(int order_id, const Order &order);
  void ModifyOrder(const OrderUpdate &update);
  void RemoveOrder(int order_id);

  const Order &GetOrder(int id);
  // Gets all orders at the PriceLevel
  const std::unordered_map<int, Order> &GetOrders();
  // Returns the total size (sum of the qty of all Orders) at the PriceLevel
  int GetSize();
  int GetPrice();
  // Returns the total number of orders at the PriceLevel
  int NumOrders();
  // Copies the price, size, and order hash table from one price level to the other while keeping pointers intact.
  // Used to swap contents of the price level to be removed with that of the IOP in the case of a two child remove
  void CopyIOP(PriceLevel *iop);

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
