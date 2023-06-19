#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../semantic-analysis/abstract-syntax-tree.h"

void Generator(int result);

void generateVmUnion(VmUnion * vmUnion);

void generateVmType (VmType * vmType);

void generateResources(Resources * resources);

void generateResource(Resource * resource);

void generateComponent(Component * component, Expression * expression);

void generateExpression(Expression * expression);

void generateVariable (Variable * variable);

void generateUnitNumber(int number, Unit * unit);

int generateUnit(int number, Unit * unit);

void generateCores(Expression * expression);

void generateBios(BiosType * biosType);

void generateNetExp(NetExp * netExp);

void generateNetType(NetType * netType, char * macAddr);

void generateResult(Variable* variable1, Operator* Operator, Variable* variable2);

void generateName(char * vmName);

void generateRam(Expression * expression);

void generateSo(SoResource * soResource);

void generateDisk(Expression * expression);

#endif
