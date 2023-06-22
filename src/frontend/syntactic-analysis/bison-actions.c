#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "../../backend/symbol-table/sets.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_MSG(text) 

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

void redeclarationError(char * res){
	char error[50];
	sprintf(error, "Error: %s redeclarado.\n", res);
	yyerror(error);
	state.succeed = false;
	abort();
}

void undefinedReferenceError(char * var, char * res){
	char error[50];
	sprintf(error, "Error: referencia indefinida para %s en %s.\n", res, var);
	yyerror(error);
	state.succeed = false;
	abort();
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

VmType * VmTypeGrammarAction(char * varName, Resources * resources) {
	if(pushVm(state.symbols, varName)){
		redeclarationError("VM");
	}
	printf("Estoy en nueva vm\n\n");
	VmType * newNode = malloc(sizeof(VmType));
	newNode->resources=resources;
	newNode->varName = malloc((strlen(varName)+1)*sizeof(char));
	strcpy(newNode->varName, varName);
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

Resource * ComponentConfigGrammarAction(Component * component, Expression * expression){
	int aux;
	switch (component->componentType)
	{
	case RAMNUMBER:
		aux = solve(expression);
		if(aux != 0 && setRam(state.symbols, aux)){
			redeclarationError("RAM");
		}
		break;
	case DISKNUMBER:
		aux = solve(expression);
		if(aux != 0 && setDisk(state.symbols, aux)){
			redeclarationError("disk");
		};
		break;
	case CORESNUMBER:
		aux = solve(expression);
		if(aux != 0 && setCores(state.symbols, aux)){
			redeclarationError("cores");
		};
		break;
	default:
		break;
	}
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

Resource * NameStringGrammarAction(char * vmName){
	if(setVirtualName(state.symbols, vmName)){
		redeclarationError("name");
	}
	Resource * newNode = malloc(sizeof(Resource));
	newNode->resourceType = NAMESTRING;
	newNode->component = NULL;
	newNode->expression = NULL;
	newNode->biosType = NULL;
	newNode->netExp = NULL;
	newNode->soResource = NULL;
	newNode->vmName = malloc((strlen(vmName)+1)*sizeof(char));
	strcpy(newNode->vmName, vmName);
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

NetExp * NetExpGrammarAction(NetType * netType, char * macAddr){
	NetExp * newNode = malloc(sizeof(NetExp));
	newNode->netType=netType;
	newNode->macAddr = malloc((strlen(macAddr)+1)*sizeof(char));
	strcpy(newNode->macAddr, macAddr);
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

SoResource * SoNameGrammarAction(char * soName){
	SoResource * newNode = malloc(sizeof(SoResource));
	newNode->soResourceType = SONAME;
	newNode->soName = malloc((strlen(soName)+1)*sizeof(char));
	strcpy(newNode->soName, soName);
	return newNode;
}

SoResource * IsoPathGrammarAction(char * isoPath){
	if(setIsoPath(state.symbols, isoPath)){
		redeclarationError("iso");
	}
	SoResource * newNode = malloc(sizeof(SoResource));
	newNode->soResourceType = ISOPATH;
	newNode->isoPath = malloc((strlen(isoPath)+1)*sizeof(char));
	strcpy(newNode->isoPath, isoPath);
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

Variable * NumberGrammarAction(int number){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->variableType = NUMBER;
	newNode->component = NULL;
	newNode->unit = NULL;
	newNode->number = number;
	return newNode;
}

Variable * ReferenceGrammarAction(char * varName, Component * component){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->component = component;

	Unit * unit = malloc(sizeof(Unit));

	switch (component->componentType)
	{
	case RAMNUMBER:
		int ram = getRam(state.symbols, varName);
		if (ram==0){
			undefinedReferenceError("ram", varName);
		}
		//setRam(state.symbols, ram);
		newNode->variableType = UNITNUMBER;
		unit->unitType = KILOB;
		newNode->unit = unit;
		newNode->number = ram;
		break;
	case DISKNUMBER:
		int disk = getDisk(state.symbols, varName);
		if (disk==0){
			undefinedReferenceError("disk", varName);
		}
		//setDisk(state.symbols, disk);
		newNode->variableType = UNITNUMBER;
		unit->unitType = KILOB;
		newNode->unit = unit;
		newNode->number = disk;
		break;
	case CORESNUMBER:
		int cores = getCores(state.symbols, varName);
		if (cores==0){
			undefinedReferenceError("cores", varName);
		}
		//setCores(state.symbols, cores);
		newNode->variableType = NUMBER;
		unit->unitType = KILOB;
		newNode->unit = unit;
		newNode->number = cores;
		break;
	default:
		break;
	}
	newNode->varName = malloc((strlen(varName)+1)*sizeof(char));
	strcpy(newNode->varName, varName);
	return newNode;
}

Variable * UnitNumberGrammarAction(int number, Unit * unit){
	Variable * newNode = malloc(sizeof(Variable));
	newNode->variableType = UNITNUMBER;
	newNode->component = NULL;
	newNode->number = number;
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
























