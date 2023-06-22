#ifndef UTILS_H
#define UTILS_H

#include "../semantic-analysis/abstract-syntax-tree.h"

typedef struct {
    char * varName;
    char * virtualName;
    int cores;
    int ram;
    int disk;
    char * isoPath;
}vmInfo;

struct symbols {
    vmInfo ** vms;
    int qty;
    vmInfo * toAdd;
    int partialRes;
};

typedef struct symbols Symbols;

Symbols * initS();

int pushVm(Symbols * s, char * varName);

int exists(Symbols * s, char * varName);

int setRam(Symbols * s, int ram);

int setDisk(Symbols * s, int disk);

int setCores(Symbols * s, int cores);

int setVirtualName(Symbols * s, char* virtualName);

int setIsoPath(Symbols * s, char* isoPath);

int getRam(Symbols * s, char * varName);

int getDisk(Symbols * s, char * varName);

int getCores(Symbols * s, char * varName);

int solve(Expression * expression);


#endif