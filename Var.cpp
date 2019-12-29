//
// Created by eldad on 22/12/2019.
//

#include "Var.h"

Var::Var(double val, int dir, const string &path) : val(val), dir(dir), path(path) {}

Var::~Var() {

}


void Var::setVal(double val) {
    Var::val = val;
}

double Var::getVal() {
    return this->val;
}

int Var::getDir() const {
    return dir;
}

void Var::setDir(int dir) {
    Var::dir = dir;
}

const string &Var::getPath() const {
    return path;
}
