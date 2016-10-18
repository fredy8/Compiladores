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
int               { return T_INT; }
float             { return T_FLOAT; }
string            { return T_STRING; }
char              { return T_CHAR; }
void              { return T_VOID; }
for               { return FOR; }
while             { return WHILE; }
do                { return DO; }
if                { return IF; }
else              { return ELSE; }
return            { return RETURN; }
class             { return CLASS; }
[0-9]+\.[0-9]+    { yylval.fval = atof(yytext); return C_FLOAT; }
[0-9]+            { yylval.ival = atoi(yytext); return C_INT; }
[a-zA-Z_][a-zA-Z0-9_]*      { yylval.sval = strdup(yytext); return ID; }
!                 { yylval.ival = atoi(yytext); return UN_OP; }
\<=|>=|&&|==|\|\||\+|\-|\*|\/|\<|\<|\%        { yylval.sval = strdup(yytext); return BIN_OP; }
[;,:\{\}=\(\)\.\[\]]    { return yytext[0]; }
\'[0-9]\'           { yylval.cval = yytext[1]; return C_CHAR; }
\"[ a-zA-Z0-9]+\" { yylval.sval = strdup(yytext); return C_STRING; }

%%
