#ifndef HashMap_h
#define HashMap_h

#include <stdbool.h>

#include "stack.h"
#include "arraylist.h"

typedef struct HashMap HashMap;

typedef struct Pair {
     char * key; 
     void * value; 
} Pair;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair * searchMap(HashMap * table, char * key);

Pair * firstMap(HashMap * table);

Pair * nextMap(HashMap * table);

void enlarge(HashMap * map);

bool areProductPresents(HashMap * map);

long sizeMap(HashMap * map);


#endif /* HashMap_h */