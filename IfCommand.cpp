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
    cout << first->calculate() << identifier << second->calculate() << endl;
    map<string, Command *> hashMap = initilize();
    if (identifier == "==") {
        if (first->calculate() == second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }
        }

    } else if (identifier == "!=") {
        if (first->calculate() != second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }

        }

    } else if (identifier == "<=") {
        if (first->calculate() <= second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }

        }

    } else if (identifier == ">=") {
        if (first->calculate() >= second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }

        }

    } else if (identifier == ">") {
        if (first->calculate() > second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }

        }

    } else if (identifier == "<") {
        if (first->calculate() < second->calculate()) {
            index = 2;
            while (index < num) {
                if (hashMap.count(v[index])) {
                    Command *c = hashMap[v[index]];
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else if (varsMap->count(v[index])) {
                    Command *c = new AssignmentCommand();
                    if (c != NULL) {
                        index += c->execute(v, index, varsMap, simMap);
                    }
                } else {
                    ++index;
                }
            }

        }

    }

    return num;
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

