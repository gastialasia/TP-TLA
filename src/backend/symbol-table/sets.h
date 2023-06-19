#ifndef SETS_H
#define SETS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define COMPONENT_QTY 4

/*typedef enum{
  CORES,
  RAM,
  DISK,
  ISOSO
} component;
*/

struct vm{
  unsigned flags[COMPONENT_QTY];
  unsigned cores;
  unsigned ram;
  unsigned disk;
  char *isoso;
  char *vmName;
  char *varName;
};

// define the Set data structure
typedef struct {
  struct vm**vms;    // pointer to dynamically allocated array of the set members
  int length;      // the number of members of the set
} Set;

Set* init();
bool is_empty(Set *set);
void insert(Set *set, char* member);
void print_set(Set *set);
bool is_member(Set *set, char* value);
void destroy_set(Set* set);

#endif