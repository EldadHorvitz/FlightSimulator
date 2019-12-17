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

