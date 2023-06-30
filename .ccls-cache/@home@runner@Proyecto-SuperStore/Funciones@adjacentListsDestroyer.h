#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include "constantesYRegistros.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/btree.h"

void destroyAllAdjacentListsProductos(HashMap* map); // Libera memoria de las listas de supermercados adyacentes al mapa de producto.

void destroyAllAdjacentListsSupermercados(HashMap* map); // Libera memoria de las listas de productos adyacentes al mapa de supermercados.

void destroyAllAdjacentListsCategorias(HashMap* map); // Libera memoria de las listas de productos adyacentes al mapa de categorías.

void destroyAllAdjacentListsBTree(BTreeNode* node); // Libera memoria de las listas de supermercados adyacentes al mapa ordenado de productos.

#endif