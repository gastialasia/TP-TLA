%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	/*
	Program program;
	Expression expression;
	Factor factor;
	Constant constant;
	...
	*/

	// No-terminales (frontend).
	int program;
	char* expression;
	char* factor;
	char* constant2;


	// Terminales.
	token token;
	char* str;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS

%token <str> STRING

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <expression> expression
%type <factor> factor
%type <constant2> constant2

// Reglas de asociatividad y precedencia (de menor a mayor).


// El símbolo inicial de la gramatica.
%start program

%%

program: expression													{ $$ = ProgramGrammarAction($1); }
	;

expression: constant2														{ $$ = StringConstantGrammarAction($1); }
	| factor
	;

factor: OPEN_BRACKETS constant2 CLOSE_BRACKETS								{ $$ = ExpressionFactorGrammarAction($2); }
	| OPEN_BRACKETS constant2 constant2 CLOSE_BRACKETS						{ $$ = ExpressionFactorGrammarAction($2); }
	;

constant2: STRING													{ $$ = StringConstantGrammarAction($1); }
	;

%%
