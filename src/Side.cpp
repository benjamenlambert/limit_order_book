//
// Created by Benjamen Lambert on 3/31/2020.
//

#include <iostream>

#include "Side.h"

Side::~Side() {
  root_ = DestroySide(root_);
}

void Side::AddLevel(PriceLevel *level) {
  root_ = Add(level, root_);
}

PriceLevel *Side::FindLevel(const int &price) const {
  return Find(price, root_);
}

void Side::RemoveLevel(const int &price) {
  root_ = Remove(price, root_);
}

PriceLevel *Side::FindMin() const {
  return Min(root_);
}

PriceLevel *Side::FindMax() const {
  return Max(root_);
}

void Side::GetSnapshot(const char &side, int n_levels, std::deque<PriceLevel *> &deq) const {
  GetSnapshot(root_, side, n_levels, deq);
}

void Side::InOrderString(std::string &str) const {
  InOrderString(root_, str);
}

void Side::PreOrderString(std::string &str) const {
  PreOrderString(root_, str);
}

void Side::PrintSide() const {
  Print(root_);
}

// Private methods

PriceLevel *Side::Add(PriceLevel *level,
                      PriceLevel *current_level) { // Recursive add.  Required to ensure balance of the tree
  if (current_level == nullptr) { // PriceLevel not found
    current_level = level;
  }
  int level_price = level->GetPrice();
  int current_level_price = current_level->GetPrice();

  if (level_price < current_level_price) { // Search for PriceLevel
    current_level->left_ = Add(level, current_level->left_);
  } else if (level_price > current_level_price) {
    current_level->right_ = Add(level, current_level->right_);
  } else { // PriceLevel found.  Should not happen as no duplicates should exist
    return current_level;
  }

  BalanceTree(current_level); // Ensure AVL tree balance after insertion

  return current_level;
}

PriceLevel *Side::Find(int price, PriceLevel *current_level) const { // Recursive find
  if (current_level == nullptr) { // PriceLevel not found
    return current_level;
  } else {
    int current_level_price = current_level->GetPrice();

    if (price == current_level_price) { // PriceLevel found.
      return current_level;
    } else if (price < current_level_price) { // Search for PriceLevel
      return Find(price, current_level->left_);
    } else {
      return Find(price, current_level->right_);
    }
  }
}

PriceLevel *Side::Remove(int price,
                         PriceLevel *current_level) { // Recursive remove.  Required to ensure balance of the tree
  if (current_level == nullptr) { // PriceLevel not found
    return current_level;
  }
  int current_level_price = current_level->GetPrice();

  if (price == current_level_price) { // Found PriceLevel to remove
    if (current_level->left_ == nullptr) {// One child right and zero child remove
      PriceLevel *level = current_level->right_;
      delete current_level;
      current_level = nullptr;
      return level;
    } else if (current_level->right_ == nullptr) {// One child left remove
      PriceLevel *level = current_level->left_;
      delete current_level;
      current_level = nullptr;
      return level;
    } else { // Two child remove
      PriceLevel *iop = Max(current_level->left_); // Get in-order predecessor
      current_level->CopyIOP(iop); // Copy iop price_, size_, and orders_ to current_level
      if (iop == top_of_book_) { // If iop is top_of_book_
        top_of_book_ = current_level; // Update top_of_book_ to point to current_level
      }
      current_level->left_ = Remove(iop->GetPrice(), current_level->left_); // Delete iop
    }
  } else if (price < current_level_price) { // Search for PriceLevel
    current_level->left_ = Remove(price, current_level->left_);
  } else {
    current_level->right_ = Remove(price, current_level->right_);
  }

  BalanceTree(current_level); // Ensure AVL tree balance after removal

  return current_level;
}

PriceLevel *Side::Min(PriceLevel *current_level) const {
  if (current_level == nullptr) { // Empty book
    return nullptr;
  } else if (current_level->left_ == nullptr) { // Min found
    return current_level;
  } else { // Search left
    return Min(current_level->left_);
  }
}

