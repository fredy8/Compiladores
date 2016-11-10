%{
#include <cstring>
#include <iostream>
#include "storm.tab.h"
using namespace std;
#define YY_DECL extern "C" int yylex()
int linenum = 1;
%}
%option noyywrap

%%

[ \t]             ;
\n                { linenum++; }
function          { return FUNCTION; }
int               { yylval.sval = strdup(yytext); return T_INT; }
float             { yylval.sval = strdup(yytext); return T_FLOAT; }
string            { yylval.sval = strdup(yytext); return T_STRING; }
char              { yylval.sval = strdup(yytext); return T_CHAR; }
void              { yylval.sval = strdup(yytext); return T_VOID; }
for               { return FOR; }
while             { return WHILE; }
do                { return DO; }
if                { return IF; }
else              { return ELSE; }
return            { return RETURN; }
class             { return CLASS; }
-?[0-9]+\.[0-9]+    { yylval.fval = atof(yytext); return C_FLOAT; }
-?[0-9]+            { yylval.ival = atoi(yytext); return C_INT; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.sval = strdup(yytext); return ID; }
\*|\/|%           { yylval.sval = strdup(yytext); return BIN_OP_P1; }
\+|\-             { yylval.sval = strdup(yytext); return BIN_OP_P2; }
\<|\<=|\>=|\>     { yylval.sval = strdup(yytext); return BIN_OP_P3; }
==|!=             { yylval.sval = strdup(yytext); return BIN_OP_P4; }
&&                { yylval.sval = strdup(yytext); return BIN_OP_P5; }
\|\|              { yylval.sval = strdup(yytext); return BIN_OP_P6; }
!                 { yylval.sval = strdup(yytext); return UN_OP_P0; }
[;,:\{\}=\(\)\.\[\]]    { return yytext[0]; }
\'[ a-zA-Z0-0(\\n)\.,]\'           { yylval.cval = yytext[1]; return C_CHAR; }
\"[ a-zA-Z0-9(\\n)\.,]+\" { yylval.sval = strdup(yytext); return C_STRING; }

%%
