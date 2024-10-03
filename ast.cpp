#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>
#include "ast.h"

using namespace std;

// *** binaryOp_node ***
binaryOp_node::binaryOp_node(exp_node *L, exp_node *R)
  : left(L), right(R) {}

// *** number_node ***
number_node::number_node(float value)
  : num(value) {}

void number_node::print() {
  cout << num;
}

float number_node::evaluate() {
  return num;
}

// *** neg_node ***
neg_node::neg_node(exp_node *L)
  : exp(L) {}

void neg_node::print() {
  cout << "- ( ";
  exp->print();
  cout << " )";
}

float neg_node::evaluate() {
  float expValue = exp->evaluate();
  return -expValue;
}

// *** variable_node ***
variable_node::variable_node(string value)
  : id(value) {}

void variable_node::print() {
  cout << id;
}

float variable_node::evaluate() {
  return state[id];
}

// *** add_node ***
add_node::add_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void add_node::print() {
  cout << "(";
  left->print();
  cout << " + ";
  right->print();
  cout << ")";
}

float add_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num + right_num;
}

// *** subtract_node ***
subtract_node::subtract_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void subtract_node::print() {
  cout << "(";
  left->print();
  cout << " - ";
  right->print();
  cout << ")";
}

float subtract_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num - right_num;
}

// *** multiply_node ***
multiply_node::multiply_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void multiply_node::print() {
  cout << "(";
  left->print();
  cout << " * ";
  right->print();
  cout << ")";
}

float multiply_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num * right_num;
}

// *** divide_node ***
divide_node::divide_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void divide_node::print() {
  cout << "(";
  left->print();
  cout << " / ";
  right->print();
  cout << ")";
}

float divide_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();

  if (right_num) {
    return left_num / right_num;
  } else {
    cout << "division by zero -> " << left_num << " / " << 0 << endl;
    exit(1);
  }
}

// *** assign_node ***
assign_node::assign_node(string name, exp_node *expression)
  : id(name), exp(expression) {}

void assign_node::print() {
  cout << id << " = ";
  exp->print();
}

void assign_node::evaluate() {
  float result = exp->evaluate();
  state[id] = result;
}

// *** declare_node ***
declare_node::declare_node(string name, string type)
  : id(name), type(type) {}

void declare_node::print() {
  cout << type + " " + id;
}

void declare_node::evaluate() {
  state[id] = 0;
}

// *** print_node ***
print_node::print_node(exp_node *myexp)
  : exp(myexp) {}

void print_node::print() {
  cout << "print ";
  exp->print();
}

void print_node::evaluate() {
  cout << "output: " << exp->evaluate() << endl << endl;
}

// *** skip_node ***
skip_node::skip_node() {}

void skip_node::evaluate() {}
void skip_node::print() {}

// *** sequence_node ***
sequence_node::sequence_node(stmt_node *mystmt1, stmt_node *mystmt2)
  : stmt1(mystmt1), stmt2(mystmt2) {}

void sequence_node::print() {
  stmt1->print();
  cout << " ;" << endl;
  stmt2->print();
}

void sequence_node::evaluate() {
  stmt1->evaluate();
  stmt2->evaluate();
}

// *** if_node ***
if_node::if_node(exp_node *condition, stmt_node *then_stmt, stmt_node *else_stmt)
  : condition(condition), then_stmt(then_stmt), else_stmt(else_stmt) {}

void if_node::print() {
  cout << "if (";
  condition->print();
  cout << ") {" << endl;
  then_stmt->print();

  if (else_stmt) {
    cout << "} else {" << endl;
    else_stmt->print();
  }

  cout << "}" << endl;
}

void if_node::evaluate() {
  if (condition->evaluate()) {
    then_stmt->evaluate();
  } else {
    else_stmt->evaluate();
  }
}

// *** while_node ***
while_node::while_node(exp_node *condition, stmt_node *do_stmt)
  : condition(condition), do_stmt(do_stmt) {}

void while_node::print() {
  cout << "while (";
  condition->print();
  cout << ") {" << endl;
  do_stmt->print();
  cout << "}" << endl;
}

void while_node::evaluate() {
  while (condition->evaluate()) {
    do_stmt->evaluate();
  }
}

// *** eq_node ***
eq_node::eq_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void eq_node::print() {
  left->print();
  cout << " == ";
  right->print();
}

float eq_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num == right_num;
}

// *** ne_node ***
ne_node::ne_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void ne_node::print() {
  left->print();
  cout << " != ";
  right->print();
}

float ne_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num != right_num;
}

// *** gt_node ***
gt_node::gt_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void gt_node::print() {
  left->print();
  cout << " > ";
  right->print();
}

float gt_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num > right_num;
}

// *** lt_node ***
lt_node::lt_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void lt_node::print() {
  left->print();
  cout << " < ";
  right->print();
}

float lt_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num < right_num;
}

// *** ge_node ***
ge_node::ge_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void ge_node::print() {
  left->print();
  cout << " >= ";
  right->print();
}

float ge_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num >= right_num;
}

// *** le_node ***
le_node::le_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void le_node::print() {
  left->print();
  cout << " <= ";
  right->print();
}

float le_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num <= right_num;
}

// *** or_node ***
or_node::or_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void or_node::print() {
  cout << " (";
  left->print();
  cout << ") || (";
  right->print();
  cout << ") ";
}

float or_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num || right_num;
}

// *** and_node ***
and_node::and_node(exp_node *L, exp_node *R)
  : binaryOp_node(L, R) {}

void and_node::print() {
  cout << " (";
  left->print();
  cout << ") && (";
  right->print();
  cout << ") ";
}

float and_node::evaluate() {
  float left_num = left->evaluate();
  float right_num = right->evaluate();
  return left_num && right_num;
}

// *** not_node ***
not_node::not_node(exp_node *exp)
  : exp(exp) {}

void not_node::print() {
  cout << " !(";
  exp->print();
  cout << ") ";
}

float not_node::evaluate() {
  float val = exp->evaluate();
  return !val;
}

// *** input_node ***
input_node::input_node(string id)
  : id(id) {}

void input_node::print() {
  cout << "input for " << id;
}

void input_node::evaluate() {
  float val;
  cout << "input value for " << id << ": ";
  cin >> val;
  state[id] = val;
}

// *** string_node ***
string_node::string_node(string val)
  : val(val) {}

void string_node::print() {
  cout << val;
}

float string_node::evaluate() {
  print(); cout << "\n";
  return 0;
}

map<string, float> state;