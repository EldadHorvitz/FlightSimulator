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

WhileCommand::WhileCommand() {}

int WhileCommand::execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) {
    int num=0;
    while (v[num+index]!="}"){
        num++;
    }
    string expfirst = "";
    string expsecond = "";
    string identifier="";
    int counter = 0;
    for (char c: v[index + 1]) {
        counter++;
        if (c == '<' || c == '>' || c == '!' || c == '=') {
            identifier += c;
            break;
        }
        if (c!=' '){
            expfirst += c;
        }

    }
    string s=v[index + 1].substr(counter, 1);
    if (s == "<" || s == ">" || s == "!" || s == "="){
        identifier+=s;
    }


    for (char c: v[index + 1].substr(counter+1, v[index + 1].length()-counter)) {
        if (c == '{') {
            break;
        }
        if (c!=' '){
            expsecond += c;
        }
    }
    Interpreter *i1 = new Interpreter();
    Interpreter *i2 = new Interpreter();

    Expression *first = i1->interpret(expfirst,varsMap);

    Expression *second = i2->interpret(expsecond,varsMap);
    cout<<first->calculate()<<identifier<<second->calculate()<<endl;

    if (identifier=="=="){
        while (first->calculate()==second->calculate()){

        }

    } else if (identifier=="!="){
        while (first->calculate()!=second->calculate()){

        }

    }else if (identifier=="<="){
        while (first->calculate()<=second->calculate()){

        }

    } else if (identifier==">="){
        while (first->calculate()>=second->calculate()){

        }

    } else if (identifier==">"){
        while (first->calculate()>second->calculate()){

        }

    }else if (identifier=="<"){
        while (first->calculate()<second->calculate()){

        }

    }

    return num;
}
