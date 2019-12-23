//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__UPLUS_H_
#define UNTITLED__UPLUS_H_

#include "Expression.h"
#include "UnaryOperator.h"
class UPlus : public UnaryOperator {

 public:

 private:
 public:
  UPlus(Expression *exp);
  double calculate() override {
    return this->expression->calculate();
  }
  virtual ~UPlus();
};

#endif //UNTITLED__UPLUS_H_
