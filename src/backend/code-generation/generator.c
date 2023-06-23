#include "../support/logger.h"
#include "generator.h"
#include "../support/shared.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/**
 * Implementación de "generator.h".
 */
FILE * file;
static int counter = 1;
static char path[50];

void Generator(int result) {
	//LogInfo("El resultado de la expresion computada es: '%d'.", result);
	Program * p = state.program;
	generateVmUnion(p->vmUnion);
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
	sprintf(path, "./output/config%d.xml", counter);
	
	file = fopen(path, "w+");
	if (file==NULL){
		printf("Error en la creación de archivo. Asegurarse tener la carpeta output en la raíz del proyecto.\n");
		return;
	}

	fprintf(file, "\n<domain type=\"kvm\">\n");
	generateResources(vmType->resources);
	addDefaultResources(state.symbols->vms[counter-1]);
	addExtras(state.symbols->vms[counter-1]);
	fprintf(file, "</domain>\n\n");

	fclose(file);
	counter++;
}

static void generateRandomMACAddress(char* macAddress) {
    srand(time(NULL)); // Seed the random number generator with the current time

    // Generate six random hexadecimal numbers for the MAC address
    for (int i = 0; i < 6; i++) {
        int randomNum = (rand() + counter)% 256; // Generate a random number between 0 and 255
        sprintf(macAddress + (i * 3), "%02X:", randomNum); // Format the random number as a two-digit hexadecimal and store it in the MAC address string
    }

    macAddress[17] = '\0'; // Null-terminate the MAC address string
}

void addExtras(vmInfo* vmInfo){
	char mac[30];
	generateRandomMACAddress(mac);
	fprintf(file, EXTRAS);
	fprintf(file, DISCO, getenv("PWD"), counter, mac,vmInfo->isoPath);
}

void addDefaultResources(vmInfo* vmInfo){
	if(!vmInfo->cores)
		fprintf(file, "<vcpu>2</vcpu>\n");
	if(!vmInfo->disk)
		vmInfo->disk = 15728640; //esta en KB
	//	fprintf(file, "<disk>15728640</disk>\n");//default 15GB
	if(!vmInfo->ram)
		fprintf(file, "<memory>2097152</memory>\n<currentMemory>2097152</currentMemory>\n");//default 2GB
	if(!vmInfo->net){
		char macaddress[20];
		generateRandomMACAddress(macaddress);
		fprintf(file, "<interface type=\"network\">\n<source network=\"default\"/>\n<mac address=\"%s\"/>\n<model type=\"virtio\"/>\n</interface>\n", macaddress);//default 2GB	
	}
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
		//generateSo(resource->soResource);
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
		//generateDisk(expression);
		break;
	default:
		break;
	}
}

void generateExpression(Expression * expression, ComponentType type){
	switch (expression->expressionType)
	{
	case WITHOUTOPERATOR:
		generateVariable(expression->variable1, type);
		break;
	case WITHOPERATOR:
		generateResult(expression->variable1, expression->operator, expression->variable2);
	default:
		break;
	}
}

void generateResult(Variable* variable1, Operator* Operator, Variable* variable2){
	int num1 = generateUnit(variable1->number, variable1->unit);
	int num2 = generateUnit(variable2->number, variable2->unit);
	int res;
	switch (Operator->operatorType)
	{
	case ADDITION:
		res = num1+num2;
		break;
	case MULTIPLICATION:
		res = num1*num2;
		break;
	case SUBSTRACTION:
		res = num1-num2;
		res *= res<0?-1:1;
		break;
	default:
		break;
	}
	fprintf(file, "%d", res);
}

void generateVariable(Variable * variable, ComponentType type){
	switch (variable->variableType)
	{
	case NUMBER:
		fprintf(file, "%d", variable->number);
		break;
	case REFERENCE:
		//Me traigo la referencia de la Tabla
		switch (type)
		{
		case RAMNUMBER:
			fprintf(file, "%d", getRam(state.symbols, variable->varName));
			break;
		case DISKNUMBER:
			//fprintf(file, "%d", getDisk(state.symbols, variable->varName));
			break;
		case CORESNUMBER:
			fprintf(file, "%d", getCores(state.symbols, variable->varName));
			break;
		default:
			break;
		}
		break;
	case UNITNUMBER:
		generateUnitNumber(variable->number, variable->unit);
		break;
	default:
		break;
	}
}

void generateUnitNumber(int number, Unit * unit){
	fprintf(file, "%d", generateUnit(number, unit));
}

int generateUnit(int number, Unit * unit){
	if (unit==NULL){
		return number;
	}
	int multiplicator;
	switch (unit->unitType)
	{
	case TERAB:
		multiplicator = 1024*1024*1024;
		break;
	case GIGAB:
		multiplicator = 1024*1024;
		break;
	case MEGAB:
		multiplicator = 1024;
		break;
	case KILOB:
		multiplicator = 1;
		break;
	default:
		break;
	}
	return number*multiplicator;
}

void generateCores(Expression * expression){
	fprintf(file, "<vcpu>");
	generateExpression(expression, CORESNUMBER);
	fprintf(file, "</vcpu>\n");
}

void generateRam(Expression * expression){
	fprintf(file, "<memory>");
	generateExpression(expression, RAMNUMBER);
	fprintf(file, "</memory>\n");
	fprintf(file, "<currentMemory>");
	generateExpression(expression, RAMNUMBER);
	fprintf(file, "</currentMemory>\n");
}

void generateDisk(Expression * expression){
	fprintf(file, "<disk>");
	generateExpression(expression, DISKNUMBER);
	fprintf(file, "</disk>\n");
}

void generateBios(BiosType * biosType){
	switch (biosType->biosTypeType)
	{
	case UEFISYSTEM:
		fprintf(file, "UEFI\n");
		break;
	case LEGACYSYSTEM:
		fprintf(file, "legacy\n");
		break;
	default:
		break;
	}
}

void generateNetExp(NetExp * netExp){
	fprintf(file, "<interface type=\"network\">\n");
	generateNetType(netExp->netType, netExp->macAddr);
	fprintf(file, "<model type=\"virtio\"/>\n");
	fprintf(file, "</interface>\n");
}

void generateNetType(NetType * netType, char * macAddr){
	fprintf(file, "<mac address=\"%s\"/>\n", macAddr+1);
	switch (netType->netTypeType)
	{
	case NATCONFIG:
		fprintf(file, "<source network=\"default\"/>\n");
		break;
	case BRIDGECONFIG:
		fprintf(file, "<source bridge=\"default\"/>\n");
		break;
	case MACVTAPCONFIG:
		fprintf(file, "<source dev=\"default\"/>\n");
		break;
	default:
		break;
	}
}

void generateName(char * vmName){
	fprintf(file, "<name>%s</name>\n", vmName);
}

void generateSo(SoResource * soResource){
	switch(soResource->soResourceType){
		case SONAME:
			fprintf(file, "ACa procesamos el SONAME\n");
		case ISOPATH:
			fprintf(file, "<disk type=\"file\" device=\"cdrom\">\n<driver name=\"qemu\" type=\"raw\"/>\n<source file=\"%s\"/>\n<target dev=\"sda\" bus=\"sata\"/>\n<readonly/>\n", soResource->isoPath);
	}
}
