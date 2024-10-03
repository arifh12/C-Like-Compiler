%{
  
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "ast.h"

using namespace std;

extern FILE *yyin;

stmt_node *root;

int line_num = 1;

int yylex();
void yyerror(const char* s);

%}

%start program

%union {
  float number;
  char *var_name;
  exp_node *exp_node_ptr;
  stmt_node *stmt_node_ptr;
}

%error-verbose

%token <number> NUMBER
%token <var_name> ID
%token <var_name> STRING
%token SEMICOLON EQUALS PRINT PLUS MINUS TIMES DIVIDE LPAREN RPAREN LBRACE RBRACE 
%token IF ELSE WHILE GT LT GE LE EQ NE AND OR NOT INPUT INT_TYPE FLOAT_TYPE CHAR_TYPE BOOL_TYPE STRING_TYPE
%type <exp_node_ptr> exp
%type <exp_node_ptr> mulexp
%type <exp_node_ptr> primexp
%type <exp_node_ptr> logicand
%type <exp_node_ptr> logicor
%type <exp_node_ptr> logicnot
%type <exp_node_ptr> relexp
%type <stmt_node_ptr> stmtlist
%type <stmt_node_ptr> stmt
%type <stmt_node_ptr> program


%%

program: stmtlist {root = $$;}
;

stmtlist: stmtlist SEMICOLON stmt {$$ = new sequence_node($1,$3);}
        | stmtlist SEMICOLON error {$$ = $1; yyclearin;}
        | stmt {$$ = $1;}
;

stmt: INT_TYPE ID {$$ = new declare_node($2,"int");}
    | FLOAT_TYPE ID {$$ = new declare_node($2,"float");}
    | CHAR_TYPE ID {$$ = new declare_node($2,"char");}
    | BOOL_TYPE ID {$$ = new declare_node($2,"bool");}
    | STRING_TYPE ID {$$ = new declare_node($2,"string");}
    | ID EQUALS exp {$$ = new assign_node($1,$3);}
    | PRINT exp {$$ = new print_node($2);}
    | IF LPAREN exp RPAREN stmt ELSE stmt {$$ = new if_node($3, $5, $7);}
    | IF LPAREN exp RPAREN stmt {$$ = new if_node($3, $5, nullptr);}
    | WHILE LPAREN exp RPAREN stmt {$$ = new while_node($3, $5);}
    | {$$ = new skip_node();}
    | LBRACE stmtlist RBRACE {$$ = $2;}
    | INPUT ID {$$ = new input_node($2);}
;

exp: exp PLUS mulexp {$$ = new add_node($1,$3);}
   | exp MINUS mulexp {$$ = new subtract_node($1,$3);}
   | mulexp {$$ = $1;}
   | logicor {$$ = $1;}
;

mulexp: mulexp TIMES primexp {$$ = new multiply_node($1,$3);}
      | mulexp DIVIDE primexp {$$ = new divide_node($1,$3);}
      | primexp {$$ = $1;}
;

primexp: MINUS primexp {$$ = new neg_node($2);}
       | LPAREN exp RPAREN {$$ = $2;}
       | NUMBER {$$ = new number_node($1);}
       | STRING { $$ = new string_node($1); }
       | ID {$$ = new variable_node($1);}
;

logicor: logicor OR logicand {$$ = new or_node($1, $3);}
       | logicand {$$ = $1;}

logicand: logicand AND logicnot {$$ = new and_node($1, $3);}
        | logicnot {$$ = $1;}

logicnot: NOT logicnot {$$ = new not_node($2);}
        | relexp {$$ = $1;}

relexp: exp GT exp {$$ = new gt_node($1,$3);}
      | exp LT exp {$$ = new lt_node($1,$3);}
      | exp GE exp {$$ = new ge_node($1,$3);}
      | exp LE exp {$$ = new le_node($1,$3);}
      | exp EQ exp {$$ = new eq_node($1,$3);}
      | exp NE exp {$$ = new ne_node($1,$3);}
;

%%

int main(int argc, char **argv) {
  if(argc > 1) yyin = fopen(argv[1], "r");

  yyparse();

  cout << "---------- list of input program------------" << endl << endl;
  root -> print();
  cout << "---------- execution of input program------------" << endl << endl;

  root->evaluate();
}

void yyerror(const char * s) {
  fprintf(stderr, "line %d: %s\n", line_num, s);
}