//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__BINARYOPERATOR_H_
#define UNTITLED__BINARYOPERATOR_H_

#include "Expression.h"
class BinaryOperator : public Expression {

 protected:
  Expression *right;
  Expression *left;
};

#endif //UNTITLED__BINARYOPERATOR_H_
