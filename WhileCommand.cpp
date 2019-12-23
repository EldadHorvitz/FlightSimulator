//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include <algorithm>
#include "WhileCommand.h"
#include "Interpreter.h"
#include "Plus.h"
#include "Value.h"
#include "Mul.h"
#include "Div.h"
#include "Minus.h"
#include "Expression.h"
#include "UMinus.h"
#include "UPlus.h"
#include "UnaryOperator.h"
#include "Variable.h"
#include "BinaryOperator.h"

WhileCommand::WhileCommand() {}

int WhileCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    string expfirst = "";
    string expsecond = "";
    char identifier;
    int counter = 1;
    for (char c: v[index + 1]) {
        counter++;
        if (c == '<' || c == '>' || c == '!' || c == '=') {
            identifier = c;
            break;
        }
        expfirst += c;
    }
    std::string::iterator end_pos = std::remove(expfirst.begin(), expfirst.end(), ' ');
    expfirst.erase(end_pos, expfirst.end());

    for (char c: v[index + 1].substr(counter, v[index + 1].length())) {
        if (c == '{') {
            break;
        }
        expsecond += c;
    }
    end_pos = std::remove(expfirst.begin(), expfirst.end(), ' ');
    expsecond.erase(end_pos, expfirst.end());


    Interpreter *i1 = new Interpreter();
    Interpreter *i2 = new Interpreter();

    Expression *first = i1->interpret(expfirst, varsMap);

    Expression *second = i2->interpret(expsecond, varsMap);

    cout << first->calculate() << endl;


    return 2;
}
