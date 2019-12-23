//
// Created by nizan on 06/11/2019.
//

#include <string>
#include "Expression.h"
#ifndef UNTITLED__VARIABLE_H_
#define UNTITLED__VARIABLE_H_

#endif //UNTITLED__VARIABLE_H_

class Variable : public Expression {

 private:
  double value;
  string name;
 public:
  Variable(string name, double value);
  Variable &operator++();
  Variable &operator--();
  Variable &operator+=(double num);
  Variable &operator-=(double num);
  Variable &operator++(int);
  Variable &operator--(int);
  double calculate() override;
  virtual ~Variable();

};