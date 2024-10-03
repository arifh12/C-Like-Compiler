#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include <list>

using namespace std;

// *** exp_node ***
class exp_node {
public:
  virtual void print() = 0;
  virtual float evaluate() = 0;
};

// *** binaryOp_node ***
class binaryOp_node : public exp_node {
public:
  exp_node *left;
  exp_node *right;

  binaryOp_node(exp_node *L, exp_node *R);
};

// *** number_node ***
class number_node : public exp_node {
private:
  float num;

public:
  number_node(float value);
  void print();
  float evaluate();
};

// *** neg_node ***
class neg_node : public exp_node {
protected:
  exp_node *exp;

public:
  neg_node(exp_node *exp);
  void print();
  float evaluate();
};

// *** variable_node ***
class variable_node : public exp_node {
protected:
  string id;

public:
  variable_node(string value);
  void print();
  float evaluate();
};

// *** add_node ***
class add_node : public binaryOp_node {
public:
  add_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** subtract_node ***
class subtract_node : public binaryOp_node {
public:
  subtract_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** multiply_node ***
class multiply_node : public binaryOp_node {
public:
  multiply_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** divide_node ***
class divide_node : public binaryOp_node {
public:
  divide_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** stmt_node ***
class stmt_node {
public:
  virtual void print() {}
  virtual void evaluate() = 0;
};

// *** assign_node ***
class assign_node : public stmt_node {
protected:
  string id;
  exp_node *exp;

public:
  assign_node(string name, exp_node *expression);
  void print();
  void evaluate();
};

// *** declare_node ***
class declare_node : public stmt_node {
protected:
  string id;
  string type;

public:
  declare_node(string name, string type);
  void print();
  void evaluate();
};

// *** print_node ***
class print_node : public stmt_node {
protected:
  exp_node *exp;

public:
  print_node(exp_node *myexp);
  void print();
  void evaluate();
};

// *** skip_node ***
class skip_node : public stmt_node {
public:
  skip_node();
  void print();
  void evaluate();
};

// *** sequence_node ***
class sequence_node : public stmt_node {
protected:
  stmt_node *stmt1, *stmt2;

public:
  sequence_node(stmt_node *mystmt1, stmt_node *mystmt2);
  void print();
  void evaluate();
};

// *** if_node ***
class if_node : public stmt_node {
protected:
  exp_node *condition;
  stmt_node *then_stmt, *else_stmt;

public:
  if_node(exp_node *condition, stmt_node *then_stmt, stmt_node *else_stmt);
  void print();
  void evaluate();
};

// *** while_node ***
class while_node : public stmt_node {
protected:
  exp_node *condition;
  stmt_node *do_stmt;

public:
  while_node(exp_node *condition, stmt_node *do_stmt);
  void print();
  void evaluate();
};

// *** eq_node ***
class eq_node : public binaryOp_node {
public:
  eq_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** ne_node ***
class ne_node : public binaryOp_node {
public:
  ne_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** gt_node ***
class gt_node : public binaryOp_node {
public:
  gt_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** lt_node ***
class lt_node : public binaryOp_node {
public:
  lt_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** ge_node ***
class ge_node : public binaryOp_node {
public:
  ge_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** le_node ***
class le_node : public binaryOp_node {
public:
  le_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** or_node ***
class or_node : public binaryOp_node {
public:
  or_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** and_node ***
class and_node : public binaryOp_node {
public:
  and_node(exp_node *L, exp_node *R);
  void print();
  float evaluate();
};

// *** not_node ***
class not_node : public exp_node {
protected:
  exp_node *exp;

public:
  not_node(exp_node *exp);
  void print();
  float evaluate();
};

// *** input_node ***
class input_node : public stmt_node {
protected:
  string id;

public:
  input_node(string id);
  void print();
  void evaluate();
};

// *** string_node ***
class string_node : public exp_node {
protected:
  string val;

public:
  string_node(string val);
  void print();
  float evaluate();
};

extern map<string, float> state;