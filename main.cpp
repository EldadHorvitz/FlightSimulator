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

void
parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap, map<string, Var *> *simMap);

void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap);

map<string, Command *> initilize();


int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw "error-no filename given";
    }
    vector<string> v = lexer(argv[1]);
    map<string, Command *> commandsMap = initilize();
    map<string, Var *> *varsMap = new map<string, Var *>();
    map<string, Var *> *simMap = new map<string, Var *>();
    xmlInit(varsMap, simMap);
    parser(v, commandsMap, varsMap, simMap);
    return 0;
}

void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    //1
    Var *a = new Var(999, -1, "/instrumentation/airspeed-indicator/indicated-speed-kt");
    varsMap->insert({"airspeed", a});
    simMap->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt", a});
    //2
    a = new Var(999, -1, "/sim/time/warp");
    varsMap->insert({"warp", a});
    simMap->insert({"/sim/time/warp", a});
    //3
    a = new Var(999, -1, "/controls/switches/magnetos");
    varsMap->insert({"magnetos", a});
    simMap->insert({"/controls/switches/magnetos", a});
    //4
    a = new Var(999, -1, "/instrumentation/heading-indicator/offset-deg");
    varsMap->insert({"heading", a});
    simMap->insert({"/instrumentation/heading-indicator/offset-deg", a});
    //5
    a = new Var(999, -1, "/instrumentation/altimeter/indicated-altitude-ft");
    varsMap->insert({"alt", a});
    simMap->insert({"/instrumentation/altimeter/indicated-altitude-ft", a});
    //6 does not apper at fly.txt
    a = new Var(999, -1, "/instrumentation/altimeter/pressure-alt-ft");
    varsMap->insert({"altimeter", a});
    simMap->insert({"/instrumentation/altimeter/pressure-alt-ft", a});
    //7 does not apper at fly.txt
    a = new Var(999, -1, "/instrumentation/attitude-indicator/indicated-pitch-deg");
    varsMap->insert({"attitude", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg", a});
    //8
    a = new Var(999, -1, "/instrumentation/attitude-indicator/indicated-roll-deg");
    varsMap->insert({"roll", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-roll-deg", a});
    //9
    a = new Var(999, -1, "/instrumentation/attitude-indicator/internal-pitch-deg");
    varsMap->insert({"pitch", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-pitch-deg", a});
    //10 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/attitude-indicator/internal-roll-deg");
    varsMap->insert({"attitude2", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-roll-deg", a});
    //11 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/encoder/indicated-altitude-ft");
    varsMap->insert({"attitude3", a});
    simMap->insert({"/instrumentation/encoder/indicated-altitude-ft", a});
    //12 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/encoder/pressure-alt-ft");
    varsMap->insert({"pressure", a});
    simMap->insert({"/instrumentation/encoder/pressure-alt-ft", a});
    //13 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/gps/indicated-altitude-ft");
    varsMap->insert({"gps", a});
    simMap->insert({"/instrumentation/gps/indicated-altitude-ft", a});
    //14 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/gps/indicated-ground-speed-kt");
    varsMap->insert({"gps2", a});
    simMap->insert({"/instrumentation/gps/indicated-ground-speed-kt", a});
    //15 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/gps/indicated-vertical-speed");
    varsMap->insert({"gps3", a});
    simMap->insert({"/instrumentation/gps/indicated-vertical-speed", a});
    //16 does not apper in fly.txt
    a = new Var(999, -1, "/instrumentation/heading-indicator/indicated-heading-deg");
    varsMap->insert({"indicated", a});
    simMap->insert({"/instrumentation/heading-indicator/indicated-heading-deg", a});
    //17
    a = new Var(999, -1, "/instrumentation/magnetic-compass/indicated-heading-deg");
    varsMap->insert({"magnetic", a});
    simMap->insert({"/instrumentation/magnetic-compass/indicated-heading-deg", a});
    //18
    a = new Var(999, -1, "/instrumentation/slip-skid-ball/indicated-slip-skid");
    varsMap->insert({"slip", a});
    simMap->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid", a});
    //19
    a = new Var(999, -1, "/instrumentation/turn-indicator/indicated-turn-rate");
    varsMap->insert({"turn", a});
    simMap->insert({"/instrumentation/turn-indicator/indicated-turn-rate", a});
    //20
    a = new Var(999, -1, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    varsMap->insert({"vertical", a});
    simMap->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", a});
    //21



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


void parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap,
            map<string, Var *> *simMap) {
    int index = 0;
    while (index < lexered.size()) {
        if (hashMap.count(lexered[index])) {
            Command *c = hashMap[lexered[index]];
            if (c != NULL) {
                try {
                    index += c->execute(lexered, index, varsMap, simMap);
                }
                catch (const char *e) {
                    cout << e;
                }
            }
        } else if (varsMap->count(lexered[index])) {
            Command *c = new AssignmentCommand();
            if (c != NULL) {
                index += c->execute(lexered, index, varsMap, simMap);
            }
        } else {
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
    /*
    c = new WhileCommand();
    hash.insert({"while", c});
    c = new IfCommand();
    hash.insert({"if", c});
 */
    return hash;
}

