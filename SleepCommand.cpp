//
// Created by nizan on 19/12/2019.
//

#include <iostream>
#include <thread>
#include "SleepCommand.h"

SleepCommand::SleepCommand() { }

int SleepCommand::execute(vector<string> v, int index,map<string, Var *> *varsMap,map<string, Var *> *simMap) {
    int secondstosleep = stoi(v[index + 1]);
    std::this_thread::sleep_for(std::chrono::milliseconds(secondstosleep));
    return 2;
}
