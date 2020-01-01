//
// Created by nizan on 06/11/2019.
//

#include "Div.h"
double Div::calculate() {
  if (right->calculate() == 0) {
    throw "division by zero";
  }
  return left->calculate() / right->calculate();

}
Div::Div(Expression *leftl, Expression *rightl) {
  this->left = leftl;
  this->right = rightl;
}

Div::~Div() {
  delete this->right;
  delete this->left;
  this->left = nullptr;
  this->right = nullptr;
}
