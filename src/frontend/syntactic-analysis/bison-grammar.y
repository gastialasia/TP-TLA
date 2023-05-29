%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	block block;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	int vmStructure;
	int block;
	int text;
	int integer;
	int biostype;
	int nettype;
	int netExp;
	int resource;
	int operator;
	int expression;
	int vmtype;

	// Terminales.
	token token;
	int str;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS

%token <integer> STRING
%token <integer> INTEGER

%token <integer> CREATE
%token <integer> VM
%token <integer> NAME CORES RAM DISK ISO BIOS SO
%token <integer> TB GB MB KB
%token <integer> UEFI LEGACY
%token <integer> NET TYPE MAC
%token <integer> NAT BRIDGE MACVTAP
%token <integer> ADD SUB MUL
%token <integer> DOT

// Tipos de dato para los no-terminales generados desde Bison.
%type <integer> program
%type <integer> vmStructure
%type <integer> block
%type <integer> text
%type <integer> biostype
%type <integer> netExp
%type <integer> nettype
%type <integer> soresource
%type <integer> resources
%type <integer> resource
%type <integer> operator
%type <integer> expression

%type <integer> reference
%type <integer> vmtype
%type <integer> vmunion
%type <integer> variable
%type <integer> component
%type <integer> unit

// Reglas de asociatividad y precedencia (de menor a mayor).

// El símbolo inicial de la gramatica.
%start program

%%

program: vmunion 					 											{ $$ = ProgramGrammarAction($1); }
	;

vmunion: vmtype vmunion | vmtype												{ $$ = StringConstantGrammarAction($1); }
	;

vmtype: text vmStructure													{ $$ = StringConstantGrammarAction($1); }
	;

vmStructure: CREATE VM OPEN_BRACKETS block CLOSE_BRACKETS						{ $$ = StringConstantGrammarAction($3); }
	;

block: resources														{ $$ = NameGrammarAction($1); }	
	;	

text: STRING													{ $$ = StringConstantGrammarAction($1); }
	;

netExp: OPEN_BRACKETS TYPE nettype MAC text CLOSE_BRACKETS				{ $$ = StringConstantGrammarAction($3); }
	;

biostype: UEFI | LEGACY															{ $$ = StringConstantGrammarAction($1); }
	;

nettype: NAT | BRIDGE | MACVTAP															{ $$ = StringConstantGrammarAction($1); }
	;

resources: resource resources | resource										{ $$ = StringConstantGrammarAction($1); }
	;

soresource: SO text | ISO text										{ $$ = StringConstantGrammarAction($1); }
	;

resource: component expression | BIOS biostype | NET netExp | NAME text | soresource	{ $$ = StringConstantGrammarAction($1); }
	;

operator: ADD | MUL | SUB															{ $$ = StringConstantGrammarAction($1); }
	;

expression: variable | variable operator variable										{ $$ = StringConstantGrammarAction($1); }
	;

variable: INTEGER | reference | INTEGER unit 												{ $$ = StringConstantGrammarAction($1); }
	;

unit: TB | GB | MB | KB															{ $$ = StringConstantGrammarAction($1); }
	;

reference: STRING DOT component													{ $$ = StringConstantGrammarAction($1); }
	;

component: CORES | RAM | DISK														{ $$ = StringConstantGrammarAction($1); }
	;

%%
