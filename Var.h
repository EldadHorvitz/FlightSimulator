//
// Created by eldad on 22/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H

#include <string>

using namespace std;


class Var {
public:
    double val;
    int dir;
    string path;

    virtual ~Var();

    Var(double val, int dir, const string &path);

    void setVal(double val);

    double getVal() const;


};


#endif //EX3_VAR_H
