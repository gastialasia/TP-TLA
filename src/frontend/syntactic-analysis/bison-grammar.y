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
%type <integer> biostype
%type <integer> netExp
%type <integer> nettype
%type <integer> soresource
%type <integer> resources
%type <integer> resource
%type <integer> operator
%type <integer> expression

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

vmunion: vmtype  																{ $$ = SingleVmGrammarAction($1); }
	| vmtype vmunion															{ $$ = MultipleVmsGrammarAction($1, $2); }
	;

vmtype: STRING CREATE VM OPEN_BRACKETS resources CLOSE_BRACKETS					{ $$ = VmTypeGrammarAction($5); }
	;

resources: resource																{ $$ = SingleResourcesGrammarAction($1); }
	| resource resources														{ $$ = MultipleResourcesGrammarAction($1, $2); }
	;

resource: component expression 													{ $$ = ComponentExpGrammarAction($1, $2); }
	| BIOS biostype 															{ $$ = BiosExpGrammarAction($2); }
	| NET netExp 																{ $$ = NetExpGrammarAction($2); }
	| NAME STRING 																{ $$ = NameStringGrammarAction(); }
	| soresource																{ $$ = SoExpGrammarAction($1); }
	;

netExp: OPEN_BRACKETS TYPE nettype MAC STRING CLOSE_BRACKETS					{ $$ = NetExpGrammarAction($3); }
	;

biostype: UEFI 																	{ $$ = UefiSystemGrammarAction(); }
	| LEGACY																	{ $$ = LegacySystemGrammarAction(); }
	;

nettype: NAT 																	{ $$ = NatConfigGrammarAction(); }
	| BRIDGE 																	{ $$ = BridgeConfigGrammarAction(); }
	| MACVTAP																	{ $$ = MacvtapConfigGrammarAction(); }
	;

soresource: SO STRING 															{ $$ = SoNameGrammarAction(); }
	| ISO STRING																{ $$ = IsoPathGrammarAction(); }
	;

operator: ADD 																	{ $$ = AdditionGrammarAction(); }
	| MUL 																		{ $$ = MultiplicationGrammarAction(); }
	| SUB																		{ $$ = SubstractionGrammarAction(); }
	;

expression: variable 															{ $$ = WithoutOperatorGrammarAction($1); }
	| variable operator variable												{ $$ = WithOperatorGrammarAction($1, $2, $3); }
	;

variable: INTEGER 																{ $$ = NumberGrammarAction(); }
	| STRING DOT component 														{ $$ = ReferenceGrammarAction($3); }
	| INTEGER unit 																{ $$ = UnitNumberGrammarAction($2); }
	;

unit: TB 																		{ $$ = TerabGrammarAction(); }
	| GB 																		{ $$ = GigabGrammarAction(); }
	| MB 																		{ $$ = MegabGrammarAction(); }
	| KB																		{ $$ = KilobGrammarAction(); }
	;

component: CORES 																{ $$ = CoresNumberGrammarAction(); }
	| RAM 																		{ $$ = RamNumberGrammarAction(); }
	| DISK																		{ $$ = DiskNumberGrammarAction(); }
	;

%%

