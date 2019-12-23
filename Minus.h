//
// Created by nizan on 07/11/2019.
//

#ifndef UNTITLED__MINUS_H_
#define UNTITLED__MINUS_H_

#include "BinaryOperator.h"
class Minus : public BinaryOperator {
 public:
  Minus(Expression *exp1, Expression *exp2);
  virtual ~Minus();
  double calculate() override;
};

#endif //UNTITLED__MINUS_H_
