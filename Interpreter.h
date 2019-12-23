//
// Created by nizan on 06/11/2019.
//

#ifndef UNTITLED__INTERPRETER_H_
#define UNTITLED__INTERPRETER_H_

#include <stack>
#include <queue>
#include <array>
#include "Expression.h"
#include "map"
#include "Var.h"

class Interpreter {
 private:
  stack<string> operators;
  queue<string> output;
  map<string, Var*> variables;
 public:
  Interpreter();
  Expression *interpret(string);
  int presedence(char);
  virtual ~Interpreter();
  void setVariables(string);
  int numCounter(string phrase);
  int varCounter(string phrase);
  bool isNumber(string phrase);
  bool isOperator(string op1, char op2);
};

#endif //UNTITLED__INTERPRETER_H_
