//
// Created by Benjamen Lambert on 3/31/2020.
//

#include "Side.h"

Side::~Side() {
  root_ = DestroySide(root_);
}

void Side::AddLevel(PriceLevel *level) {
  root_ = Add(level, root_);
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

void Side::RemoveLevel(int price) {
  root_ = Remove(price, root_);
}

void Side::PrintSide() {
  ReverseOrder(root_);
}

void Side::ToStringInOrder(std::string &str) {
  ToStringInOrder(root_, str);
}

void Side::ToStringPreOrder(std::string &str) {
  ToStringPreOrder(root_, str);
}

void Side::ToDequeInOrder(std::deque<PriceLevel *> &deq) {
  ToDequeInOrder(root_, deq);
}

//Private

PriceLevel *Side::Add(PriceLevel *level, PriceLevel *current_level) {
  if (current_level == nullptr) {
    current_level = level;
  }

  if (level->GetPrice() < current_level->GetPrice()) {
    current_level->left_ = Add(level, current_level->left_);
  } else if (level->GetPrice() > current_level->GetPrice()) {
    current_level->right_ = Add(level, current_level->right_);
  } else {
    return current_level;
  }

  BalanceTree(current_level); // Ensure AVL tree balance after insertion

  return current_level;
}

PriceLevel *Side::Find(int price, PriceLevel *current_level) {
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

PriceLevel *Side::Remove(int price, PriceLevel *current_level) {
  if (current_level == nullptr) {
    return current_level;
  }
  if (price < current_level->GetPrice()) {
    current_level->left_ = Remove(price, current_level->left_);
  } else if (price > current_level->GetPrice()) {
    current_level->right_ = Remove(price, current_level->right_);
  } else { // Found PriceLevel to remove
    if (current_level->left_ == nullptr) {// One child right and zero child remove
      //current_level = current_level->right_;
      PriceLevel *level = current_level->right_;
      delete current_level;
      current_level = nullptr;
      return level;
      //std::cout << "One child right or zero child remove" << std::endl;
    } else if (current_level->right_ == nullptr) {// One child left remove
      //current_level = current_level->left_;
      PriceLevel *level = current_level->left_;
      delete current_level;
      current_level = nullptr;
      return level;
      //std::cout << "One child left remove" << std::endl;
    } else { // Two child remove
      PriceLevel *iop = Max(current_level->left_); // Get in-order predecessor
      current_level->CopyIOP(iop);
      current_level->left_ = Remove(iop->GetPrice(), current_level->left_);
    }
  }

  BalanceTree(current_level); // Ensure AVL tree balance after removal

  return current_level;
}

int Side::GetHeight(PriceLevel *level) {
  if (level == nullptr) {
    return -1;
  } else {
    return level->height_;
  }
}

void Side::UpdateHeight(PriceLevel *current_level) {
  if (current_level == nullptr) {
    return;
  } else {
    current_level->height_ = 1 + std::max(GetHeight(current_level->left_), GetHeight(current_level->right_));
  }
}

int Side::GetBalanceFactor(PriceLevel *level) {
  if (level == nullptr) {
    return 0;
  } else {
    return GetHeight(level->right_) - GetHeight(level->left_);
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

  if (balance_factor == 2) {
    int right_balance_factor = GetBalanceFactor(current_level->right_);

    if (right_balance_factor == -1) {
      //std::cout << "Right left rotation" << std::endl;
      RotateRightLeft(current_level);
    } else if (right_balance_factor == 1
        || right_balance_factor == 0) // Can change to else once satisfied and after removing error checking below
    {
      //std::cout << "Left rotation" << std::endl;
      RotateLeft(current_level);
    } else {
      // Error checking
      std::string msg("ERROR: right_balance_factor has unexpected value: ");
      msg += std::to_string(right_balance_factor);
      throw std::runtime_error(msg);
    }
  } else if (balance_factor == -2) {
    int left_balance_factor = GetBalanceFactor(current_level->left_);

    if (left_balance_factor == 1) {
      //std::cout << "Left right rotation" << std::endl;
      RotateLeftRight(current_level);
    } else if (left_balance_factor == -1
        || left_balance_factor == 0) // Can change to else once satisfied and after removing error checking below
    {
      //std::cout << "Right rotation" << std::endl;
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

void Side::InOrder(PriceLevel *level) {
  if (level != nullptr) {
    InOrder(level->left_);
    std::cout << "Price Level : " << level->GetPrice() << std::endl;
    std::cout << "\tSize : " << level->GetSize() << " Num orders : " << level->NumOrders() << std::endl;
    for (auto &iter: level->GetOrders()) {
      std::cout << "\t\tid: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    }
    InOrder(level->right_);
  }
}

void Side::ReverseOrder(PriceLevel *level) {
  if (level != nullptr) {
    ReverseOrder(level->right_);
    std::cout << "Price Level : " << level->GetPrice() << std::endl;
    std::cout << "\tSize : " << level->GetSize() << " Num orders : " << level->NumOrders() << std::endl;
    for (auto &iter: level->GetOrders()) {
      std::cout << "\t\tid: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    }
    ReverseOrder(level->left_);
  }
}

void Side::ToStringInOrder(PriceLevel *level, std::string &str) {
  if (level == nullptr) {
    return;
  }

  ToStringInOrder(level->left_, str);
  str += (std::to_string(level->GetPrice()) + ' ');

  if (level->left_ == nullptr && level->right_ == nullptr) {
    return;
  }

  ToStringInOrder(level->right_, str);

}
void Side::ToStringPreOrder(PriceLevel *level, std::string &str) {
  if (level == nullptr) {
    return;
  }

  str += (std::to_string(level->GetPrice()) + ' ');

  if (level->left_ == nullptr && level->right_ == nullptr) {
    return;
  }

  ToStringPreOrder(level->left_, str);
  ToStringPreOrder(level->right_, str);
}
void Side::ToDequeInOrder(PriceLevel *level, std::deque<PriceLevel *> &deq) {
  if (level == nullptr) {
    return;
  }

  ToDequeInOrder(level->left_, deq);
  deq.push_back(level);

  if (level->left_ == nullptr && level->right_ == nullptr) {
    return;
  }

  ToDequeInOrder(level->right_, deq);

}