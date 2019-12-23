//
// Created by eldad on 22/12/2019.
//

#ifndef EX3_VAR_H
#define EX3_VAR_H

#include <string>

using namespace std;


class Var {
private:
    double val;
    int dir;
    string path;
public:
    virtual ~Var();

    Var(double val, int dir, const string &path);

    void setVal(double val);

    double getVal();


};


#endif //EX3_VAR_H
