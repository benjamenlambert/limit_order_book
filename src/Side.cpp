//
// Created by Benjamen Lambert on 3/31/2020.
//

#include "Side.h"

Side::Side() {
  root_ = nullptr;
}

Side::~Side() {
  root_ = DestroySide(root_);
}

PriceLevel *Side::InsertLevel(PriceLevel &level) {
  int price = level.GetPrice();

  PriceLevel *&new_node = Find(price, root_);
  new_node = &level;
  return new_node;
}

PriceLevel *Side::FindLevel(int price) {
  return Find(price, root_);
}

PriceLevel *Side::FindMin() {
  return Min(root_);
}

PriceLevel *Side::FindMax() {
  return Max(root_);
}

int Side::RemoveLevel(int key) {
  PriceLevel *&node = Find(key, root_);
  if (node != nullptr) {
    Remove(node);
    return 1;
  } else {
    return 0;
  }

}

void Side::PrintSide() {
  Print(root_);
}

//Private

PriceLevel *&Side::Find(int price, PriceLevel *&current_level) {
  if (current_level == nullptr) {
    return current_level;
  } else {
    int current_level_price = current_level->GetPrice();

    if (price == current_level_price) {
      return current_level;
    } else if (price < current_level_price) {
      return Find(price, current_level->left_);
    } else {
      return Find(price, current_level->right_);
    }
  }
}

PriceLevel *Side::Min(PriceLevel *current_level) {
  if (current_level == nullptr)
    return nullptr; // How do I want to handle this case?
    //throw std::runtime_error("Error: Node not found");
  else if (current_level->left_ == nullptr)
    return current_level;
  else
    return Min(current_level->left_);
}

PriceLevel *Side::Max(PriceLevel *current_level) {
  if (current_level == nullptr)
    return nullptr; // How do I want to handle this case?
    //throw std::runtime_error("Error: Node not found");
  else if (current_level->right_ == nullptr)
    return current_level;
  else
    return Max(current_level->right_);
}

PriceLevel *&Side::Remove(PriceLevel *&level) {
  if (level->left_ == nullptr) {// One child right and zero child remove
    level = level->right_;
  } else if (level->right_ == nullptr) {// One child left remove
    level = level->left_;
  } else { // Two child remove
    PriceLevel *iop = Max(level->left_); // Get in-order predecessor
    level = iop;
    level->left_ = Remove(level->left_);
  }
  return level;
}

PriceLevel *Side::DestroySide(PriceLevel *current_level) {
  if (current_level == nullptr) {
    return nullptr;
    //throw std::runtime_error("Side empty");
  } else {
    DestroySide(current_level->left_);
    DestroySide(current_level->right_);
    delete current_level;
    current_level = nullptr;
  }
  return nullptr;
}

void Side::Print(PriceLevel *level) {
  if (level != nullptr) {
    Print(level->left_);
    std::cout << "Price Level : " << level->GetPrice() << std::endl;
    std::cout << "\tSize : " << level->GetSize() << " Num orders : " << level->NumOrders() << std::endl;
    for (auto &iter: level->GetOrders()) {
      std::cout << "\t\tid: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    }
    Print(level->right_);
  }
}