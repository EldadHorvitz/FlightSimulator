//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__DIV_H_
#define UNTITLED__DIV_H_

#include "BinaryOperator.h"
class Div : public BinaryOperator {
 public:
  Div(Expression *left, Expression *right);
  virtual ~Div();
  double calculate() override;

};

#endif //UNTITLED__DIV_H_
