//
// Created by nizan on 19/12/2019.
//

#include <iostream>
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

WhileCommand::WhileCommand() { this->parmeterNum = 2; }

int WhileCommand::execute(vector<string> v, int index) {
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


    for (char c: v[index + 1].substr(counter, v[index + 1].length())) {
        if (c == '{') {
            break;
        }
        expsecond += c;
    }
    //if its a variable
    if (identifier == '=') {
        // Expression *c = new Variable(expfirst, this->varsMap[exp]);
    }

    return 2;
}
