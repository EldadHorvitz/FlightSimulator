#include <iostream>
#include <vector>
#include<fstream>
#include "Command.h"
#include "OpenServerCommand.h"
#include "DefineVarCommand.h"
#include "ConnectCommand.h"
#include "PrintCommand.h"
#include "SleepCommand.h"
#include "WhileCommand.h"
#include "AssignmentCommand.h"
#include "IfCommand.h"
#include "Var.h"
#include <map>


using namespace std;

vector<string> lexer(char *string);

void parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap, map<string, Var *> *simMap);

map<string, Command *> initilize();


int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw "error-no filename given";
    }
    vector<string> v = lexer(argv[1]);
    map<string, Command *> commandsMap = initilize();
    map<string, Var *> *varsMap=new map<string, Var *> ();
    map<string, Var *> *simMap=new map<string, Var *>();
    parser(v, commandsMap,varsMap,simMap);
    return 0;
}

vector<string> lexer(char *filename) {
    vector<string> vector1;
    ifstream file;
    file.open(filename);
    int indexVector = 0;
    char c = file.get();
    string temp = "";
    int flag = 1;
    while (c != EOF) {
        if ((c == ' ' || c == '(' || c == ')' || c == ',') && flag) {
            vector1.insert(vector1.begin() + indexVector, temp);
            temp = "";
            indexVector++;
            flag = 0;
        } else if (c != '\n') {
            temp += c;
        } else {

            vector1.insert(vector1.begin() + indexVector, temp);
            temp = "";
            indexVector++;
            flag = 1;
        }
        c = file.get();
    }
    return vector1;
}


void parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    int index = 0;
    while (index < lexered.size()) {
        if (hashMap.count(lexered[index])) {
            Command *c = hashMap[lexered[index]];
            if (c != NULL) {
                index += c->execute(lexered, index,varsMap,simMap);
            }
        } else if(varsMap->count(lexered[index])){
            Command *c = new AssignmentCommand();
            if (c != NULL) {
                index += c->execute(lexered, index,varsMap,simMap);
            }
        }else{
            ++index;
        }

    }
}

map<string, Command *> initilize() {
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

