#ifndef SETS_H
#define SETS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// define the Set data structure
typedef struct {
  char**members;    // pointer to dynamically allocated array of the set members
  int length;      // the number of members of the set
} Set;

Set* init();
bool is_empty(Set *set);
void insert(Set *set, char* member);
void print_set(Set *set);
bool is_member(Set *set, char* value);
void destroy_set(Set* set);

#endif