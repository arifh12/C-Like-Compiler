%{
/* * * * * * * * * * * *
 * * * DEFINITIONS * * *
 * * * * * * * * * * * */
%}
%{
	
#include <string.h>
#include "ast.h"
#include "y.tab.h"

extern int line_num;
	
%}

%option noyywrap
DIGIT [0-9]
LETTER [a-zA-Z]

%x ERROR

%% 
%{
/* * * * * * * * * 
 * * * RULES * * *
 * * * * * * * * */
%}
print		{return PRINT;}
if      {return IF;}
else    {return ELSE;}
while   {return WHILE;}
input   {return INPUT;}

int     {return INT_TYPE;}
float   {return FLOAT_TYPE;}
char    {return CHAR_TYPE;}
bool    {return BOOL_TYPE;}
string  {return STRING_TYPE;}

"==" {return EQ;}
"!=" {return NE;}
">" {return GT;}
"<" {return LT;}
">=" {return GE;}
"<=" {return LE;}

"&&" {return AND;}
"||" {return OR;}
"!" {return NOT;}

\"(\\.|[^\\"])*\"       { yylval.var_name = strdup(yytext); return STRING; }
{DIGIT}+				{yylval.number = atof(yytext); return NUMBER;}
{LETTER}[0-9a-zA-Z]*	{yylval.var_name = strdup(yytext); return ID;}
[ \t\f\r]				;

\n	{line_num++;}
"-" {return MINUS;}
"+"	{return PLUS;}
"*"	{return TIMES;}
"/"	{return DIVIDE;}
"("	{return LPAREN;}
")"	{return RPAREN;}
"{"	{return LBRACE;}
"}"	{return RBRACE;}
"=" {return EQUALS;}
";" {return SEMICOLON;}

. { BEGIN(ERROR); yymore(); }
<ERROR>[^{DIGIT}{LETTER}+\-/*(){}= \t\n\f\r] { yymore(); }
<ERROR>(.|\n) { yyless(yyleng-1); printf("error token: %s on line %d\n", yytext, line_num); 
           BEGIN(INITIAL); }

%%

