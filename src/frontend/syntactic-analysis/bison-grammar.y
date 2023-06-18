%{

#include "bison-actions.h"

%}

// Tipos de dato utilizados en las variables semánticas ($$, $1, $2, etc.).
%union {
	// No-terminales (backend).
	Program * program;
	VmUnion * vmunion;
	VmType * vmtype;
	Resources * resources;
	Resource * resource;
	NetExp * netexp;
	BiosType * biostype;
	NetType * nettype;
	SoResource * soresource;
	Operator * operator;
	Expression * expression;
	Variable * variable;
	Unit * unit;
	Component * component;

	// Terminales.
	token token;
	char* str;
	int integer;
}

// IDs y tipos de los tokens terminales generados desde Flex.
%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS

%token <str> STRING
%token <integer> INTEGER

%token <token> CREATE
%token <token> VM
%token <token> NAME CORES RAM DISK ISO BIOS SO
%token <token> TB GB MB KB
%token <token> UEFI LEGACY
%token <token> NET TYPE MAC
%token <token> NAT BRIDGE MACVTAP
%token <token> ADD SUB MUL
%token <token> DOT

// Tipos de dato para los no-terminales generados desde Bison.
%type <program> program
%type <vmunion> vmunion;
%type <vmtype> vmtype;
%type <resources> resources;
%type <resource> resource;
%type <netexp> netexp;
%type <biostype> biostype;
%type <nettype> nettype;
%type <soresource> soresource;
%type <operator> operator;
%type <expression> expression;
%type <variable> variable;
%type <unit> unit;
%type <component> component;

// Reglas de asociatividad y precedencia (de menor a mayor).

// El símbolo inicial de la gramatica.
%start program

%%

program: vmunion 					 											{ $$ = ProgramGrammarAction($1); }
	;

vmunion: vmtype  																{ $$ = SingleVmGrammarAction($1); }
	| vmtype vmunion															{ $$ = MultipleVmsGrammarAction($1, $2); }
	;

vmtype:STRING CREATE VM OPEN_BRACKETS resources CLOSE_BRACKETS					{ $$ = VmTypeGrammarAction($1, $5); }
	;

resources: resource																{ $$ = SingleResourcesGrammarAction($1); }
	| resource resources														{ $$ = MultipleResourcesGrammarAction($1, $2); }
	;

resource: component expression 													{ $$ = ComponentConfigGrammarAction($1, $2); }
	| BIOS biostype 															{ $$ = BiosConfigGrammarAction($2); }
	| NET netexp 																{ $$ = NetConfigGrammarAction($2); }
	| NAME STRING 																{ $$ = NameStringGrammarAction($2); }
	| soresource																{ $$ = SoConfigGrammarAction($1); }
	;

netexp: OPEN_BRACKETS TYPE nettype MAC STRING CLOSE_BRACKETS					{ $$ = NetExpGrammarAction($3, $5); }
	;

biostype: UEFI 																	{ $$ = UefiSystemGrammarAction(); }
	| LEGACY																	{ $$ = LegacySystemGrammarAction(); }
	;

nettype: NAT 																	{ $$ = NatConfigGrammarAction(); }
	| BRIDGE 																	{ $$ = BridgeConfigGrammarAction(); }
	| MACVTAP																	{ $$ = MacvtapConfigGrammarAction(); }
	;

soresource: SO STRING 															{ $$ = SoNameGrammarAction($2); }
	| ISO STRING																{ $$ = IsoPathGrammarAction($2); }
	;

operator: ADD 																	{ $$ = AdditionGrammarAction(); }
	| MUL 																		{ $$ = MultiplicationGrammarAction(); }
	| SUB																		{ $$ = SubstractionGrammarAction(); }
	;

expression: variable 															{ $$ = WithoutOperatorGrammarAction($1); }
	| variable operator variable												{ $$ = WithOperatorGrammarAction($1, $2, $3); }
	;

variable: INTEGER 																{ $$ = NumberGrammarAction($1); }
	| STRING DOT component 														{ $$ = ReferenceGrammarAction($1, $3); }
	| INTEGER unit 																{ $$ = UnitNumberGrammarAction($1, $2); }
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

