//
// Created by nizan on 07/11/2019.
//

#include "UnaryOperator.h"
double UnaryOperator::calculate() {
  return this->expression->calculate();
}
UnaryOperator::~UnaryOperator() {
  delete this->expression;
  this->expression = nullptr;
}
