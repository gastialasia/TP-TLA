%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Contextos de Flex. */
%x COMMENT

/* Patrones reutilizables. */
letter          [a-zA-Z]
endline			[\n]
whitespace		[ \f\n\r\t\v]
digit			[0-9]


%%

"/*"										{ BEGIN(COMMENT); BeginCommentPatternAction(); }
<COMMENT>.									{ ; }
<COMMENT>{endline}							{ ; }
<COMMENT>"*/"								{ EndCommentPatternAction(); BEGIN(INITIAL); }

"{"											{ return OpenBracketPatternAction(yytext); }
"}"											{ return CloseBracketPatternAction(yytext); }

"create vm"                                 { return CREATE; }
"name"                                      { return NAME; }
"cores"                                     { return CORES; }
"ram"                                       { return RAM; }
"disk"                                      { return DISK; }
"iso"                                       { return ISO; }
"bios"                                      { return BIOS; }

"G"                                         { return GB; }

{letter}+									{ return LetterPatternAction(yytext, yyleng); }

{digit}+									{ return IntegerPatternAction(yytext, yyleng); }

{whitespace}								{ IgnoredPatternAction(yytext, yyleng); }

.											{ return UnknownPatternAction(yytext, yyleng); }

%%
