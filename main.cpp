#include <iostream>
#include <vector>
#include<fstream>
#include "Command.h"
#include "OpenServerCommand.h"
#include <map>
using namespace std;

vector<string> lexer(char *string);

int main(int argc, char *argv[]) {
    lexer(argv[1]);
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

}


void parser(vector<string> lexered,map<string,Command> hashMap) {
    int index=0;
    while (index < lexered.size()){
        Command c =  hashMap[lexered[index]];
        if(c!=NULL) {
            index += c.execute();
        }
    }
}

