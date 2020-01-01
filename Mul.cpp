//
// Created by nizan on 06/11/2019.
//

#include "Mul.h"

Mul::Mul(Expression *exp1, Expression *exp2) {
  this->left = exp1;
  this->right = exp2;
}
Mul::~Mul() {
  delete this->right;
  delete this->left;
  this->left = nullptr;
  this->right = nullptr;
}
double Mul::calculate() {
  return (this->right->calculate() * this->left->calculate());
}

