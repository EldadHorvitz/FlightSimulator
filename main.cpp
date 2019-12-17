#include <iostream>
#include <vector>
#include<fstream>
#include "Command.h"
#include "DefineVarCommand.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include <map>

using namespace std;

vector<string> lexer(char *string);

void parser(vector<string> lexered, map<string, Command *> hashMap);

map<string, Command *> initilize();


int main(int argc, char *argv[]) {
    vector<string> v = lexer(argv[1]);
    map<string, Command *> hashMap = initilize();
    parser(v, hashMap);
    return 0;
}

vector<string> lexer(char *filename) {
    vector<string> vector;
    ifstream file;
    file.open(filename);
    int indexVector = 0;
    char c = file.get();
    string temp = "";
    while (c != EOF) {
        if (c == ' ' || c == '(' || c == ')' || c == ',') {
            vector.insert(vector.begin() + indexVector, temp);
            temp = "";
            indexVector++;
        } else if (c != '\n') {
            temp += c;
        }
        c = file.get();
    }
    return vector;
}


void parser(vector<string> lexered, map<string, Command *> hashMap) {
    int index = 0;
    while (index < lexered.size()) {
        Command *c = hashMap[lexered[index]];
        if (c != NULL) {
            index += c->execute(lexered, index);
        }
    }
}


map<string, Command *> initilize() {

    map<string, Command *> hash;
    Command *c = new DefineVarCommand();
    hash.insert({"var", c});
    Command *d = new OpenServerCommand();
    hash.insert({"openDataServer", d});
    Command *e = new ConnectCommand();
    hash.insert({"connectControlClient", e});
    return hash;
}
