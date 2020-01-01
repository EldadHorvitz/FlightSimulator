//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__MUL_H_
#define UNTITLED__MUL_H_

#include "Expression.h"
#include "BinaryOperator.h"
class Mul : public BinaryOperator {
 public:
  double calculate() override;
  Mul(Expression *one, Expression *two);
  virtual ~Mul();
};

#endif //UNTITLED__MUL_H_
