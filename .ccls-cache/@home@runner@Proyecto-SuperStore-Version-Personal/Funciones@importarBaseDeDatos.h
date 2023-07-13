#ifndef IMPORTAR_BASE_DE_DATOS_H
#define IMPORTAR_BASE_DE_DATOS_H

#include "../TDAs/bplustree.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/list.h"
#include "constantesYRegistros.h"

// Importacion base de datos

void importarDatosCSV(HashMap *mapaProductos, HashMap *mapaSupermercados,
                      HashMap *mapaCategorias, BPlusTree *arbolProductos);

void importarCredencialesAdmin(HashMap *mapaAdmin);

#endif
