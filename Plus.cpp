//
// Created by nizan on 07/11/2019.
//

#include "Plus.h"
double Plus::calculate() {
  return right->calculate() + left->calculate();
}
Plus::Plus(Expression *exp1, Expression *exp2) {
  this->right = exp1;
  this->left = exp2;
}

Plus::~Plus() {
  delete this->left;
  delete this->right;
  this->left = nullptr;
  this->right = nullptr;
}
