//
// Created by eldad on 10/11/2019.
//

#ifndef UNTITLED1_INTERPRETER_H
#define UNTITLED1_INTERPRETER_H


#include <stack>
#include <queue>
#include <array>
#include "Expression.h"
#include "Var.h"
#include <map>

static vector<Expression *> pointers;
static Expression *eGlobal = nullptr;

class Interpreter {
private:
    stack<string> operatorsStack;
    queue<string> numbersQueue;
    map<string, double> vars;
public:
    Interpreter();

    virtual ~Interpreter();

    void setVariables(string);

    void addVariable(string input);

    Expression *interpret(string, map<string, Var *> *varsMap);

    bool isOperator(char c);

    bool isOperatorStr(string s);

    bool isNum(string s);

    bool isLetter(char c);

    bool priority(string f, string s);

    string updateOp(string exp, int i);
};


#endif //UNTITLED1_INTERPRETER_H