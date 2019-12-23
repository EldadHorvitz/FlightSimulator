//
// Created by nizan on 06/11/2019.
//

#include "UMinus.h"
#include "Value.h"

UMinus::UMinus(Expression *exp) { this->expression = exp; }

double UMinus::calculate() {
  return (this->expression->calculate() * -1);
}
UMinus::~UMinus() {
  delete this->expression;
  this->expression = nullptr;
}



