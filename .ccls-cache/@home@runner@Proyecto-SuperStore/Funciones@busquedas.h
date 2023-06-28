#ifndef BUSQUEDAS_H
#define BUSQUEDAS_H

#include "constantesYRegistros.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/btree.h"
#include "mostrarElementosSistema.h"

//Mostrar productos por nombre
void busquedaProductosDirecta(HashMap* mapa);

// Mostrar productos por precio
void busquedaPorPrecio(BTree* arbolP);

// Mostrar proudctos por supermercado y categoria
void busquedaProductosAdyacentes(HashMap* mapa, int indicador);

#endif