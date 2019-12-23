//
// Created by nizan on 06/11/2019.
//

#include "Variable.h"

Variable::Variable(string namel, double valuel) : value(valuel), name(namel) {}

double Variable::calculate() {
  return this->value;
}

Variable &Variable::operator+=(double num) {
  this->value = this->value + num;
  return *this;
}

Variable &Variable::operator-=(double num) {
  this->value = this->value - num;
  return *this;
}

Variable &Variable::operator++() {
  this->value = this->value + 1;
  return *this;
}

Variable &Variable::operator--() {
  this->value = this->value - 1;
  return *this;
}

Variable &Variable::operator++(int) {
  this->value = 1 + this->value;
  return *this;
}

Variable &Variable::operator--(int) {
  this->value = this->value - 1;
  return *this;
}

Variable::~Variable() {

}
