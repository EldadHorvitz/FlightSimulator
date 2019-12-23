//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__VALUE_H_
#define UNTITLED__VALUE_H_

#include "Expression.h"
class Value : public Expression {
 private:
  double value;
 public:
  Value(double value);
  double calculate() override;
  virtual ~Value();
};

#endif //UNTITLED__VALUE_H_
