//
// Created by nizan on 06/11/2019.
//

#include <string>
#include <sstream>
#include <algorithm>
#include "Interpreter.h"
#include "Plus.h"
#include "Value.h"
#include "Mul.h"
#include "Div.h"
#include "Minus.h"

Interpreter::Interpreter() {
}
Expression *Interpreter::interpret(string phrase) {
  string number;
  string var;
  int counterNum = 0;
  int counterVar = 0;
  int stringPos = 0;
  //converting to postfix
  for (char &c : phrase) {
    if (counterNum > 1) {
      counterNum--;
      stringPos++;
      continue;
    }
    //if its a number
    if (isdigit(c)) {
      counterNum = this->numCounter(phrase.substr(stringPos, phrase.length() - 1));
      number.append(phrase.substr(stringPos, counterNum));
      this->output.push(number);
      number.clear();
    }

      //if its an variable
    else if (isalpha(c)) {
      counterVar = this->varCounter(phrase.substr(stringPos, phrase.length() - 1));
      var.append(phrase.substr(stringPos, counterVar));
      if (this->variables.count(var)) {
        double value = this->variables[var];
        std::ostringstream strs;
        strs << value;
        std::string str = strs.str();
        this->output.push(str);
      } else {
        throw "illegal math expression";
      }
      var.clear();
    }

      //if its an opertaor
    else if (c == '*' || c == '/' || c == '-' || c == '+') {
      //cases for UMinus
      if (stringPos == 0 && c == '-') {
        this->operators.push("#");
        stringPos++;
        continue;
      }

      if (!this->operators.empty()) {
        if (this->operators.top() == "(" && c == '-') {
          this->operators.push("#");
          stringPos++;
          continue;
        }
      }
      //checking for double opertators
      if (!this->operators.empty()) {
        if (isOperator(this->operators.top(), c)) {
          throw "illegal math expression";
        }
        /*
         *   if (this->operators.top() == "*" && c == '*') {
          throw "illegal math expression";
        } else if (this->operators.top() == "/" && c == '/') {
          throw "illegal math expression";
        } else if (this->operators.top() == "-" && c == '-') {
          throw "illegal math expression";
        } else if (this->operators.top() == "+" && c == '+') {
          throw "illegal math expression";
        } else
         */
      }

      while (presedence(c)) {
        string temp = this->operators.top();
        this->operators.pop();
        this->output.push(temp);
      }
      this->operators.push(string(1, c));
    } else if (c == '(') {
      this->operators.push(string(1, c));
    } else if (c == ')') {
      while (this->operators.top() != "(") {
        string temp = this->operators.top();
        this->operators.pop();
        this->output.push(temp);
      }
      this->operators.pop();
    } else {
      throw "bad input";
    }
    stringPos++;
  }
  //now the queue is postfix, we will convert it to Expression stack
  while (!this->operators.empty()) {
    string temp = this->operators.top();
    this->operators.pop();
    this->output.push(temp);
  }
  stack<Expression *> experession;
  Expression *tempa;
  Expression *tempb;
  while (!this->output.empty()) {
    if (isNumber(this->output.front())) {
      string temp = this->output.front();
      this->output.pop();
      experession.push(new Value(stod(temp)));
      continue;
    }

//if its a variable
    if (isalpha(this->output.front().at(0))) {
      string temp = this->output.front();
      this->output.pop();
      experession.push(new Value(this->variables[temp]));
    }
    switch (this->output.front().at(0)) {
      case '*':this->output.pop();
        tempa = experession.top();
        experession.pop();
        tempb = experession.top();
        experession.pop();
        experession.push(new Mul(tempb, tempa));
        break;
      case '+':this->output.pop();
        tempa = experession.top();
        experession.pop();
        tempb = experession.top();
        experession.pop();
        experession.push(new Plus(tempb, tempa));
        break;
      case '/':this->output.pop();
        tempa = experession.top();
        experession.pop();
        tempb = experession.top();
        experession.pop();
        experession.push(new Div(tempb, tempa));
        break;
      case '-':this->output.pop();
        tempa = experession.top();
        experession.pop();
        tempb = experession.top();
        experession.pop();
        experession.push(new Minus(tempb, tempa));
        break;
      case '#':this->output.pop();
        tempa = experession.top();
        experession.pop();
        experession.push(new Value(tempa->calculate() * -1));
        break;
      case '$':this->output.pop();
        tempa = experession.top();
        experession.pop();
        experession.push(new Value(tempa->calculate()));
        break;
    }
  }
  return experession.top();
}

