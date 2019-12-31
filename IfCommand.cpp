//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include "IfCommand.h"
#include "AssignmentCommand.h"
#include "DefineVarCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "Interpreter.h"

IfCommand::IfCommand() {}

int IfCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    int num = 0;
    while (v[num + index] != "}") {
        num++;
    }
    int jump=num;
    num=num+index;
    int x=2;
    string expfirst = "";
    string expsecond = "";
    string identifier = "";
    int counter = 0;
    for (char c: v[index + 1]) {
        counter++;
        if (c == '<' || c == '>' || c == '!' || c == '=') {
            identifier += c;
            break;
        }
        if (c != ' ') {
            expfirst += c;
        }

    }
    string s = v[index + 1].substr(counter, 1);
    if (s == "<" || s == ">" || s == "!" || s == "=") {
        identifier += s;
    }


    for (char c: v[index + 1].substr(counter + 1, v[index + 1].length() - counter)) {
        if (c == '{') {
            break;
        }
        if (c != ' ') {
            expsecond += c;
        }
    }
    Interpreter *i1 = new Interpreter();
    Interpreter *i2 = new Interpreter();

    Expression *first = i1->interpret(expfirst, varsMap);

    Expression *second = i2->interpret(expsecond, varsMap);
    x = 2+index;
    if (identifier == "==") {
        if (first->calculate() == second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    } else if (identifier == "!=") {
        if (first->calculate() != second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    } else if (identifier == "<=") {
        if (first->calculate() <= second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    } else if (identifier == ">=") {
        if (first->calculate() >= second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    } else if (identifier == ">") {
        if (first->calculate() > second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    } else if (identifier == "<") {
        if (first->calculate() < second->calculate()) {
            miniParser(x,num,v,varsMap,simMap);
        }
    }
    return jump;
}

map<string, Command *> IfCommand::initilize() {
    map<string, Command *> hash;
    Command *c = new DefineVarCommand();
    hash.insert({"var", c});
    c = new OpenServerCommand();
    hash.insert({"openDataServer", c});
    c = new ConnectCommand();
    hash.insert({"connectControlClient", c});
    c = new PrintCommand();
    hash.insert({"Print", c});
    c = new SleepCommand();
    hash.insert({"Sleep", c});
    c = new WhileCommand();
    hash.insert({"while", c});
    c = new IfCommand();
    hash.insert({"if", c});

    return hash;
}
string IfCommand::RemoveChar(string str, char c) {
    string result;
    int flag = 0;
    for (size_t i = 0; i < str.size(); i++) {
        char currentChar = str[i];
        if (currentChar != c || flag == 1){
            result += currentChar;
            flag = 1;
        }

    }
    return result;
}

void IfCommand::miniParser(int x , int num,vector<string> v,map<string, Var *> *varsMap,map<string, Var *> *simMap){
    map<string, Command *> hashMap = initilize();
    while (x < num) {
        v[x] = RemoveChar(v[x], '\t');
        v[x] = RemoveChar(v[x], ' ');
        if (hashMap.count(v[x])) {
            Command *c = hashMap[v[x]];
            if (c != NULL) {
                x += c->execute(v, x, varsMap, simMap);
            }
        } else if (varsMap->count(v[x])) {
            Command *c = new AssignmentCommand();
            if (c != NULL) {
                x += c->execute(v, x, varsMap, simMap);
            }
        } else {
            ++x;
        }
    }
}