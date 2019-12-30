//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include <thread>
#include "SleepCommand.h"
#include "Interpreter.h"

SleepCommand::SleepCommand() {}
//excuting the sleep command
int SleepCommand::execute(vector<string> v, int index, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    Interpreter *i1 = new Interpreter();
    string sleepstring = v[index + 1];
    sleepstring = sleepstring.substr(0, sleepstring.length() - 1);
    Expression *ex = i1->interpret(sleepstring, varsMap);
    int secondstosleep = ex->calculate();
    std::this_thread::sleep_for(std::chrono::milliseconds(secondstosleep));
    return 2;
}
