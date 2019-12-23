//
// Created by nizan on 07/11/2019.
//

#include "UPlus.h"

UPlus::UPlus(Expression *exp) { this->expression = exp; }
UPlus::~UPlus() {
  delete this->expression;
  this->expression = nullptr;
}
