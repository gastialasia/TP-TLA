#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
Program * ProgramGrammarAction(VmUnion * vmUnion) {

	//LogDebug("\tProgramGrammarAction(%s)", value);

	state.succeed = true;
	
	Program * newNode = malloc(sizeof(Program));
	newNode->vmUnion = vmUnion;
	state.program = newNode;
	return newNode;
}

VmUnion * SingleVmGrammarAction(VmType * vmType) {
	VmUnion * newNode = malloc(sizeof(VmUnion));
	newNode->vmUnionType = SINGLEVM;
	newNode->vmType = vmType;
	newNode->vmUnion = NULL;
	return newNode;
}

VmUnion * MultipleVmsGrammarAction(VmType * vmType, VmUnion * vmUnion) {
	VmUnion * newNode = malloc(sizeof(VmUnion));
	newNode->vmUnionType = MULTIPLEVMS;
	newNode->vmType = vmType;
	newNode->vmUnion = vmUnion;
	return newNode;
}

VmType * VmTypeGrammarAction(Resources * resources) {
	VmType * newNode = malloc(sizeof(VmType));
	newNode->resources=resources;
	return newNode;
}

Resources * SingleResourcesGrammarAction(Resource * resource) {
	Resources * newNode = malloc(sizeof(Resources));
	newNode->resourcesType = SINGLERESOURCES;
	newNode->resource=resource;
	newNode->resources=NULL;
	return newNode;
}

Resources * MultipleResourcesGrammarAction(Resource * resource, Resources * resources) {
	Resources * newNode = malloc(sizeof(Resources));
	newNode->resourcesType = MULTIPLERESOURCES;
	newNode->resource=resource;
	newNode->resources=resources;
	return newNode;
}

//-----

Resource * ComponentConfigGrammarAction(Component * component, Expression * expression){
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = COMPONENTCONFIG;
	newNode->component = component;
	newNode->expression = expression;
	newNode->biosType = NULL;
	newNode->netExp = NULL;
	newNode->soResource = NULL;
	return newNode;
}

Resource * BiosConfigGrammarAction(BiosType * biostype){
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = BIOSCONFIG;
	newNode->component = NULL;
	newNode->expression = NULL;
	newNode->biosType = biostype;
	newNode->netExp = NULL;
	newNode->soResource = NULL;
	return newNode;
}

Resource * NetConfigGrammarAction(NetExp * netExp){
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = NETCONFIG;
	newNode->component = NULL;
	newNode->expression = NULL;
	newNode->biosType = NULL;
	newNode->netExp = netExp;
	newNode->soResource = NULL;
	return newNode;
}

Resource * NameStringGrammarAction(){
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = NAMESTRING;
	newNode->component = NULL;
	newNode->expression = NULL;
	newNode->biosType = NULL;
	newNode->netExp = NULL;
	newNode->soResource = NULL;
	return newNode;
}

Resource * SoConfigGrammarAction(SoResource * soresource){
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = SOCONFIG;
	newNode->component = NULL;
	newNode->expression = NULL;
	newNode->biosType = NULL;
	newNode->netExp = NULL;
	newNode->soResource = soresource;
	return newNode;
}

//-----

NetExp * NetExpGrammarAction(NetType * netType){
	NetExp * newNode = malloc(sizeof(NetExp));
	newNode->netType=netType;
	return newNode;
}

BiosType * UefiSystemGrammarAction(){
	BiosType * newNode = malloc(sizeof(BiosType));
	newNode->biosTypeType = UEFISYSTEM;
	return newNode;
}

BiosType * LegacySystemGrammarAction(){
	BiosType * newNode = malloc(sizeof(BiosType));
	newNode->biosTypeType = LEGACYSYSTEM;
	return newNode;
}

NetType * NatConfigGrammarAction(){
	NetType * newNode = malloc(sizeof(NetType));
	newNode->netTypeType = NATCONFIG;
	return newNode;
}

NetType * BridgeConfigGrammarAction(){
	NetType * newNode = malloc(sizeof(NetType));
	newNode->netTypeType = BRIDGECONFIG;
	return newNode;
}

NetType * MacvtapConfigGrammarAction(){
	NetType * newNode = malloc(sizeof(NetType));
	newNode->netTypeType = MACVTAPCONFIG;
	return newNode;
}

SoResource * SoNameGrammarAction(){
	SoResource * newNode = malloc(sizeof(SoResource));
	newNode->soResourceType = SONAME;
	return newNode;
}

SoResource * IsoPathGrammarAction(){
	SoResource * newNode = malloc(sizeof(SoResource));
	newNode->soResourceType = ISOPATH;
	return newNode;
}

Operator * AdditionGrammarAction(){
	Operator * newNode = malloc(sizeof(Operator));
	newNode->operatorType = ADDITION;
	return newNode;
}

Operator * MultiplicationGrammarAction(){
	Operator * newNode = malloc(sizeof(Operator));
	newNode->operatorType = MULTIPLICATION;
	return newNode;
}

Operator * SubstractionGrammarAction(){
	Operator * newNode = malloc(sizeof(Operator));
	newNode->operatorType = SUBSTRACTION;
	return newNode;
}

Expression * WithoutOperatorGrammarAction(Variable * variable){
	Expression * newNode = malloc(sizeof(Expression));
	newNode->expressionType = WITHOUTOPERATOR;
	newNode->operator=NULL;
	newNode->variable1=variable;
	newNode->variable2=NULL;
	return newNode;
}

Expression * WithOperatorGrammarAction(Variable * variable1, Operator * operator, Variable * variable2){
	Expression * newNode = malloc(sizeof(Expression));
	newNode->expressionType = WITHOPERATOR;
	newNode->operator=operator;
	newNode->variable1=variable1;
	newNode->variable2=variable2;
	return newNode;
}

Variable * NumberGrammarAction(){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->variableType = NUMBER;
	newNode->component = NULL;
	newNode->unit = NULL;
	return newNode;
}

Variable * ReferenceGrammarAction(Component * component){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->variableType = REFERENCE;
	newNode->component = component;
	newNode->unit = NULL;
	return newNode;
}

Variable * UnitNumberGrammarAction(Unit * unit){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->variableType = UNITNUMBER;
	newNode->component = NULL;
	newNode->unit = unit;
	return newNode;
}

Unit * TerabGrammarAction(){
	Unit * newNode = malloc(sizeof(Unit));
	newNode->unitType = TERAB;
	return newNode;
}

Unit * GigabGrammarAction(){
	Unit * newNode = malloc(sizeof(Unit));
	newNode->unitType = GIGAB;
	return newNode;
}

Unit * MegabGrammarAction(){
	Unit * newNode = malloc(sizeof(Unit));
	newNode->unitType = MEGAB;
	return newNode;
}

Unit * KilobGrammarAction(){
	Unit * newNode = malloc(sizeof(Unit));
	newNode->unitType = KILOB;
	return newNode;
}

Component * CoresNumberGrammarAction(){
	Component * newNode = malloc(sizeof(Component));
	newNode->componentType = CORESNUMBER;
	return newNode;
}

Component * RamNumberGrammarAction(){
	Component * newNode = malloc(sizeof(Component));
	newNode->componentType = RAMNUMBER;
	return newNode;
}

Component * DiskNumberGrammarAction(){
	Component * newNode = malloc(sizeof(Component));
	newNode->componentType = DISKNUMBER;
	return newNode;
}

























