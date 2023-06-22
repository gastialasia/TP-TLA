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

int pushVm(Symbols * s, char * vmName){
    if (s->qty+1>MAX_VMS || exists(s, vmName)){
        return -1;
    }
    s->vms[s->qty++] = s->toAdd;
    s->toAdd = calloc(1, sizeof(vmInfo));
    return 0;
}

int exists(Symbols * s, char * varName){
    for (int i=0;i<s->qty;i++){
        if (!strcmp(s->vms[i]->varName, varName)){
            return 1;
        }
    }
    return 0;
}

int setRam(Symbols * s, int ram){
    if (s->toAdd->ram!=0){
        return -1;
    }
    s->toAdd->ram = ram;
}


int getRam(Symbols * s, char * varName){
    for (int i=0; i<s->qty; i++){
        vmInfo * currVm = s->vms[i];
        if (!strcmp(currVm->varName, varName) && currVm->ram!=NULL){
            return currVm->ram;
        }
    }
}


