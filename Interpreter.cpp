//
// Created by nizan on 06/11/2019.
//

#include "Interpreter.h"
#include "Value.h"
#include "Mul.h"
#include "Plus.h"
#include "UPlus.h"
#include "Div.h"
#include "Minus.h"
#include "UMinus.h"
#include <sstream>
#include <algorithm>
#include <regex>

Interpreter::Interpreter() {

}

Interpreter::~Interpreter() {

}

bool Interpreter::isOperator(char c) {
    return (c == '+' || c == '*' || c == '/' || c == '-');
}

bool Interpreter::isOperatorStr(string s) {
    return (s == "+" || s == "*" || s == "/" || s == "-" || s == "~" || s == "#");
}

bool Interpreter::isNum(string s) {
    for (char c:s) {
        if (!isdigit(c) && (c != '.')) {
            return false;
        }
    }
    return true;
}

bool Interpreter::isLetter(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));

}

void Interpreter::setVariables(string input) {

    int begin = 0;
    for (unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == ';') {
            this->addVariable(input.substr(begin, i - begin));
            begin = i + 1;
        }
        if (i == input.length() - 1) {
            this->addVariable(input.substr(begin, input.length() - begin));
        }
    }
}

void Interpreter::addVariable(__attribute__((unused)) string str) {
    return;
}

bool Interpreter::priority(string f, string s) {
    if (f == "*" || f == "/" || f == "~" || f == "#") {
        if (s == "+" || s == "-") {
            return true;
        }
    }
    return false;
}

string Interpreter::updateOp(string exp, int index) {

    switch (exp[index]) {
        case '+':
            if (index == 0) {
                return "#";
            } else if (exp[index - 1] == '(') {
                return "#";
            } else {
                return "+";
            }
        case '-':
            if (index == 0) {
                return "~";
            } else if (exp[index - 1] == '(') {
                return "~";
            } else {
                return "-";
            }
        case '*':
            return "*";
        case '/':
            return "/";
        case '(':
            return "(";
        case ')':
            return ")";
        default:
            return "";
    }
}
//making an expression out of a string
Expression *Interpreter::interpret(string exp, map<string, Var *> *varsMap) {
    std::regex r("\\s+");
    exp = std::regex_replace(exp, r, "");
    //checks the string to find the brackets and the number ,variables and the mathematical operations
    for (unsigned int i = 0; i < exp.length(); i++) {
        char c = exp[i];
        if (isdigit(c)) {
            int index = i;
            while (isdigit(c) || (c == '.')) {
                i++;
                c = exp[i];
            }
            this->numbersQueue.push(exp.substr(index, i - index));
            i--;
        }
            //if its an opertaor
        else if (isOperator(c)) {
            if (isOperator(exp[i + 1])) {
                throw "illegal math expression";
            }
            string op = updateOp(exp, i);
            if (!this->operatorsStack.empty()) {
                while (priority(this->operatorsStack.top(), op) && !this->operatorsStack.empty()) {
                    string temp = this->operatorsStack.top();
                    this->operatorsStack.pop();
                    this->numbersQueue.push(temp);
                }
            }
            this->operatorsStack.push(op);
        } else if (isLetter(c)) {
            int index = i;
            while (!(isOperator(c)) && c != '(' && c != ')' && c != ' ') {
                i++;
                c = exp[i];
            }
            string varName = exp.substr(index, i - index);
            if (!(varsMap->count(varName))) {
                throw "bad input1";
            } else {
                this->numbersQueue.push(varName);
            }
            i--;

        } else if (c == '(') {
            this->operatorsStack.push(exp.substr(i, 1));
        } else if (c == ')') {
            while (this->operatorsStack.top() != "(") {
                string temp = this->operatorsStack.top();
                if (this->operatorsStack.empty()) {
                    throw "bad input2";
                }
                this->operatorsStack.pop();
                this->numbersQueue.push(temp);
            }
            this->operatorsStack.pop();
        } else {
            throw "bad input3";
        }
    }
    while (!this->operatorsStack.empty()) {
        string temp = this->operatorsStack.top();
        this->operatorsStack.pop();
        this->numbersQueue.push(temp);
    }
    stack<Expression *> experessionStack;
    Expression *first;
    Expression *second;
    while (!this->numbersQueue.empty()) {
        if (isNum(this->numbersQueue.front())) {
            string temp = this->numbersQueue.front();
            this->numbersQueue.pop();
            double number;
            stringstream convert(temp);
            convert >> number;

            Expression *e = new Value(number);
            experessionStack.push(e);
            pointers.push_back(e);


        } else if (varsMap->count(this->numbersQueue.front())) {
            string temp = this->numbersQueue.front();
            this->numbersQueue.pop();
            Expression *e = new Value((*varsMap)[temp]->getVal());
            experessionStack.push(e);
            pointers.push_back(e);

        } else if (isOperatorStr(this->numbersQueue.front())) {
            if (this->numbersQueue.front() == "*") {
                if (experessionStack.empty()) {
                    throw "bad input4";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input5";
                }
                second = experessionStack.top();
                experessionStack.pop();
                Expression *e = new Mul(second, first);
                experessionStack.push(e);
                pointers.push_back(e);

            } else if (this->numbersQueue.front() == "/") {
                if (experessionStack.empty()) {
                    throw "bad input6";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input7";
                }
                second = experessionStack.top();
                experessionStack.pop();
                Expression *e = new Div(second, first);
                experessionStack.push(e);
                pointers.push_back(e);

            } else if (this->numbersQueue.front() == "+") {
                if (experessionStack.empty()) {
                    throw "bad input8";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input9";
                }
                second = experessionStack.top();
                experessionStack.pop();
                Expression *e = new Plus(second, first);
                experessionStack.push(e);
                pointers.push_back(e);

            } else if (this->numbersQueue.front() == "-") {
                if (experessionStack.empty()) {
                    throw "bad input10";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input11";
                }
                second = experessionStack.top();
                experessionStack.pop();
                Expression *e = new Minus(second, first);
                experessionStack.push(e);
                pointers.push_back(e);

            } else if (this->numbersQueue.front() == "~") {
                if (experessionStack.empty()) {
                    throw "bad input12";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                Expression *e = new UMinus(first);
                experessionStack.push(e);
                pointers.push_back(e);

            } else if (this->numbersQueue.front() == "#") {
                if (experessionStack.empty()) {
                    throw "bad input13";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                Expression *e = new UPlus(first);
                experessionStack.push(e);
                pointers.push_back(e);

            }

        } else {
            throw "bad input14";
        }
    }
    return experessionStack.top();
}
