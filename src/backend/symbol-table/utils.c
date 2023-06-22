#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_VMS 5

Symbols * initS(){
    Symbols * ret = malloc(sizeof(Symbols));
    ret->vms = malloc(MAX_VMS*sizeof(vmInfo));
    ret->toAdd = calloc(1, sizeof(vmInfo));
    return ret;
}

//si ya existia la vm con ese nombre devuelve 1
int pushVm(Symbols * s, char * varName){
    if (s->qty+1>MAX_VMS || exists(s, varName)){
        return 1;
    }
    s->toAdd->varName = malloc((strlen(varName)+1)*sizeof(char));
    strcpy(s->toAdd->varName, varName);
    s->vms[s->qty++] = s->toAdd;
    s->toAdd = calloc(1, sizeof(vmInfo));
    return 0;
}

int exists(Symbols * s, char * varName){
    for (int i=0;i<s->qty;i++){
        if (strcmp(s->vms[i]->varName, varName) == 0){
            return 1;
        }
    }
    return 0;
}

//devuelve 1 si ya tenia ram asignada
int setRam(Symbols * s, int ram){
    printf("Estoy seteando la RAM, %d\n", ram);
    if (s->toAdd->ram!=0){
        return 1;
    }
    s->toAdd->ram = ram;
    return 0;
}

int setDisk(Symbols * s, int disk){
    printf("Estoy seteando el DISK, %d\n", disk);
    if (s->toAdd->disk!=0){
        return 1;
    }
    s->toAdd->disk = disk;
    return 0;
}

int setCores(Symbols * s, int cores){
    printf("Estoy seteando los CORES, %d\n", cores);
    if (s->toAdd->cores!=0){
        return 1;
    }
    s->toAdd->cores = cores;
    return 0;
}

int setVirtualName(Symbols * s, char* virtualName){
    if (s->toAdd->virtualName!=NULL){
        return 1;
    }
    s->toAdd->virtualName = malloc((strlen(virtualName)+1)*sizeof(char));
    strcpy(s->toAdd->virtualName, virtualName);
    return 0;
}

int setIsoPath(Symbols * s, char* isoPath){
    if (s->toAdd->isoPath!=NULL){
        return 1;
    }
    s->toAdd->isoPath = malloc((strlen(isoPath)+1)*sizeof(char));
    strcpy(s->toAdd->isoPath, isoPath);
    return 0;
}


int getRam(Symbols * s, char * varName){
    for (int i=0; i<s->qty; i++){
        vmInfo * currVm = s->vms[i];
        if (!strcmp(currVm->varName, varName) && currVm->ram!=0){
            return currVm->ram;
        }
    }
    return -1;
}

int getCores(Symbols * s, char * varName){
    for (int i=0; i<s->qty; i++){
        vmInfo * currVm = s->vms[i];
        if (!strcmp(currVm->varName, varName) && currVm->cores!=0){
            return currVm->cores;
        }
    }
    return -1;
}

int getDisk(Symbols * s, char * varName){
    for (int i=0; i<s->qty; i++){
        vmInfo * currVm = s->vms[i];
        if (!strcmp(currVm->varName, varName) && currVm->disk!=0){
            return currVm->disk;
        }
    }
    return -1;
}

static int toKb(int number, Unit * unit){
    if(unit == NULL)
        return number;
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

int solve(Expression * expression){
    int num1, num2, res;
    if(expression->expressionType == WITHOPERATOR){
        num1 = toKb(expression->variable1->number, expression->variable1->unit);
        num2 = toKb(expression->variable2->number, expression->variable2->unit);
        switch (expression->operator->operatorType)
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
    }
    else if(expression->expressionType == WITHOUTOPERATOR){
        res = toKb(expression->variable1->number, expression->variable1->unit);
    }
	return res;
}


