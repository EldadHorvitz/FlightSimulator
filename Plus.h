//
// Created by nizan on 07/11/2019.
//

#ifndef UNTITLED__PLUS_H_
#define UNTITLED__PLUS_H_

#include "BinaryOperator.h"
class Plus : public BinaryOperator {

 public:
  Plus(Expression *exp1, Expression *exp2);
  double calculate() override;
  virtual ~Plus();
};

#endif //UNTITLED__PLUS_H_
