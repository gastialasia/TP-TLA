#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>
#include <string.h>

/**
 * Implementación de "flex-actions.h".
 *
 * Cada función debe realizar 2 operaciones básicas para lograr el streaming
 * de tokens hacia Bison:
 *
 *	1) Computar los atributos del token y almacenarlos donde sea conveniente
 *		(en la tabla de símbolos, en "yylval", o en ambos).
 *	2) Retornar el token que identifica el terminal identificado.
 *
 * Bison utilizará el token retornado en el punto (2) para matchear dicho
 * terminal en la gramática. Por otro lado, el valor almacenado en "yylval" es
 * el que Bison proveerá como valor semántico al realizar una reducción
 * (mediante $1, $2, $3, etc.).
 */

void BeginCommentPatternAction() {
	LogDebug("BeginCommentPatternAction.");
}

void EndCommentPatternAction() {
	LogDebug("EndCommentPatternAction.");
}

token OpenBracketPatternAction(const char * lexeme) {
	LogDebug("OpenBracketPatternAction: '%s'.", lexeme);
	yylval.token = OPEN_BRACKETS;
	return OPEN_BRACKETS;
}

token CloseBracketPatternAction(const char * lexeme) {
	LogDebug("CloseBracketPatternAction: '%s'.", lexeme);
	yylval.token = CLOSE_BRACKETS;
	return CLOSE_BRACKETS;
}

token CreatePatternAction(const char * lexeme) {
	LogDebug("CreatePatternAction: '%s' (length = %d).", lexeme);
	yylval.token = CREATE;
	return CREATE;
}

token NamePatternAction(const char * lexeme) {
	LogDebug("NamePatternAction: '%s' (length = %d).", lexeme);
	yylval.token = NAME;
	return NAME;
}

token CoresPatternAction(const char * lexeme) {
	LogDebug("CoresPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = CORES;
	return CORES;
}

token RamPatternAction(const char * lexeme) {
	LogDebug("RamPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = RAM;
	return RAM;
}

token DiskPatternAction(const char * lexeme) {
	LogDebug("DiskPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = DISK;
	return DISK;
}

token IsoPatternAction(const char * lexeme) {
	LogDebug("IsoPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = ISO;
	return ISO;
}

token BiosPatternAction(const char * lexeme) {
	LogDebug("BiosPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = BIOS;
	return BIOS;
}

token GbPatternAction(const char * lexeme) {
	LogDebug("GbPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = GB;
	return GB;
}

token UEFIPatternAction(const char * lexeme) {
	LogDebug("UEFIPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = UEFI;
	return UEFI;
}

token legacyPatternAction(const char * lexeme) {
	LogDebug("LegacyPatternAction: '%s' (length = %d).", lexeme);
	yylval.token = LEGACY;
	return LEGACY;
}

token LetterPatternAction(const char * lexeme, const int length) {
	LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = STRING;
	return STRING;
}

token IntegerPatternAction(const char * lexeme, const int length) {
	LogDebug("IntegerPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.integer = atoi(lexeme);
	return INTEGER;
}

token UnknownPatternAction(const char * lexeme, const int length) {
	LogDebug("UnknownPatternAction: '%s' (length = %d).", lexeme, length);
	yylval.token = YYUNDEF;
	// Al emitir este token, el compilador aborta la ejecución.
	return YYUNDEF;
}

void IgnoredPatternAction(const char * lexeme, const int length) {
	LogDebug("IgnoredPatternAction: '%s' (length = %d).", lexeme, length);
	// Como no debe hacer nada con el patrón, solo se loguea en consola.
}
