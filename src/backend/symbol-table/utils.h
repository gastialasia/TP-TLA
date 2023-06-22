#ifndef UTILS_H
#define UTILS_H

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
};

typedef struct symbols Symbols;

Symbols * initS();

int addVm(Symbols * s, char * vmName);

int pushVm(Symbols * s, char * vmName);

int exists(Symbols * s, char * varName);

int setRam(Symbols * s, int ram);

int getRam(Symbols * s, char * varName);

#endif