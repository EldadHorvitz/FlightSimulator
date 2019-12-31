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
#include "Expression.h"
#include "Interpreter.h"
#include <map>

using namespace std;

//functions declerations
vector<string> lexer(char *string);

void memoryFree();

void
parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap, map<string, Var *> *simMap);

void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap);

map<string, Command *> initilize();

static vector<Command *> commandsPointers;
static vector<Var *> xmlPointers;


int main(int argc, char *argv[]) {
    if (argc < 2) {
        throw "error-no filename given";
    }
    vector<string> v = lexer(argv[1]);
    map<string, Command *> commandsMap = initilize();
    map<string, Var *> *varsMap = new map<string, Var *>();
    map<string, Var *> *simMap = new map<string, Var *>();
    xmlInit(varsMap, simMap);
    try {
        parser(v, commandsMap, varsMap, simMap);;
    } catch (const char *e) {
        cout << e << endl;
    }
    close((*varsMap)["client_sock"]->getDir());
    memoryFree();
    delete simMap;
    delete varsMap;
    return 0;
}

void memoryFree() {
    for (auto const &value: pointers) {
        delete value;
    }
    for (auto const &value: commandsPointers) {
        delete value;
    }
    for (auto const &value: xmlPointers) {
        delete value;
    }


    delete eGlobal;
}


