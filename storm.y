%{
#include <cstdio>
#include <iostream>
using namespace std;

// stuff from flex that bison needs to know about:
extern "C" int yylex();
extern "C" int yyparse();
extern "C" FILE *yyin;
extern int linenum;
 
void yyerror(const char *s);
%}

// Bison fundamentally works by asking flex to get the next token, which it
// returns as an object of type "yystype".  But tokens could be of any
// arbitrary data type!  So we deal with that in Bison by defining a C union
// holding each of the types of tokens that Flex could return, and have Bison
// use that union instead of "int" for the definition of "yystype":
%union {
  int ival;
  float fval;
  char *sval;
  char cval;
}

// define the "terminal symbol" token types I'm going to use (in CAPS
// by convention), and associate each with a field of the union:
%token<ival> C_INT
%token<fval> C_FLOAT
%token<sval> C_STRING
%token<cval> C_CHAR
%token<sval> ID
%token FUNCTION
%token T_INT
%token T_FLOAT
%token T_STRING
%token T_CHAR
%token T_VOID
%token FOR
%token WHILE
%token DO
%token IF
%token ELSE
%token CLASS

%%
// Sintactic variables
program:
  | var_declr program
  | function program
  | class_declr program;
var_declr:
  type var_declr_a ';';
var_declr_a:
  var_arr
  | var_declr_a ',' var_arr;
var_arr:
  ID 
  | ID '[' C_INT ']';
function:
  FUNCTION return_type ID '(' parameters ')' block;
parameters:
  parameter
  | parameters ',' parameter;
parameter:
  type var_arr;
block:
  '{' statements '}';
statements:
  | statements statement;
statement:
  var_declr
  | expr ';'
  | for_stm
  | while_stm
  | do_while_stm
  | if_stm;
for_stm:
  FOR '(' assign ';' expr ';' assign ')' block;
while_stm:
  WHILE '(' expr ')' block;
do_while_stm:
  DO block WHILE '(' expr ')' ';'
if_stm:
  IF '(' expr ')' block else_stm;
else_stm:
  | ELSE block;
return_type:
  T_VOID | type;
type:
  T_INT | T_FLOAT | T_STRING | T_CHAR | ID;
class_declr:
  CLASS ID '{' class_declr_a '}';
class_declr_a:
  | var_declr class_declr_a
  | function class_declr_a;
expr:
  assign
  | fn_call
  | obj_fn_call
  | operation
  | '(' expr ')'
  | literal
  | arr_access
  | ID { cout << yylval.sval << endl; };
assign:
  ID '=' expr;
operation:
  unary_operator expr
  | expr binary_operator expr;
unary_operator:
  '!';
binary_operator:
  '+' | '-' | '*' | '/' | '<' | '>';
fn_call:
  ID '(' arguments ')';
obj_fn_call:
  expr '.' fn_call;
arguments:
  | args;
args:
  expr
  | args ',' expr;
literal:
  C_INT | C_FLOAT | C_STRING | C_CHAR;
arr_access:
  ID '[' expr ']';

%%

int main(int, char**) {
  // Open a file to read the input from it
  string filename = "test\\test1.storm";
  FILE *myfile = fopen(filename.c_str(), "r");
  if (!myfile) {
    cout << "I can't open " << filename << "!" << endl;
    return -1;
  }
  // set flex to read from it instead of defaulting to STDIN:
  yyin = myfile;
  
  // parse through the input until there is no more:
  do {
    yyparse();
  } while (!feof(yyin));
  
}

void yyerror(const char *s) {
  // Print an error message along with the line number where it failed
  cout << "EEK, parse error on line " << linenum << "!  Message: " << s << endl;
  exit(-1);
}