PriceLevel *Side::Max(PriceLevel *current_level) const {
  if (current_level == nullptr) {// Empty book
    return nullptr;
  } else if (current_level->right_ == nullptr) { // Max found
    return current_level;
  } else { // Search right
    return Max(current_level->right_);
  }
}

void Side::BalanceTree(PriceLevel *&current_level) {
  if (current_level == nullptr) {
    return;
  }

  int balance_factor = GetBalanceFactor(current_level);

  // Error checking
  if (balance_factor < -2 || balance_factor > 2) {
    std::string msg("ERROR: Detected invalid initial balance factor: ");
    msg += std::to_string(balance_factor);
    std::cerr << "price: " << current_level->GetPrice() << std::endl;
    std::cerr << "current_node left price: " << current_level->left_->GetPrice() << " current_node right price: "
              << current_level->right_->GetPrice() << std::endl;
    std::cerr << "current_node left height: " << GetHeight(current_level->left_) << " current_node right height: "
              << GetHeight(current_level->right_) << std::endl;
    throw std::runtime_error(msg);
  }

  if (balance_factor == 2) { // Rebalance required
    int right_balance_factor = GetBalanceFactor(current_level->right_);

    if (right_balance_factor == -1) { // RightLeft rotation
      RotateRightLeft(current_level);
    } else if (right_balance_factor == 1
        || right_balance_factor
            == 0) // Left rotation // Can change to else once satisfied and after removing error checking below
    {
      RotateLeft(current_level);
    } else {
      // Error checking
      std::string msg("ERROR: right_balance_factor has unexpected value: ");
      msg += std::to_string(right_balance_factor);
      throw std::runtime_error(msg);
    }
  } else if (balance_factor == -2) { // Rebalance required
    int left_balance_factor = GetBalanceFactor(current_level->left_);

    if (left_balance_factor == 1) { // LeftRight rotation
      RotateLeftRight(current_level);
    } else if (left_balance_factor == -1
        || left_balance_factor
            == 0) // Right rotation // Can change to else once satisfied and after removing error checking below
    {
      RotateRight(current_level);
    } else {
      // Error checking
      std::string msg("ERROR: left_balance_factor has unexpected value: ");
      msg += std::to_string(left_balance_factor);
      throw std::runtime_error(msg);
    }
  }

  UpdateHeight(current_level);

  // Final error check
  balance_factor = GetBalanceFactor(current_level);
  if (balance_factor < -1 || balance_factor > 1) {
    std::string msg("ERROR: Invalid balance factor after BalanceTree: ");
    msg += std::to_string(balance_factor);
    throw std::runtime_error(msg);
  }
}

void Side::RotateLeft(PriceLevel *&current_level) {
  if (current_level == nullptr) {
    throw std::runtime_error("ERROR: RotateLeft called on nullptr");
  }
  if (current_level->right_ == nullptr) {
    throw std::runtime_error("ERROR: RotateLeft: right child is nullptr");
  }

  PriceLevel *subtree_root = current_level;
  PriceLevel *subtree_root_right = current_level->right_;
  PriceLevel *subtree_root_right_left = current_level->right_->left_;

  subtree_root->right_ = subtree_root_right_left;
  subtree_root_right->left_ = subtree_root;
  current_level = subtree_root_right;

  UpdateHeight(subtree_root);
  UpdateHeight(subtree_root_right);
}

void Side::RotateRight(PriceLevel *&current_level) {
  if (current_level == nullptr) {
    throw std::runtime_error("ERROR: RotateRight called on nullptr");
  }
  if (current_level->left_ == nullptr) {
    throw std::runtime_error("ERROR: RotateRight: left child is nullptr");
  }

  PriceLevel *subtree_root = current_level;
  PriceLevel *subtree_root_left = current_level->left_;
  PriceLevel *subtree_root_left_right = current_level->left_->right_;

  subtree_root->left_ = subtree_root_left_right;
  subtree_root_left->right_ = subtree_root;
  current_level = subtree_root_left;

  UpdateHeight(subtree_root);
  UpdateHeight(subtree_root_left);
}

