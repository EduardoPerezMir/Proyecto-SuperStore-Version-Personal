#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include "constantesYRegistros.h"
#include "mostrarElementosSistema.h"
#include "../TDAs/trie.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/bplustree.h"

// Mostrar productos por nombre
void busquedaProductosDirecta(HashMap* mapa);

// Mostrar productos por precio
void busquedaPorPrecio(BPlusTree* arbolP);

void busquedaProductosPorNombreParcial(HashMap* mapa, trieTree* trie);

// Mostrar proudctos por supermercado y categoria
void busquedaProductosAdyacentes(HashMap* mapa, int indicador);

#endif