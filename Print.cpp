//
// Created by nizan on 22/12/2019.
//

#include <iostream>
#include "Print.h"

int Print::execute(vector<string> v, int index) {
    int i = 0;
    char c = v[index + 1][i];
    string name = "";
    double val;
    while (c!='"'&&c!=')') {
        name+=c;
        i++;
        c = v[index + 1][i];
    }
    if (c=='"'){
        i++;
        c = v[index + 1][i];
        while (c!='"'&&c!=')') {
            cout<<c;
            i++;
            c = v[index + 1][i];
        }
        cout<<"\n";
    }
    while (isalpha(c)) {
        name += c;
        i++;
        c = v[index + 1][i];
    }
    if (c == ' ') {
        i++;
        c = v[index + 1][i];
    }

    if (c == '-' && v[index + 1][i + 1] == '>') {
        dir = 1;
    }
    if (c == '<' && v[index + 1][i + 1] == '-') {
        dir = 0;
    }
    while (c != '"') {
        i++;
        c = v[index + 1][i];
    }
    i++;
    c = v[index + 1][i];
    while (c != '"') {
        path += c;
        i++;
        c = v[index + 1][i];
    }






    int flag = 0;
    string temp = "";
    if (v[index + 1][0] == '"') {
        for (char c: v[index + 1]) {
            if (c == '"') {
                flag = 1;
                temp += c;
                if (flag == 1 && c == '"') {
                    cout << temp;
                    flag = 0;
                    temp = "";
                }
            }
        }
    } else {
        //   cout << varsMap[v[index + 1]];<<endl
    }

}
