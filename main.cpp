#include <iostream>
#include <vector>
#include<fstream>

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
    for (string line; getline(file, line);) {
        int startString = 0;
        int endString = 0;
        for (char &c: line) {
            if (c == ' ' || c == '(') {
                break;
            }
            endString++;
        }
        vector.insert(vector.begin() + indexVector, line.substr(startString, endString));
        startString = endString;
        indexVector++;
    }
}

