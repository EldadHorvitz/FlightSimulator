//
// Created by nizan on 07/11/2019.
//

#include "Minus.h"
double Minus::calculate() {
  return left->calculate() - right->calculate();
}
Minus::Minus(Expression *exp1, Expression *exp2) {
  this->left = exp1;
  this->right = exp2;
}
Minus::~Minus() {

  delete this->left;
  delete this->right;
  this->left = nullptr;
  this->right = nullptr;
}
