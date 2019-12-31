//
// Created by eldad on 22/12/2019.
//

#include "Var.h"

Var::Var(double vall, int dirl, const string &pathl) : val(vall), dir(dirl), path(pathl) {}

Var::~Var() {

}


void Var::setVal(double vall) {
    Var::val = vall;
}

double Var::getVal() {
    return this->val;
}

int Var::getDir() const {
    return dir;
}

void Var::setDir(int dirl) {
    Var::dir = dirl;
}

const string &Var::getPath() const {
    return path;
}