void Side::RotateRightLeft(PriceLevel *&current_level) {
  if (current_level == nullptr) {
    throw std::runtime_error("ERROR: RotateRightLeft called on nullptr");
  }

  RotateRight(current_level->right_);
  RotateLeft(current_level);
}

void Side::RotateLeftRight(PriceLevel *&current_level) {
  if (current_level == nullptr) {
    throw std::runtime_error("ERROR: RotateLeftRight called on nullptr");
  }

  RotateLeft(current_level->left_);
  RotateRight(current_level);
}

int Side::GetHeight(const PriceLevel *level) {
  if (level == nullptr) {
    return -1;
  } else {
    return level->height_;
  }
}

int Side::GetBalanceFactor(const PriceLevel *level) {
  if (level == nullptr) {
    return 0;
  } else {
    return GetHeight(level->right_) - GetHeight(level->left_);
  }
}

void Side::UpdateHeight(PriceLevel *current_level) {
  if (current_level == nullptr) {
    return;
  } else {
    current_level->height_ = 1 + std::max(GetHeight(current_level->left_), GetHeight(current_level->right_));
  }
}

PriceLevel *Side::DestroySide(PriceLevel *current_level) {
  if (current_level == nullptr) {
    return nullptr;
  } else {
    DestroySide(current_level->left_);
    DestroySide(current_level->right_);
    delete current_level;
    current_level = nullptr;
  }
  return nullptr;
}

void Side::Print(const PriceLevel *level) const {
  if (level != nullptr) {
    Print(level->right_);
    std::cout << "Price Level : " << level->GetPrice() << std::endl;
    std::cout << "\tSize : " << level->GetSize() << " Num orders : " << level->NumOrders() << std::endl;
    for (const auto &iter : level->GetOrders()) {
      std::cout << "\t\tid: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    }
    Print(level->left_);
  }
}

void Side::InOrderString(const PriceLevel *level, std::string &str) const {
  if (level == nullptr) {
    return;
  }

  InOrderString(level->left_, str);
  str += (std::to_string(level->GetPrice()) + ' ');

  if (level->left_ == nullptr && level->right_ == nullptr) {
    return;
  }

  InOrderString(level->right_, str);

}

void Side::PreOrderString(const PriceLevel *level, std::string &str) const {
  if (level == nullptr) {
    return;
  }

  str += (std::to_string(level->GetPrice()) + ' ');

  if (level->left_ == nullptr && level->right_ == nullptr) {
    return;
  }

  PreOrderString(level->left_, str);
  PreOrderString(level->right_, str);
}

void Side::GetSnapshot(PriceLevel *level, char side, int &n_levels, std::deque<PriceLevel *> &deq) const {
  if (level == nullptr) { // If the PriceLevel is null
    return; // Stop recursion
  }

  if (side == 'b') { // If getting the bid side
    GetSnapshot(level->right_, side, n_levels, deq); // Get the highest PriceLevel (rightmost node)
  } else { // Get the lowest PriceLevel (leftmost node)
    GetSnapshot(level->left_, side, n_levels, deq);
  }

  if (n_levels > 0) { // If n_levels haven't already been added to the deque
    deq.push_back(level); // Add the level
    n_levels--; // Decrement n_levels
  }

  if ((level->left_ == nullptr && level->right_ == nullptr) || n_levels == 0) { // If the PriceLevel if a leaf node
    // or if n_levels is 0 (we have added as many levels to the deque as needed), stop recursion
    return;
  }

  if (side == 'b') { // If getting the bid side
    GetSnapshot(level->left_, side, n_levels, deq); // Get the next highest PriceLevel
  } else { // Get the next lowest PriceLevel
    GetSnapshot(level->right_, side, n_levels, deq);
  }
}