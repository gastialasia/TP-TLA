#ifndef SETS_H
#define SETS_H

typedef struct Set* setADT;

Set* init();
bool is_empty(Set *set);
void insert(Set *set, char* member);
void print_set(Set *set);
bool is_member(Set *set, char* value);
void destroy_set(Set* set);

#endif