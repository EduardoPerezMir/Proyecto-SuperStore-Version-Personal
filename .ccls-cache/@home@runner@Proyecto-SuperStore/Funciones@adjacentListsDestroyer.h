#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H


#include "constantesYRegistros.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/btree.h"

void destroyAllAdjacentListsProductos(HashMap* map);

void destroyAllAdjacentListsSupermercados(HashMap* map);

void destroyAllAdjacentListsCategorias(HashMap* map);

//void destroyAllAdjacentListsBTree(BTree* arbolB);

#endif