int Interpreter::numCounter(string phrase) {
  int counterNum = 0;
  for (char &c : phrase) {
    //if its a number
    if (isdigit(c) || c == '.') {
      counterNum++;
    } else {
      break;
    }
  }
  return counterNum;
}

int Interpreter::varCounter(string phrase) {
  int counterVar = 0;
  for (char &c : phrase) {
    //if its a number
    if (c != '(' && c != ')' && c != '*' && c != '+' && c != '-' && c != '/') {
      counterVar++;
    } else {
      break;
    }
  }
  return counterVar;
}

int Interpreter::presedence(char s) {
  if (this->operators.empty()) {
    return 0;
  }
  if (this->operators.top().at(0) == '*' || this->operators.top().at(0) == '/' || this->operators.top().at(0)
      == '#' || this->operators.top().at(0) == '$') {
    if (s == '+' || s == '-') {
      return 1;
    }
  }
  return 0;
}

bool Interpreter::isNumber(string phrase) {
  if (phrase.empty()) {
    return false;
  }
  for (char &c:phrase) {
    if (!isdigit(c) && c != '.') {
      return false;
    }
  }
  return true;
}

Interpreter::~Interpreter() {

}

void Interpreter::setVariables(string assignment) {

  int counter = 0;
  int length = assignment.length();
  for (char &c: assignment) {
    if (c == ';') {
      counter++;
    }
  }
  string *strings = new string[counter + 1];
  // string strings[counter + 1];
  int counterl = 0;
  int start = 0;
  for (int i = 0; i < length; i++) {
    if (assignment[i] == ';') {
      strings[counterl] = assignment.substr(start, i);
      start = i + 1;
      counterl++;
    }
    if (counterl == counter) {
      strings[counterl] = assignment.substr(start, assignment.length());
    }
  }

  for (int j = 0; j <= counter; j++) {
    string temp;
    double value;
    string token = strings[j];
    if (!isalpha(token[0])) {
      throw "illegal variable assignment!";
    } else {
      temp = token[0];
    }
    int counti;
    for (unsigned int i = 0; i < token.length(); i++) {
      if (token[i] == '=') {
        if (!isdigit(token[i + 1])) {
          throw "illegal variable assignment!";
        } else {
          counti = i;
          break;
        }
      }
    }

    temp = token.substr(0, counti);
    int counterendassign = 0;
    for (unsigned int i = 0; i < token.length(); i++) {
      if (token[i] == ';') {
        counterendassign = i - 1;
        break;
      }

    }
    string valuestr = token.substr(counti + 1, counterendassign - 1);
    counterendassign = 0;

    int countdot = 0;
    for (unsigned int i = 0; i < valuestr.length(); i++) {
      if (valuestr[i] == '.') {
        countdot++;
      }
    }
    if (countdot > 1) {
      throw "illegal variable assignment!";
    }
    countdot = 0;
    for (unsigned int i = 0; i < valuestr.length(); i++) {
      if (!isdigit(valuestr[i]) && valuestr[i] != '.') {
        throw "illegal variable assignment!";
      }
    }

    stringstream convert(valuestr);
    convert >> value;
    if (!this->variables.count(temp)) {

      this->variables.insert(std::pair<string, double>(temp, value));
    } else {
      this->variables.erase(temp);
      this->variables.insert(std::pair<string, double>(temp, value));
    }
  }

}

bool Interpreter::isOperator(string op1, char op2) {
  if (op1 == "+" || op1 == "*" || op1 == "/" || op1 == "-") {
    if (op2 == '+' || op2 == '*' || op2 == '/' || op2 == '-') {
      return true;
    }
  }
  return false;
}
