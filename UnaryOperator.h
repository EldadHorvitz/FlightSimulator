//
// Created by nizan on 07/11/2019.
//

#ifndef UNTITLED__UNARYOPERATOR_H_
#define UNTITLED__UNARYOPERATOR_H_

#include "Expression.h"
class UnaryOperator : public Expression {
 protected:
  Expression *expression;
 public:
  double calculate();
  virtual ~UnaryOperator();
};

#endif //UNTITLED__UNARYOPERATOR_H_
