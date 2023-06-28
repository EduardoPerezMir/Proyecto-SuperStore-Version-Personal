#ifndef IMPORTAR_BASE_DE_DATOS_H
#define IMPORTAR_BASE_DE_DATOS_H

#include "constantesYRegistros.h"
#include "../TDAs/list.h"
#include "../TDAs/hashmap.h"
#include "../TDAs/btree.h"

// Importacion base de datos

void importarDatosCSV(HashMap* mapaProductos, HashMap* mapaSupermercados, HashMap* mapaCategorias, BTree* arbolProductos);

void importarCredencialesAdmin (HashMap* mapaAdmin);

#endif
