//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__UMINUS_H_
#define UNTITLED__UMINUS_H_

#include "UnaryOperator.h"
class UMinus : public UnaryOperator {
 public:
  UMinus(Expression *exp);
  double calculate() override;
  virtual ~UMinus();
};

#endif //UNTITLED__UMINUS_H_
