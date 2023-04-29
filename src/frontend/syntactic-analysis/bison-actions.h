#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../../backend/semantic-analysis/abstract-syntax-tree.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
int ProgramGrammarAction(const char* value);

// Expresión.
char* FactorExpressionGrammarAction(const char* value);

// Factores.
char* ExpressionFactorGrammarAction(const char* value);
char* ConstantFactorGrammarAction(const char* value);

// Constantes.
char* StringConstantGrammarAction(const char* value);

char* InnerExpressionGrammarAction(const char* value);

char* NameGrammarAction(const char* value);

#endif
