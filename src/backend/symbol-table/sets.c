/*******************************************************************************
*
* Program: Set Data Structure
* 
* Description: Example of a set data structure and operations (union, subset,
* intersection, etc.) implemented in C.  See the Wikipedia article on Sets:
* https://en.wikipedia.org/wiki/Set_(mathematics)
*
* YouTube Lesson: https://www.youtube.com/watch?v=RVqdK6WAjUI
*
* Author: Kevin Browne @ https://portfoliocourses.com
*
*******************************************************************************/

#include "sets.h"

// returns a pointer to a new Set allocated on the heap
Set* init()
{
  // allocate space for the set
  Set *new_set = malloc(sizeof(Set));
  
  // initially the set will be empty with no members, so set length to 0
  new_set->length = 0;

  // allocate enough space to store 1 member, we'll expand this as needed
  new_set->members = malloc(sizeof(char*));

  // return the new Set (or more specifically, a pointer to it)
  return new_set;
}

// returns true if the Set is empty, and false otherwise
bool is_empty(Set *set)
{
  return (set->length == 0);
}

// returns true if value is a member of set, and false otherwise
bool is_member(Set *set, char* value)
{
  // if we can find the value in the set's members, it is in the set
  for (int i = 0; i < set->length; i++)
    if (strcmp(set->members[i], value) == 0) return true;
  
  // if after checking all the set's members we can't find the value, it is 
  // not a member of the set
  return false;
}

// pasar un puntero con memoria ya alocada
// inserts the member value into the set (if it is not already in the set!)
void insert(Set *set, char* member)
{
  // check to make the member value is not in the set already
  if (!is_member(set, member))
  {
    // allocate space to store the *new* amount of members in the set 
    set->members = realloc(set->members, sizeof(char*) * (set->length + 1));

    // put the member into the set at the next available index
    set->members[set->length] = member;

    // increment the set length to acknowledge the new length of the set
    set->length = set->length + 1;
  }
}

// prints out the set
void print_set(Set *set)
{
  // loop through the array of set values, print each of them out separated by 
  // a comma, except the last element - instead output a newline afterwards
  for (int i = 0; i < set->length; i++)
    printf("%s,", set->members[i]);
  putchar('\n');
}

void destroy_set(Set* set){
  for (int i = 0; i < set->length; i++)
    free(set->members[i]);
  free(set);
}