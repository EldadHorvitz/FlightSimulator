//
// Created by nizan on 22/12/2019.
//

#include <iostream>
#include "Print.h"

int Print::execute(vector<string> v, int index) {
    int flag = 0;
    string temp = "";
    if (v[index + 1][0] == '\c') {
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
        cout << varsMap[v[index + 1]];<<endl
    }


}
