%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	InnerExp innerExp;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int expression;
	int innerExp;
	int constant2;
	int integer;
	int biostype;
	int nettype;
	int netExp;
	int resource;
	int operator;
	int variable;

	// Terminales.
	token token;
	int str;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS

%token <variable> STRING
%token <variable> INTEGER

%token <integer> CREATE
%token <resource> NAME CORES RAM DISK ISO BIOS GB SO
%token <biostype> UEFI LEGACY
%token <integer> NET TYPE MAC
%token <nettype> NAT BRIDGE MACVTOP
%token <operator> ADD SUB MUL

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <innerExp> innerExp
%type <constant2> constant2
%type <biostype> biostype
%type <netExp> netExp
%type <nettype> nettype
%type <resource> soresource
%type <resource> resources
%type <resource> resource
%type <operator> operator
%type <variable> variable

// Reglas de asociatividad y precedencia (de menor a mayor).

// El símbolo inicial de la gramatica.
%start program

%%

program: constant2 expression													{ $$ = ProgramGrammarAction($2); }
	;

expression: CREATE OPEN_BRACKETS innerExp CLOSE_BRACKETS						{ $$ = InnerExpressionGrammarAction($3); }
	;

innerExp: NAME constant2 resources soresource resources						{ $$ = NameGrammarAction($2); }	
	|	NAME constant2 soresource resources									{ $$ = NameGrammarAction($2); }	
	|	NAME constant2 resources soresource									{ $$ = NameGrammarAction($2); }	
	|	NAME constant2 soresource											{ $$ = NameGrammarAction($2); }	
	;	

constant2: STRING													{ $$ = StringConstantGrammarAction($1); }
	;

netExp: OPEN_BRACKETS TYPE nettype MAC constant2 CLOSE_BRACKETS				{ $$ = StringConstantGrammarAction($3); }
	;

biostype: UEFI | LEGACY															{ $$ = StringConstantGrammarAction($1); }
	;

nettype: NAT | BRIDGE | MACVTOP															{ $$ = StringConstantGrammarAction($1); }
	;

resources: resource resources | resource										{ $$ = StringConstantGrammarAction($1); }
	;

soresource: SO constant2 | ISO constant2										{ $$ = StringConstantGrammarAction($1); }
	;

resource: CORES variable | RAM variable GB | DISK variable GB | BIOS biostype | NET netExp	{ $$ = StringConstantGrammarAction($1); }
	;

operator: ADD | MUL | SUB															{ $$ = StringConstantGrammarAction($1); }
	;

variable: INTEGER | INTEGER operator INTEGER | STRING | STRING operator INTEGER | INTEGER operator STRING	{ $$ = StringConstantGrammarAction($1); }
	;

%%
