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
Program * ProgramGrammarAction(VmUnion * vmUnion);

VmUnion * SingleVmGrammarAction(VmType * vmType);

VmUnion * MultipleVmsGrammarAction(VmType * vmType, VmUnion * vmUnion);

VmType * VmTypeGrammarAction(Resources * resources);

Resources * SingleResourcesGrammarAction(Resource * resource);

Resources * MultipleResourcesGrammarAction(Resource * resource, Resources * resources);

Resource * ComponentConfigGrammarAction(Component * component, Expression * expression);

Resource * BiosConfigGrammarAction(BiosType * biostype);

Resource * NetConfigGrammarAction(NetExp * netExp);

Resource * NameStringGrammarAction();

Resource * SoConfigGrammarAction(SoResource * soresource);

NetExp * NetExpGrammarAction(NetType * netType);

BiosType * UefiSystemGrammarAction();

BiosType * LegacySystemGrammarAction();

NetType * NatConfigGrammarAction();

NetType * BridgeConfigGrammarAction();

NetType * MacvtapConfigGrammarAction();

SoResource * SoNameGrammarAction();

SoResource * IsoPathGrammarAction();

Operator * AdditionGrammarAction();

Operator * MultiplicationGrammarAction();

Operator * SubstractionGrammarAction();

Expression * WithoutOperatorGrammarAction(Variable * variable);

Expression * WithOperatorGrammarAction(Variable * variable1, Operator * operator, Variable * variable2);

Variable * NumberGrammarAction();

Variable * ReferenceGrammarAction(Component * component);

Variable * UnitNumberGrammarAction(Unit * unit);

Unit * TerabGrammarAction();

Unit * GigabGrammarAction();

Unit * MegabGrammarAction();

Unit * KilobGrammarAction();

Component * CoresNumberGrammarAction();

Component * RamNumberGrammarAction();

Component * DiskNumberGrammarAction();

#endif
