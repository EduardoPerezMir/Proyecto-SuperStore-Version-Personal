#ifndef OPCIONES_CANASTA_H
#define OPCIONES_CANASTA_H

#include "constantesYRegistros.h"
#include "mostrarMenus.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"

tipoCanasta* searchListCanasta(List* canasta, char* producto, char* supermercado);

void armarCanasta(List* canasta, HashMap* mapaProductos, HashMap* mapaSupermercado);

void eliminarProduCanasta(List* canasta);

void agregarProduCanasta(HashMap* mapaProductos,HashMap* mapaSupermercados,List* canasta);

void printListPC(List* Super); // Muestra los productos de la canasta

#endif