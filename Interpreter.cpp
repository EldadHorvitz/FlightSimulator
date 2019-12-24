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
    for ( unsigned int i = 0; i < input.length(); i++) {
        if (input[i] == ';') {
            this->addVariable(input.substr(begin, i - begin));
            begin = i + 1;
        }
        if (i == input.length() - 1) {
            this->addVariable(input.substr(begin, input.length() - begin));
        }
    }

}

void Interpreter::addVariable(string str) {
    /*
    double number;
    int index = 0;
    if (!this->isLetter(str[0])) {
        throw "bad input";
    } else {
        for (unsigned int i = 0; i < str.length(); i++) {
            if (str[i] == '=') {
                index = i;
                break;
            }
        }
    }
    if (index == 0) {
        throw "bad input";
    }
    if (!this->isNum(str.substr(index + 1, str.length() - index - 1))) {
        throw "illegal variable assignment!";
    }
    string valuestr = str.substr(index + 1, str.length() - index - 1);
    stringstream convert(valuestr);
    convert >> number;
    string name = str.substr(0, index);
    if (this->vars.count(name)) {
        this->vars[name] = number;
    } else {
        this->vars.insert(std::pair<string, double>(name, number));
    }
*/
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

Expression *Interpreter::interpret(string exp,map<string, Var *> *varsMap) {
    std::regex r("\\s+");
    exp = std::regex_replace(exp, r, "");
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
            while (!(isOperator(c)) && c != '(' && c != ')') {
                i++;
                c = exp[i];
            }
            string varName = exp.substr(index, i - index-1);
            if (!(varsMap->count(varName))) {
                throw "bad input";
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
                    throw "bad input";
                }
                this->operatorsStack.pop();
                this->numbersQueue.push(temp);
            }
            this->operatorsStack.pop();
        } else {
            throw "bad input";
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
            experessionStack.push(new Value(number));

        } else if (varsMap->count(this->numbersQueue.front())) {
            string temp = this->numbersQueue.front();
            this->numbersQueue.pop();
            experessionStack.push(new Value((*varsMap)[temp]->getVal()));

        } else if (isOperatorStr(this->numbersQueue.front())) {
            if (this->numbersQueue.front() == "*") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                second = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new Mul(second,first));
            } else if (this->numbersQueue.front() == "/") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                second = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new Div(second,first));
            } else if (this->numbersQueue.front() == "+") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                second = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new Plus(second,first));
            } else if (this->numbersQueue.front() == "-") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                second = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new Minus(second,first));
            } else if (this->numbersQueue.front() == "~") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new UMinus(first));
            } else if (this->numbersQueue.front() == "#") {
                if (experessionStack.empty()) {
                    throw "bad input";
                }
                this->numbersQueue.pop();
                first = experessionStack.top();
                experessionStack.pop();
                experessionStack.push(new UPlus(first));
            }

        } else {
            throw "bad input";
        }
    }

    return experessionStack.top();

}