//initalzing the xmlTable
void xmlInit(map<string, Var *> *varsMap, map<string, Var *> *simMap) {
    //1
    Var *a = new Var(0, -1, "/instrumentation/airspeed-indicator/indicated-speed-kt");
    xmlPointers.push_back(a);
    varsMap->insert({"airspeed", a});
    simMap->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt", a});
    //2
    a = new Var(0, -1, "/sim/time/warp");
    xmlPointers.push_back(a);
    varsMap->insert({"warp", a});
    simMap->insert({"/sim/time/warp", a});
    //3
    a = new Var(0, -1, "/controls/switches/magnetos");
    xmlPointers.push_back(a);
    varsMap->insert({"magnetos", a});
    simMap->insert({"/controls/switches/magnetos", a});
    //4
    a = new Var(0, -1, "/instrumentation/heading-indicator/offset-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"heading", a});
    simMap->insert({"/instrumentation/heading-indicator/offset-deg", a});
    //5
    a = new Var(0, -1, "/instrumentation/altimeter/indicated-altitude-ft");
    xmlPointers.push_back(a);
    varsMap->insert({"alt", a});
    simMap->insert({"/instrumentation/altimeter/indicated-altitude-ft", a});
    //6 does not apper at fly.txt
    a = new Var(0, -1, "/instrumentation/altimeter/pressure-alt-ft");
    xmlPointers.push_back(a);
    varsMap->insert({"altimeter", a});
    simMap->insert({"/instrumentation/altimeter/pressure-alt-ft", a});
    //7 does not apper at fly.txt
    a = new Var(0, -1, "/instrumentation/attitude-indicator/indicated-pitch-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"attitude", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg", a});
    //8
    a = new Var(0, -1, "/instrumentation/attitude-indicator/indicated-roll-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"roll", a});
    simMap->insert({"/instrumentation/attitude-indicator/indicated-roll-deg", a});
    //9
    a = new Var(0, -1, "/instrumentation/attitude-indicator/internal-pitch-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"pitch", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-pitch-deg", a});
    //10 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/attitude-indicator/internal-roll-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"attitude2", a});
    simMap->insert({"/instrumentation/attitude-indicator/internal-roll-deg", a});
    //11 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/encoder/indicated-altitude-ft");
    xmlPointers.push_back(a);
    varsMap->insert({"attitude3", a});
    simMap->insert({"/instrumentation/encoder/indicated-altitude-ft", a});
    //12 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/encoder/pressure-alt-ft");
    xmlPointers.push_back(a);
    varsMap->insert({"pressure", a});
    simMap->insert({"/instrumentation/encoder/pressure-alt-ft", a});
    //13 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-altitude-ft");
    xmlPointers.push_back(a);
    varsMap->insert({"gps", a});
    simMap->insert({"/instrumentation/gps/indicated-altitude-ft", a});
    //14 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-ground-speed-kt");
    xmlPointers.push_back(a);
    varsMap->insert({"gps2", a});
    simMap->insert({"/instrumentation/gps/indicated-ground-speed-kt", a});
    //15 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/gps/indicated-vertical-speed");
    xmlPointers.push_back(a);
    varsMap->insert({"gps3", a});
    simMap->insert({"/instrumentation/gps/indicated-vertical-speed", a});
    //16 does not apper in fly.txt
    a = new Var(0, -1, "/instrumentation/heading-indicator/indicated-heading-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"indicated", a});
    simMap->insert({"/instrumentation/heading-indicator/indicated-heading-deg", a});
    //17
    a = new Var(0, -1, "/instrumentation/magnetic-compass/indicated-heading-deg");
    xmlPointers.push_back(a);
    varsMap->insert({"magnetic", a});
    simMap->insert({"/instrumentation/magnetic-compass/indicated-heading-deg", a});
    //18
    a = new Var(0, -1, "/instrumentation/slip-skid-ball/indicated-slip-skid");
    xmlPointers.push_back(a);
    varsMap->insert({"slip", a});
    simMap->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid", a});
    //19
    a = new Var(0, -1, "/instrumentation/turn-indicator/indicated-turn-rate");
    xmlPointers.push_back(a);
    varsMap->insert({"turn", a});
    simMap->insert({"/instrumentation/turn-indicator/indicated-turn-rate", a});
    //20
    a = new Var(0, -1, "/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
    xmlPointers.push_back(a);
    varsMap->insert({"vertical", a});
    simMap->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", a});
    //21 IS IN FLY.TXT
    a = new Var(0, -1, "/controls/flight/aileron");
    xmlPointers.push_back(a);
    varsMap->insert({"aileron", a});
    simMap->insert({"/controls/flight/aileron", a});
    //22
    a = new Var(0, -1, "/controls/flight/elevator");
    xmlPointers.push_back(a);
    varsMap->insert({"elevator", a});
    simMap->insert({"/controls/flight/elevator", a});
    //23 IS IN MAP
    a = new Var(0, -1, "/controls/flight/rudder");
    xmlPointers.push_back(a);
    varsMap->insert({"rudder", a});
    simMap->insert({"/controls/flight/rudder", a});
    //24
    a = new Var(0, -1, "/controls/flight/flaps");
    xmlPointers.push_back(a);
    varsMap->insert({"flight_flaps", a});
    simMap->insert({"/controls/flight/flaps", a});
    //25
    a = new Var(0, -1, "/controls/engines/engine/throttle");
    xmlPointers.push_back(a);
    varsMap->insert({"engine_throttle", a});
    simMap->insert({"/controls/engines/engine/throttle", a});
    //26 is in map
    a = new Var(0, -1, "/controls/engines/current-engine/throttle");
    xmlPointers.push_back(a);
    varsMap->insert({"throttle", a});
    simMap->insert({"/controls/engines/current-engine/throttle", a});
    //27 is in map
    a = new Var(0, -1, "/controls/switches/master-avionics");
    xmlPointers.push_back(a);
    varsMap->insert({"masteravionics", a});
    simMap->insert({"/controls/switches/master-avionics", a});
    //28 is in map
    a = new Var(0, -1, "/controls/switches/starter");
    xmlPointers.push_back(a);
    varsMap->insert({"starter", a});
    simMap->insert({"/controls/switches/starter", a});
    //29 is in map
    a = new Var(0, -1, "/engines/active-engine/auto-start");
    xmlPointers.push_back(a);
    varsMap->insert({"autostart", a});
    simMap->insert({"/engines/active-engine/auto-start", a});
    //30 is in map
    a = new Var(0, -1, "/controls/flight/speedbrake");
    xmlPointers.push_back(a);
    varsMap->insert({"breaks", a});
    simMap->insert({"/controls/flight/speedbrake", a});
    //31 is in map
    a = new Var(0, -1, "/sim/model/c172p/brake-parking");
    xmlPointers.push_back(a);
    varsMap->insert({"brakeparking", a});
    simMap->insert({"/sim/model/c172p/brake-parking", a});
    //32 is in map
    a = new Var(0, -1, "/controls/engines/engine/primer");
    xmlPointers.push_back(a);
    varsMap->insert({"primer", a});
    simMap->insert({"/controls/engines/engine/primer", a});
    //33  is in map
    a = new Var(0, -1, "/controls/engines/current-engine/mixture");
    xmlPointers.push_back(a);
    varsMap->insert({"mixture", a});
    simMap->insert({"/controls/engines/current-engine/mixture", a});
    //34 is in map
    a = new Var(0, -1, "/controls/switches/master-bat");
    xmlPointers.push_back(a);
    varsMap->insert({"masterbat", a});
    simMap->insert({"/controls/switches/master-bat", a});
    //35 is in map
    a = new Var(0, -1, "/controls/switches/master-alt");
    xmlPointers.push_back(a);
    varsMap->insert({"masterlat", a});
    simMap->insert({"/controls/switches/master-alt", a});
    //36 is in map
    a = new Var(0, -1, "/engines/engine/rpm");
    xmlPointers.push_back(a);
    varsMap->insert({"rpm", a});
    simMap->insert({"/engines/engine/rpm", a});


}

//lexer function to read from the provided txt file
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
    vector1.insert(vector1.begin() + indexVector, temp);
    return vector1;
}

//parser function that will excute the commands given in the file
void parser(vector<string> lexered, map<string, Command *> hashMap, map<string, Var *> *varsMap,
            map<string, Var *> *simMap) {
    int index = 0;
    while (index < lexered.size()) {
        if (hashMap.count(lexered[index])) {
            Command *c = hashMap[lexered[index]];
            if (c != NULL) {
                index += c->execute(lexered, index, varsMap, simMap);
            }
        } else if (varsMap->count(lexered[index])) {
            Command *c = new AssignmentCommand();
            if (c != NULL) {
                index += c->execute(lexered, index, varsMap, simMap);
            }
            delete c;
            c = nullptr;
        } else {
            ++index;
        }
    }
    isConnect = false;
}

//initalzing the Commands map
map<string, Command *> initilize() {
    map<string, Command *> hash;
    Command *c = new DefineVarCommand();
    hash.insert({"var", c});
    commandsPointers.push_back(c);
    c = new OpenServerCommand();
    hash.insert({"openDataServer", c});
    commandsPointers.push_back(c);

    c = new ConnectCommand();
    hash.insert({"connectControlClient", c});
    commandsPointers.push_back(c);

    c = new PrintCommand();
    hash.insert({"Print", c});
    commandsPointers.push_back(c);

    c = new SleepCommand();
    hash.insert({"Sleep", c});
    commandsPointers.push_back(c);

    c = new WhileCommand();
    hash.insert({"while", c});
    commandsPointers.push_back(c);

    c = new IfCommand();
    hash.insert({"if", c});
    commandsPointers.push_back(c);

    return hash;
}
