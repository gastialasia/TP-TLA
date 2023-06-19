#include "../support/logger.h"
#include "generator.h"
#include "../support/shared.h"

/**
 * Implementación de "generator.h".
 */

void Generator(int result) {
	//LogInfo("El resultado de la expresion computada es: '%d'.", result);
	Program * p = state.program;
	printf("<domain type=\"kvm\">");
	generateVmUnion(p->vmUnion);
	printf("</domain>");
}

void generateVmUnion(VmUnion * vmUnion){
	switch (vmUnion->vmUnionType)
	{
	case SINGLEVM:
		generateVmType(vmUnion->vmType);
		break;
	case MULTIPLEVMS:
		generateVmType(vmUnion->vmType);
		generateVmUnion(vmUnion->vmUnion);
		break;
	default:
		break;
	}
}

void generateVmType (VmType * vmType){
	//printf(vmType->varName);
	generateResources(vmType->resources);
}

void generateResources(Resources * resources){
	switch (resources->resourcesType)
	{
	case SINGLERESOURCES:
		generateResource(resources->resource);
		break;
	case MULTIPLERESOURCES:
		generateResource(resources->resource);
		generateResources(resources->resources);
		break;
	default:
		break;
	}
}

void generateResource(Resource * resource){
	switch (resource->resourceType)
	{
	case COMPONENTCONFIG:
		generateComponent(resource->component, resource->expression);
		break;
	case BIOSCONFIG:
		generateBios(resource->biosType);
		break;
	case NETCONFIG:
		generateNetExp(resource->netExp);
		break;
	case NAMESTRING:
		generateName(resource->vmName);
		break;
	case SOCONFIG:
		generateSo(resource->soResource);
		break;
	default:
		break;
	}
}

void generateComponent(Component * component, Expression * expression){
	switch (component->componentType)
	{
	case CORESNUMBER:
		generateCores(expression);
		break;
	case RAMNUMBER:
		generateRam(expression);
		break;
	case DISKNUMBER:
		generateDisk(expression);
		break;
	default:
		break;
	}
}

void generateExpression(Expression * expression){
	switch (expression->expressionType)
	{
	case WITHOUTOPERATOR:
		generateVariable(expression->variable1);
		break;
	case WITHOPERATOR:
		generateResult(expression->variable1, expression->operator, expression->variable2);
	default:
		break;
	}
}

void generateVariable (Variable * variable){
	switch (variable->variableType)
	{
	case NUMBER:
		printf("%d", variable->number);
		break;
	case REFERENCE:
		printf("%s", variable->varName);
		break;
	case UNITNUMBER:
		generateUnitNumber(variable->number, variable->unit);
		break;
	default:
		break;
	}
}

void generateUnitNumber(int number, Unit * unit){
	printf("%d", number);
	generateUnit(unit);
}

void generateUnit(Unit * unit){
	switch (unit->unitType)
	{
	case TERAB:
		printf("TB");
		break;
	case GIGAB:
		printf("GB");
		break;
	case MEGAB:
		printf("MB");
		break;
	case KILOB:
		printf("KB");
		break;
	default:
		break;
	}
}

void generateCores(Expression * expression){
	printf("<vcpu>");
	generateExpression(expression);
	printf("<vcpu/>");
}

void generateBios(BiosType * biosType){
	switch (biosType->biosTypeType)
	{
	case UEFISYSTEM:
		printf("UEFI");
		break;
	case LEGACYSYSTEM:
		printf("legacy");
		break;
	default:
		break;
	}
}

void generateNetExp(NetExp * netExp){
	/*
	<interface type="network">
    <source network="default"/>
    <mac address="52:54:00:bb:09:42"/>
    <model type="virtio"/>
  </interface>
	*/
	printf("<interface type=\"network\">");
	generateNetType(netExp->netType, netExp->macAddr);
	printf("<model type=\"virtio\"/>");
	printf("</interface>");
}

void generateNetType(NetType * netType, char * macAddr){
	printf("mac address=\"%s\"/", macAddr);
	switch (netType->netTypeType)
	{
	case NATCONFIG:
		printf("<source network=\"default\"/>");
		break;
	case BRIDGECONFIG:
		printf("<source bridge=\"default\"/>");
		break;
	case MACVTAPCONFIG:
		printf("<source dev=\"default\"/>");
		break;
	default:
		break;
	}
}

void generateName(char * vmName){
	printf("<name>%s</name>", vmName);
}

void generateSo(SoResource * soResource){

}
