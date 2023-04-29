#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

/**
* Esta función se ejecuta cada vez que se emite un error de sintaxis.
*/
void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

/**
* Esta acción se corresponde con el no-terminal que representa el símbolo
* inicial de la gramática, y por ende, es el último en ser ejecutado, lo que
* indica que efectivamente el programa de entrada se pudo generar con esta
* gramática, o lo que es lo mismo, que el programa pertenece al lenguaje.
*/
int ProgramGrammarAction(const char* value) {
	LogDebug("\tProgramGrammarAction(%s)", value);
	/*
	* "state" es una variable global que almacena el estado del compilador,
	* cuyo campo "succeed" indica si la compilación fue o no exitosa, la cual
	* es utilizada en la función "main".
	*/
	state.succeed = true;
	/*
	* Por otro lado, "result" contiene el resultado de aplicar el análisis
	* sintáctico mediante Bison, y almacenar el nood raíz del AST construido
	* en esta variable. Para el ejemplo de la calculadora, no hay AST porque
	* la expresión se computa on-the-fly, y es la razón por la cual esta
	* variable es un simple entero, en lugar de un nodo.
	*/
	state.result = 0;
	return 0;
}

char* FactorExpressionGrammarAction(const char* value) {
	LogDebug("\tFactorExpressionGrammarAction(%s)", value);
	return strdup(value);
}

char* ExpressionFactorGrammarAction(const char* value) {
	LogDebug("\tExpressionFactorGrammarAction(%s)", value);
	return strdup(value);
}

char* ConstantFactorGrammarAction(const char* value) {
	LogDebug("\tConstantFactorGrammarAction(%s)", value);
	return strdup(value);
}

char* StringConstantGrammarAction(const char* value) {
	LogDebug("\tStringConstantGrammarAction(%s)", value);
	return strdup(value);
}